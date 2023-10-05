// DMAALLOC.c - main module for VxD DMAEXAMP
#define WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include "vxdcall.h"
#include <vxdwraps.h>
#include <wrappers.h>

#ifdef DEBUG
#define DPRINTF0(buf, fmt) _Sprintf(buf, fmt ); Out_Debug_String( buf )
#define DPRINTF1(buf, fmt, arg1) _Sprintf(buf, fmt, arg1 ); Out_Debug_String( buf )
#define DPRINTF2(buf, fmt, arg1, arg2) _Sprintf(buf, fmt, arg1, arg2 ); Out_Debug_String( buf )
#else
#define DPRINTF0(buf, fmt)
#define DPRINTF1(buf, fmt, arg1)
#define DPRINTF2(buf, fmt, arg1, arg2)
#endif

PVOID AllocSysDmaBuf( DWORD nPages, PVOID pPhysAddr ); 
PVOID AllocBusMasterBuf( DWORD nPages, PVOID pPhysAddr ); 
PVOID AllocScatterGatherBuf( DWORD nPages, PVOID pPhysAddr ); 

PVOID lin;
char buf[80];

BOOL OnSysDynamicDeviceInit(VMHANDLE hVM)
{
   BOOL  rc;
   DWORD PTEOffset;
   DWORD nPages, phys;
   DDS     myDDS;
   int i;

   DPRINTF0(buf, "DynInit\r\n" );
   nPages = 4;
   lin = AllocScatterGatherBuf( nPages, &phys ); 
   if (!lin)
   {
      DPRINTF0(buf, "ERR PageAlloc\r\n" );
   }
   else
   {
      DPRINTF2(buf, "Lin=%x, Phys=%x\r\n", lin, phys);
   }


   myDDS.dds.DDS_linear = lin;
   myDDS.dds.DDS_size = 4 * 4 * 1024;
   myDDS.dds.DDS_seg = myDDS.dds.RESERVED = 0;
   myDDS.dds.DDS_avail = 16;
   rc = VDMAD_Scatter_Lock( Get_Cur_VM_Handle(), 0, &myDDS, &PTEOffset );
   DPRINTF1(buf, "Scatter_Lock rc=%x\r\n", rc);
   DPRINTF1(buf, "nRegions=%x\r\n", myDDS.dds.DDS_used);
   for (i=0; i < myDDS.dds.DDS_used; i++)
   {
      DPRINTF2(buf, "Region phys=%x size=%d\r\n", myDDS.aRegionInfo[i].PhysAddr, myDDS.aRegionInfo[i].Size );
   }
                                         
   return TRUE;
}



BOOL OnSysDynamicDeviceExit(void)
{
   BOOL rc;
   DPRINTF0(buf, "DynExit\r\n" );
   rc = _PageFree( lin, 0 );
   if (!rc)
      DPRINTF0(buf, "PageFree failed\n");
   return TRUE;
}


PVOID AllocSysDmaBuf( DWORD nPages, PVOID pPhysAddr ) 
{
   return( _PageAllocate(nPages, PG_SYS, 0, 
      0x0F, 0, 0x1000L, 
      pPhysAddr, PAGECONTIG | PAGEUSEALIGN | PAGEFIXED ) );
}


PVOID AllocBusMasterBuf( DWORD nPages, PVOID pPhysAddr )
{
   return( _PageAllocate(nPages, PG_SYS, 0, 
      0, 0, 0x100000L, 
      pPhysAddr, PAGECONTIG | PAGEUSEALIGN | PAGEFIXED ) );
}

PVOID AllocScatterGatherBuf( DWORD nPages, PVOID pPhysAddr )
{
   return( _PageAllocate(nPages, PG_SYS, 0, 
      0, 0, 0x100000L, 
      pPhysAddr, 0 ) );
}
