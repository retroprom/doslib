#ifndef KRN_SDADEF_H
#define KRN_SDADEF_H

#pragma pack(push,1)
struct krn_sda {
	/*00*/ byte_t       sda_critical;
	/*01*/ byte_t       sda_indos;
	/*02*/ byte_t       sda_error_drive;
	/*03*/ byte_t       sda_error_locus;
	/*04*/ word_t       sda_error_code;
	/*06*/ byte_t       sda_error_action;
	/*07*/ byte_t       sda_error_class;
	/*08*/ byte_t far  *sda_error_esdi;
	/*0C*/ krn_dta_t    sda_current_dta;
	/*10*/ krn_psp_t    sda_current_psp;
	/*12*/ word_t       sda_saved_sp;
	/*14*/ word_t       sda_return_code;
	/*16*/ byte_t       sda_current_drive;
	/*17*/ byte_t       sda_extended_break;
};
#pragma pack(pop)

#endif
