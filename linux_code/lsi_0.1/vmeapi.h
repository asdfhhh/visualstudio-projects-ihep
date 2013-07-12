/*******************************************************************************
*
* Filename: 	vmeapi.h
* 
* Description:	Windows VME driver API Header file.
*
* $Revision: 1.1 $
*
* $Date: 2009/01/12 10:00:49 $
*
* $Source: z:\\cvsroot/WinBSP/VME/WINVME/src/winvmeapi/vmeapi.h,v $
*
* Copyright 2007-2008 Concurrent Technologies.
*
*******************************************************************************/

#ifndef _WINVME_DRIVER_H
#define _WINVME_DRIVER_H

/* ERROR Codes                                                   */
/* Note: Failure conditions detected by the API functions return */
/*       an error code value less than zero e.g. (-EPERM)        */
#define	ESUCCESS	(0)		/* Operation successful              */
#define	EPERM		(1)		/* Operation not permitted           */
#define	ENOENT		(2)		/* No such file or directory         */
#define	EIO			(5)		/* I/O error                         */
#define	ENOMEM		(12)	/* Out of memory                     */
#define	EFAULT		(14)	/* Bad address                       */
#define	EBUSY		(16)	/* Device or resource busy           */
#define	ENODEV		(19)	/* No such device                    */
#define	EINVAL		(22)	/* Invalid argument                  */
#define	ENOSYS		(38)	/* Function not supported            */
#define	ETIME		(62)	/* Timer expired                     */
#define	EUSERS		(87)	/* Too many users                    */


#define MAX_DEV_USERS		8		/* Max. number of users per device file */
#define VERSION_INFO_LEN	120		/* Max. length of Version string        */
#define BOARD_INFO_LEN		12		/* Max. length of Board name string     */

/* DMA Constants */
#define EN_DMA_READ    0
#define EN_DMA_WRITE   1

/* VME bus constants */
#define EN_VME_D8 		0x0
#define EN_VME_D16 		0x1
#define EN_VME_D32 		0x2
#define EN_VME_D64 		0x3
#define EN_VME_A16		0x0
#define EN_VME_A24 		0x1
#define EN_VME_A32 		0x2
#define EN_VME_A64		0x4
#define EN_VME_CRCSR	        0x5
#define EN_VME_USER1_AM_UNV     0x6 /* User 1 AM for Universe */
#define EN_VME_USER2_AM_UNV     0x7	/* User 2 AM for Universe */
#define EN_VME_USER1_AM_TSI 	0x8	/* User 1 AM for Tsi148   */
#define EN_VME_USER2_AM_TSI 	0x9	/* User 2 AM for Tsi148   */
#define EN_VME_USER3_AM_TSI 	0xa	/* User 3 AM for Tsi148   */
#define EN_VME_USER4_AM_TSI 	0xb	/* User 4 AM for Tsi148   */

#define EN_LSI_DATA		0
#define EN_LSI_PGM		1
#define EN_LSI_USER		0
#define EN_LSI_SUPER	1

#define EN_VSI_DATA		1
#define EN_VSI_PGM		2
#define EN_VSI_USER		1
#define EN_VSI_SUPER	2
#define EN_VSI_BOTH		3

#define	EN_IMG_NO_BLT		0
#define	EN_IMG_SINGLE_BLT	1

#define	EN_IMG_PWEN		1
#define	EN_IMG_PREN		1


/* Byte Swap constants */
#define EN_SWAP_MASTER	0x08
#define EN_SWAP_SLAVE	0x10
#define EN_SWAP_FAST	0x20
#define EN_SWAP_MASK	(EN_SWAP_MASTER | EN_SWAP_SLAVE | EN_SWAP_FAST)
#define EN_SWAP_PORT	0x210


/* Interrupt Modes */
#define INT_MODE_ROAK	0
#define INT_MODE_RORA	1

/* UNIT DEFINE							 */
typedef signed char UINT8;
typedef unsigned int UINT32;
typedef unsigned short UINT16;
typedef signed int INT32;
/* Interrupt Numbers */
enum en_int_nums
{
  EN_RESERVED1_VOWN = 0, /* RESERVED1(Tsi148) or VOWN(Universe) */
  EN_IRQ1,               
  EN_IRQ2,
  EN_IRQ3,
  EN_IRQ4,
  EN_IRQ5,
  EN_IRQ6,
  EN_IRQ7,
  EN_ACFAIL,
  EN_SYSFAIL,
  EN_IACK,
  EN_VIE_SWINT,         /* VIE(Tsi148) or SWINT(Universe) */ 
  EN_VERR,
  EN_PERR,
  EN_RESERVED2,
  EN_RESERVED3,
  EN_MBOX0,
  EN_MBOX1,
  EN_MBOX2,
  EN_MBOX3,
  EN_LM0,
  EN_LM1,
  EN_LM2,
  EN_LM3,
  EN_DMA0,
  EN_DMA1,             /* Supported only on Tsi148 */ 
};


