# SKELETON.mak - makefile for VxD SKELETON

DEVICENAME = SKELETON
FRAMEWORK = C
DEBUG = 1
OBJECTS = skeleton.OBJ

!include $(VTOOLSD)\include\vtoolsd.mak
!include $(VTOOLSD)\include\vxdtarg.mak

skeleton.OBJ:	skeleton.c skeleton.h