#ifndef CCheckCPU_H
#define CCheckCPU_H

// CONSTANT DEFINITIONS ////////////////////////////////////////
#define CLONE_MASK		0x8000	// Mask to be 'OR'ed with proc-

// OPCODE DEFINITIONS //////////////////////////////////////////
#define CPU_ID _asm _emit 0x0f _asm _emit 0xa2 	
										// CPUID instruction




class CCheckCPU
{
public:
	CCheckCPU();
//	~CCheckCPU();
	WORD wincpuid();
	WORD wincpuidsupport();
	WORD check_IDProc();
	WORD check_8086();
	WORD check_80286();
	WORD check_80386();
	WORD check_clone();

public:
	// Global Variable /////////////////////////////////////////////
	int clone_flag;				// Flag to show whether processor
								//   is an Intel clone
};

#endif CCheckCPU_H