/* Status Information Type Numbers */
enum vme_stats
{
	VME_STATUS_CTRL = 1,
	VME_STATUS_LSI0,
	VME_STATUS_LSI1,
	VME_STATUS_LSI2,
	VME_STATUS_LSI3,
	VME_STATUS_LSI4,
	VME_STATUS_LSI5,
	VME_STATUS_LSI6,
	VME_STATUS_LSI7,
	VME_STATUS_VSI0,
	VME_STATUS_VSI1,
	VME_STATUS_VSI2,
	VME_STATUS_VSI3,
	VME_STATUS_VSI4,
	VME_STATUS_VSI5,
	VME_STATUS_VSI6,
	VME_STATUS_VSI7,
	VME_STATUS_DMA0,
	VME_STATUS_DMA1,
	VME_STATUS_INTS,
	VME_STATUS_PCI_MEM,
	VME_STATUS_VME_MEM
};


/* Tsi148 Specific enumerators */
enum tsi148sstModes 
{
	TSI148_SST160 = 0,
	TSI148_SST267,
	TSI148_SST320
};

enum tsi148VmeCycles 
{
	TSI148_SCT = 0,
	TSI148_BLT,
	TSI148_MBLT,
	TSI148_2eVME,
	TSI148_2eSST,
	TSI148_2eSSTB
};	

enum tsi148DmaBlkSize 
{
	TSI148_32 = 0,
	TSI148_64,
	TSI148_128,
	TSI148_256,
	TSI148_512,
	TSI148_1024,
	TSI148_2048,
	TSI148_4096
};

enum tsi148DmaBackOff 
{
	TSI148_1US = 1,
	TSI148_2US,
	TSI148_4US,
	TSI148_8US,
	TSI148_16US,
	TSI148_32US,
	TSI148_64US
};


/***************************** Data Structures ****************************/

typedef struct
{
	UINT32 pciAddress;			/* Lower 32-bits of PCI address                                 */
	UINT32 pciAddressUpper;		/* Upper 32-bits of PCI address                                 */
	UINT32 vmeAddress;			/* Lower 32-bits of vme address                                 */
	UINT32 vmeAddressUpper;		/* Upper 32-bits of vme address                                 */
	UINT32 size;				/* Lower 32-bits of the size                                    */
	UINT32 sizeUpper;			/* Upper 32-bits of the size                                    */
	UINT32 readPrefetch;		/* Prefetched reads: 0=disable, 1=enable (Tsi148 only)          */
	UINT32 prefetchSize;		/* Cache lines: 0=2, 1=4, 2=8, 3=16 (Tsi148 only)               */
	UINT32 postedWrites;		/* Posted writes: 0=disable, 1=enable (Universe only)           */
	
	UINT32 dataWidth;			/* Data width: 0=8 bits, 1=16 bits, 2=32 bits, 3=64 bits        */
								/* (8 and 64 bit supported on Universe only)                    */
	
	UINT32 addrSpace;			/* Address space: 0=A16, 1=A24, 2=A32, 4=A64 (Tsi148 only),     */
								/* 5=CR/CSR, 6=User1 (Universe only), 7=User2 (Universe only),  */
								/* 8=User1 (Tsi148 only), 9=User2 (Tsi148 only),                */
								/* 10=User3 (Tsi148 only), 11=User4 (Tsi148 only)               */
	
	UINT32 type;				/* Type: 0=data, 1=program                                      */
	UINT32 mode;				/* Mode: 0=non-privileged, 1=supervisor                         */
	
	UINT32 vmeCycle;			/* Cycle type: 0=SCT, 1=BLT, 2=MBLT, 3=2eVME,                   */
								/* 4=2eSST, 5=2eSSTB (Universe supports only 0=SCT and 1=BLT)   */
	
	UINT32 sstMode;				/* 2eSST modes: 0=SST160, 1=SST267 , 2=SST320 (Tsi148 only)     */
	UINT32 vton;				/* Not used                                                     */
	UINT32 vtoff;				/* Not used                                                     */
	UINT32 sstbSel;				/* 2eSST Broadcast select: Bit pattern 0-0x1FFFFF (Tsi148 only) */
	UINT32 pciBusSpace;			/* PCI bus space: (Universe only) 0=pci_mem, 1=pci_IO           */
	UINT32 ioremap;				/* Not used                                                     */

} EN_PCI_IMAGE_DATA;


