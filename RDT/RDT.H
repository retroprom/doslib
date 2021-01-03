#ifndef RDT_RDT_H
#define RDT_RDT_H

#include <bsx/types.h>

#include <krn/krn.h>

/* built-in TSR functions */
#define RDT_FUN_DETECT   0x00
#define RDT_FUN_UNLOAD   0x01
#define RDT_FUN_START    0x02
#define RDT_FUN_REPORT   0x03
#define RDT_FUN_FAST_FIRST 0x10
#define RDT_FUN_FAST_LAST  0x3F
#define RDT_FUN_CALL_FIRST 0x40
#define RDT_FUN_CALL_LAST  0x7F

/* activation causes */
typedef enum {
	RDT_CAUSE_NONE = 0,
	RDT_CAUSE_REQUEST = 1,
	RDT_CAUSE_HOTKEY = 2,
	RDT_CAUSE_TIMER = 3,
	RDT_CAUSE_BREAK = 4,
} rdt_cause_t;

/* type for resident main function */
typedef int (*rdt_main_t)(void);
/* type for resident call handler */
typedef int (*rdt_call_t)(byte_t func, krn_intreg_t *regs);

/* RDT info structure
 *
 * Specifies the signature of a TSR.
 */
struct rdt_info {
	/* interrupt to be used */
	krn_int_t serv_interrupt;
	/* function code to be used (AH) */
	byte_t    serv_function;
	/* service name for identification */
	char      serv_name[9];
};
typedef struct rdt_info rdt_info_t;

/* RDT state structure
 *
 * Encapsulates state of a TSR.
 */
struct rdt_state {
	/* signature */
	const rdt_info_t *rs_info;
	/* resident main function */
	rdt_main_t  rs_main;
	/* handler for fast calls */
	rdt_call_t  rs_fast;
	/* handler for slow calls */
	rdt_call_t  rs_call;
};
typedef struct rdt_state rdt_state_t;

/* global TSR state */
extern rdt_state_t rdt_state;

/* Management: check if TSR is present */
extern int rdt_present(const rdt_info_t *info);
/* Management: install current process as TSR */
extern int rdt_install(const rdt_info_t *info);
/* Management: uninstall TSR if present */
extern int rdt_uninstall(const rdt_info_t *info);

/* Calls: generic call */
extern int rdt_call(
		const rdt_info_t *info,
		byte_t subfunc,
		word_t *w1,
		word_t *w2,
		word_t *w3,
		byte_t far *p1,
		byte_t far *p2);

/* Calls: run TSR main function */
extern int rdt_start(const rdt_info_t *info);
/* Calls: run TSR status function */
extern int rdt_status(const rdt_info_t *info);

#endif
