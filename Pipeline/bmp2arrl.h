
#ifndef _BMP2ARRL_H
#define _BMP2ARRL_H

#include <stdio.h>

/* what to emit */
enum rec98_bmp2arr_output_type {
    REC98_OUT_C=0,
    REC98_OUT_ASM,
    REC98_OUT_BIN,
    REC98_OUT_BMP
};

struct saveout_ctx {
    unsigned int            sscols,ssrows,spritenum,bytesperrow,sscol,ssrow,sspreshift;
    FILE*                   fp; /* for that nice fprintf formatting if needed */
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

void cstr_free(char **s);
void cstr_set(char **s,const char *n);
void rec98_bmp2arr_task_free_bmp(struct rec98_bmp2arr_task *t);
int rec98_bmp2arr_task_init(struct rec98_bmp2arr_task *t);
int rec98_bmp2arr_task_free(struct rec98_bmp2arr_task *t);
int rec98_bmp2arr_save_debug_bmp_out(struct rec98_bmp2arr_task *t);
int rec98_bmp2arr_save_output(struct rec98_bmp2arr_task *t);
int rec98_bmp2arr_load_bitmap(struct rec98_bmp2arr_task *t);

#endif /* _BMP2ARRL_H */

