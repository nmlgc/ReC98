
#if defined(REC98_PROJECT)
# include "platform.h" /* see also [https://github.com/nmlgc/ReC98/issues/8] */
#else
# include <stdint.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#if defined(__GNUC__)
# include <endian.h>
#else
# define le16toh(x) (x)
# define le32toh(x) (x)
# define htole16(x) (x)
# define htole32(x) (x)
#endif

/* O_BINARY is needed for MS-DOS, Windows, etc.
 * Linux, Mac OS X, etc. do not have O_BINARY */
#ifndef O_BINARY
#define O_BINARY (0)
#endif

/* what to emit */
enum rec98_bmp2arr_output_type {
    REC98_OUT_C=0,
    REC98_OUT_ASM,
    REC98_OUT_OMF,
    REC98_OUT_BIN
};

/* the task at hand */
struct rec98_bmp2arr_task {
    char*           input_bmp;
    char*           output_symname;     /* what to name the symbol */
    char*           output_file;
    unsigned char   output_type;
    unsigned char   sprite_width;       /* 8, or 16 [https://github.com/nmlgc/ReC98/issues/8 ref. dots8_t, dots16_t] */
    unsigned char   sprite_height;      /* according to list, either 4, 8, or 16 */
    unsigned char   preshift;           /* 1=generate preshifted variations or 0=don't   This makes the bitmap one byte wider */
    unsigned char   upsidedown;         /* 1=output upside down  (ref. game 3 score bitmap) */
    unsigned char   preshift_inner;     /* 1=[number][PRESHIFT][height]    0=[PRESHIFT][number][height] */
    unsigned char   debug_bmp_out;      /* 1=output file is bitmap read in (debugging) */

    /* working state */
    unsigned int    bmp_width;          /* width of bmp */
    unsigned int    bmp_height;         /* height of bmp */
    unsigned int    bmp_stride;         /* bytes per scanline */
    unsigned char*  bmp;                /* bitmap in memory (NTS: All examples listed can easily fit in 64KB or less) */
};

/* C-string utils */
void cstr_free(char **s) {
    if (s != NULL) {
        if (*s != NULL) {
            free(*s);
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
            free(t->bmp);
            t->bmp = NULL;
        }
    }
}

/* assume *t is uninitialized data */
int rec98_bmp2arr_task_init(struct rec98_bmp2arr_task *t) {
    if (t == NULL) return -1; /* failure */
    memset(t,0,sizeof(*t));
    return 0; /* success */
}

/* assume *t is initialized data */
int rec98_bmp2arr_task_free(struct rec98_bmp2arr_task *t) {
    if (t == NULL) return -1; /* failure */
    rec98_bmp2arr_task_free_bmp(t);
    cstr_free(&t->output_symname);
    cstr_free(&t->output_file);
    cstr_free(&t->input_bmp);
    memset(t,0,sizeof(*t));
    return 0; /* success */
}

static unsigned char bmp_tmp[128]; /* more than enough */

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

void memcpyxor(unsigned char *dst,unsigned char *src,unsigned int bytes,unsigned char xorval) {
    while (bytes-- != 0)
        *dst++ = *src++ ^ xorval;
}

void memcpy24to1(unsigned char *dst,unsigned char *src,unsigned int w) {
    unsigned char r,g,b,tmp;
    unsigned int x;

    while (w >= 8) {
        tmp = 0;
        for (x=0;x < 8;x++) {
            b = *src++;
            g = *src++;
            r = *src++;
            if ((r|g|b)&0x80)
                tmp |= 0x80 >> x;
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
            if ((r|g|b)&0x80)
                tmp |= 0x80 >> x;
        }

        *dst++ = tmp;
    }
}

void memcpy32to1(unsigned char *dst,unsigned char *src,unsigned int w) {
    unsigned char r,g,b,tmp;
    unsigned int x;

    while (w >= 8) {
        tmp = 0;
        for (x=0;x < 8;x++) {
            b = *src++;
            g = *src++;
            r = *src++;
                 src++; /* A */
            if ((r|g|b)&0x80)
                tmp |= 0x80 >> x;
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
            if ((r|g|b)&0x80)
                tmp |= 0x80 >> x;
        }

        *dst++ = tmp;
    }
}

int rec98_bmp2arr_save_debug_bmp_out(struct rec98_bmp2arr_task *t) {
    unsigned int y;
    int fd;

    if (t == NULL || t->output_file == NULL) return -1;
    if (t->bmp == NULL) return -1;

    fd = open(t->output_file,O_WRONLY|O_CREAT|O_TRUNC|O_BINARY,0644);
    if (fd < 0) return -1;

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
    return 0;
}

