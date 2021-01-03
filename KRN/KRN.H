#ifndef KRN_KRN_H
#define KRN_KRN_H

#include <krn/krntype.h>

/* definitions */
#define KRN_CRITICAL (krn_sda->sda_critical)
#define KRN_INDOS    (krn_sda->sda_indos)

/* vars.c */
extern byte_t    krn_ver_maj;
extern byte_t    krn_ver_min;
extern byte_t    krn_ver_oem;
extern krn_ivr_t krn_ivr;
extern krn_sda_t krn_sda;

/* init.c */
extern int krn_init(void);

/* idle.c */
extern void krn_idle(void);

/* umbl.c */
extern bool_t krn_umbl_get(void);
extern int    krn_umbl_set(bool_t link);

/* dta.c */
extern krn_dta_t krn_dta_get(void);
extern void      krn_dta_set(krn_dta_t d);

/* int.c */
extern byte_t krn_int_count;
extern bool_t krn_int_check(krn_int_t ivn, krn_intfun_t handler);
extern int    krn_int_push (krn_int_t ivn,
			krn_intfun_t handler,
			krn_intsav_t *save);
extern int    krn_int_pop  (krn_int_t ivn,
			krn_intfun_t handler,
			krn_intsav_t *save);

/* dhditer.c */
extern krn_dhd_t krn_dhd_get_first(void);
extern krn_dhd_t krn_dhd_get_next(krn_dhd_t d);

/* pspiter.c */
extern krn_psp_t  krn_psp_get(void);
extern void       krn_psp_set(krn_psp_t p);
extern krn_psp_t  krn_psp_get_parent(krn_psp_t p);

/* mcbiter.c */
extern krn_mcb_t krn_mcb_get_first(void);
extern krn_mcb_t krn_mcb_get_next(krn_mcb_t m);
/* mcbgetp.c */
extern krn_psp_t krn_mcb_get_psp(krn_mcb_t m);
/* mcbgeto.c */
extern void      krn_mcb_get_owner(krn_mcb_t m, krn_own_t *o);
/* mcbfind.c */
extern krn_mcb_t krn_mcb_find_seg(word_t seg);

#endif
