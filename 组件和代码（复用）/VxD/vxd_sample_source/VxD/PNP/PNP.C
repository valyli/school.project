#define WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include "vxdcall.h"
#include <vxdwraps.h>
#include "intrinsi.h"
#include <configmg.h>
#include <vpicd.h>
#include "wrappers.h"

#ifdef DEBUG
#define DPRINTF0(buf, fmt )				_Sprintf(buf, fmt ); Out_Debug_String( buf )
#define DPRINTF1(buf, fmt, arg1)		_Sprintf(buf, fmt, arg1 ); Out_Debug_String( buf )
#define DPRINTF2(buf, fmt, arg1, arg2)	_Sprintf(buf, fmt, arg1, arg2 ); Out_Debug_String( buf )
#else
#define DPRINTF0(buf, fmt)
#define DPRINTF1(buf, fmt, arg1)
#define DPRINTF2(buf, fmt, arg1, arg2)
#endif

#define _outpdw( port, val )	_asm mov dx, port \
								   _asm mov eax, val \
								   _asm out dx, eax 

#define REG_CTRL	0
#define REG_STATUS	1

#define CTRL_START_DEVICE	0x01
#define CTRL_STOP_DEVICE	0x00

typedef struct
{
	DWORD	Ctrl;
	DWORD	Status;
} MEMREGS;

typedef struct
{
	DWORD	MemBase;
   DWORD MemSize;
	MEMREGS	*pMem;
	WORD	IoBase;
	WORD	Irq;
   IRQHANDLE       hndIrq;
   VPICD_IRQ_DESCRIPTOR IrqDescr;
} DEVICE_CONTEXT;

BOOL OnSysDynamicDeviceInit(void);
BOOL OnSysDynamicDeviceExit(void);
CONFIGRET OnPNPNewDevnode(DEVNODE DevNode, DWORD LoadType);
CONFIGRET CM_HANDLER ConfigHandler(CONFIGFUNC cfFuncName, SUBCONFIGFUNC scfSubFuncName, DEVNODE dnToDevNode, DWORD dwRefData, ULONG ulFlags);
CONFIGRET ProcessConfigStart( DEVNODE devnode, DEVICE_CONTEXT *dev );
CONFIGRET ProcessConfigStop( DEVNODE devnode, DEVICE_CONTEXT *dev );
void Print_Assigned_Resources( CMCONFIG *pConfig );
DWORD MyMapPhysToLinear( DWORD phys, DWORD size );
BOOL UnMapPhysToLinear( DWORD lin, DWORD size );

char dbuf[80];
DEVICE_CONTEXT *pDeviceContext;

// functions in asm module
void HwIntProcThunk( void );

BOOL OnSysDynamicDeviceInit()
{
	return TRUE;
}

BOOL OnSysDynamicDeviceExit()
{
	return TRUE;
}

CONFIGRET OnPNPNewDevnode(DEVNODE DevNode, DWORD LoadType)
{	   
	CONFIGRET	rc;

	switch (LoadType) 
	{

		case DLVXD_LOAD_DEVLOADER:
			pDeviceContext = (DEVICE_CONTEXT *)_HeapAllocate( sizeof(DEVICE_CONTEXT), HEAPZEROINIT );
			if (!pDeviceContext)
				return CR_FAILURE;
                        rc = CM_Register_Device_Driver(DevNode, ConfigHandler, pDeviceContext,
                                                       CM_REGISTER_DEVICE_DRIVER_REMOVABLE |
                                                       CM_REGISTER_DEVICE_DRIVER_DISABLEABLE );
			if (rc != CR_SUCCESS)
				return rc;

			return CR_SUCCESS;

		default:
			return(CR_DEFAULT);
	}
}

#pragma VxD_PAGEABLE_DATA_SEG
#pragma VxD_PAGEABLE_CODE_SEG

CONFIGRET CM_HANDLER ConfigHandler(CONFIGFUNC cfFuncName, SUBCONFIGFUNC scfSubFuncName, DEVNODE dnToDevNode, DWORD dwRefData, ULONG ulFlags)
{
	CMCONFIG	Config;
	DWORD		rc;
	DEVICE_CONTEXT *dev = (DEVICE_CONTEXT *)dwRefData;

	switch (cfFuncName) 
	{
	case CONFIG_START:
		return ProcessConfigStart(dnToDevNode, dev );

	case CONFIG_TEST:
		return CR_SUCCESS;

	case CONFIG_STOP:
		return ProcessConfigStop(dnToDevNode, dev );

	case CONFIG_REMOVE:
		return ProcessConfigStop(dnToDevNode, dev );

	default:
		return CR_DEFAULT;
	}
}

