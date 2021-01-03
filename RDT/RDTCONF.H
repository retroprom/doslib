#ifndef DOSLIB_RDTCONF_H
#define DOSLIB_RDTCONF_H

/* Enable the status function */
#define RDT_CONFIG_STATUS 1

#if RDT_CONFIG_STATUS
/* Enable the report function */
//#define RDT_CONFIG_REPORT 1
#endif

#if RDT_CONFIG_REPORT
/* Count events */
#define RDT_CONFIG_COUNT_EVT 1
/* Count interrupts */
#define RDT_CONFIG_COUNT_INT 1
#endif

#endif