typedef struct
{
	UINT32 vmeAddress;			/* Lower 32bits of VME Address                             */
    UINT32 vmeAddressUpper;		/* Upper 32bits of VME Address                             */
	UINT32 size;				/* Lower 32bits of Image size                              */
	UINT32 sizeUpper;			/* Upper 32bits of Image size                              */
	
	UINT32 threshold;			/* Threshold for prefetch (Tsi148 only)                    */
								/* 0=prefetch on FIFO full empty                           */
								/* 1=prefetch on FIFO half empty                           */
	
	UINT32 virtualFifoSize;		/* FIFO Size: 0=64, 1=128, 2=256, 3=512 (Tsi148 only)      */
	UINT32 postedWrites;		/* Posted writes: 0=disable, 1=enable (Universe only)      */
	UINT32 prefetchRead;		/* Prefetch read: 0=disable, 1=enable (Universe only)      */
	
	UINT32 vmeCycle;			/* Cycle type: 0=SCT, 1=BLT,  2=MBLT,                      */
								/* 3=2eVME , 4 = 2eSST 5 = 2eSSTB (Tsi148 only)            */
	
	UINT32 sstMode;				/* 2eSST mode: 0=SST160, 1=SST267, 2=SST320 (Tsi148 only)  */
	UINT32 type;				/* Type: 1=data, 2=program 3=both                          */
	UINT32 mode;				/* Mode: 1=non-privileged, 2=supervisor 3=both             */
	
	UINT32 addrSpace;			/* Address space: 0=A16, 1=A24, 2=A32, 4=A64(Tsi148 only), */ 
								/* 6=User1 (Universe only), 7=User2 (Universe only)        */
	
	UINT32 pciBusSpace;			/* PCI bus space: 0=pci_mem, 1=pci_IO (Universe only)      */
	
	UINT32 pciBusLock;			/* PCI bus lock: on VME read modify write                  */
								/* 0=disable, 1=enable (Universe only)                     */
	
	UINT32 ioremap;				/* Not used                                                */

} EN_VME_IMAGE_DATA;


typedef struct
{
	UINT32 user1;			/* User1 address modifier code, values range from 16-31 */
	UINT32 user2;			/* User2 address modifier code, values range from 16-31 */

} EN_VME_USER_AM;			/* Applicable only to Universe */


typedef struct
{
    UINT8 intNum;           /* VME interrupt number 1-7                  */
    UINT32 numOfInts;       /* Number of VME interrupts since last call  */
    UINT8 vecCount;         /* Number of vectors stored in vectors array */
    UINT8 vectors[32];      /* Array to hold the STATUSID vectors        */

} EN_VME_INT_INFO;


typedef struct
{
	UINT8 intNum;			/* VME interrupt number 1-7                  */
	UINT32 numOfInts;		/* Number of VME interrupts since last call  */
	UINT8 vecCount;			/* Number of vectors stored in vectors array */
	UINT8 vectors[128];		/* Array to hold the STATUSID vectors        */

} EN_VME_EXTINT_INFO;


typedef struct
{
    UINT32 vmeAddress;      /* Lower 32bits of VME Address, lowest address in range to monitor */
	UINT32 vmeAddressUpper;	/* Upper 32bits of VME Address                                     */	
    UINT32 type;            /* Type: 1=data, 2=program 3=both                                   */
    UINT32 mode;            /* Mode: 1=non-privileged, 2=supervisor 3=both                      */
    UINT32 addrSpace;       /* Address space: 0=A16, 1=A24, 2=A32 3=Reserved 4=A64              */

} EN_VME_IMAGE_ACCESS;


