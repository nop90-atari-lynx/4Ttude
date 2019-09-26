#include "LynxSD.h"

////////////////////////////////////////////////////////////////////////////////
//
// Microcontroller communication constants
//
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	ECommandByte_OpenDir = 0,
	ECommandByte_ReadDir,
	ECommandByte_OpenFile,
	ECommandByte_GetSize,
	ECommandByte_Seek,
	ECommandByte_Read,
	ECommandByte_Write,
	ECommandByte_Close,
	ECommandByte_ProgramFile,
	ECommandByte_ClearBlocks,
	ECommandByte_LowPowerMode
} ECommandByte;

#define IO_TIMEOUT 30000

////////////////////////////////////////////////////////////////////////////////
//
// Lynx registers
//
////////////////////////////////////////////////////////////////////////////////

const unsigned char AUXMASK = 16;
#define IODAT ((volatile unsigned char *) 0xFD8B)
#define IODIR ((volatile unsigned char *) 0xFD8A)
#define CART1 ((volatile unsigned char *) 0xFCB3)
#define CART0 ((volatile unsigned char *) 0xFCB2)

////////////////////////////////////////////////////////////////////////////////
//
// Support functions to read and write bytes to the cartridge microcontroller
//
////////////////////////////////////////////////////////////////////////////////

static void __fastcall__ WriteByte(unsigned char byte)
{
	while (*IODAT & AUXMASK); // make sure the cart isnt blocking the write
	*CART1 = byte;
}

static void __fastcall__ WriteBytes(unsigned char *pBuf, unsigned int nSize)
{
	while (nSize--)
	{
		WriteByte(*pBuf++);
	}
}

static void __fastcall__ WriteWord(unsigned int word)
{
	WriteBytes((unsigned char*) &word, 2);
}

static void __fastcall__ WriteDword(unsigned long dword)
{
	WriteBytes((unsigned char*) &dword, 4);
}

static unsigned char ReadByte()
{
	while (!(*IODAT & AUXMASK)); // wait for data in read FIFO
	return *CART0; // read byte
}

static void __fastcall__ ReadBytes(unsigned char *pOut, unsigned int size)
{
	while (size--)
	{
		*pOut++ = ReadByte();
	}
}

static unsigned long ReadDword()
{
	unsigned long nDword;
	ReadBytes((unsigned char*) &nDword, 4);
	return nDword;
}

static void __fastcall__ WriteString(const char *pStr)
{
	char c;
	do
	{
		c = *pStr++;
		WriteByte(c);
	} while (c);
}

////////////////////////////////////////////////////////////////////////////////
//
// Microcontroller commands
//
////////////////////////////////////////////////////////////////////////////////

void LynxSD_Init()
{
	*IODIR = 0; // all input
	*CART1 = 0xaa; // initialise cart comms
}

void LynxSD_LowPowerMode()
{
	WriteByte(ECommandByte_LowPowerMode); // turn of sd card and enter low power state
}

FRESULT __fastcall__ LynxSD_OpenDir(const char *pDir)
{
	WriteByte(ECommandByte_OpenDir); // open dir command
	WriteString(pDir);
	return (FRESULT) ReadByte(); // read the response
}

FRESULT __fastcall__ LynxSD_ReadDir(SFileInfo *pInfo)
{
	FRESULT res;
	WriteByte(ECommandByte_ReadDir);
	res = (FRESULT) ReadByte();
	if (res == FR_OK)
	{
		ReadBytes((unsigned char *) pInfo, sizeof(SFileInfo));
	}
	return res;
}

FRESULT __fastcall__ LynxSD_OpenFile(const char *pFile)
{
	WriteByte(ECommandByte_OpenFile); // open file command
	WriteString(pFile);
	return (FRESULT) ReadByte(); // read the response
}

FRESULT __fastcall__ LynxSD_ReadFile(void *pBuffer, unsigned int nSize)
{
	WriteByte(ECommandByte_Read);
	WriteWord(nSize);
	ReadBytes((unsigned char *) pBuffer, nSize);
	return (FRESULT) ReadByte(); // final byte is status for read
}

FRESULT __fastcall__ LynxSD_WriteFile(void *pBuffer, unsigned int nSize)
{
	WriteByte(ECommandByte_Write);
	WriteWord(nSize);
	WriteBytes((unsigned char *) pBuffer, nSize);
	return (FRESULT) ReadByte(); // final byte is status for write
}

FRESULT LynxSD_CloseFile()
{
	WriteByte(ECommandByte_Close);
	return (FRESULT) ReadByte(); // status for close
}

FRESULT __fastcall__ LynxSD_SeekFile(unsigned long nSeekPos)
{
	WriteByte(ECommandByte_Seek);
	WriteDword(nSeekPos);
	return (FRESULT) ReadByte(); // seek result
}

unsigned long LynxSD_GetFileSize()
{
	WriteByte(ECommandByte_GetSize);
	return ReadDword(); // size of open file
}

FRESULT __fastcall__ LynxSD_ProgramROMFromFile(unsigned int nStartBlock, unsigned char nBlockSize, unsigned int nBlockCount, unsigned char b512BlockCard)
{
	if (b512BlockCard)
	{
		nBlockSize |= 0x10;
	}

	WriteByte(ECommandByte_ProgramFile);
	WriteWord(nStartBlock); // start block from 0-511 (>255 with 512 block card bit set)
	WriteByte(nBlockSize); // or with 0x10 for 512 block card (a19 controlled by aux pin)
	WriteWord(nBlockCount); // blocks to write
	return (FRESULT) ReadByte(); // waits for programming to end and gets result
}

FRESULT __fastcall__ LynxSD_ClearROMBlocks(unsigned int nStartBlock, unsigned int nBlocks, unsigned char b512BlockCard)
{
	if (b512BlockCard)
	{
		nBlocks |= 0x8000;
	}

	WriteByte(ECommandByte_ClearBlocks);
	WriteWord(nStartBlock); // start block from 0-511 (>255 with 512 block card bit set)
	WriteWord(nBlocks); // or with 0x8000 for 512 block card (a19 controlled by aux pin)
	return (FRESULT) ReadByte(); // waits for clearing to end and gets result
}


FRESULT __fastcall__ LynxSD_OpenFileTimeout(void *pBuffer)
{

	unsigned int count=0;
	while ((*IODAT & AUXMASK) && (count++<IO_TIMEOUT)); 
	if (count>=IO_TIMEOUT)
		return FR_DISK_ERR;
	*CART1 = ECommandByte_OpenFile;
	WriteString(pBuffer);
	count=0;
	while (!(*IODAT & AUXMASK) && (count++<IO_TIMEOUT));  // wait for data in read FIFO or timeout 
	if (count<IO_TIMEOUT)
	{
		return *CART0;
	}
	else
		return FR_DISK_ERR;
}