int rec98_bmp2arr_save_output(struct rec98_bmp2arr_task *t) {
    int sscols,ssrows,spritenum,x,y,bytesperrow;
    FILE *fp; /* for that nice fprintf formatting if needed */

    if (t == NULL || t->output_file == NULL) return -1;
    if (t->bmp == NULL) return -1;
    if (t->sprite_width < 8) return -1;
    if (t->sprite_height == 0) return -1;

    sscols = t->bmp_width / t->sprite_width;
    ssrows = t->bmp_height / t->sprite_height;
    if (sscols == 0 || ssrows == 0) return -1;

    /* PRESHIFT only supported for 8-pixel wide sprites */
    if (t->preshift && t->sprite_width != 8)
        return -1;

    fp = fopen(t->output_file,"wb");
    if (fp == NULL) return -1;

    bytesperrow = (t->sprite_width + 7u) / 8u;
    if (t->preshift) bytesperrow += 1u; /* in the examples, an 8-pixel wide sprite is shifted across 16 pixels */

    fprintf(stderr,"Sprite sheet: %d sprites total (%d x %d).\n",
        sscols * ssrows,sscols,ssrows);
    fprintf(stderr,"Each sprite is %d x %d\n",
        t->sprite_width,t->sprite_height);

    /* prologue */
    if (t->output_type == REC98_OUT_C) {
        fprintf(fp,"/* Generated by bmp2arr from %s, do not modify directly. */\n",t->input_bmp);
        fprintf(fp,"/* Sprite sheet: %d sprites (%d x %d) of %d x %d sprites. */\n",sscols * ssrows,sscols,ssrows,t->sprite_width,t->sprite_height);
        fprintf(fp,"\n");

        fprintf(fp,"const unsigned char %s",t->output_symname != NULL ? t->output_symname : "untitled");

        if (t->preshift && t->preshift_inner == 0)
            fprintf(fp,"[8/*PRESHIFT*/]");

        fprintf(fp,"[%d]",ssrows * sscols);

        if (t->preshift && t->preshift_inner == 1)
            fprintf(fp,"[8/*PRESHIFT*/]");

        fprintf(fp,"[%d/*%d bytes x %d rows*/] = {\n",
            bytesperrow * t->sprite_height,bytesperrow,t->sprite_height);
    }
    else if (t->output_type == REC98_OUT_ASM) {
        fprintf(fp,"; Generated by bmp2arr from %s, do not modify directly.\n",t->input_bmp);
        fprintf(fp,"; Sprite sheet: %d sprites (%d x %d) of %d x %d sprites.\n",sscols * ssrows,sscols,ssrows,t->sprite_width,t->sprite_height);
        fprintf(fp,"\n");

        fprintf(fp,"public %s\n",t->output_symname != NULL ? t->output_symname : "untitled");
        fprintf(fp,"label %s byte\n",t->output_symname != NULL ? t->output_symname : "untitled");
    }
    else if (t->output_type == REC98_OUT_BIN) {
        /* none needed */
    }

    // TODO

    /* epilogue */
    if (t->output_type == REC98_OUT_C) {
        fprintf(fp,"};\n");
    }
    else if (t->output_type == REC98_OUT_ASM) {
        /* none needed */
    }
    else if (t->output_type == REC98_OUT_BIN) {
        /* none needed */
    }

    return 0;
fioerr:
    fclose(fp);
    return -1;
}

int rec98_bmp2arr_load_bitmap(struct rec98_bmp2arr_task *t) {
    unsigned char *tmprow = NULL;
    uint8_t xorval = 0;
    uint32_t srcstride;
    uint32_t offbits;
    uint32_t bisize;
    uint16_t bpp;
    uint32_t row;
    int fd;

    if (t == NULL || t->input_bmp == NULL) return -1;
    if (t->bmp != NULL) return -1;

    fd = open(t->input_bmp,O_RDONLY|O_BINARY);
    if (fd < 0) return -1;
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

    if (bpp > 1)
        srcstride = ((t->bmp_width + 3u) & (~3u)) * (bpp / 8u); /* 4-pixel align */
    else
        srcstride = (t->bmp_width + 7u) / 8u; /* BYTE align */

    t->bmp_stride = (t->bmp_width + 7u) / 8u; /* BYTE align */

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

    t->bmp = malloc(t->bmp_height * t->bmp_stride);
    if (t->bmp == NULL) goto fioerr;

    /* read bitmap bits. BMPs are upside-down */
    if (lseek(fd,offbits,SEEK_SET) != offbits) goto fioerr;

    /* may need to convert to 1bpp from source */
    tmprow = malloc(srcstride);
    if (tmprow == NULL) goto fioerr;

    /* count: height-1 to 0 inclusive */
    row = t->bmp_height - 1u;
    do {
        if (read(fd,tmprow,srcstride) != srcstride) goto fioerr;

        if (bpp == 1)
            memcpyxor(t->bmp + (row * t->bmp_stride),tmprow,srcstride,xorval);
        else if (bpp == 24)
            memcpy24to1(t->bmp + (row * t->bmp_stride),tmprow,t->bmp_width);
        else if (bpp == 32)
            memcpy32to1(t->bmp + (row * t->bmp_stride),tmprow,t->bmp_width);
    } while (row-- != 0u); /* compare against post decrement to break out if it is zero */

    if (tmprow) free(tmprow);
    close(fd);

    return 0;
fioerr:
    if (tmprow) free(tmprow);
    close(fd);
    return -1;
}