typedef struct 
{
	UINT32 vmeBlkSize;			/* VME Bus block size in bytes: 0=32, 1=64, 2=128 , 3=256, */
								/* 4=512, 5=1024, 6=2048, 7=4096 (Tsi148 only)             */
	
	UINT32 vmeBackOffTimer;		/* VMEBus Back off timer in uS: 0=0, 1=1 , 2=2, 3=4 , 4=8, */
								/* 5=16, 6=32, 7=64 (Tsi148 only)                          */
	
	UINT32 pciBlkSize;			/* PCI Bus block size in bytes: 0=32, 1=64, 2=128, 3=256,  */
								/* 4=512, 5=1024, 6=2048, 7=4096 (Tsi148 only)             */	
	
	UINT32 pciBackOffTimer;		/* PCI Bus Back off timer in uS: 0=0, 1=1, 2=2, 3=4, 4=8,  */
								/* 5=16, 6=32, 7=64 (Tsi148 only)                          */
	
	UINT32 vton;				/* Not used                                                */
	UINT32 vtoff;				/* Not used                                                */
	UINT32 timeout;				/* Transfer timeout in seconds                             */
	UINT32 ownership;			/* VME bus On/Off counters (Universe only)                 */
	
} EN_VME_TXFER_PARAMS;


typedef struct 
{
	UINT32 dataWidth;		/* Data width: 0=8 bits, 1=16 bits, 2=32 bits, 3=64 bits        */
							/* (8 and 64 bit Universe only)                                 */
	
	UINT32 addrSpace;		/* Address space: 0=A16, 1=A24, 2=A32, 4=A64 (Tsi148 only),     */
							/* 5=CR/CSR, 6=User1 (Universe only), 7=User2 (Universe only),  */
							/* 8=User1 (Tsi148 only), 9=User2 (Tsi148 only),                */
							/* 10=User3 (Tsi148 only), 11=User4 (Tsi148 only)               */
	
	UINT32 type;			/* Type: 0=data, 1=program                                      */
	UINT32 mode;			/* Mode: 0=non-privileged, 1=supervisor                         */
	
	UINT32 vmeCycle;		/* Cycle type: 0=SCT, 1=BLT,  2=MBLT, 3=2eVME,                  */ 
							/* 4=2eSST, 5=2eSSTB (Universe supports only SCT and BLT)       */
	
	UINT32 sstMode;			/* 2eSST Mode: 0=SST160, 1=SST267, 2=SST320 (Tsi148 only)       */
	UINT32 sstbSel;			/* 2eSST Broadcast select: Bit pattern 0-0x1FFFFF (Tsi148 only) */
	
} EN_VME_ACCESS_PARAMS;


typedef struct 
{
	UINT32 direction;				/* 0=read (VME to PCI bus), 1=write (PCI to VME bus) */
	UINT32 vmeAddress;				/* Lower 32-bit of destination address               */
	UINT32 vmeAddressUpper;			/* Upper 32-bit of destination address               */
	UINT32 offset;					/* Offset from start of DMA buffer                   */
	UINT32 size;					/* Size in bytes to transfer                         */
	EN_VME_TXFER_PARAMS txfer;		/* Transfer parameters                               */
	EN_VME_ACCESS_PARAMS access; 	/* Destination attributes                            */

} EN_VME_DIRECT_TXFER;


typedef struct
{
    UINT32 direction;				/* 0=read (VME to PCI bus), 1=write (PCI to VME bus) */
    UINT32 vmeAddress;				/* VME address                                       */
	UINT32 vmeAddressUpper;			/* VME address Upper                                 */
    UINT32 offset;					/* Offset from start of DMA buffer                   */
    UINT32 size;					/* Size in bytes to transfer                         */
    EN_VME_ACCESS_PARAMS access;	/* Access parameters                                 */

} EN_VME_CMD_DATA;


typedef struct
{
	char version[VERSION_INFO_LEN];	/* Driver version information                  */
	char brdName[BOARD_INFO_LEN];	/* Board name                                  */
	UINT32 devId;					/* VME bridge device ID, Universe or Tsi148    */
	UINT32 regBase;					/* Memory base address of VME bridge registers */

	UINT32 spare1;
	UINT32 spare2;
	UINT32 spare3;
	UINT32 spare4;
	
} EN_VME_STATUS_CTRL;


typedef struct
{
	UINT32 devId;				/* VME bridge device ID, Universe or Tsi148 */
	UINT32 readCount;			/* vme_read count                           */
	UINT32 writeCount;			/* vme_write count                          */
	UINT32 errorCount;			/* vme_read/write error count               */
	
/* Device registers	*/			/* Universe		Tsi148 */
	UINT32 devReg1;				/* LSIx_CTL		OTSAU  */
	UINT32 devReg2;				/* LSIx_BS		OTSAL  */
	UINT32 devReg3;				/* Not used		OTEAU  */
	UINT32 devReg4;				/* LSIx_BD		OTEAL  */
	UINT32 devReg5;				/* Not used		OTOFU  */
	UINT32 devReg6;				/* LSIx_TO		OTOFL  */
	UINT32 devReg7;				/* Not used		OTBS   */
	UINT32 devReg8;				/* Not used		OTAT   */

	UINT32 spare1;
	UINT32 spare2;
	UINT32 spare3;
	UINT32 spare4;
	
} EN_VME_STATUS_LSI;


