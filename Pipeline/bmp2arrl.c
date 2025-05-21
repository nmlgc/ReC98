
#if defined(REC98_PROJECT)
#include "platform.h" /* see also [https://github.com/nmlgc/ReC98/issues/8] */
#elif defined(_MSC_VER)/*Microsoft C++*/ || defined(__BORLANDC__) || defined(__TURBOC__)
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
#else
#include <stdint.h>
#endif
#if defined(_MSC_VER)/*Microsoft C++*/ || defined(__BORLANDC__) || defined(__TURBOC__)
# include <io.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <fcntl.h>

#if defined(__GNUC__)
#include <endian.h>
#else
#define le16toh(x) (x)
#define le32toh(x) (x)
#define htole16(x) (x)
#define htole32(x) (x)
#endif

#include "bmp2arrl.h"

/* O_BINARY is needed for MS-DOS, Windows, etc.
 * Linux, Mac OS X, etc. do not have O_BINARY */
#ifndef O_BINARY
#define O_BINARY (0)
#endif

static unsigned char bmp_tmp[(640 / 8) * 40]; /* exactly enough */

/*
    typedef struct tagBITMAPFILEHEADER {
        WORD  bfType;                                           +0
        DWORD bfSize;                                           +2
        WORD  bfReserved1;                                      +6
        WORD  bfReserved2;                                      +8
        DWORD bfOffBits;                                        +10
    } BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;=14

    typedef struct tagBITMAPINFOHEADER {
        DWORD biSize;                                           +0
        LONG  biWidth;                                          +4
        LONG  biHeight;                                         +8
        WORD  biPlanes;                                         +12
        WORD  biBitCount;                                       +14
        DWORD biCompression;                                    +16
        DWORD biSizeImage;                                      +20
        LONG  biXPelsPerMeter;                                  +24
        LONG  biYPelsPerMeter;                                  +28
        DWORD biClrUsed;                                        +32
        DWORD biClrImportant;                                   +36
    } BITMAPINFOHEADER, *PBITMAPINFOHEADER;                     =40
 */

/* error reporting */
static const char* BMP2ARR_PARAMETERLESS_ERRORS[BMP2ARR_ERROR_COUNT] = {
    /* SUCCESS                  */ "Success",
    /* INTERNAL_ERROR_ERROR     */ "bmp2arr_error structure used incorrectly",
    /* INTERNAL_NULLPTR         */ "Tried to dereference a null pointer",
    /* INTERNAL_ARRAY_TOO_SMALL */ "Internal array too small",

    /* EXPECTED_ARGUMENT        */ NULL,
    /* EXPECTED_SWITCH          */ NULL,

    /* MISSING_INPUT_BMP        */ "Input BMP file name required (-i)",
    /* MISSING_OUTPUT_FILE      */ "Output file name required (-o)",
    /* MISSING_OUTPUT_TYPE      */ "Output type required (-of)",
    /* MISSING_SPRITE_WIDTH     */ "Sprite width required (-sw)",
    /* MISSING_SPRITE_HEIGHT    */ "Sprite height required (-sh)",

    /* INVALID_SWITCH           */ NULL,
    /* INVALID_OUTPUT_TYPE      */ "Invalid output type; must be (asm | bin | bmp | c | cpp)",
    /* INVALID_PRESHIFT         */ "Invalid preshift type, must be (outer | inner)",
    /* INVALID_PRESHIFT_WIDTH   */ "Pre-shifting is only supported for 8-pixel wide sprites",
    /* INVALID_SPRITE_WIDTH     */ "Sprite width must be <=640",
    /* INVALID_SPRITE_HEIGHT    */ "Sprite height must be between 1 and 40",

    /* INPUT_OPEN_ERROR         */ NULL,
    /* INPUT_OUT_OF_MEMORY      */ "Not enough memory to read the input BMP",
    /* INPUT_INVALID            */ "Error reading input file (not a valid BMP?)",
    /* INPUT_TOO_SMALL          */ "Input BMP is too small to contain even a single sprite",
    /* INPUT_COLOR_AT           */ NULL,
    /* INPUT_ALREADY_LOADED     */ "Input BMP already loaded",

    /* OUTPUT_NO_INPUT_LOADED   */ "Input BMP needs to be loaded before saving the output file",
    /* OUTPUT_OPEN_ERROR        */ NULL,
    /* OUTPUT_IO_ERROR          */ "Error writing output file",
};

static enum bmp2arr_error nullptr_error(void) {
    fprintf(stderr,"%s\n", BMP2ARR_PARAMETERLESS_ERRORS[INTERNAL_NULLPTR]);
    return INTERNAL_NULLPTR;
}

