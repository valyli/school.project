// BELLEVT.H - include file for class BellEvent, see bellevt.cpp for details
// Copyright (c) 1995, Vireo Software, Inc.

class BellEvent : public VGlobalEvent
{
public:
	BellEvent(VOID);	
	VOID handler(VMHANDLE hVM, CLIENT_STRUCT* pRegs, PVOID refData);
};