typedef struct
{
	UINT32 devId;				/* VME bridge device ID, Universe or Tsi148 */
	UINT32 readCount;			/* vme_read count                           */
	UINT32 writeCount;			/* vme_write count                          */
	UINT32 errorCount;			/* vme_read/write error count               */
	
/* Device registers	*/			/* Universe		Tsi148 */
	UINT32 devReg1;				/* VSIx_CTL		ITSAU  */
	UINT32 devReg2;				/* VSIx_BS		ITSAL  */
	UINT32 devReg3;				/* Not used		ITEAU  */
	UINT32 devReg4;				/* VSIx_BD		ITEAL  */
	UINT32 devReg5;				/* Not used		ITOFU  */
	UINT32 devReg6;				/* VSIx_TO		ITOFL  */
	UINT32 devReg7;				/* Not used		ITAT   */

	UINT32 spare1;
	UINT32 spare2;
	UINT32 spare3;
	UINT32 spare4;
	UINT32 spare5;
	
} EN_VME_STATUS_VSI;


typedef struct
{
	UINT32 devId;				/* VME bridge device ID, Universe or Tsi148        */
	UINT32 readCount;			/* vme_read count                                  */
	UINT32 writeCount;			/* vme_write count                                 */
	UINT32 errorCount;			/* vme_read/write error count                      */
	
	UINT32 txferCount;			/* DMA transfers count                             */
	UINT32 txferErrors;			/* Number of DMA transfer errors                   */
	UINT32 timeoutCount;		/* Number of DMA timeouts                          */
	
	UINT32 cmdPktCount;			/* Command packet count                            */
	UINT32 cmdPktBytes;			/* Number of bytes to transfer in linked list mode */

/* Device registers	*/			/* Universe		Tsi148 */
	UINT32 devReg1;				/* DCTL			DCTL   */
	UINT32 devReg2;				/* DTBC			DSAU   */
	UINT32 devReg3;				/* Not used		DSAL   */
	UINT32 devReg4;				/* DLA			DDAU   */
	UINT32 devReg5;				/* DVA			DDAL   */
	UINT32 devReg6;				/* DGCS			DSAT   */
	UINT32 devReg7;				/* Not used		DDAT   */
	UINT32 devReg8;				/* DCPP			DNLAU  */
	UINT32 devReg9;				/* Not used		DNLAL  */
	UINT32 devReg10;			/* Not used		DCNT   */
	UINT32 devReg11;			/* Not used		DDBS   */

	UINT32 spare1;
	UINT32 spare2;
	UINT32 spare3;
	UINT32 spare4;
	
} EN_VME_STATUS_DMA;


typedef struct
{
	/* Counters from the ISR */
	UINT32 intCount;				/* VME bridge interrupt count   */
	UINT32 otherIntCount;			/* Other shared interrupt count */
	UINT32 vectorFIFOOverruns;		/* Vector FIFO Overruns         */
	UINT32 vectorErrors;			/* Vector errors                */

	/* Counters from the DPC */
	UINT32 dpcIsrCount;				/* DPC run count                                    */
	UINT32 dpcIsrVmeCount;			/* VME interrupts processed by DPC                  */
	UINT32 dpcIsrDmaCount;			/* DMA interrupts processed by DPC                  */
	UINT32 dpcIsrVerrCount;			/* VERR interrupts processed by DPC                 */
	UINT32 dpcIsrMboxCount;			/* MBOX interrupts processed by DPC                 */
	UINT32 dpcIsrLmonCount;			/* LMON interrupts processed by DPC                 */
	UINT32 virqEventCount;			/* User events triggered by DPC                     */
	UINT32 noEventCount;			/* Interrupts processed by DPC with no user event   */
	UINT32 maxDPCInterrupts;		/* Max. interrupts processed by DPC in a single run */
	UINT32 dpcTotalInterrupts;		/* Total interrupts processed by DPC                */
	UINT32 dpcQueueOverflow;		/* DPC queue overflow count                         */

	UINT32 spare1;
	UINT32 spare2;
	UINT32 spare3;
	UINT32 spare4;
	UINT32 spare5;

} EN_VME_STATUS_INTS;