CONFIGRET ProcessConfigStart( DEVNODE devnode, void *p )
{
   DEVICE_CONTEXT *dev = (DEVICE_CONTEXT *)p;
   CONFIGRET rc;
   CMCONFIG  Config;
   MEMREGS *regs;
   WORD     reg;
   IRQHANDLE hndIrq;

   rc = CM_Get_Alloc_Log_Conf(&Config, devnode, CM_GET_ALLOC_LOG_CONF_ALLOC);
	if (rc != CR_SUCCESS)
	{
      DPRINTF1(dbuf, "CM_Get_Alloc_Log_Conf failed rc=%x\n", rc );
		return CR_FAILURE;
	}

	Print_Assigned_Resources(&Config);
	if (! ((Config.wNumIRQs == 1) && 
		    (Config.wNumIOPorts == 1 || Config.wNumMemWindows == 1))
	   )
	{
      DPRINTF0(dbuf, "Expected resources not assigned" );
		return CR_FAILURE;
	}

	if (Config.wNumMemWindows)
	{
		dev->MemBase = Config.dMemBase[0];
      dev->MemSize = Config.dMemLength[0];
		dev->pMem = (MEMREGS *)MyMapPhysToLinear( dev->MemBase, Config.dMemLength[0] );
		if (!dev->pMem)
		{
         DPRINTF0(dbuf, "MyMapPhysToLinear failed" );
			return CR_FAILURE;
		}	
		dev->pMem->Ctrl = CTRL_START_DEVICE;
	}
	else
	{
		dev->IoBase = Config.wIOPortBase[0];
      reg = dev->IoBase + REG_CTRL;
		_outpdw( reg, CTRL_START_DEVICE )
	}
			
	dev->IrqDescr.VID_IRQ_Number = Config.bIRQRegisters[0];
	dev->IrqDescr.VID_Options = VPICD_OPT_REF_DATA;
	dev->IrqDescr.VID_Hw_Int_Ref = dev;
	dev->IrqDescr.VID_Hw_Int_Proc = HwIntProcThunk;
	hndIrq = VPICD_Virtualize_IRQ( &dev->IrqDescr );
	if (!hndIrq)
	{
      DPRINTF0(dbuf, "VPICD_Virt failed" );
		return CR_FAILURE;
	}

	return CR_SUCCESS;
}

CONFIGRET ProcessConfigStop( DEVNODE devnode, void *p )
{
   DEVICE_CONTEXT *dev = (DEVICE_CONTEXT *)p; 
   WORD  reg;

 	if (dev->pMem)
 	{
 		dev->pMem->Ctrl = CTRL_STOP_DEVICE;
 		UnMapPhysToLinear( (DWORD)dev->pMem, dev->MemSize );
 	}
 	else if (dev->IoBase)
 	{
      reg = dev->IoBase + REG_CTRL;
		_outpdw( reg, CTRL_STOP_DEVICE )
 	}
 	VPICD_Force_Default_Behavior( dev->hndIrq );
 	_HeapFree( dev, 0 );
 	return CR_SUCCESS;
}

void Print_Assigned_Resources( CMCONFIG *pConfig )
{
	int			i;

	if (pConfig->wNumMemWindows)
	{
		DPRINTF0(dbuf, "Mem resources\r\n" );
		for (i=0; i < pConfig->wNumMemWindows; i++)
		{
			DPRINTF1(dbuf, "Range #%d: ", pConfig->wNumMemWindows );
			DPRINTF2(dbuf, "starts at %x len is %d\r\n", pConfig->dMemBase[i],pConfig->dMemLength[i] );
		}		  
	}

	if (pConfig->wNumIOPorts)
	{
		DPRINTF0(dbuf, "IO resources\r\n" );
		for (i=0; i < pConfig->wNumIOPorts; i++)
		{
			DPRINTF1(dbuf, "Range #%d: ", pConfig->wNumIOPorts );
			DPRINTF2(dbuf, "starts at %x len is %d\r\n", pConfig->wIOPortBase[i],pConfig->wIOPortLength[i] );
		}
	}

	if (pConfig->wNumIRQs)
	{
		DPRINTF0(dbuf, "IRQs: " );
		for (i=0; i < pConfig->wNumIRQs; i++)
		{
			DPRINTF1(dbuf, "%d ", pConfig->bIRQRegisters[i]); 
		}
		DPRINTF0(dbuf, "\r\n"); 
	}

	if (pConfig->wNumDMAs)
	{
		DPRINTF0(dbuf, "DMA channels:" );
		for (i=0; i < pConfig->wNumDMAs; i++)
		{
			DPRINTF1(dbuf, "%d ", pConfig->bDMALst[i]); 
		}
		DPRINTF0(dbuf, "\r\n"); 
	}

}

DWORD MyMapPhysToLinear( DWORD phys, DWORD size )
{
   DWORD lin;
   DWORD nPages = size / 4096;

   lin = _PageReserve( PR_SYSTEM, nPages, 0 );
   if (lin == -1)
      return 0;
   if (!_PageCommitPhys( lin >> 12, nPages, phys, PC_INCR | PC_WRITEABLE  ))
	    return 0;
   if (!_LinPageLock( lin >> 12, nPages, 0 ))
       return 0;
   return lin;
}


BOOL UnMapPhysToLinear( DWORD lin, DWORD size )
{
   DWORD nPages = size / 4096;

   if (!_LinPageUnlock( lin, nPages, 0 ))
       return 0;
   if (!_PageDecommit( lin, nPages, 0))
	return 0;
   if (!_PageFree( (void *)lin, 0 ))
      return 0;
   return 1;
}


BOOL __stdcall HwIntProcHandler(VMHANDLE hVM, IRQHANDLE hIRQ, void *pRefData)
{
   DEVICE_CONTEXT *dev = (DEVICE_CONTEXT *)pRefData;

	return TRUE;
}
