
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

                if (!strcmp(a,"asm"))
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