typedef struct
{
	int	imageNum;				/* Image number	                 */
	UINT32 physStart;			/* Lower 32-bit of start address */
	UINT32 physStartUpper;		/* Upper 32-bit of start address */
	UINT32 physEnd;				/* Lower 32-bit of end address   */
	UINT32 physEndUpper;		/* Upper 32-bit of end address   */
	
} EN_VME_MEM_TBL;


typedef struct
{
	UINT32 physStart;			/* Lower 32-bit of start address */
	UINT32 physStartUpper;		/* Upper 32-bit of start address */
	UINT32 physEnd;				/* Lower 32-bit of end address   */
	UINT32 physEndUpper;		/* Upper 32-bit of end address   */
	UINT32 freeSpace;			/* Amount of free space          */
	EN_VME_MEM_TBL memTable[8];	/* 8 entries consisting of start */
								/* and end addresses             */
} EN_VME_STATUS_MEM;


#ifndef VME_DRIVER_BUILD

#define UNIVERSE_DEVID	0x000010E3
#define TSI148_DEVID	0x014810E3

/* Universe II Register Offsets */

#define PCI_ID		0x0000
#define PCI_CSR		0x0004
#define PCI_CLASS	0x0008
#define PCI_MISC0	0x000C
#define PCI_BS0		0x0010
#define PCI_BS1		0x0014
#define PCI_MISC1	0x003C

#define LSI0_CTL	0x0100
#define LSI0_BS		0x0104
#define LSI0_BD		0x0108
#define LSI0_TO		0x010C

#define LSI1_CTL	0x0114
#define LSI1_BS		0x0118
#define LSI1_BD		0x011C
#define LSI1_TO		0x0120

#define LSI2_CTL	0x0128
#define LSI2_BS		0x012C
#define LSI2_BD		0x0130
#define LSI2_TO		0x0134

#define LSI3_CTL	0x013C
#define LSI3_BS		0x0140
#define LSI3_BD		0x0144
#define LSI3_TO		0x0148

#define SCYC_CTL	0x0170
#define SCYC_ADDR	0x0174
#define SCYC_EN		0x0178
#define SCYC_CMP	0x017C
#define SCYC_SWP	0x0180
#define LMISC		0x0184
#define SLSI		0x0188
#define L_CMDERR	0x018C
#define LAERR		0x0190

#define LSI4_CTL	0x01A0
#define LSI4_BS		0x01A4
#define LSI4_BD		0x01A8
#define LSI4_TO		0x01AC

#define LSI5_CTL	0x01B4
#define LSI5_BS		0x01B8
#define LSI5_BD		0x01BC
#define LSI5_TO		0x01C0

#define LSI6_CTL	0x01C8
#define LSI6_BS		0x01CC
#define LSI6_BD		0x01D0
#define LSI6_TO		0x01D4

#define LSI7_CTL	0x01DC
#define LSI7_BS		0x01E0
#define LSI7_BD		0x01E4
#define LSI7_TO		0x01E8

#define DCTL		0x0200
#define DTBC		0x0204
#define DLA			0x0208
#define DVA			0x0210
#define DCPP		0x0218
#define DGCS		0x0220
#define D_LLUE		0x0224

#define LINT_EN		0x0300
#define LINT_STAT	0x0304
#define LINT_MAP0	0x0308
#define LINT_MAP1	0x030C
#define VINT_EN		0x0310
#define VINT_STAT	0x0314
#define VINT_MAP0	0x0318
#define VINT_MAP1	0x031C
#define STATID		0x0320
#define V1_STATID	0x0324
#define V2_STATID	0x0328
#define V3_STATID	0x032C
#define V4_STATID	0x0330
#define V5_STATID	0x0334
#define V6_STATID	0x0338
#define V7_STATID	0x033C

#define LINT_MAP2	0x340
#define VINT_MAP2	0x344
#define MBOX0		0x348
#define MBOX1		0x34C
#define MBOX2		0x350
#define MBOX3		0x354
#define SEMA0		0x358
#define SEMA1		0x35C

#define MAST_CTL	0x0400
#define MISC_CTL	0x0404
#define MISC_STAT	0x0408
#define USER_AM		0x040C

#define VSI0_CTL	0x0F00
#define VSI0_BS		0x0F04
#define VSI0_BD		0x0F08
#define VSI0_TO		0x0F0C

#define VSI1_CTL	0x0F14
#define VSI1_BS		0x0F18
#define VSI1_BD		0x0F1C
#define VSI1_TO		0x0F20

