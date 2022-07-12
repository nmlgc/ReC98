
#ifndef _BMP2ARRL_H
#define _BMP2ARRL_H

#include <stdio.h>

/* what to emit */
enum rec98_bmp2arr_output_type {
    REC98_OUT_NONE=0,
    REC98_OUT_C,
    REC98_OUT_ASM,
    REC98_OUT_BIN,
    REC98_OUT_BMP,

    BMP2ARR_OUTPUT_TYPE_COUNT,
};

/* conversion flags */

/* Whether to generate preshifted variations or not. Makes the bitmap one byte wider */
#define PRESHIFT_OUTER (1 << 0) /* [PRESHIFT][number][height] */
#define PRESHIFT_INNER (1 << 1) /* [number][PRESHIFT][height] */

#define UPSIDEDOWN     (1 << 2) /* output upside down  (ref. game 3 score bitmap) */
#define DEBUG_BMP_OUT  (1 << 3) /* output file is bitmap read in (debugging) */

#define QUIET          (1 << 4) /* don't print debug messages on stderr */

/* only used internally */
#define PRESHIFT_ANY (PRESHIFT_OUTER | PRESHIFT_INNER)

struct saveout_ctx {
    unsigned int            sscols,ssrows,spritenum,bytesperrow,sscol,ssrow,sspreshift;
    FILE*                   fp; /* for that nice fprintf formatting if needed */
};

/* potential errors */
enum bmp2arr_error {
    SUCCESS=0,
    INTERNAL_ERROR_ERROR,
    INTERNAL_NULLPTR,
    INTERNAL_ARRAY_TOO_SMALL,

    EXPECTED_ARGUMENT,
    EXPECTED_SWITCH,

    MISSING_INPUT_BMP,
    MISSING_OUTPUT_FILE,
    MISSING_OUTPUT_TYPE,
    MISSING_SPRITE_WIDTH,
    MISSING_SPRITE_HEIGHT,

    INVALID_SWITCH,
    INVALID_OUTPUT_TYPE,
    INVALID_PRESHIFT,
    INVALID_PRESHIFT_WIDTH,
    INVALID_SPRITE_WIDTH,
    INVALID_SPRITE_HEIGHT,

    INPUT_OPEN_ERROR,
    INPUT_OUT_OF_MEMORY,
    INPUT_INVALID,
    INPUT_TOO_SMALL,
    INPUT_COLOR_AT,
    INPUT_ALREADY_LOADED,

    OUTPUT_NO_INPUT_LOADED,
    OUTPUT_OPEN_ERROR,
    OUTPUT_IO_ERROR,

    BMP2ARR_ERROR_COUNT,
};

/* extended error information */
struct bmp2arr_error_info {
    enum bmp2arr_error type;
    const char*        param_str;
    int                param_int[2];
};

/* the task at hand */
struct rec98_bmp2arr_task {
    char*           input_bmp;
    char*           output_symname;     /* what to name the symbol */
    char*           output_file;
    unsigned char   output_type;
    unsigned char   sprite_width;       /* 8, or 16 [https://github.com/nmlgc/ReC98/issues/8 ref. dots8_t, dots16_t] */
    unsigned char   sprite_height;      /* according to list, either 4, 8, or 16 */
    unsigned char   flags;              /* see flag list above */

    /* error of the last operation */
    struct bmp2arr_error_info err;

    /* working state */
    unsigned int    bmp_width;          /* width of bmp */
    unsigned int    bmp_height;         /* height of bmp */
    unsigned int    bmp_stride;         /* bytes per scanline */
    unsigned char*  bmp;                /* bitmap in memory (NTS: All examples listed can easily fit in 64KB or less) */
};

void cstr_free(char **s);
void cstr_set(char **s,const char *n);
void rec98_bmp2arr_task_free_bmp(struct rec98_bmp2arr_task *t);
enum bmp2arr_error rec98_bmp2arr_task_init(struct rec98_bmp2arr_task *t);
enum bmp2arr_error rec98_bmp2arr_task_free(struct rec98_bmp2arr_task *t);
enum bmp2arr_error rec98_bmp2arr_save_debug_bmp_out(struct rec98_bmp2arr_task *t);
enum bmp2arr_error rec98_bmp2arr_save_output(struct rec98_bmp2arr_task *t);
enum bmp2arr_error rec98_bmp2arr_load_bitmap(struct rec98_bmp2arr_task *t);

enum bmp2arr_error bmp2arr_error_set(struct rec98_bmp2arr_task *t, enum bmp2arr_error type);
enum bmp2arr_error bmp2arr_error_set_str(struct rec98_bmp2arr_task *t, enum bmp2arr_error type, const char *param);
enum bmp2arr_error bmp2arr_error_set_int_int(struct rec98_bmp2arr_task *t, enum bmp2arr_error type, int param_1, int param_2);
enum bmp2arr_error bmp2arr_error_report(struct bmp2arr_error_info *err);

#endif /* _BMP2ARRL_H */

