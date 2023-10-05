// CONSTANT DEFINITIONS ////////////////////////////////////////
#define CLONE_MASK		0x8000	// Mask to be 'OR'ed with proc-


// Global Variable /////////////////////////////////////////////
int clone_flag;				// Flag to show whether processor
							//   is an Intel clone


/***************************************************************
* wincpuid()
*
* Inputs: none
*
* Returns:
*  0 = 8086/88
*  2 = 80286
*  3 = 80386
*  4 = 80486
*  5 = Pentium(R) Processor
*  6 = PentiumPro(R) Processor
*  7 or higher = Processor beyond the PentiumPro6(R) Processor
*
*  Note: This function also sets the global variable clone_flag
***************************************************************/

WORD wincpuid() {

	WORD cpuid;
	
	if ( wincpuidsupport() ) 	// Determine whether CPUID 
								//   opcode is supported
		cpuid=check_IDProc();

	else {
		
		clone_flag=check_clone();
	
		cpuid=check_8086();			// Will return FFFFh or 0
		if (cpuid == 0) goto end;
	
    	cpuid=check_80286();       	// Will return FFFFh or 2
		if (cpuid == 2) goto end;

    	cpuid=check_80386();       	// Will return FFFFh or 3
		if (cpuid == 3) goto end;    // temporarily commented out.
        
        cpuid=4;		// If the processor does not support CPUID,
        				//  is not an 8086, 80286, or 80386, assign
        				//  processor to be an 80486
	}

end:
	if (clone_flag)
		cpuid = cpuid | CLONE_MASK;	// Signify that a clone has been
									//   detected by setting MSB high 

   	return cpuid;

} // wincpuid ()


/***************************************************************
* wincpuidsupport()
*
* Inputs: none
*
* Returns:
*  1 = CPUID opcode is supported
*  0 = CPUID opcode is not supported
***************************************************************/

WORD wincpuidsupport() {
	int cpuid_support = 1;

	_asm {
        pushfd					// Get original EFLAGS
		pop		eax
		mov 	ecx, eax
        xor     eax, 200000h	// Flip ID bit in EFLAGS
        push    eax				// Save new EFLAGS value on
        						//   stack
        popfd					// Replace current EFLAGS value
        pushfd					// Get new EFLAGS
        pop     eax				// Store new EFLAGS in EAX
        xor     eax, ecx		// Can not toggle ID bit,
        jnz     support			// Processor=80486
		
		mov cpuid_support,0		// Clear support flag
support:
      }
	
	return cpuid_support;

} // wincpuidsupport()



/***************************************************************
* check_IDProc()
*
* Inputs: none
*
* Returns:
*  CPU Family (i.e. 4 if Intel 486, 5 if Pentium(R) Processor)
*
*  Note: This function also sets the global variable clone_flag
***************************************************************/

static WORD check_IDProc() {

		int i=0;
		WORD cpu_type=0xffff;
		BYTE stepping=0;
		BYTE model=0;
		BYTE vendor_id[12]="------------";
		BYTE intel_id[12]="GenuineIntel";

_asm {      

        xor     eax, eax		// Set up for CPUID instruction
        
        CPU_ID                  // Get and save vendor ID

        mov     dword ptr vendor_id, ebx
        mov     dword ptr vendor_id[+4], edx
        mov     dword ptr vendor_id[+8], ecx
}

for (i=0;i<12;i++)
{
	if (!(vendor_id[i]==intel_id[i]))
		clone_flag = 1;    
}

_asm {

        cmp     eax, 1			// Make sure 1 is valid input 
        						//   for CPUID
        
        jl      end_IDProc		// If not, jump to end
        xor     eax, eax
        inc		eax
        CPU_ID					// Get family/model/stepping/
        						//   features

		mov 	stepping, al
		and		stepping, 0x0f //0fh
		
		and 	al, 0f0h
		shr		al, 4
		mov 	model, al
		
		and		eax, 0f00h
        shr     eax, 8			// Isolate family
		and		eax, 0fh
        mov     cpu_type, ax	// Set _cpu_type with family

end_IDProc:
		mov		ax, cpu_type
      }
	
	return cpu_type;

} // Check_IDProc()



/***************************************************************
* check_8086()
*
* Inputs: none
*
* Returns: 
*   0      if processor 8086
*   0xffff otherwise
***************************************************************/

static WORD check_8086()
{

		WORD cpu_type=0xffff;

_asm {
        pushf                   // Push original FLAGS
        pop     ax              // Get original FLAGS
        mov     cx, ax          // Save original FLAGS
        and     ax, 0fffh       // Clear bits 12-15 in FLAGS
        push    ax              // Save new FLAGS value on stack
        popf                    // Replace current FLAGS value
        pushf                   // Get new FLAGS
        pop     ax              // Store new FLAGS in AX
        and     ax, 0f000h      // If bits 12-15 are set, then
        cmp     ax, 0f000h      //   processor is an 8086/8088
        mov     cpu_type, 0    	// Turn on 8086/8088 flag
        je      end_8086    	// Jump if processor is 8086/
        						//   8088
        mov		cpu_type, 0ffffh
end_8086:
		push 	cx
		popf
		mov		ax, cpu_type

      }
	
	return cpu_type;

} // check_8086()



/***************************************************************
* check_80286()
*
* Inputs: none
*
* Returns:
*   2      if processor 80286
*   0xffff otherwise
***************************************************************/

static WORD check_80286()
{

		WORD cpu_type=0xffff;

_asm {
		pushf
		pop		cx
		mov		bx, cx
        or      cx, 0f000h      // Try to set bits 12-15
        push    cx              // Save new FLAGS value on stack
        popf                    // Replace current FLAGS value
        pushf                   // Get new FLAGS
        pop     ax              // Store new FLAGS in AX
        and     ax, 0f000h      // If bits 12-15 are clear
        
        mov     cpu_type, 2     // Processor=80286, turn on 
        						//   80286 flag
        
        jz      end_80286       // If no bits set, processor is 
        						//   80286
		
		mov		cpu_type, 0ffffh
end_80286:
		push	bx
		popf
		mov		ax, cpu_type

      }
	
	return cpu_type;

} // check_80286()



/***************************************************************
* check_80386()
*
* Inputs: none
*
* Returns:
*   3      if processor 80386
*   0xffff otherwise
***************************************************************/

static WORD check_80386()
{

		WORD cpu_type=0xffff;

_asm {   
		mov 	bx, sp
		and		sp, not 3
        pushfd					// Push original EFLAGS 
        pop     eax				// Get original EFLAGS
        mov     ecx, eax		// Save original EFLAGS
        xor     eax, 40000h		// Flip AC bit in EFLAGS
        
        push    eax             // Save new EFLAGS value on
        						//   stack
        
        popfd                   // Replace current EFLAGS value
        pushfd					// Get new EFLAGS
        pop     eax             // Store new EFLAGS in EAX
        
        xor     eax, ecx        // Can't toggle AC bit, 
        						//   processor=80386
        
        mov     cpu_type, 3		// Turn on 80386 processor flag
        jz      end_80386		// Jump if 80386 processor
		mov		cpu_type, 0ffffh
end_80386:
		push	ecx
		popfd
		mov		sp, bx
		mov		ax, cpu_type
		and		eax, 0000ffffh
      }

	return cpu_type;

} // check_80386()