#define VSI2_CTL	0x0F28
#define VSI2_BS		0x0F2C
#define VSI2_BD		0x0F30
#define VSI2_TO		0x0F34

#define VSI3_CTL	0x0F3C
#define VSI3_BS		0x0F40
#define VSI3_BD		0x0F44
#define VSI3_TO		0x0F48

#define LM_CTL		0xF64
#define LM_BS		0xF68

#define VRAI_CTL	0x0F70
#define VRAI_BS		0x0F74
#define VCSR_CTL	0x0F80
#define VCSR_TO		0x0F84
#define V_AMERR		0x0F88
#define VAERR		0x0F8C

#define VSI4_CTL	0x0F90
#define VSI4_BS		0x0F94
#define VSI4_BD		0x0F98
#define VSI4_TO		0x0F9C

#define VSI5_CTL	0x0FA4
#define VSI5_BS		0x0FA8
#define VSI5_BD		0x0FAC
#define VSI5_TO		0x0FB0

#define VSI6_CTL	0x0FB8
#define VSI6_BS		0x0FBC
#define VSI6_BD		0x0FC0
#define VSI6_TO		0x0FC4

#define VSI7_CTL	0x0FCC
#define VSI7_BS		0x0FD0
#define VSI7_BD		0x0FD4
#define VSI7_TO		0x0FD8

#define VCSR_CLR	0x0FF4
#define VCSR_SET	0x0FF8
#define VCSR_BS		0x0FFC


/* Tsi148 Register Offset */

#define OTAT0		0x011C
#define OTAT1		0x013C
#define OTAT2		0x015C
#define OTAT3		0x017C
#define OTAT4		0x019C
#define OTAT5		0x01BC
#define OTAT6		0x01DC
#define OTAT7		0x01FC

#define VIACK1		0x0204
#define VIACK2		0x0208
#define VIACK3		0x020C
#define VIACK4		0x0210
#define VIACK5		0x0214
#define VIACK6		0x0218
#define VIACK7		0x021C

#define RMWAU		0x0220
#define RMWAL		0x0224
#define RMWEN		0x0228
#define RMWC		0x022C
#define RMWS		0x0230

#define VMCTRL		0x0234
#define VSTAT		0x023C
#define VEAU		0x0260
#define VEAL		0x0264
#define VEAT		0x0268

#define ITAT0		0x0318
#define ITAT1		0x0338
#define ITAT2		0x0358
#define ITAT3		0x0378
#define ITAT4		0x0398
#define ITAT5		0x03B8
#define ITAT6		0x03D8
#define ITAT7		0x03F8

#define CBAU		0x040C
#define CBAL		0x0410
#define CRGAT		0x0414

#define CROU		0x0418
#define CROL		0x041C
#define CRAT		0x0420

#define LMBAU		0x0424
#define LMBAL		0x0428
#define LMAT		0x042C

#define VICR		0x0440
#define INTEN		0x0448
#define INTEO		0x044C
#define INTS		0x0450
#define INTC		0x0454
#define INTM1		0x0458
#define INTM2		0x045C

#define DCTL0		0x0500
#define DCTL1		0x0580
#define DCSTA0		0x0504
#define DCSTA1		0x0584
#define DSAU0		0x0520
#define DSAU1		0x05A0
#define DSAL0		0x0524
#define DSAL1		0x05A4
#define DDAU0		0x0528
#define DDAU1		0x05A8
#define DDAL0		0x052C
#define DDAL1		0x05AC
#define DSAT0		0x0530
#define DSAT1		0x05B0
#define DDAT0		0x0534
#define DDAT1		0x05B4
#define DNLAU0		0x0538
#define DNLAU1		0x05B8
#define DNLAL0		0x053C
#define DNLAL1		0x05BC
#define DCNT0 		0x0540
#define DCNT1		0x05C0
#define DDBS0		0x0544
#define DDBS1		0x05C4
#define SEMAR0		0x060C
#define SEMAR1		0x0608
#define TSIMBOX0	0x0610
#define TSIMBOX1	0x0614
#define TSIMBOX2	0x0618
#define TSIMBOX3	0x061C

#define CSRBCR		0x0FF4


/* The following ifdef block is the standard way of creating macros which make exporting   */
/* from a DLL simpler. All files within this DLL are compiled with the VMEAPI_EXPORTS      */
/* symbol defined on the command line. This symbol should not be defined on any project    */
/* that uses this DLL. This way any other project whose source files include this file see */
/* VMEAPI_API functions as being imported from a DLL, where as this DLL sees symbols       */
/* as being exported.                                                                      */

