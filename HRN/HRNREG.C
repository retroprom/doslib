
#include <dos.h>

#include <hrn/hrn.h>
#include <hrn/hrnreg.h>

byte_t hrn_reg_getb(byte_t index) {
	outportb(HORNET_PORT_HIR, index);
	return inportb(HORNET_PORT_HDR);
}

void hrn_reg_setb(byte_t index, byte_t value) {
	outportb(HORNET_PORT_HIR, index);
	outportb(HORNET_PORT_HDR, value);
}
