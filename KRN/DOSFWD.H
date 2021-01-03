#ifndef KRN_DOSFWD_H
#define KRN_DOSFWD_H

/* forward declarations */
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

#endif