enum bmp2arr_error bmp2arr_error_report(struct bmp2arr_error_info *err) {
    if (err == NULL) {
        return nullptr_error();
    }
    switch(err->type) {
    case EXPECTED_ARGUMENT:
        fprintf(stderr,"*** Error: Missing argument for '-%s'\n", err->param_str);
        break;
    case EXPECTED_SWITCH:
        fprintf(stderr,"*** Error: Expected a command-line switch at '%s'\n", err->param_str);
        break;
    case INVALID_SWITCH:
        fprintf(stderr,"*** Error: Invalid command-line switch: '%s'\n", err->param_str);
        break;
    case INPUT_OPEN_ERROR:
        fprintf(stderr,"*** Error: Failed to open input file: '%s'\n", err->param_str);
        break;
    case INPUT_COLOR_AT:
        fprintf(stderr,"*** Error: Found a non-#000/#FFF pixel at (%d, %d)\n", err->param_int[0], err->param_int[1]);
        break;
    case OUTPUT_OPEN_ERROR:
        fprintf(stderr,"*** Error: Failed to open output file: '%s'\n", err->param_str);
        break;
    default:
        fprintf(stderr,"*** Error: %s\n", BMP2ARR_PARAMETERLESS_ERRORS[err->type]);
        break;
    }
    return err->type;
}

/* error generation */
enum bmp2arr_error bmp2arr_error_set(struct rec98_bmp2arr_task *t, enum bmp2arr_error type) {
    if (t == NULL) {
        return nullptr_error();
    }
    t->err.type = type;
    if (BMP2ARR_PARAMETERLESS_ERRORS[type] == NULL)
        t->err.type = INTERNAL_ERROR_ERROR;

    t->err.param_str = NULL;
    t->err.param_int[0] = 0;
    t->err.param_int[1] = 0;
    return type;
}

enum bmp2arr_error bmp2arr_error_set_str(struct rec98_bmp2arr_task *t, enum bmp2arr_error type, const char *param) {
    if (t == NULL) {
        return nullptr_error();
    }
    t->err.type = type;
    if (BMP2ARR_PARAMETERLESS_ERRORS[type] != NULL)
        t->err.type = INTERNAL_ERROR_ERROR;

    t->err.param_str = param;
    t->err.param_int[0] = 0;
    t->err.param_int[1] = 0;
    return type;
}

enum bmp2arr_error bmp2arr_error_set_int_int(struct rec98_bmp2arr_task *t, enum bmp2arr_error type, int param_1, int param_2) {
    if (t == NULL) {
        return nullptr_error();
    }
    t->err.type = type;
    if (BMP2ARR_PARAMETERLESS_ERRORS[type] != NULL)
        t->err.type = INTERNAL_ERROR_ERROR;

    t->err.param_str = NULL;
    t->err.param_int[0] = param_1;
    t->err.param_int[1] = param_2;
    return type;
}

static int is_black_or_white(uint8_t r,uint8_t g,uint8_t b) {
    return (
        ((r == 0x00) && (g == 0x00) && (b == 0x00)) ||
        ((r == 0xFF) && (g == 0xFF) && (b == 0xFF))
    );
}

static void memcpyxor(unsigned char *dst,unsigned char *src,unsigned int bytes,unsigned char xorval) {
    while (bytes-- != 0)
        *dst++ = *src++ ^ xorval;
}

/* return -1 on success, or the position of a non-#000/#FFF pixel otherwise */
static int memcpy24to1(unsigned char *dst,unsigned char *src,unsigned int w) {
    unsigned int w_total = w;
    uint8_t r,g,b,tmp;
    unsigned int x;

    while (w >= 8) {
        tmp = 0;
        for (x=0;x < 8;x++) {
            b = *src++;
            g = *src++;
            r = *src++;
            if (is_black_or_white(r,g,b))
                tmp |= 0x80 >> x;
            else
                return ((w_total - w) + x);
        }

        *dst++ = tmp;
        w -= 8;
    }

    if (w > 0) {
        tmp = 0;
        for (x=0;x < w;x++) {
            b = *src++;
            g = *src++;
            r = *src++;
            if (is_black_or_white(r,g,b))
                tmp |= 0x80 >> x;
            else
                return ((w_total - w) + x);
        }

        *dst++ = tmp;
    }
    return -1;
}

static int memcpy32to1(unsigned char *dst,unsigned char *src,unsigned int w) {
    unsigned int w_total = w;
    uint8_t r,g,b,tmp;
    unsigned int x;

    while (w >= 8) {
        tmp = 0;
        for (x=0;x < 8;x++) {
            b = *src++;
            g = *src++;
            r = *src++;
                 src++; /* A */
            if (is_black_or_white(r,g,b))
                tmp |= 0x80 >> x;
            else
                return ((w_total - w) + x);
        }

        *dst++ = tmp;
        w -= 8;
    }

    if (w > 0) {
        tmp = 0;
        for (x=0;x < w;x++) {
            b = *src++;
            g = *src++;
            r = *src++;
                 src++; /* A */
            if (is_black_or_white(r,g,b))
                tmp |= 0x80 >> x;
            else
                return ((w_total - w) + x);
        }

        *dst++ = tmp;
    }
    return -1;
}

