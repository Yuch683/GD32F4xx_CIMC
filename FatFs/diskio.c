/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2025        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* Declarations FatFs MAI */

#include "SPI.h"		/* Drive by SPI_1 */
#include "instruction_set.h"

/* Example: Mapping of physical drive number for each drive */
#define SD_CARD	 0  //SD卡,卷标为0
#define EX_FLASH 1	//外部flash,卷标为1

/*-----------------------------------------------------------------------*/
/* 获得磁盘状态                                                     */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	//int result;

	switch (pdrv) {
		// translate the reslut code here
	case SD_CARD :
		if(SD_Is_Present() == 1)
			stat = 0;
		else
			stat = STA_NOINIT;

		return stat;

	case EX_FLASH :
		if(Flash_ReadID() != GD25Q40ETIGR)
			stat = STA_NOINIT;
		// translate the reslut code here
		else
			stat =0;
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* 初始化磁盘(只检查状态，不重复初始化，不支持热拔插)                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	//int result;

	switch (pdrv) {
		// translate the reslut code here
	case SD_CARD :
		if(SD_Is_Present() == 1)
			stat = 0;
		else
			stat = STA_NOINIT;

		return stat;

	case EX_FLASH :
		if(Flash_ReadID() != GD25Q40ETIGR)
			stat = STA_NOINIT;
		// translate the reslut code here
		else
			stat =0;
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	//int result;

	switch (pdrv) {
	case SD_CARD :

		

		return res;

	case EX_FLASH :

		

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	//int result;

	switch (pdrv) {
	case SD_CARD :
		// translate the arguments here



		// translate the reslut code here

		return res;

	case EX_FLASH :
		// translate the arguments here



		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	//int result;

	switch (pdrv) {
	case SD_CARD :

		// Process of the command for the RAM drive

		return res;

	case EX_FLASH :

		// Process of the command for the MMC/SD card

		return res;
	}

	return RES_PARERR;
}

