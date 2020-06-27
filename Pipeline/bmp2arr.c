
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
    REC98_OUT_BIN,
    REC98_OUT_BMP
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

struct saveout_ctx {
    unsigned int            sscols,ssrows,spritenum,bytesperrow,sscol,ssrow,sspreshift;
    FILE*                   fp; /* for that nice fprintf formatting if needed */
};

static int saveout_write_prologue(struct rec98_bmp2arr_task *t,struct saveout_ctx *sctx) {
    if (t->output_type == REC98_OUT_C) {
        fprintf(sctx->fp,"/* Generated by bmp2arr from %s, do not modify directly. */\n",t->input_bmp);
        fprintf(sctx->fp,"/* Sprite sheet: %d sprites (%d x %d) of %d x %d sprites. */\n",sctx->sscols * sctx->ssrows,sctx->sscols,sctx->ssrows,t->sprite_width,t->sprite_height);
        fprintf(sctx->fp,"\n");

        fprintf(sctx->fp,"const unsigned char %s",t->output_symname != NULL ? t->output_symname : "untitled");

        if (t->preshift && t->preshift_inner == 0)
            fprintf(sctx->fp,"[8/*PRESHIFT*/]");

        fprintf(sctx->fp,"[%d]",sctx->ssrows * sctx->sscols);

        if (t->preshift && t->preshift_inner == 1)
            fprintf(sctx->fp,"[8/*PRESHIFT*/]");

        fprintf(sctx->fp,"[%d/*%d bytes x %d rows*/] = {\n",
            sctx->bytesperrow * t->sprite_height,sctx->bytesperrow,t->sprite_height);
    }
    else if (t->output_type == REC98_OUT_ASM) {
        fprintf(sctx->fp,"; Generated by bmp2arr from %s, do not modify directly.\n",t->input_bmp);
        fprintf(sctx->fp,"; Sprite sheet: %d sprites (%d x %d) of %d x %d sprites.\n",sctx->sscols * sctx->ssrows,sctx->sscols,sctx->ssrows,t->sprite_width,t->sprite_height);
        fprintf(sctx->fp,"\n");

        fprintf(sctx->fp,"; const unsigned char %s",t->output_symname != NULL ? t->output_symname : "untitled");

        if (t->preshift && t->preshift_inner == 0)
            fprintf(sctx->fp,"[8/*PRESHIFT*/]");

        fprintf(sctx->fp,"[%d]",sctx->ssrows * sctx->sscols);

        if (t->preshift && t->preshift_inner == 1)
            fprintf(sctx->fp,"[8/*PRESHIFT*/]");

        fprintf(sctx->fp,"[%d/*%d bytes x %d rows*/];\n",
            sctx->bytesperrow * t->sprite_height,sctx->bytesperrow,t->sprite_height);

        fprintf(sctx->fp,"public %s\n",t->output_symname != NULL ? t->output_symname : "untitled");
        fprintf(sctx->fp,"label %s byte\n",t->output_symname != NULL ? t->output_symname : "untitled");
    }
    else if (t->output_type == REC98_OUT_BIN) {
        /* none needed */
    }
    else if (t->output_type == REC98_OUT_BMP) {
        const unsigned int balign = (sctx->bytesperrow + 3u) & (~3u);

        /* BITMAPFILEHEADER */
        memcpy(bmp_tmp+0, "BM",2);
        *((uint32_t*)(bmp_tmp+2 )) = htole32(14+40+4*2+(balign*t->sprite_height*sctx->ssrows*sctx->sscols*(t->preshift?8u:1u)));  /* bfSize */
        *((uint16_t*)(bmp_tmp+6 )) = htole16(0);
        *((uint16_t*)(bmp_tmp+8 )) = htole16(0);
        *((uint32_t*)(bmp_tmp+10)) = htole32(14+40+4*2);                                /* bfOffBits */
        fwrite(bmp_tmp,14,1,sctx->fp);

        /* BITMAPINFOHEADER */
        *((uint32_t*)(bmp_tmp+0 )) = htole32(40);
        *((uint32_t*)(bmp_tmp+4 )) = htole32(sctx->bytesperrow*8u);
        *((uint32_t*)(bmp_tmp+8 )) = htole32(t->sprite_height*sctx->ssrows*sctx->sscols*(t->preshift?8u:1u));
        *((uint16_t*)(bmp_tmp+12)) = htole16(1);
        *((uint16_t*)(bmp_tmp+14)) = htole16(1);
        *((uint32_t*)(bmp_tmp+16)) = htole32(0);
        *((uint32_t*)(bmp_tmp+20)) = htole32(balign*t->sprite_height*sctx->ssrows*sctx->sscols*(t->preshift?8u:1u));
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
    if (t->output_type == REC98_OUT_C) {
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

int saveout_write_sprite(struct rec98_bmp2arr_task *t,struct saveout_ctx *sctx,const unsigned char *bmp/*length bytesperrow * height*/) {
    unsigned int r,c,b;

    if (t->output_type == REC98_OUT_C) {
        if (t->preshift) {
            fprintf(sctx->fp,"%c",sctx->sspreshift != 0 ? ',' : ' ');
            fprintf(sctx->fp,"{/*sprite %u preshift %u*/\n",sctx->spritenum,sctx->sspreshift);
        }
        else {
            fprintf(sctx->fp,"%c",sctx->spritenum != 0 ? ',' : ' ');
            fprintf(sctx->fp,"{/*sprite %u*/\n",sctx->spritenum);
        }

        for (r=0;r < t->sprite_height;r++) {
            fprintf(sctx->fp,"\t");
            for (c=0;c < sctx->bytesperrow;c++) {
                fprintf(sctx->fp,"%c",(c != 0 || r != 0) ? ',' : ' ');
                fprintf(sctx->fp,"0x%02x",*bmp++);
            }
            fprintf(sctx->fp," /* row %u */",t->upsidedown ? (t->sprite_height - 1u - r) : r);
            fprintf(sctx->fp,"\n");
        }

        if (t->preshift) {
            fprintf(sctx->fp," }/*end sprite %u preshift %u*/\n",sctx->spritenum,sctx->sspreshift);
        }
        else {
            fprintf(sctx->fp," }/*end sprite %u*/\n",sctx->spritenum);
        }
    }
    else if (t->output_type == REC98_OUT_ASM) {
        if (t->preshift) {
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
            fprintf(sctx->fp," ; row %u",t->upsidedown ? (t->sprite_height - 1u - r) : r);
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

int rec98_bmp2arr_save_output(struct rec98_bmp2arr_task *t) {
    struct saveout_ctx sctx;

    if (t == NULL || t->output_file == NULL) return -1;
    if (t->bmp == NULL) return -1;
    if (t->sprite_width < 8) return -1;
    if (t->sprite_height == 0) return -1;

    sctx.sscols = t->bmp_width / t->sprite_width;
    sctx.ssrows = t->bmp_height / t->sprite_height;
    if (sctx.sscols == 0 || sctx.ssrows == 0) return -1;

    /* PRESHIFT only supported for 8-pixel wide sprites */
    if (t->preshift && t->sprite_width != 8)
        return -1;

    sctx.bytesperrow = (t->sprite_width + 7u) / 8u;
    if (t->preshift) sctx.bytesperrow += 1u; /* in the examples, an 8-pixel wide sprite is shifted across 16 pixels */

    if ((sctx.bytesperrow * t->sprite_height) > sizeof(bmp_tmp))
        return -1;

    sctx.fp = fopen(t->output_file,"wb");
    if (sctx.fp == NULL) return -1;

    fprintf(stderr,"Sprite sheet: %d sprites total (%d x %d).\n",
        sctx.sscols * sctx.ssrows,sctx.sscols,sctx.ssrows);
    fprintf(stderr,"Each sprite is %d x %d\n",
        t->sprite_width,t->sprite_height);

    if (saveout_write_prologue(t,&sctx))
        goto fioerr;

    if (t->preshift && t->preshift_inner == 1) {
        for (sctx.ssrow=0;sctx.ssrow < sctx.ssrows;sctx.ssrow++) {
            sctx.spritenum = sctx.ssrow * sctx.sscols;
            for (sctx.sscol=0;sctx.sscol < sctx.sscols;sctx.sscol++,sctx.spritenum++) {
                if (t->output_type == REC98_OUT_C) {
                    fprintf(sctx.fp,"%c",sctx.spritenum != 0 ? ',' : ' ');
                    fprintf(sctx.fp,"{/*preshift*/\n");
                }

                for (sctx.sspreshift=0;sctx.sspreshift < 8;sctx.sspreshift++) {
                    unsigned char *dbits = bmp_tmp; /* use bmp_tmp[], this is why the size check */
                    unsigned int y,b;

                    for (y=0;y < t->sprite_height;y++) {
                        unsigned int shif = 0;
                        unsigned int sr =
                            t->upsidedown ? (t->sprite_height - 1 - y) : y;
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

                if (t->output_type == REC98_OUT_C) {
                    fprintf(sctx.fp," }/*end preshift*/\n");
                }
            }
        }
    }
    else if (t->preshift && t->preshift_inner == 0) {
        for (sctx.sspreshift=0;sctx.sspreshift < 8;sctx.sspreshift++) {
            for (sctx.ssrow=0;sctx.ssrow < sctx.ssrows;sctx.ssrow++) {
                sctx.spritenum = sctx.ssrow * sctx.sscols;
                for (sctx.sscol=0;sctx.sscol < sctx.sscols;sctx.sscol++,sctx.spritenum++) {
                    unsigned char *dbits = bmp_tmp; /* use bmp_tmp[], this is why the size check */
                    unsigned int y,b;

                    for (y=0;y < t->sprite_height;y++) {
                        unsigned int shif = 0;
                        unsigned int sr =
                            t->upsidedown ? (t->sprite_height - 1 - y) : y;
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
                        t->upsidedown ? (t->sprite_height - 1 - y) : y;
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
    return 0;
fioerr:
    fclose(sctx.fp);
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
                else if (!strcmp(a,"bmp"))
                    tsk->output_type = REC98_OUT_BMP;
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