static void saveout_write_c_type(struct rec98_bmp2arr_task *t,struct saveout_ctx *sctx) {
    if (t->output_type == REC98_OUT_CPP)
        fprintf(sctx->fp,"const dot_rect_t(%d, %d) %s",sctx->bytesperrow * 8,t->sprite_height,t->output_symname != NULL ? t->output_symname : "untitled");
    else if (t->output_type == REC98_OUT_C)
        fprintf(sctx->fp,"const unsigned char %s",t->output_symname != NULL ? t->output_symname : "untitled");

    if (t->flags & PRESHIFT_OUTER)
        fprintf(sctx->fp,"[8/*PRESHIFT*/]");

    fprintf(sctx->fp,"[%d]",sctx->ssrows * sctx->sscols);

    if (t->flags & PRESHIFT_INNER)
        fprintf(sctx->fp,"[8/*PRESHIFT*/]");

    if (t->output_type == REC98_OUT_C)
	    fprintf(sctx->fp,"[%d/*%d bytes x %d rows*/]",sctx->bytesperrow * t->sprite_height,sctx->bytesperrow,t->sprite_height);
}

static int saveout_write_prologue(struct rec98_bmp2arr_task *t,struct saveout_ctx *sctx) {
    if (t->output_type == REC98_OUT_C || t->output_type == REC98_OUT_CPP) {
        fprintf(sctx->fp,"/* Generated by bmp2arr from %s, do not modify directly. */\n",t->input_bmp);
        fprintf(sctx->fp,"/* Sprite sheet: %d sprites (%d x %d) of %d x %d sprites. */\n",sctx->sscols * sctx->ssrows,sctx->sscols,sctx->ssrows,t->sprite_width,t->sprite_height);
        fprintf(sctx->fp,"\n");

        if (t->output_type == REC98_OUT_CPP)
            fprintf(sctx->fp,"#include \"planar.h\"\n\n");

        saveout_write_c_type(t,sctx);
        fprintf(sctx->fp," = {\n");
    }
    else if (t->output_type == REC98_OUT_ASM) {
        fprintf(sctx->fp,"; Generated by bmp2arr from %s, do not modify directly.\n",t->input_bmp);
        fprintf(sctx->fp,"; Sprite sheet: %d sprites (%d x %d) of %d x %d sprites.\n",sctx->sscols * sctx->ssrows,sctx->sscols,sctx->ssrows,t->sprite_width,t->sprite_height);
        fprintf(sctx->fp,"\n");

        fprintf(sctx->fp,"; ");
        saveout_write_c_type(t,sctx);
        fprintf(sctx->fp,";\n");

        fprintf(sctx->fp,"public %s\n",t->output_symname != NULL ? t->output_symname : "untitled");
        fprintf(sctx->fp,"label %s byte\n",t->output_symname != NULL ? t->output_symname : "untitled");
    }
    else if (t->output_type == REC98_OUT_BIN) {
        /* none needed */
    }
    else if (t->output_type == REC98_OUT_BMP) {
        const unsigned int balign = (sctx->bytesperrow + 3u) & (~3u);
        const unsigned int bitmap_size = t->sprite_height*sctx->ssrows*sctx->sscols*((t->flags&PRESHIFT_ANY)?8u:1u);

        /* BITMAPFILEHEADER */
        memcpy(bmp_tmp+0, "BM",2);
        *((uint32_t*)(bmp_tmp+2 )) = htole32(14+40+4*2+(balign*bitmap_size));  /* bfSize */
        *((uint16_t*)(bmp_tmp+6 )) = htole16(0);
        *((uint16_t*)(bmp_tmp+8 )) = htole16(0);
        *((uint32_t*)(bmp_tmp+10)) = htole32(14+40+4*2);                       /* bfOffBits */
        fwrite(bmp_tmp,14,1,sctx->fp);

        /* BITMAPINFOHEADER */
        *((uint32_t*)(bmp_tmp+0 )) = htole32(40);
        *((uint32_t*)(bmp_tmp+4 )) = htole32(sctx->bytesperrow*8u);
        *((uint32_t*)(bmp_tmp+8 )) = htole32(bitmap_size);
        *((uint16_t*)(bmp_tmp+12)) = htole16(1);
        *((uint16_t*)(bmp_tmp+14)) = htole16(1);
        *((uint32_t*)(bmp_tmp+16)) = htole32(0);
        *((uint32_t*)(bmp_tmp+20)) = htole32(balign*bitmap_size);
        *((uint32_t*)(bmp_tmp+24)) = htole32(0);
        *((uint32_t*)(bmp_tmp+28)) = htole32(0);
        *((uint32_t*)(bmp_tmp+32)) = htole32(2);
        *((uint32_t*)(bmp_tmp+36)) = htole32(2);
        fwrite(bmp_tmp,40,1,sctx->fp);

        /* color palette */
        bmp_tmp[0+0] = 0x00;
        bmp_tmp[0+1] = 0x00;
        bmp_tmp[0+2] = 0x00;
        bmp_tmp[0+3] = 0x00;
        bmp_tmp[4+0] = 0xFF;
        bmp_tmp[4+1] = 0xFF;
        bmp_tmp[4+2] = 0xFF;
        bmp_tmp[4+3] = 0x00;
        fwrite(bmp_tmp,4,2,sctx->fp);
    }

    return 0;
}

