#include "stdafx.h"
#include <stdio.h>
#include "enumser.h"


void main()
{
  CUIntArray ports;
  EnumerateSerialPorts(ports);

  _tprintf(_T("The following serial ports are installed on this machine\n"));
  for (int i=0; i<ports.GetSize(); i++)
  {
    _tprintf(_T("COM%d\n"), ports.ElementAt(i));
  }
}