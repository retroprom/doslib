
#include <string.h>
#include <stdio.h>

#include <bsx/opt.h>

int opt_usage(const char *banner, const char *program) {
	int res, i;

	/* iterate all option definitions */
	for(i = 0; i < opt_defc; i++) {
		opt_t *def = opt_defv + i;
		int flags = def->def_flags;
		if(flags & OPT_FLAG_CATEGORY) {
			/* categories */
			printf("\n %s - %s\n", def->def_name, def->def_help);
		} else {
			/* regular options */
			char l = '[', r = ']';
			if(flags & OPT_FLAG_MANDATORY) {
				l = r = ' ';
			}
			printf("  %c%s%c\t %s\n",
				l, def->def_name, r, def->def_help);
		}
	}

	return 0;
}