static int saveout_write_epilogue(struct rec98_bmp2arr_task *t,struct saveout_ctx *sctx) {
    if (t->output_type == REC98_OUT_C || t->output_type == REC98_OUT_CPP) {
        fprintf(sctx->fp,"};/*end spritesheet*/\n");
    }
    else if (t->output_type == REC98_OUT_ASM) {
        /* none needed */
    }
    else if (t->output_type == REC98_OUT_BIN) {
        /* none needed */
    }
    else if (t->output_type == REC98_OUT_BMP) {
        /* none needed */
    }

    return 0;
}

/* C-string utils */
void cstr_free(char **s) {
    if (s != NULL) {
        if (*s != NULL) {
            free((void*)(*s));
            *s = NULL;
        }
    }
}

void cstr_set(char **s,const char *n) {
    if (s != NULL) {
        cstr_free(s);
        if (n != NULL) *s = strdup(n);
    }
}

void rec98_bmp2arr_task_free_bmp(struct rec98_bmp2arr_task *t) {
    if (t != NULL) {
        if (t->bmp != NULL) {
            free((void*)(t->bmp));
            t->bmp = NULL;
        }
    }
}

/* assume *t is uninitialized data */
enum bmp2arr_error rec98_bmp2arr_task_init(struct rec98_bmp2arr_task *t) {
    if (t == NULL)
        return INTERNAL_NULLPTR;

    memset(t,0,sizeof(*t));
    return SUCCESS;
}

/* assume *t is initialized data */
enum bmp2arr_error rec98_bmp2arr_task_free(struct rec98_bmp2arr_task *t) {
    if (t == NULL)
        return INTERNAL_NULLPTR;

    rec98_bmp2arr_task_free_bmp(t);
    cstr_free(&t->output_symname);
    cstr_free(&t->output_file);
    cstr_free(&t->input_bmp);
    memset(t,0,sizeof(*t));
    return SUCCESS;
}

enum bmp2arr_error rec98_bmp2arr_save_debug_bmp_out(struct rec98_bmp2arr_task *t) {
    unsigned int y;
    int fd;

    if (t == NULL)
        return INTERNAL_NULLPTR;

    if (t->output_file == NULL)
        return bmp2arr_error_set(t, MISSING_OUTPUT_FILE);

    if (t->bmp == NULL)
        return bmp2arr_error_set(t, OUTPUT_NO_INPUT_LOADED);

    fd = open(t->output_file,O_WRONLY|O_CREAT|O_TRUNC|O_BINARY,0644);
    if (fd < 0)
        return bmp2arr_error_set_str(t, OUTPUT_OPEN_ERROR, t->output_file);

    /* BITMAPFILEHEADER */
    memcpy(bmp_tmp+0, "BM",2);
    *((uint32_t*)(bmp_tmp+2 )) = htole32(14+40+4*2+(t->bmp_height*t->bmp_stride));  /* bfSize */
    *((uint16_t*)(bmp_tmp+6 )) = htole16(0);
    *((uint16_t*)(bmp_tmp+8 )) = htole16(0);
    *((uint32_t*)(bmp_tmp+10)) = htole32(14+40+4*2);                                /* bfOffBits */
    write(fd,bmp_tmp,14);

    /* BITMAPINFOHEADER */
    *((uint32_t*)(bmp_tmp+0 )) = htole32(40);
    *((uint32_t*)(bmp_tmp+4 )) = htole32(t->bmp_width);
    *((uint32_t*)(bmp_tmp+8 )) = htole32(t->bmp_height);
    *((uint16_t*)(bmp_tmp+12)) = htole16(1);
    *((uint16_t*)(bmp_tmp+14)) = htole16(1);
    *((uint32_t*)(bmp_tmp+16)) = htole32(0);
    *((uint32_t*)(bmp_tmp+20)) = htole32(t->bmp_height*t->bmp_stride);
    *((uint32_t*)(bmp_tmp+24)) = htole32(0);
    *((uint32_t*)(bmp_tmp+28)) = htole32(0);
    *((uint32_t*)(bmp_tmp+32)) = htole32(2);
    *((uint32_t*)(bmp_tmp+36)) = htole32(2);
    write(fd,bmp_tmp,40);

