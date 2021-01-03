
#include <string.h>

#include <krn/krn.h>
#include <krn/dos.h>

void krn_mcb_get_owner(krn_mcb_t m, krn_own_t *o) {
	krn_mcb_ptr mp = KRN_MCB_PTR(m);
	word_t p = mp->mcb_psp;
	_fmemset(o, 0, sizeof(krn_own_t));
	if(p == 0) {
		o->own_type = krn_own_type_free;
	} else if(p == 8) {
		o->own_type = krn_own_type_dos;
	} else {
		o->own_type = krn_own_type_psp;
		o->own_ref.own_psp = p;
	}
}
