#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "..\32\skel32.h"


HDEVICE hDevice;

void main(int ac, char* av[])
{
   hDevice = DeviceOpen32();
   printf("hDevice=%x\n", hDevice );
}