    /* color palette */
    bmp_tmp[0+0] = 0x00;
    bmp_tmp[0+1] = 0x00;
    bmp_tmp[0+2] = 0x00;
    bmp_tmp[0+3] = 0x00;
    bmp_tmp[4+0] = 0xFF;
    bmp_tmp[4+1] = 0xFF;
    bmp_tmp[4+2] = 0xFF;
    bmp_tmp[4+3] = 0x00;
    write(fd,bmp_tmp,4*2);

    /* the bits */
    y = t->bmp_height - 1;
    do {
        write(fd,t->bmp + (y*t->bmp_stride),t->bmp_stride);
    } while (y-- != 0);

    close(fd);
    return bmp2arr_error_set(t, SUCCESS);
}

static int saveout_write_sprite(struct rec98_bmp2arr_task *t,struct saveout_ctx *sctx,const unsigned char *bmp/*length bytesperrow * height*/) {
    unsigned int r,c,b;

    if (t->output_type == REC98_OUT_C || t->output_type == REC98_OUT_CPP) {
        if (t->flags & PRESHIFT_INNER) {
            fprintf(sctx->fp,"%c",sctx->sspreshift != 0 ? ',' : ' ');
        }
        else {
            fprintf(sctx->fp,"%c",sctx->spritenum != 0 ? ',' : ' ');
        }

        if (t->flags & PRESHIFT_ANY) {
            fprintf(sctx->fp,"{/*sprite %u preshift %u*/\n",sctx->spritenum,sctx->sspreshift);
        }
        else {
            fprintf(sctx->fp,"{/*sprite %u*/\n",sctx->spritenum);
        }

        for (r=0;r < t->sprite_height;r++) {
            fprintf(sctx->fp,"\t");
            if (t->output_type == REC98_OUT_C)
                for (c=0;c < sctx->bytesperrow;c++)
                    fprintf(sctx->fp,"0x%02x,",*bmp++);
            else if (t->output_type == REC98_OUT_CPP) {
                uint8_t byte[4];
                switch (sctx->bytesperrow) {
                    case 2:
                        byte[0] = *bmp++;
                        byte[1] = *bmp++;
                        fprintf(sctx->fp,"0x%02x%02x,",byte[1],byte[0]);
                        break;
                    case 4:
                        byte[0] = *bmp++;
                        byte[1] = *bmp++;
                        byte[2] = *bmp++;
                        byte[3] = *bmp++;
                        fprintf(sctx->fp,"0x%02x%02x%02x%02x,",byte[3],byte[2],byte[1],byte[0]);
                        break;
                    default:
                        for (c=0;c < sctx->bytesperrow;c++)
                            fprintf(sctx->fp,"0x%02x,",*bmp++);
                        break;
                }
            }
            fprintf(sctx->fp," /* row %u */",(t->flags & UPSIDEDOWN) ? (t->sprite_height - 1u - r) : r);
            fprintf(sctx->fp,"\n");
        }

        if (t->flags & PRESHIFT_ANY) {
            fprintf(sctx->fp," }/*end sprite %u preshift %u*/\n",sctx->spritenum,sctx->sspreshift);
        }
        else {
            fprintf(sctx->fp," }/*end sprite %u*/\n",sctx->spritenum);
        }
    }
    else if (t->output_type == REC98_OUT_ASM) {
        if (t->flags & PRESHIFT_ANY) {
            fprintf(sctx->fp,"; sprite %u preshift %u\n",sctx->spritenum,sctx->sspreshift);
        }
        else {
            fprintf(sctx->fp,"; sprite %u\n",sctx->spritenum);
        }

        for (r=0;r < t->sprite_height;r++) {
            fprintf(sctx->fp,"\tdb ");
            for (c=0;c < sctx->bytesperrow;c++) {
                if (c != 0) fprintf(sctx->fp,",");

                for (b=0;b < 8;b++)
                    fprintf(sctx->fp,"%u",(*bmp >> (7u - b)) & 1u);

                fprintf(sctx->fp,"b");
                bmp++;
            }
            fprintf(sctx->fp," ; row %u",(t->flags & UPSIDEDOWN) ? (t->sprite_height - 1u - r) : r);
            fprintf(sctx->fp,"\n");
        }
    }
    else if (t->output_type == REC98_OUT_BIN) {
        fwrite(bmp,sctx->bytesperrow * t->sprite_height,1,sctx->fp);
    }
    else if (t->output_type == REC98_OUT_BMP) {
        const unsigned int balign = (sctx->bytesperrow + 3u) & (~3u);
        for (r=0;r < t->sprite_height;r++) {
            memcpy(bmp_tmp,bmp,sctx->bytesperrow);
            fwrite(bmp_tmp,balign,1,sctx->fp);
            bmp += sctx->bytesperrow;
        }
    }

    return 0;
}

enum bmp2arr_error rec98_bmp2arr_save_output(struct rec98_bmp2arr_task *t) {
    struct saveout_ctx sctx;

