#ifndef DOSLIB_HRNREG_H
#define DOSLIB_HRNREG_H

#include <bsx/types.h>

/************************************************** I/O REGISTERS        */

/* These registers are directly accessible in I/O space.
 *
 * Note that most registers can be accessed only by
 * using the HIR and HDR registers for indirection.
 *
 * This design decision prevents cluttering the
 * address space and makes the device more compatible.
 */

/* Internal register access */
#define HORNET_PORT_HIR     0x22
#define HORNET_PORT_HDR     0x23

/* CPU power control */
#define HORNET_PORT_CPUPWR  0x28
#define HORNET_CPUPWR_ENTER_IDLE 0x02
#define HORNET_CPUPWR_ENTER_DOWN 0x01

/* CPU stepping */
#define HORNET_PORT_STEPPING 0x2C
#define HORNET_STEPPING_MASK  0x0F
#define HORNET_STEPPING_SHIFT 0

/************************************************** MEMORY MAP           */

/* This is the static memory map of the Hornet chip.
 *
 * There are some static mappings for the ROM as well
 * as a large window for the system RAM.
 *
 * 192k of upper memory are banked in blocks of 64k and 16k
 * and can be mapped to any of the 7 chip selects, with
 * alignment being equal to size.
 *
 * The display controller has two additional 64k windows
 * outside the main address space that can be mapped
 * at 16k granularity. One of them is used for the
 * display memory, another for font memory.
 */

/* Up to 640k from NRAS0+1 */
#define HORNET_BASE_NRAS   0x00000
/* 64k of NRCE@0x10000 - ROM */
#define HORNET_BASE_NRCE0  0xA0000
/* 16k of NRCE@0x17F00 - ROM */
#define HORNET_BASE_NRCE1  0xB4000
/* 16k of NRCE@0x13F00 - ROM */
#define HORNET_BASE_NRCE2  0xBC000
/* 64k of banking window C */
#define HORNET_BASE_BANKC  0xC0000
/* 16k of banking window D0 */
#define HORNET_BASE_BANKD0 0xD0000
/* 16k of banking window D1 */
#define HORNET_BASE_BANKD1 0xD4000
/* 16k of banking window D2 */
#define HORNET_BASE_BANKD2 0xD8000
/* 16k of banking window D3 */
#define HORNET_BASE_BANKD3 0xDC000
/* 16k of banking window E0 */
#define HORNET_BASE_BANKE0 0xE0000
/* 16k of banking window E1 */
#define HORNET_BASE_BANKE1 0xE4000
/* 16k of banking window E2 */
#define HORNET_BASE_BANKE2 0xE8000
/* 16k of banking window E3 */
#define HORNET_BASE_BANKE3 0xEC000
/* 64k of NRCE@0x00000 - ROM */
#define HORNET_BASE_NRCE3  0xF0000

/************************************************** MEM WAITSTATE REGS   */

/* Waitstate configuration regs */
#define HORNET_REG_MEM_WAIT0 0x80
#define HORNET_REG_MEM_WAIT1 0x81
#define HORNET_REG_MEM_WAIT2 0x82
#define HORNET_REG_MEM_WAIT3 0x83

/************************************************** MEM MAIN WINDOW REGS */

/* Main window size regs
 *
 * These can be used to split the main RAM window
 * into two parts for NRAS0 and NRAS1 in steps of 128k.
 *
 * WSZ_NRAS0  is the size of the NRAS0 region
 * WSZ_NRAS10 is the size of both regions together
 *
 * The chip will internally compute the boundary and
 * direct access to corresponding chip selects.
 *
 * On chip reset both of these will be 1 so that
 * a 128k window will be open towards NRAS0.
 */
#define HORNET_REG_MEM_WSZ_NRAS0  0x84
#define HORNET_REG_MEM_WSZ_NRAS10 0x85

/************************************************** MEM WRITE ENABLE REGS*/

/* Write-enable regs
 *
 * These bits enable writes through their respective chip selects.
 *
 * Note that this will restrict only memory writes, not I/O writes.
 */
#define HORNET_REG_MEM_WEN 0x86
#define HORNET_MEM_WEN_NCS1  0x40
#define HORNET_MEM_WEN_NCS0  0x20
#define HORNET_MEM_WEN_NRAS3 0x10
#define HORNET_MEM_WEN_NRAS2 0x08
#define HORNET_MEM_WEN_NRAS1 0x04
#define HORNET_MEM_WEN_NRAS0 0x02
#define HORNET_MEM_WEN_NRCE  0x01

/************************************************** MEM MAIN WINDOW WP   */

/* Main window write-protect boundary
 *
 * This allows setting up a write-protected main window
 * region at the end of the main window, below 0xA0000.
 *
 * The register specifies the boundary, in 4k counts,
 * above which memory is write-protected.
 *
 * It should never be set to something greater than 0xA0.
 */
#define HORNET_REG_MEM_WPB 0x87

/************************************************** MEM BANKING REGS     */

/* Base address
 *
 * This can be used to compute the register address for each bank.
 *
 * There is a total of 11 banks, 8 of 16k and 3 of 64k each.
 *
 * Corresponding to each there are two registers for a total of 22.
 */
