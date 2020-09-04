
#if defined(REC98_PROJECT)
# include "platform.h" /* see also [https://github.com/nmlgc/ReC98/issues/8] */
#elif defined(_MSC_VER)/*Microsoft C++*/ || defined(__BORLANDC__) || defined(__TURBOC__)
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
#else
# include <stdint.h>
#endif
#if defined(_MSC_VER)/*Microsoft C++*/ || defined(__BORLANDC__) || defined(__TURBOC__)
# include <io.h>
#else
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
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

#include "bmp2arrl.h"

/* O_BINARY is needed for MS-DOS, Windows, etc.
 * Linux, Mac OS X, etc. do not have O_BINARY */
#ifndef O_BINARY
#define O_BINARY (0)
#endif

static enum bmp2arr_error parse_argv(struct rec98_bmp2arr_task *tsk,int argc,char **argv) {
    char *a;
    int i;

    for (i=1;i < argc;) {
        a = argv[i++];

        if (*a == '-') {
            do { a++; } while (*a == '-');

            if (!strcmp(a,"i")) {
                a = argv[i++];
                if (a == NULL)
                    return bmp2arr_error_set_str(tsk, EXPECTED_ARGUMENT, "i");
                cstr_set(&tsk->input_bmp,a);
            }
            else if (!strcmp(a,"o")) {
                a = argv[i++];
                if (a == NULL)
                    return bmp2arr_error_set_str(tsk, EXPECTED_ARGUMENT, "o");
                cstr_set(&tsk->output_file,a);
            }
            else if (!strcmp(a,"sym")) {
                a = argv[i++];
                if (a == NULL)
                    return bmp2arr_error_set_str(tsk, EXPECTED_ARGUMENT, "sym");
                cstr_set(&tsk->output_symname,a);
            }
            else if (!strcmp(a,"of")) {
                a = argv[i++];
                if (a == NULL)
                    return bmp2arr_error_set_str(tsk, EXPECTED_ARGUMENT, "of");

                if (!strcmp(a,"asm"))
                    tsk->output_type = REC98_OUT_ASM;
                else if (!strcmp(a,"bin"))
                    tsk->output_type = REC98_OUT_BIN;
                else if (!strcmp(a,"bmp"))
                    tsk->output_type = REC98_OUT_BMP;
                else if (!strcmp(a,"c"))
                    tsk->output_type = REC98_OUT_C;
                else
                    return bmp2arr_error_set(tsk, INVALID_OUTPUT_TYPE);
            }
            else if (!strcmp(a,"sw")) {
                a = argv[i++];
                if (a == NULL)
                    return bmp2arr_error_set_str(tsk, EXPECTED_ARGUMENT, "sw");

                tsk->sprite_width = atoi(a);
                if (!(tsk->sprite_width == 8 || tsk->sprite_width == 16))
                    return bmp2arr_error_set(tsk, INVALID_SPRITE_WIDTH);
            }
            else if (!strcmp(a,"sh")) {
                a = argv[i++];
                if (a == NULL)
                    return bmp2arr_error_set_str(tsk, EXPECTED_ARGUMENT, "sh");

                tsk->sprite_height = atoi(a);
                if (tsk->sprite_height < 1 || tsk->sprite_height > 32)
                    return bmp2arr_error_set(tsk, INVALID_SPRITE_HEIGHT);
            }
            else if (!strcmp(a,"u")) {
                tsk->flags |= UPSIDEDOWN;
            }
            else if (!strcmp(a,"dbg-bmp")) {
                tsk->flags |= DEBUG_BMP_OUT;
            }
            else if (!strcmp(a,"q")) {
                tsk->flags |= QUIET;
            }
            else if (!strcmp(a,"pshf")) {
                a = argv[i++];
                if (a == NULL)
                    return bmp2arr_error_set_str(tsk, EXPECTED_ARGUMENT, "pshf");

                if (!strcmp(a,"inner"))
                    tsk->flags |= PRESHIFT_INNER;
                else if (!strcmp(a,"outer"))
                    tsk->flags |= PRESHIFT_OUTER;
                else
                    return bmp2arr_error_set(tsk, INVALID_PRESHIFT);
            }
            else {
                return bmp2arr_error_set_str(tsk, INVALID_SWITCH, a);
            }
        }
        else {
            return bmp2arr_error_set_str(tsk, EXPECTED_SWITCH, a);
        }
    }

    /* required fields */
    if (tsk->input_bmp == NULL)
        return bmp2arr_error_set(tsk, MISSING_INPUT_BMP);

    if (tsk->output_file == NULL)
        return bmp2arr_error_set(tsk, MISSING_OUTPUT_FILE);

    if (tsk->output_type == REC98_OUT_NONE)
        return bmp2arr_error_set(tsk, MISSING_OUTPUT_TYPE);

    if (tsk->sprite_width == 0)
        return bmp2arr_error_set(tsk, MISSING_SPRITE_WIDTH);

    if (tsk->sprite_height == 0)
        return bmp2arr_error_set(tsk, MISSING_SPRITE_HEIGHT);

    return bmp2arr_error_set(tsk, SUCCESS);
}

int main(int argc,char **argv) {
    struct rec98_bmp2arr_task tsk;

    if (rec98_bmp2arr_task_init(&tsk))
        return 1;

    if (parse_argv(&tsk,argc,argv))
        return bmp2arr_error_report(&tsk.err);

    if (rec98_bmp2arr_load_bitmap(&tsk))
        return bmp2arr_error_report(&tsk.err);

    if (tsk.flags & DEBUG_BMP_OUT) {
        if (rec98_bmp2arr_save_debug_bmp_out(&tsk))
            return bmp2arr_error_report(&tsk.err);

        return 0;
    }

    if (rec98_bmp2arr_save_output(&tsk))
        return bmp2arr_error_report(&tsk.err);

    rec98_bmp2arr_task_free(&tsk);
    return 0;
}