    if (t == NULL)
        return INTERNAL_NULLPTR;

    if(t->output_file == NULL)
        return bmp2arr_error_set(t, MISSING_OUTPUT_FILE);

    if(t->output_type == REC98_OUT_NONE)
        return bmp2arr_error_set(t, MISSING_OUTPUT_TYPE);
    if(t->output_type > BMP2ARR_OUTPUT_TYPE_COUNT)
        return bmp2arr_error_set(t, INVALID_OUTPUT_TYPE);

    if (t->bmp == NULL)
        return bmp2arr_error_set(t, OUTPUT_NO_INPUT_LOADED);

    if (t->sprite_width > 640)
        return bmp2arr_error_set(t, INVALID_SPRITE_WIDTH);

    if (t->sprite_height == 0)
        return bmp2arr_error_set(t, MISSING_SPRITE_HEIGHT);

    if ((t->flags & PRESHIFT_ANY) == PRESHIFT_ANY)
        return bmp2arr_error_set(t, INVALID_PRESHIFT);

    sctx.sscols = t->bmp_width / t->sprite_width;
    sctx.ssrows = t->bmp_height / t->sprite_height;
    if (sctx.sscols == 0 || sctx.ssrows == 0)
        return bmp2arr_error_set(t, INPUT_TOO_SMALL);

    if (t->flags & PRESHIFT_ANY && t->sprite_width != 8)
        return bmp2arr_error_set(t, INVALID_PRESHIFT_WIDTH);

    sctx.bytesperrow = (t->sprite_width + 7u) / 8u;
    if (t->flags & PRESHIFT_ANY) sctx.bytesperrow += 1u; /* in the examples, an 8-pixel wide sprite is shifted across 16 pixels */

    if ((sctx.bytesperrow * t->sprite_height) > sizeof(bmp_tmp))
        return bmp2arr_error_set(t, INTERNAL_ARRAY_TOO_SMALL);

    sctx.fp = fopen(t->output_file,"wb");
    if (sctx.fp == NULL)
        return bmp2arr_error_set_str(t, OUTPUT_OPEN_ERROR, t->output_file);

    if (!(t->flags & QUIET)) {
        unsigned int cels = sctx.sscols * sctx.ssrows;
        const char *str_layout = NULL;
        static const char *TYPES[BMP2ARR_OUTPUT_TYPE_COUNT] = {
            NULL, "C", "ASM", "binary", "BMP"
        };

        if (t->flags & PRESHIFT_OUTER) {
            str_layout = "[PRESHIFT][cels][rows]";
        } else if (t->flags & PRESHIFT_INNER) {
            str_layout = "[cels][PRESHIFT][rows]";
        } else  {
            str_layout = "[cels][rows] (no pre-shifting)";
        }

        fprintf(stderr,
            "Input bitmap: %s (size %d x %d)\n"
            " Sprite size: %d x %d\n"
            "      = Cels: %d (arranged as %d x %d)\n"
            " Data layout: %s\n"
            " Y direction: %s\n"
            " Output file: %s (Format: %s)\n"
            ,
            t->input_bmp,(sctx.sscols*t->sprite_width),(sctx.ssrows*t->sprite_height),
            t->sprite_width,t->sprite_height,
            cels,sctx.sscols,sctx.ssrows,
            str_layout,
            (t->flags & UPSIDEDOWN) ? "upside down" : "normal",
            t->output_file, TYPES[t->output_type]
        );
    }

    if (saveout_write_prologue(t,&sctx))
        goto fioerr;

