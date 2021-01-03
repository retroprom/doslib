#ifndef DOSLIB_OPT_H
#define DOSLIB_OPT_H

/* #define OPT_DEBUG */

/* option definitions */
#define OPT_FLAG_NONE      0x00
#define OPT_FLAG_MANDATORY 0x01
#define OPT_FLAG_VALUE     0x02
#define OPT_FLAG_NEGATE    0x04
#define OPT_FLAG_CATEGORY  0x08

typedef struct opt {
        int   def_code;
        int   def_flags;
        char *def_name;
        char *def_help;
} opt_t;

/* optparse.c */
extern int    opt_defc;
extern opt_t *opt_defv;

extern opt_t *opt_current;
extern char   opt_name[64];
extern char   opt_value[64];

extern int opt_start(int defc, opt_t *defv, int argc, char **argv);
extern int opt_parse(void);
extern int opt_finish(void);

/* optusage.c */
extern int opt_usage(const char *banner, const char *program);

#endif