#define HORNET_REG_BANK_BASE  0x88

/* Address computation helpers */
#define HORNET_REG_BANK_xx_R0(bank) \
	(HORNET_REG_BANK_BASE + (bank * 2) + 0)
#define HORNET_REG_BANK_xx_R1(bank) \
	(HORNET_REG_BANK_BASE + (bank * 2) + 1)

/* Banking control - 16k windows */
#define HORNET_REG_BANK_D0_R0 0x88
#define HORNET_REG_BANK_D0_R1 0x89
#define HORNET_REG_BANK_D1_R0 0x8A
#define HORNET_REG_BANK_D1_R1 0x8B
#define HORNET_REG_BANK_D2_R0 0x8C
#define HORNET_REG_BANK_D2_R1 0x8D
#define HORNET_REG_BANK_D3_R0 0x8E
#define HORNET_REG_BANK_D3_R1 0x8F
#define HORNET_REG_BANK_E0_R0 0x90
#define HORNET_REG_BANK_E0_R1 0x91
#define HORNET_REG_BANK_E1_R0 0x92
#define HORNET_REG_BANK_E1_R1 0x93
#define HORNET_REG_BANK_E2_R0 0x94
#define HORNET_REG_BANK_E2_R1 0x95
#define HORNET_REG_BANK_E3_R0 0x96
#define HORNET_REG_BANK_E3_R1 0x97
/* Banking control - 64k window */
#define HORNET_REG_BANK_C_R0  0x98
#define HORNET_REG_BANK_C_R1  0x99
/* Banking control - 64k display memory window */
#define HORNET_REG_BANK_DM_R0 0x9A
#define HORNET_REG_BANK_DM_R1 0x9B
/* Banking control - 64k font memory window */
#define HORNET_REG_BANK_FM_R0 0x9C
#define HORNET_REG_BANK_FM_R1 0x9D

/* Banking control - common definitions
 *
 * Physical device addresses are 26 bits, with
 * some devices only decoding 25 bits.
 *
 * R0 always represents the upper 8 bits of the device address.
 * R1 contains either 4 (Dx and Ex, DM and FM) or 2 bits (C) at its left.
 * R1 for the C bank contains an attribute memory flag at bit 4.
 * R1 also contains the chipselect (bits 2:0) and an enable bit at bit 3.
 * R1 has no enable bit or attribute memory flag for DM and FM banks.
 * R1 does not contain the attribute memory flag in banks Dx and Ex,
 *    for those see HORNET_REG_MEM_AT.
 */
#define HORNET_BANK_C_R1_ATTRMEM    0x10
#define HORNET_BANK_xx_R1_ENABLE    0x08
#define HORNET_BANK_xx_R1_CS_MASK   0x07
#define HORNET_BANK_xx_R1_CS_SHIFT  0

/* Banking control - chip select definitions
 */
#define HORNET_BANK_xx_CS_NCS1    0x06
#define HORNET_BANK_xx_CS_NCS0    0x05
#define HORNET_BANK_xx_CS_NRAS3   0x04
#define HORNET_BANK_xx_CS_NRAS2   0x03
#define HORNET_BANK_xx_CS_NRAS1   0x02
#define HORNET_BANK_xx_CS_NRAS0   0x01
#define HORNET_BANK_xx_CS_NRCE    0x00

/************************************************** MEM ATTR SELECT REGS */

/* Attribute memory select
 *
 * Setting bit to 1 switches the respective bank to ATTR access.
 *
 * This is for use with PCMCIA cards, which use it for Plug-and-Play.
 *
 * The C bank is not included here but has its own
 * configuration bit in its R1 banking register.
 */
#define HORNET_REG_MEM_ATTRMEM 0x9E
#define HORNET_MEM_ATTRMEM_E3  0x80
#define HORNET_MEM_ATTRMEM_E2  0x40
#define HORNET_MEM_ATTRMEM_E1  0x20
#define HORNET_MEM_ATTRMEM_E0  0x10
#define HORNET_MEM_ATTRMEM_D3  0x08
#define HORNET_MEM_ATTRMEM_D2  0x04
#define HORNET_MEM_ATTRMEM_D1  0x02
#define HORNET_MEM_ATTRMEM_D0  0x01

/************************************************** IO WINDOWS           */

/* IO Window configuration regs */
#define HORNET_REG_MEM_W0_BASEH   0xA0
#define HORNET_REG_MEM_W0_BASEL   0xA1
#define HORNET_REG_MEM_W0_SIZE    0xA2
#define HORNET_REG_MEM_W0_CONTROL 0xA3
#define HORNET_REG_MEM_W1_BASEH   0xA4
#define HORNET_REG_MEM_W1_BASEL   0xA5
#define HORNET_REG_MEM_W1_SIZE    0xA6
#define HORNET_REG_MEM_W1_CONTROL 0xA7
/* values for IOM Wx CONTROL registers */
#define HORNET_MEM_Wx_CONTROL_NCS0    0x05
#define HORNET_MEM_Wx_CONTROL_NCS1    0x06
#define HORNET_MEM_Wx_CONTROL_ENABLE  0x08
#define HORNET_MEM_Wx_CONTROL_OVERLAP 0x10

#endif
