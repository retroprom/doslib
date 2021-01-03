#ifndef KRN_KRNTYPE_H
#define KRN_KRNTYPE_H

#include <dos.h>

#include <bsx/types.h>

/* structures */
struct krn_dhd;
struct krn_ivr;
struct krn_mcb;
struct krn_psp;
struct krn_sda;

typedef struct krn_dhd krn_dhd_s;
typedef struct krn_ivr krn_ivr_s;
typedef struct krn_mcb krn_mcb_s;
typedef struct krn_psp krn_psp_s;
typedef struct krn_sda krn_sda_s;

typedef krn_dhd_s far * krn_dhd_ptr;
typedef krn_ivr_s far * krn_ivr_ptr;
typedef krn_mcb_s far * krn_mcb_ptr;
typedef krn_psp_s far * krn_psp_ptr;
typedef krn_sda_s far * krn_sda_ptr;

/* types of various handles */
typedef byte_t      krn_int_t;

typedef seg_t       krn_mcb_t;
typedef seg_t       krn_psp_t;

typedef byte_t far *krn_stk_t;
typedef byte_t far *krn_dta_t;

typedef struct krn_dhd far *krn_dhd_t;
typedef struct krn_ivr far *krn_ivr_t;
typedef struct krn_sda far *krn_sda_t;

/* structure of interrupt stack - should be in RTL */
struct IREGS {
	word_t bp,di,si;
	word_t ds,es;
	word_t dx,cx,bx,ax;
	word_t ip,cs,flags;
};

/* type for interrupt handler arguments */
typedef struct IREGS krn_intreg_t;

/* type for interrupt handlers */
typedef void interrupt (far *krn_intfun_t) (void);

/* type for interrupt saving */
typedef krn_intfun_t krn_intsav_t;

/* types for owner identification */
enum {
	krn_own_type_unknown = 0,
	krn_own_type_reserved,
	krn_own_type_free,
	krn_own_type_dos,
	krn_own_type_dhd,
	krn_own_type_psp,
};
/* structure for owner identification */
struct krn_own {
	byte_t own_type;
	char   own_name[13];
	union {
		krn_dhd_t own_dhd;
		krn_psp_t own_psp;
	} own_ref;
};
typedef struct krn_own krn_own_t;

#endif
