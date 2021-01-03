
#include <ctype.h>
#include <string.h>

#include <bsx/opt.h>

#ifdef OPT_DEBUG
#include <stdio.h>
#endif

/* parser states */
enum {
	state_start = 0,
	state_slash,
	state_name,
	state_colon,
	state_value,
	state_error,
	state_finish,
};

/* option definitions */
int    opt_defc   = 0;
opt_t *opt_defv   = 0;

/* arguments to parse */
int    opt_argc   = 0;
char **opt_argv   = 0;

/* parser state */
int    opt_state  = 0;
int    opt_index  = 0;
int    opt_offset = 0;

opt_t    *opt_current = NULL;
unsigned  opt_nameidx = 0;
char      opt_name[64];
unsigned  opt_valueidx = 0;
char      opt_value[64];

int opt_start(int defc, opt_t *defv, int argc, char **argv) {
	opt_defc   = defc;
	opt_defv   = defv;
	opt_argc   = argc;
	opt_argv   = argv;
	opt_state  = state_start;
	opt_index  = 1;
	opt_offset = 0;
	return 0;
}

int opt_finish() {
	return opt_start(0,0,0,0);
}

static void opt_push_name(char chr) {
	opt_name[opt_nameidx++] = chr;
	opt_name[opt_nameidx] = 0;
}

/* state machine dispatch */
static void opt_state_start(char chr) {
	if(chr == 0) {
		opt_state = state_finish;
	} else if(chr == '/') {
		opt_push_name(chr);
		opt_state = state_slash;
	} else if (isgraph(chr)) {
		opt_state = state_value;
	} else {
		opt_state = state_error;
	}
}
static void opt_state_slash(char chr) {
	if(chr == '/') {
		opt_state = state_error;
	} else if(isgraph(chr)) {
		opt_push_name(chr);
		opt_state = state_name;
	} else {
		opt_state = state_error;
	}
}
static void opt_state_name(char chr) {
	if(chr == 0) {
		opt_state = state_start;
	} else if (chr == ':') {
		opt_state = state_colon;
	} else if (chr == '/') {
		opt_state = state_slash;
	} else if (isgraph(chr)) {
		opt_push_name(chr);
		opt_state = state_name;
	} else {
		opt_state = state_error;
	}
}
static void opt_state_colon(char chr) {
	if (chr == 0) {
		opt_state = state_value;
	} else if (chr == '/') {
		opt_state = state_error;
	} else if (isgraph(chr)) {
		opt_state = state_value;
	} else {
		opt_state = state_error;
	}
}
static void opt_state_value(char chr) {
	if(chr == 0) {
		opt_state = state_start;
	} else if (chr == '/') {
		opt_state = state_slash;
	} else if (isgraph(chr)) {
		opt_state = state_value;
	} else {
		opt_state = state_error;
	}
}

/* parse one argument character */
static int opt_parse_char(char chr) {
	int res = 0, old_state = opt_state, i;

	/* dispatch on previous state */
	switch(old_state) {
	case state_start:
		opt_state_start(chr);
		break;
	case state_slash:
		opt_state_slash(chr);
		break;
	case state_name:
		opt_state_name(chr);
		break;
	case state_colon:
		opt_state_colon(chr);
		break;
	case state_value:
		opt_state_value(chr);
		break;
	case state_finish:
		break;
	default: /* invalid state */
		return -1;
	}

	/* debug trace */
#ifdef OPT_DEBUG
	printf("   state %d -> %d char '%c' [%02x]\n",
		old_state, opt_state, chr, chr);
#endif

	/* errors */
	if(opt_state == state_error) {
		return -1;
	}

	if(opt_state != old_state) {
		/* reductions */
		if(old_state == state_name) {
			opt_t *def = NULL;
			for(i = 0; i < opt_defc; i++) {
				def = &opt_defv[i];
				if(def->def_flags & OPT_FLAG_CATEGORY) {
					continue;
				}
				if(strcmp(opt_name, def->def_name) == 0) {
#ifdef OPT_DEBUG
					printf("   option %d: %s\n", i, opt_name);
#endif
					opt_current = def;
					break;
				}
			}
			if(opt_current) {
				if(opt_current->def_flags&OPT_FLAG_VALUE) {
					/* requires value */
					return -1;
				} else {
					res = opt_current->def_code;
					if(opt_state != state_finish) {
						opt_state = state_start;
					}
				}
			} else {
				/* bad option */
				return -1;
			}
		}
		if(old_state == state_value) {
			if(opt_current) {
				res = opt_current->def_code;
				if(opt_state != state_finish) {
					opt_state = state_start;
				}
			} else {
				/* value without option */
				return -1;
			}
		}
	}

	/* return result */
	return res;
}

/* parse one argument string */
static int opt_parse_string(char *arg) {
	int res = 0, len = strlen(arg), i;

	/* debug trace */
#ifdef OPT_DEBUG
	printf("  string \"%s\"\n", arg + opt_offset);
#endif

	/* process each character */
	for(i = opt_offset; i <= len; i++) {
		res = opt_parse_char(arg[i]);
		if(res != 0) {
			break;
		}
	}

	/* save offset for restart */
	opt_offset = i;

	/* return result */
	return res;
}

int opt_parse(void) {
	int res = 0, i;

	/* debug trace */
#ifdef OPT_DEBUG
	printf(" parse idx %d off %d state %d\n",
		opt_index, opt_offset, opt_state);
#endif

	/* reset string buffers */
	opt_name[0] = 0;
	opt_nameidx = 0;
	opt_value[0] = 0;
	opt_valueidx = 0;

	/* process each string */
	for(i = opt_index; i < opt_argc; i++) {
		char *arg = opt_argv[i];
		res = opt_parse_string(arg);
		if(res != 0) {
			if(opt_offset == 0) {
				i++;
			}
			break;
		}
	}

	/* debug trace */
#ifdef OPT_DEBUG
	printf("  return %d\n", res);
#endif

	/* restore index for restart */
	opt_index = i;

	/* return result */
	return res;
}