    if (t->flags & PRESHIFT_INNER) {
        for (sctx.ssrow=0;sctx.ssrow < sctx.ssrows;sctx.ssrow++) {
            sctx.spritenum = sctx.ssrow * sctx.sscols;
            for (sctx.sscol=0;sctx.sscol < sctx.sscols;sctx.sscol++,sctx.spritenum++) {
                if (t->output_type == REC98_OUT_C || t->output_type == REC98_OUT_CPP) {
                    fprintf(sctx.fp,"%c",sctx.spritenum != 0 ? ',' : ' ');
                    fprintf(sctx.fp,"{/*preshift*/\n");
                }

                for (sctx.sspreshift=0;sctx.sspreshift < 8;sctx.sspreshift++) {
                    unsigned char *dbits = bmp_tmp; /* use bmp_tmp[], this is why the size check */
                    unsigned int y,b;

                    for (y=0;y < t->sprite_height;y++) {
                        unsigned int shif = 0;
                        unsigned int sr =
                            (t->flags & UPSIDEDOWN) ? (t->sprite_height - 1 - y) : y;
                        const unsigned char *sbits =
                            (const unsigned char*)t->bmp +
                            (sctx.sscol * ((t->sprite_width + 7u) / 8u)) +
                            (((sctx.ssrow * t->sprite_height) + sr) * t->bmp_stride);

                        b = sctx.bytesperrow;
                        while (b >= 2) {
                            b--;
                            shif = (shif << 8u) + (((unsigned int)(*sbits++)) << (8u - sctx.sspreshift));
                            *dbits++ = shif >> 8u;
                        }
                        while (b >= 1) {
                            b--;
                            shif = (shif << 8u);
                            *dbits++ = shif >> 8u;
                        }
                    }

                    if (saveout_write_sprite(t,&sctx,bmp_tmp))
                        goto fioerr;
                }

                if (t->output_type == REC98_OUT_C || t->output_type == REC98_OUT_CPP) {
                    fprintf(sctx.fp," }/*end preshift*/\n");
                }
            }
        }
    }
    else if (t->flags & PRESHIFT_OUTER) {
        for (sctx.sspreshift=0;sctx.sspreshift < 8;sctx.sspreshift++) {
            if (t->output_type == REC98_OUT_C || t->output_type == REC98_OUT_CPP) {
                fprintf(sctx.fp,"%c",sctx.sspreshift != 0 ? ',' : ' ');
                fprintf(sctx.fp,"{/*preshift %u*/\n",sctx.sspreshift);
            }

            for (sctx.ssrow=0;sctx.ssrow < sctx.ssrows;sctx.ssrow++) {
                sctx.spritenum = sctx.ssrow * sctx.sscols;
                for (sctx.sscol=0;sctx.sscol < sctx.sscols;sctx.sscol++,sctx.spritenum++) {
                    unsigned char *dbits = bmp_tmp; /* use bmp_tmp[], this is why the size check */
                    unsigned int y,b;

                    for (y=0;y < t->sprite_height;y++) {
                        unsigned int shif = 0;
                        unsigned int sr =
                            (t->flags & UPSIDEDOWN) ? (t->sprite_height - 1 - y) : y;
                        const unsigned char *sbits =
                            (const unsigned char*)t->bmp +
                            (sctx.sscol * ((t->sprite_width + 7u) / 8u)) +
                            (((sctx.ssrow * t->sprite_height) + sr) * t->bmp_stride);

                        b = sctx.bytesperrow;
                        while (b >= 2) {
                            b--;
                            shif = (shif << 8u) + (((unsigned int)(*sbits++)) << (8u - sctx.sspreshift));
                            *dbits++ = shif >> 8u;
                        }
                        while (b >= 1) {
                            b--;
                            shif = (shif << 8u);
                            *dbits++ = shif >> 8u;
                        }
                    }

                    if (saveout_write_sprite(t,&sctx,bmp_tmp))
                        goto fioerr;
                }
            }

            if (t->output_type == REC98_OUT_C || t->output_type == REC98_OUT_CPP) {
                fprintf(sctx.fp," }/*end preshift %u*/\n",sctx.sspreshift);
            }
        }
    }
    else {
        sctx.sspreshift = 0;
        for (sctx.ssrow=0;sctx.ssrow < sctx.ssrows;sctx.ssrow++) {
            sctx.spritenum = sctx.ssrow * sctx.sscols;
            for (sctx.sscol=0;sctx.sscol < sctx.sscols;sctx.sscol++,sctx.spritenum++) {
                unsigned char *dbits = bmp_tmp; /* use bmp_tmp[], this is why the size check */
                unsigned int y,b;

                for (y=0;y < t->sprite_height;y++) {
                    unsigned int sr =
                        (t->flags & UPSIDEDOWN) ? (t->sprite_height - 1 - y) : y;
                    const unsigned char *sbits =
                        (const unsigned char*)t->bmp +
                        (sctx.sscol * ((t->sprite_width + 7u) / 8u)) +
                        (((sctx.ssrow * t->sprite_height) + sr) * t->bmp_stride);

                    for (b=0;b < sctx.bytesperrow;b++)
                        *dbits++ = *sbits++;
                }

                if (saveout_write_sprite(t,&sctx,bmp_tmp))
                    goto fioerr;
            }
        }
    }

    if (saveout_write_epilogue(t,&sctx))
        goto fioerr;

    fclose(sctx.fp);
    return bmp2arr_error_set(t, SUCCESS);
fioerr:
    fclose(sctx.fp);
    return bmp2arr_error_set(t, OUTPUT_IO_ERROR);
}

enum bmp2arr_error rec98_bmp2arr_load_bitmap(struct rec98_bmp2arr_task *t) {
    enum bmp2arr_error err = SUCCESS;
    unsigned char *tmprow = NULL;
    uint8_t xorval = 0;
    uint32_t srcstride;
    uint32_t offbits;
    uint32_t bisize;
    uint16_t bpp;
    uint32_t row;
    int fd;

    if (t == NULL)
        return INTERNAL_NULLPTR;

    if (t->input_bmp == NULL)
        return bmp2arr_error_set(t, MISSING_INPUT_BMP);