#define _ATTR_ __stdcall
#ifdef WINVME_EXPORTS
#define //__declspec(dllexport)
#else
#ifdef __cplusplus
#define extern "C" __declspec(dllimport) 
#else
#define __declspec(dllimport)
#endif
#endif /* WINVME_EXPORTS */


/* API Function Prototypes */

int vme_openDevice( char *deviceName );
int vme_closeDevice( INT32 deviceHandle );

int vme_readRegister( INT32 deviceHandle, UINT16 offset, UINT32 *reg );
int vme_writeRegister( INT32 deviceHandle, UINT16 offset, UINT32 reg );

int vme_setInterruptMode( INT32 deviceHandle, UINT8 mode );
int vme_enableInterrupt( INT32 deviceHandle, UINT8 intNumber );
int vme_disableInterrupt( INT32 deviceHandle, UINT8 intNumber );
int vme_generateInterrupt( INT32 deviceHandle, UINT8 intNumber );
int vme_readInterruptInfo( INT32 deviceHandle, EN_VME_INT_INFO *iPtr );

int vme_setStatusId( INT32 deviceHandle, UINT8 statusId );
int vme_waitInterrupt( INT32 deviceHandle, UINT32 selectedInts, UINT32 timeout, UINT32 *intNum );

int vme_setByteSwap( INT32 deviceHandle, UINT8 enable );

int vme_enableCsrImage( INT32 deviceHandle, UINT8 imageNumber );
int vme_disableCsrImage( INT32 deviceHandle, UINT8 imageNumber );
int vme_enableRegAccessImage( INT32 deviceHandle, EN_VME_IMAGE_ACCESS *iPtr );
int vme_disableRegAccessImage( INT32 deviceHandle );
int vme_enableLocationMon( INT32 deviceHandle, EN_VME_IMAGE_ACCESS *iPtr );
int vme_disableLocationMon( INT32 deviceHandle );

int vme_enablePciImage( INT32 deviceHandle, EN_PCI_IMAGE_DATA *iPtr );
int vme_disablePciImage( INT32 deviceHandle );
int vme_enableVmeImage( INT32 deviceHandle, EN_VME_IMAGE_DATA *iPtr );
int vme_disableVmeImage( INT32 deviceHandle );
int vme_setUserAmCodes( INT32 deviceHandle, EN_VME_USER_AM *amPtr );

int vme_getApiVersion( char *buffer );
int vme_getStats( INT32 deviceHandle, UINT32 type, void *iPtr );
int vme_clearStats( INT32 deviceHandle );

int vme_dmaDirectTransfer( INT32 deviceHandle, EN_VME_DIRECT_TXFER *dPtr );
int vme_addDmaCmdPkt( INT32 deviceHandle, EN_VME_CMD_DATA *cmdPtr );
int vme_clearDmaCmdPkts( INT32 deviceHandle );
int vme_dmaListTransfer( INT32 deviceHandle, EN_VME_TXFER_PARAMS *tPtr );
int vme_allocDmaBuffer( INT32 deviceHandle, UINT32 *size );
int vme_freeDmaBuffer( INT32 deviceHandle );

int vme_read( INT32 deviceHandle, UINT32 offset, UINT8 *buffer, UINT32 length );
int vme_write( INT32 deviceHandle, UINT32 offset, UINT8 *buffer, UINT32 length );

#ifdef _WIN64
int vme_mmap( INT32 deviceHandle, UINT32 offset, UINT32 length, UINT64 *userAddress );
int vme_unmap( INT32 deviceHandle, UINT64 userAddress, UINT32 length );
int vme_readVerrInfo( INT32 deviceHandle, UINT64 *Address, UINT8 *Direction, UINT8 *AmCode );
#else
int vme_mmap( INT32 deviceHandle, UINT32 offset, UINT32 length, UINT32 *userAddress );
int vme_unmap( INT32 deviceHandle, UINT32 userAddress, UINT32 length );
int vme_readVerrInfo( INT32 deviceHandle, UINT32 *Address, UINT8 *Direction, UINT8 *AmCode );
#endif

/* The following functions are not supported, but are defined for compatibility purposes */
int vme_readExtInterruptInfo( INT32 deviceHandle, EN_VME_EXTINT_INFO *iPtr );
int vme_reserveMemory( INT32 deviceHandle, UINT32 physicalAddress, UINT32 size );

#endif /* VME_DRIVER_BUILD */

#endif /* _WINVME_DRIVER_H */
