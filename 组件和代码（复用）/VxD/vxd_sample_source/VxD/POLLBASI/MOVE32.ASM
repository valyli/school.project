  .MODEL SMALL
  .CODE
  .386

move32 PROC C PhysSize:DWORD, PhysBase: DWORD

  mov ax, 0           ; DPMI Alloc Selector
  mov cx, 1
  int 31h

  mov bx, ax          ; selector from Alloc
  mov cx, WORD PTR [PhysSize+2]    
  mov dx, WORD PTR [PhysSize]
  mov ax, 08h         ; DPMI Set Selector Limit
  int 31h

  mov dx, bx          ; save selector 
  mov bx, WORD PTR [PhysBase+2]
  mov cx, WORD PTR [PhysBase]
  mov si, WORD PTR [PhysSize+2]
  mov di, WORD PTR [PhysSize]
  mov ax, 0800h       ; DPMI Map Physical Address
  int 31h
  
  push dx             ; save selector
  mov cx, bx          ; HI word of linear base
  mov dx, cx          ; LO word of linear base
  pop bx              ; restore selector
  mov ax, 07h         ; DPMI Set Selector Base
  int 31h

  mov es, bx
  xor edi, edi
  mov ecx, PhysSize
  shr ecx, 2
  rep stosd es:[edi]

move32  ENDP 

  END