static int parse_argv(struct rec98_bmp2arr_task *tsk,int argc,char **argv) {
    char *a;
    int i;

    for (i=1;i < argc;) {
        a = argv[i++];

        if (*a == '-') {
            do { a++; } while (*a == '-');

            if (!strcmp(a,"i")) {
                a = argv[i++];
                if (a == NULL) return -1;
                cstr_set(&tsk->input_bmp,a);
            }
            else if (!strcmp(a,"o")) {
                a = argv[i++];
                if (a == NULL) return -1;
                cstr_set(&tsk->output_file,a);
            }
            else if (!strcmp(a,"sym")) {
                a = argv[i++];
                if (a == NULL) return -1;
                cstr_set(&tsk->output_symname,a);
            }
            else if (!strcmp(a,"of")) {
                a = argv[i++];
                if (a == NULL) return -1;

                if (!strcmp(a,"omf"))
                    tsk->output_type = REC98_OUT_OMF;
                else if (!strcmp(a,"asm"))
                    tsk->output_type = REC98_OUT_ASM;
                else if (!strcmp(a,"bin"))
                    tsk->output_type = REC98_OUT_BIN;
                else if (!strcmp(a,"c"))
                    tsk->output_type = REC98_OUT_C;
                else
                    return -1;
            }
            else if (!strcmp(a,"sw")) {
                a = argv[i++];
                if (a == NULL) return -1;
                tsk->sprite_width = atoi(a);
                if (!(tsk->sprite_width == 8 || tsk->sprite_width == 16)) return -1;
            }
            else if (!strcmp(a,"sh")) {
                a = argv[i++];
                if (a == NULL) return -1;
                tsk->sprite_height = atoi(a);
                if (tsk->sprite_height < 1 || tsk->sprite_height > 32) return -1;
            }
            else if (!strcmp(a,"u")) {
                tsk->upsidedown = 1;
            }
            else if (!strcmp(a,"dbg-bmp")) {
                tsk->debug_bmp_out = 1;
            }
            else if (!strcmp(a,"pshf")) {
                a = argv[i++];
                if (a == NULL) return -1;

                tsk->preshift = 1;
                if (!strcmp(a,"inner"))
                    tsk->preshift_inner = 1;
                else if (!strcmp(a,"outer"))
                    tsk->preshift_inner = 0;
                else
                    return -1;
            }
            else {
                fprintf(stderr,"Unknown switch '%s'\n",a);
            }
        }
        else {
            fprintf(stderr,"Unexpected\n");
            return -1;
        }
    }

    /* input BMP is required */
    if (tsk->input_bmp == NULL) {
        fprintf(stderr,"Input BMP required (-i)\n");
        return -1;
    }

    /* output file is required */
    if (tsk->output_file == NULL) {
        fprintf(stderr,"Output file required (-o)\n");
        return -1;
    }

    if (tsk->sprite_width == 0 || tsk->sprite_height == 0) {
        fprintf(stderr,"Sprite width/height required (-sw and -sh)\n");
        return -1;
    }
    if (!(tsk->sprite_width == 8 || tsk->sprite_width == 16)) {
        fprintf(stderr,"Sprite width must be 8 or 16\n");
        return -1;
    }

    return 0; /* success */
}

int main(int argc,char **argv) {
    struct rec98_bmp2arr_task tsk;

    if (rec98_bmp2arr_task_init(&tsk))
        return 1;

    if (parse_argv(&tsk,argc,argv))
        return 1;

    if (rec98_bmp2arr_load_bitmap(&tsk))
        return 1;

    if (tsk.debug_bmp_out) {
        if (rec98_bmp2arr_save_debug_bmp_out(&tsk))
            return 1;

        return 0;
    }

    if (rec98_bmp2arr_save_output(&tsk))
        return 1;

    rec98_bmp2arr_task_free(&tsk);
    return 0;
}

