#ifndef DOSLIB_KRN_REQS_H
#define DOSLIB_KRN_REQS_H

#define KRN_AH_SET_DTA           0x1A

#define KRN_AH_GET_DTA           0x2F

#define KRN_AH_GET_VERSION       0x30
#define KRN_AX_GET_VERSION_OEM   0x3000
#define KRN_AX_GET_VERSION_FLAG  0x3001

#define KRN_AX_GET_BOOT_DRIVE    0x3305
#define KRN_AX_GET_TRUE_VERSION  0x3306

#define KRN_AH_GET_INDOS         0x34

#define KRN_AH_SET_PSP           0x50
#define KRN_AH_GET_PSP           0x51

#define KRN_AH_GET_IVR           0x52

#define KRN_AH_XLT_BPB_TO_DPB    0x53

#define KRN_AH_GET_VERIFY_FLAG   0x54

#define KRN_AH_CREATE_CHILD_PSP  0x55

#define KRN_AX_GET_ALLOC_STRAT   0x5800
#define KRN_AX_SET_ALLOC_STRAT   0x5801

#define KRN_AX_GET_UMB_LINK      0x5802
#define KRN_AX_SET_UMB_LINK      0x5803

#define KRN_AX_GET_SDA           0x5D06

#define KRN_AX_GET_GLOBAL_CP     0x6601
#define KRN_AX_SET_GLOBAL_CP     0x6602

#define KRN_AH_SET_HANDLE_COUNT  0x67

#endif
