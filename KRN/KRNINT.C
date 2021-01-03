
#include <krn/krn.h>
#include <krn/dos.h>

byte_t krn_int_count = 0;

bool_t krn_int_check(krn_int_t ivn, krn_intfun_t handler) {
	return getvect(ivn) == handler ? TRUE : FALSE;
}

int krn_int_push(krn_int_t ivn, krn_intfun_t handler, krn_intsav_t *save) {
	krn_int_count++;
	*save = getvect(ivn);
	setvect(ivn, handler);
	return 0;
}

int krn_int_pop(krn_int_t ivn, krn_intfun_t handler, krn_intsav_t *save) {
	if(!krn_int_count) {
		return 1;
	}
	if(handler != getvect(ivn)) {
		return 1;
	}
	setvect(ivn, *save);
	*save = 0;
	krn_int_count--;
	return 0;
}