    if (t->bmp != NULL)
        return bmp2arr_error_set(t, INPUT_ALREADY_LOADED);

    fd = open(t->input_bmp,O_RDONLY|O_BINARY);
    if (fd < 0)
        return bmp2arr_error_set_str(t, INPUT_OPEN_ERROR, t->input_bmp);

    if (lseek(fd,0,SEEK_SET) != 0) goto fioerr;

    /* BITMAPFILEHEADER */
    if (read(fd,bmp_tmp,14) != 14) goto fioerr;
    if (memcmp(bmp_tmp,"BM",2)) goto fioerr;
    offbits = le32toh( *((uint32_t*)(bmp_tmp+10)) ); /* endian.h little endian to host */

    /* BITMAPINFOHEADER */
    if (read(fd,bmp_tmp,40) != 40) goto fioerr;
    bisize = le32toh( *((uint32_t*)(bmp_tmp+0)) );
    if (bisize < 40) goto fioerr; /* *sigh* GIMP has decided to export the larger header with NO option to emit the traditional 40-byte format */

    t->bmp_width = le32toh( *((uint32_t*)(bmp_tmp+4)) );
    t->bmp_height = le32toh( *((uint32_t*)(bmp_tmp+8)) );
    if (t->bmp_width < 1 || t->bmp_height < 1 || t->bmp_width > 1024 || t->bmp_height > 1024) goto fioerr;

    if ( le16toh( *((uint16_t*)(bmp_tmp+12)) ) != 1 /* biPlanes*/)
        goto fioerr;

    /* biCompression can be 0 (no compression) or 3 (BI_RGB) */
    if (!(le32toh( *((uint32_t*)(bmp_tmp+16)) ) == 0 /* biCompression */ ||
          le32toh( *((uint32_t*)(bmp_tmp+16)) ) == 3 /* biCompression */))
        goto fioerr;

    bpp = le16toh( *((uint16_t*)(bmp_tmp+14)) );
    if (!(bpp == 1 || bpp == 24 || bpp == 32)) goto fioerr;

    t->bmp_stride = srcstride = (((t->bmp_width * bpp) + 31u) & (~31u)) / 8u; /* 4-byte align */

#if TARGET_MSDOS == 16
    if ((32768u / t->bmp_stride) < t->bmp_height) /* cannot fit into 32KB */
        goto fioerr;
#endif

    /* skip anything beyond the 40 byte header we expect */
    if (bisize > 40)
        lseek(fd,bisize-40,SEEK_CUR);

    /* palette */
    if (bpp == 1) {
        if (read(fd,bmp_tmp,4*2) != (4*2)) goto fioerr;

        /* in case of stupid editing programs that put the white color first */
        if ((bmp_tmp[0]|bmp_tmp[1]|bmp_tmp[2])&0x80) xorval = 0xFF;
    }

    t->bmp = (unsigned char*)malloc(t->bmp_height * t->bmp_stride);
    if (t->bmp == NULL) {
        err = bmp2arr_error_set(t, INPUT_OUT_OF_MEMORY);
        goto fioerr;
    }

    /* read bitmap bits. BMPs are upside-down */
    if (lseek(fd,offbits,SEEK_SET) != offbits) goto fioerr;

    /* may need to convert to 1bpp from source */
#if TARGET_MSDOS == 16
    if (srcstride >= 0xFFFFul) goto fioerr;
#endif
    tmprow = (unsigned char*)malloc((unsigned int)srcstride);
    if (tmprow == NULL) goto fioerr;

    /* count: height-1 to 0 inclusive */
    row = t->bmp_height - 1u;
    do {
        if ((uint32_t)read(fd,tmprow,(unsigned int)srcstride) != srcstride) goto fioerr;

        if (bpp == 1)
            memcpyxor(t->bmp + (row * t->bmp_stride),tmprow,(unsigned int)srcstride,xorval);
        else if (bpp == 24) {
            int err_x = memcpy24to1(t->bmp + (row * t->bmp_stride),tmprow,t->bmp_width);
            if (err_x != -1) {
                err = bmp2arr_error_set_int_int(t, INPUT_COLOR_AT, err_x, (int)row);
                goto fioerr;
            }
        }
        else if (bpp == 32) {
            int err_x = memcpy32to1(t->bmp + (row * t->bmp_stride),tmprow,t->bmp_width);
            if (err_x != -1) {
                err = bmp2arr_error_set_int_int(t, INPUT_COLOR_AT, err_x, (int)row);
                goto fioerr;
            }
        }
    } while (row-- != 0u); /* compare against post decrement to break out if it is zero */

    if (tmprow) free((void*)tmprow);
    close(fd);

    return bmp2arr_error_set(t, SUCCESS);
fioerr:
    if (tmprow) free((void*)tmprow);
    close(fd);
    if (err == SUCCESS) {
        return bmp2arr_error_set(t, INPUT_INVALID);
    }
    return err;
}

