#ifndef DOSLIB_EMSDEFS_H
#define DOSLIB_EMSDEFS_H

#define EMS_INT 0x67

#define EMS_DRIVER "EMMXXXX0"

#define EMS_MIN_VERSION 0x32

#define EMS_REQ_GET_MSTAT  0x40
#define EMS_REQ_GET_PFSEG  0x41
#define EMS_REQ_GET_NPAGES 0x42
#define EMS_REQ_ALLOCATE   0x43
#define EMS_REQ_MAP        0x44
#define EMS_REQ_RELEASE    0x45
#define EMS_REQ_VERSION    0x46
#define EMS_REQ_SAVE_MCTX  0x47
#define EMS_REQ_RSTR_MCTX  0x48
#define EMS_REQ_GET_NHDLS  0x4b
#define EMS_REQ_GET_HPAGE  0x4c
#define EMS_REQ_GET_APAGE  0x4d
#define EMS_REQ_PAGEMAP    0x4e

#endif
