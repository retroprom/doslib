#ifndef DOSLIB_KRN_PSPDEF_H
#define DOSLIB_KRN_PSPDEF_H

#define KRN_PSP_PTR(psp) \
	((krn_psp_ptr)MK_FP(psp,0))

#define KRN_PSP_IS_TOP(psp) \
	(KRN_PSP_PTR(psp)->psp_parent == psp)

#pragma pack(push,1)
struct krn_psp {
	/*00*/ word_t     psp_cpmexit;
	/*04*/ word_t     psp_endseg;
	/*08*/ byte_t    _psp_reserved1;
	/*09*/ byte_t     psp_cpmcall[5];
	/*0A*/ dword_t    psp_prev_int22;
	/*0E*/ dword_t    psp_prev_int23;
	/*12*/ dword_t    psp_prev_int24;
	/*16*/ krn_psp_t  psp_parent;
	/*18*/ byte_t    _psp_jft[20];
	/*2C*/ word_t     psp_envseg;
	/*2E*/ dword_t   _psp_callstack;
	/*32*/ word_t    _psp_jftsize;
	/*34*/ dword_t   _psp_jftptr;
	/*38*/ dword_t    psp_prev_pspptr;
	/*3C*/ byte_t    _psp_reserved2[4];
	/*40*/ word_t     psp_dosver;
	/*42*/ byte_t    _psp_reserved3[14];
	/*50*/ byte_t     psp_doscall[3];
	/*53*/ byte_t    _psp_reserved4[2];
	/*55*/ byte_t    _psp_reserved5[7];
	/*5C*/ byte_t    _psp_fcb1[16];
	/*6C*/ byte_t    _psp_fcb2[16];
	/*7C*/ byte_t    _psp_reserved6[4];
	/*80*/ byte_t     psp_arglen;
	/*81*/ byte_t     psp_args[127];
};
#pragma pack(pop)

#endif
