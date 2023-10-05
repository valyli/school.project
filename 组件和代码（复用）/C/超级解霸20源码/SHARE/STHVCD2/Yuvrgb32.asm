	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "YUVRGB32.C"
	?debug	C E980B8FE200A59555652474233322E43
	?debug	C E9959DFC20085643444150492E48
	?debug	C E94019CA1817443A5C42435C494E434C5544455C57494E444F5753+
	?debug	C 2E48
YUVRGB32_TEXT	segment byte public use32 'CODE'
YUVRGB32_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:YUVRGB32_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
YUVRGB32_TEXT	segment byte public use32 'CODE'
	?debug	C E8010A59555652474233322E4380B8FE20
   ;	
   ;	void	PASCAL	FAR	DrawYVU12(void)	//YVU12 Planar
   ;	
	?debug	L 17
	assume	cs:YUVRGB32_TEXT
DRAWYVU12	proc	far
	?debug	B
	push	esi
	push	edi
	?debug	B
   ;	
   ;	{
   ;		_EDI=_EDI;
   ;	
	?debug	L 19
   ;	
   ;		asm	xor	eax,eax
   ;	
	?debug	L 20
		xor		eax,eax
   ;	
   ;		asm	push	ds
   ;	
	?debug	L 21
		push		ds
   ;	
   ;	//	_ES=LinearSelSurface;
   ;	//	_EDX=VCDHigh;
   ;	//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
   ;		asm	mov	ds,OffScrSel;
   ;	
	?debug	L 25
		mov		ds,_OffScrSel
   ;	
   ;		asm	mov	esi,[eax+4]
   ;	
	?debug	L 26
		mov		esi,[eax+4]
   ;	
   ;		asm	mov	ebx,[eax+8]
   ;	
	?debug	L 27
		mov		ebx,[eax+8]
   ;	
   ;		asm	mov	ds,[eax+0x10]	//GS-> Video data
   ;	
	?debug	L 28
		mov		ds,[eax+010H]	
   ;	
   ;		///////// Move Y Data //////////
   ;		asm	push	edx
   ;	
	?debug	L 30
		push		edx
@1@226:
   ;	
   ;		MoveYData:
   ;			_ECX=88;
   ;	
	?debug	L 32
	mov	ecx,large 88
   ;	
   ;			asm	rep	movsd//32 bits address
   ;	
	?debug	L 33
		rep	movsd	
   ;	
   ;			_ESI+=800;
   ;	
	?debug	L 34
	add	esi,large 800
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 35
		dec		edx
   ;	
   ;		asm	jnz	MoveYData
   ;	
	?debug	L 36
	jne	short @1@226
   ;	
   ;		////////// Move V Data //////////
   ;		_ESI=_EBX;
   ;	
	?debug	L 38
	mov	esi,ebx
   ;	
   ;		_ESI+=0x240;	//VPlane
   ;	
	?debug	L 39
	add	esi,large 576
   ;	
   ;		asm	pop	edx
   ;	
	?debug	L 40
		pop		edx
   ;	
   ;		asm	shr	edx,1	//_EDX/=2;
   ;	
	?debug	L 41
		shr		edx,1	
   ;	
   ;		asm	push	edx
   ;	
	?debug	L 42
		push		edx
@1@478:
   ;	
   ;		MoveVData:
   ;			_ECX=44;
   ;	
	?debug	L 44
	mov	ecx,large 44
   ;	
   ;			asm	rep	movsd//32 bits address
   ;	
	?debug	L 45
		rep	movsd	
   ;	
   ;			_ESI+=976;
   ;	
	?debug	L 46
	add	esi,large 976
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 47
		dec		edx
   ;	
   ;		asm	jnz	MoveVData
   ;	
	?debug	L 48
	jne	short @1@478
   ;	
   ;		////////// Move U Data //////////
   ;		_ESI=_EBX;	//UPlane
   ;	
	?debug	L 50
	mov	esi,ebx
   ;	
   ;		asm	pop	edx
   ;	
	?debug	L 51
		pop		edx
@1@674:
   ;	
   ;		MoveUData:
   ;			_ECX=44;
   ;	
	?debug	L 53
	mov	ecx,large 44
   ;	
   ;			asm	rep	movsd//32 bits address
   ;	
	?debug	L 54
		rep	movsd	
   ;	
   ;			_ESI+=976;
   ;	
	?debug	L 55
	add	esi,large 976
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 56
		dec		edx
   ;	
   ;		asm	jnz	MoveUData
   ;	
	?debug	L 57
	jne	short @1@674
   ;	
   ;		asm	pop	ds
   ;	
	?debug	L 58
		pop		ds
   ;	
   ;	}
   ;	
	?debug	L 59
	pop	edi
	pop	esi
        db	066h
	ret
	?debug	E
	?debug	E
DRAWYVU12	endp
   ;	
   ;	void	PASCAL	FAR	DrawYVU9(void)	//YVU9 Planar
   ;	
	?debug	L 61
	assume	cs:YUVRGB32_TEXT
DRAWYVU9	proc	far
	?debug	B
	push	esi
	push	edi
	?debug	B
   ;	
   ;	{
   ;		_EDI=_EDI;
   ;	
	?debug	L 63
   ;	
   ;		asm	xor	eax,eax
   ;	
	?debug	L 64
		xor		eax,eax
   ;	
   ;		asm	push	ds
   ;	
	?debug	L 65
		push		ds
   ;	
   ;	//	_EDX=VCDHigh;
   ;	//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
   ;	//	_ES=LinearSelSurface;
   ;		asm	mov	ds,OffScrSel;
   ;	
	?debug	L 69
		mov		ds,_OffScrSel
   ;	
   ;		asm 	mov 	esi,[eax+4]
   ;	
	?debug	L 70
 		mov	 	esi,[eax+4]
   ;	
   ;		asm 	mov 	ebx,[eax+8]
   ;	
	?debug	L 71
 		mov	 	ebx,[eax+8]
   ;	
   ;		asm	mov 	ds,[eax+0x10]	//DS-> Video data
   ;	
	?debug	L 72
		mov	 	ds,[eax+010H]	
   ;	
   ;		///////// Move Y Data //////////
   ;		asm	push	edx
   ;	
	?debug	L 74
		push		edx
@2@226:
   ;	
   ;		MoveYData:
   ;			_ECX=88;
   ;	
	?debug	L 76
	mov	ecx,large 88
   ;	
   ;			asm	rep	movsd//32 bits address
   ;	
	?debug	L 77
		rep	movsd	
   ;	
   ;			_ESI+=800;
   ;	
	?debug	L 78
	add	esi,large 800
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 79
		dec		edx
   ;	
   ;		asm	jnz	MoveYData
   ;	
	?debug	L 80
	jne	short @2@226
   ;	
   ;		/////////////////////////////////
   ;		asm	pop	edx
   ;	
	?debug	L 82
		pop		edx
   ;	
   ;		////////// Move V Data //////////
   ;		_ESI=_EBX;
   ;	
	?debug	L 84
	mov	esi,ebx
   ;	
   ;		asm	shr	edx,2	//_EDX/=4;
   ;	
	?debug	L 85
		shr		edx,2	
   ;	
   ;		_ESI+=0x240;	//VPlane
   ;	
	?debug	L 86
	add	esi,large 576
   ;	
   ;		asm	push	edx
   ;	
	?debug	L 87
		push		edx
@2@506:
   ;	
   ;		MoveVData:
   ;			_EBP=176/16;
   ;	
	?debug	L 89
	mov	ebp,large 11
@2@534:
   ;	
   ;			MoveVdata:
   ;			asm	mov	al,[esi+4]
   ;	
	?debug	L 91
		mov		al,[esi+4]
   ;	
   ;			asm	mov	cl,[esi+12]
   ;	
	?debug	L 92
		mov		cl,[esi+12]
   ;	
   ;			asm	mov	ah,[esi+6]
   ;	
	?debug	L 93
		mov		ah,[esi+6]
   ;	
   ;			asm	mov	ch,[esi+14]
   ;	
	?debug	L 94
		mov		ch,[esi+14]
   ;	
   ;			asm	shl	eax,16
   ;	
	?debug	L 95
		shl		eax,16
   ;	
   ;			asm	shl	ecx,16
   ;	
	?debug	L 96
		shl		ecx,16
   ;	
   ;			asm	mov	al,[esi]
   ;	
	?debug	L 97
		mov		al,[esi]
   ;	
   ;			asm	mov	cl,[esi+8]
   ;	
	?debug	L 98
		mov		cl,[esi+8]
   ;	
   ;			asm	mov	ah,[esi+2]
   ;	
	?debug	L 99
		mov		ah,[esi+2]
   ;	
   ;			asm	mov	es:[edi],eax
   ;	
	?debug	L 100
		mov		es:[edi],eax
   ;	
   ;			asm	mov	ch,[esi+10]
   ;	
	?debug	L 101
		mov		ch,[esi+10]
   ;	
   ;			asm	mov	es:[edi+4],ecx
   ;	
	?debug	L 102
		mov		es:[edi+4],ecx
   ;	
   ;			asm	add	edi,8
   ;	
	?debug	L 103
		add		edi,8
   ;	
   ;			asm	add	esi,16
   ;	
	?debug	L 104
		add		esi,16
   ;	
   ;			asm	dec	ebp
   ;	
	?debug	L 105
		dec		ebp
   ;	
   ;			asm	jnz	MoveVdata
   ;	
	?debug	L 106
	jne	short @2@534
   ;	
   ;			_ESI+=(976+0x480);
   ;	
	?debug	L 107
	add	esi,large 2128
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 108
		dec		edx
   ;	
   ;		asm	jnz	MoveVData
   ;	
	?debug	L 109
	jne	short @2@506
   ;	
   ;		////////// Move U Data //////////
   ;		_ESI=_EBX;	//UPlane
   ;	
	?debug	L 111
	mov	esi,ebx
   ;	
   ;		asm	pop	edx
   ;	
	?debug	L 112
		pop		edx
@2@1122:
   ;	
   ;		MoveUData:
   ;			_EBP=176/16;
   ;	
	?debug	L 114
	mov	ebp,large 11
@2@1150:
   ;	
   ;			MoveUdata:
   ;			asm	mov	al,[esi+4]
   ;	
	?debug	L 116
		mov		al,[esi+4]
   ;	
   ;			asm	mov	cl,[esi+12]
   ;	
	?debug	L 117
		mov		cl,[esi+12]
   ;	
   ;			asm	mov	ah,[esi+6]
   ;	
	?debug	L 118
		mov		ah,[esi+6]
   ;	
   ;			asm	mov	ch,[esi+14]
   ;	
	?debug	L 119
		mov		ch,[esi+14]
   ;	
   ;			asm	shl	eax,16
   ;	
	?debug	L 120
		shl		eax,16
   ;	
   ;			asm	shl	ecx,16
   ;	
	?debug	L 121
		shl		ecx,16
   ;	
   ;			asm	mov	al,[esi]
   ;	
	?debug	L 122
		mov		al,[esi]
   ;	
   ;			asm	mov	cl,[esi+8]
   ;	
	?debug	L 123
		mov		cl,[esi+8]
   ;	
   ;			asm	mov	ah,[esi+2]
   ;	
	?debug	L 124
		mov		ah,[esi+2]
   ;	
   ;			asm	mov	es:[edi],eax
   ;	
	?debug	L 125
		mov		es:[edi],eax
   ;	
   ;			asm	mov	ch,[esi+10]
   ;	
	?debug	L 126
		mov		ch,[esi+10]
   ;	
   ;			asm	mov	es:[edi+4],ecx
   ;	
	?debug	L 127
		mov		es:[edi+4],ecx
   ;	
   ;			asm	add	edi,8
   ;	
	?debug	L 128
		add		edi,8
   ;	
   ;			asm	add	esi,16
   ;	
	?debug	L 129
		add		esi,16
   ;	
   ;			asm	dec	ebp
   ;	
	?debug	L 130
		dec		ebp
   ;	
   ;			asm	jnz	MoveUdata
   ;	
	?debug	L 131
	jne	short @2@1150
   ;	
   ;			_ESI+=(976+0x480);
   ;	
	?debug	L 132
	add	esi,large 2128
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 133
		dec		edx
   ;	
   ;		asm	jnz	MoveUData
   ;	
	?debug	L 134
	jne	short @2@1122
   ;	
   ;		asm	pop	ds
   ;	
	?debug	L 135
		pop		ds
   ;	
   ;	}
   ;	
	?debug	L 136
	pop	edi
	pop	esi
	db	066h
	ret
	?debug	E
	?debug	E
DRAWYVU9	endp
   ;	
   ;	void	PASCAL	FAR	DrawIF09(void)	//YVU9 Planar and pitch
   ;	
	?debug	L 138
	assume	cs:YUVRGB32_TEXT
DRAWIF09	proc	far
	?debug	B
	push	esi
	push	edi
	?debug	B
   ;	
   ;	{
   ;		_EDI=_EDI;
   ;	
	?debug	L 140
   ;	
   ;		asm	xor	eax,eax
   ;	
	?debug	L 141
		xor		eax,eax
   ;	
   ;		asm	push	ds
   ;	
	?debug	L 142
		push		ds
   ;	
   ;		_EDX=288;
   ;	
	?debug	L 143
	mov	edx,large 288
   ;	
   ;		asm	mov	ds,OffScrSel;
   ;	
	?debug	L 144
		mov		ds,_OffScrSel
   ;	
   ;		asm 	mov 	esi,[eax+4]
   ;	
	?debug	L 145
 		mov	 	esi,[eax+4]
   ;	
   ;		asm 	mov 	ebx,[eax+8]
   ;	
	?debug	L 146
 		mov	 	ebx,[eax+8]
   ;	
   ;		asm	mov 	ds,[eax+0x10]	//GS-> Video data
   ;	
	?debug	L 147
		mov	 	ds,[eax+010H]	
@3@226:
   ;	
   ;		///////// Move Y Data //////////
   ;		MoveYData:
   ;			_ECX=88;
   ;	
	?debug	L 150
	mov	ecx,large 88
   ;	
   ;			asm	rep	movsd//32 bits address
   ;	
	?debug	L 151
		rep	movsd	
   ;	
   ;			_ESI+=800;
   ;	
	?debug	L 152
	add	esi,large 800
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 153
		dec		edx
   ;	
   ;		asm	jnz	MoveYData
   ;	
	?debug	L 154
	jne	short @3@226
   ;	
   ;		/////////////////////////////////
   ;		////////// Move V Data //////////
   ;		_ESI=_EBX;
   ;	
	?debug	L 157
	mov	esi,ebx
   ;	
   ;		_ESI+=0x240;	//VPlane
   ;	
	?debug	L 158
	add	esi,large 576
   ;	
   ;		_EDX=72;
   ;	
	?debug	L 159
	mov	edx,large 72
@3@394:
   ;	
   ;		MoveVData:
   ;			_EBP=176/16;
   ;	
	?debug	L 161
	mov	ebp,large 11
@3@422:
   ;	
   ;			MoveVdata:
   ;			asm	mov	al,[esi+4]
   ;	
	?debug	L 163
		mov		al,[esi+4]
   ;	
   ;			asm	mov	cl,[esi+12]
   ;	
	?debug	L 164
		mov		cl,[esi+12]
   ;	
   ;			asm	mov	ah,[esi+6]
   ;	
	?debug	L 165
		mov		ah,[esi+6]
   ;	
   ;			asm	mov	ch,[esi+14]
   ;	
	?debug	L 166
		mov		ch,[esi+14]
   ;	
   ;			asm	shl	eax,16
   ;	
	?debug	L 167
		shl		eax,16
   ;	
   ;			asm	shl	ecx,16
   ;	
	?debug	L 168
		shl		ecx,16
   ;	
   ;			asm	mov	al,[esi]
   ;	
	?debug	L 169
		mov		al,[esi]
   ;	
   ;			asm	mov	cl,[esi+8]
   ;	
	?debug	L 170
		mov		cl,[esi+8]
   ;	
   ;			asm	mov	ah,[esi+2]
   ;	
	?debug	L 171
		mov		ah,[esi+2]
   ;	
   ;			asm	mov	es:[edi],eax
   ;	
	?debug	L 172
		mov		es:[edi],eax
   ;	
   ;			asm	mov	ch,[esi+10]
   ;	
	?debug	L 173
		mov		ch,[esi+10]
   ;	
   ;			asm	mov	es:[edi+4],ecx
   ;	
	?debug	L 174
		mov		es:[edi+4],ecx
   ;	
   ;			asm	add	edi,8
   ;	
	?debug	L 175
		add		edi,8
   ;	
   ;			asm	add	esi,16
   ;	
	?debug	L 176
		add		esi,16
   ;	
   ;			asm	dec	ebp
   ;	
	?debug	L 177
		dec		ebp
   ;	
   ;			asm	jnz	MoveVdata
   ;	
	?debug	L 178
	jne	short @3@422
   ;	
   ;			_ESI+=(976+0x480);
   ;	
	?debug	L 179
	add	esi,large 2128
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 180
		dec		edx
   ;	
   ;		asm	jnz	MoveVData
   ;	
	?debug	L 181
	jne	short @3@394
   ;	
   ;		////////// Move U Data //////////
   ;		_ESI=_EBX;	//UPlane
   ;	
	?debug	L 183
	mov	esi,ebx
   ;	
   ;		_EDX=72;
   ;	
	?debug	L 184
	mov	edx,large 72
@3@982:
   ;	
   ;		MoveUData:
   ;			_EBP=176/16;
   ;	
	?debug	L 186
	mov	ebp,large 11
@3@1010:
   ;	
   ;			MoveUdata:
   ;			asm	mov	al,[esi+4]
   ;	
	?debug	L 188
		mov		al,[esi+4]
   ;	
   ;			asm	mov	cl,[esi+12]
   ;	
	?debug	L 189
		mov		cl,[esi+12]
   ;	
   ;			asm	mov	ah,[esi+6]
   ;	
	?debug	L 190
		mov		ah,[esi+6]
   ;	
   ;			asm	mov	ch,[esi+14]
   ;	
	?debug	L 191
		mov		ch,[esi+14]
   ;	
   ;			asm	shl	eax,16
   ;	
	?debug	L 192
		shl		eax,16
   ;	
   ;			asm	shl	ecx,16
   ;	
	?debug	L 193
		shl		ecx,16
   ;	
   ;			asm	mov	al,[esi]
   ;	
	?debug	L 194
		mov		al,[esi]
   ;	
   ;			asm	mov	cl,[esi+8]
   ;	
	?debug	L 195
		mov		cl,[esi+8]
   ;	
   ;			asm	mov	ah,[esi+2]
   ;	
	?debug	L 196
		mov		ah,[esi+2]
   ;	
   ;			asm	mov	es:[edi],eax
   ;	
	?debug	L 197
		mov		es:[edi],eax
   ;	
   ;			asm	mov	ch,[esi+10]
   ;	
	?debug	L 198
		mov		ch,[esi+10]
   ;	
   ;			asm	mov	es:[edi+4],ecx
   ;	
	?debug	L 199
		mov		es:[edi+4],ecx
   ;	
   ;			asm	add	edi,8
   ;	
	?debug	L 200
		add		edi,8
   ;	
   ;			asm	add	esi,16
   ;	
	?debug	L 201
		add		esi,16
   ;	
   ;			asm	dec	ebp
   ;	
	?debug	L 202
		dec		ebp
   ;	
   ;			asm	jnz	MoveUdata
   ;	
	?debug	L 203
	jne	short @3@1010
   ;	
   ;			_ESI+=(976+0x480);
   ;	
	?debug	L 204
	add	esi,large 2128
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 205
		dec		edx
   ;	
   ;		asm	jnz	MoveUData
   ;	
	?debug	L 206
	jne	short @3@982
   ;	
   ;		asm	pop	ds
   ;	
	?debug	L 207
		pop		ds
   ;	
   ;	}
   ;	
	?debug	L 208
	pop	edi
	pop	esi
	db	066h
	ret
	?debug	E
	?debug	E
DRAWIF09	endp
   ;	
   ;	void	PASCAL	FAR	DrawYUY2(void)	//YUYV 4:2:2 byte ordering
   ;	
	?debug	L 209
	assume	cs:YUVRGB32_TEXT
DRAWYUY2	proc	far
	?debug	B
	push	esi
	push	edi
	?debug	B
   ;	
   ;	{
   ;		asm	xor	eax,eax
   ;	
	?debug	L 211
		xor		eax,eax
   ;	
   ;		asm	push	ds
   ;	
	?debug	L 212
		push		ds
   ;	
   ;	//	_EDX=VCDHigh;
   ;	//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
   ;	//	_ES=LinearSelSurface;
   ;		asm	mov	ds,OffScrSel;
   ;	
	?debug	L 216
		mov		ds,_OffScrSel
   ;	
   ;		asm 	mov 	esi,[eax+4]
   ;	
	?debug	L 217
 		mov	 	esi,[eax+4]
   ;	
   ;		asm	mov 	ecx,[eax+8]	//ECX->V,U plane
   ;	
	?debug	L 218
		mov	 	ecx,[eax+8]	
   ;	
   ;		asm	mov 	ds,[eax+0x10]	//DS-> Video data
   ;	
	?debug	L 219
		mov	 	ds,[eax+010H]	
   ;	
   ;		///////// Move YUYV Data //////////
   ;		asm	shr	edx,1//_EDX/=2;
   ;	
	?debug	L 221
		shr		edx,1
@4@226:
   ;	
   ;		MoveYUY2Data:
   ;			_EBP=176/2;
   ;	
	?debug	L 223
	mov	ebp,large 88
   ;	
   ;			asm	push	edx
   ;	
	?debug	L 224
		push		edx
@4@282:
   ;	
   ;			Move2LineData:
   ;			asm	mov	ah,[ecx+0x240]
   ;	
	?debug	L 226
		mov		ah,[ecx+0240H]
   ;	
   ;			asm	mov	bh,[ecx+0x241]
   ;	
	?debug	L 227
		mov		bh,[ecx+0241H]
   ;	
   ;			asm	mov	al,[esi+1]
   ;	
	?debug	L 228
		mov		al,[esi+1]
   ;	
   ;			asm	mov	bl,[esi+3]
   ;	
	?debug	L 229
		mov		bl,[esi+3]
   ;	
   ;			asm	shl	eax,16		//V0Y1
   ;	
	?debug	L 230
		shl		eax,16		
   ;	
   ;			asm	mov	dh,[ecx+0x240]
   ;	
	?debug	L 231
		mov		dh,[ecx+0240H]
   ;	
   ;			asm	shl	ebx,16		//V1Y3
   ;	
	?debug	L 232
		shl		ebx,16		
   ;	
   ;			asm	mov	al,[esi]
   ;	
	?debug	L 233
		mov		al,[esi]
   ;	
   ;			asm	mov	ah,[ecx]	//U0Y0
   ;	
	?debug	L 234
		mov		ah,[ecx]	
   ;	
   ;			asm	mov	dl,[esi+0x480+1]
   ;	
	?debug	L 235
		mov		dl,[esi+0480H+1]
   ;	
   ;			asm	shl	edx,16		//V0Y1
   ;	
	?debug	L 236
		shl		edx,16		
   ;	
   ;			asm	mov	bh,[ecx+1]	//U1Y2
   ;	
	?debug	L 237
		mov		bh,[ecx+1]	
   ;	
   ;			asm	mov	es:[edi],eax		//Y1V0Y0U0
   ;	
	?debug	L 238
		mov		es:[edi],eax		
   ;	
   ;			asm	mov	bl,[esi+2]
   ;	
	?debug	L 239
		mov		bl,[esi+2]
   ;	
   ;			asm	mov	es:[edi+4],ebx		//Y3V1Y2U1
   ;	
	?debug	L 240
		mov		es:[edi+4],ebx		
   ;	
   ;			asm	mov	dl,[esi+0x480]
   ;	
	?debug	L 241
		mov		dl,[esi+0480H]
   ;	
   ;			asm	mov	bh,[ecx+0x241]
   ;	
	?debug	L 242
		mov		bh,[ecx+0241H]
   ;	
   ;			asm	mov	dh,[ecx]	//U0Y0
   ;	
	?debug	L 243
		mov		dh,[ecx]	
   ;	
   ;			asm	mov	es:[edi+704],edx
   ;	
	?debug	L 244
		mov		es:[edi+704],edx
   ;	
   ;			asm	mov	bl,[esi+0x480+3]
   ;	
	?debug	L 245
		mov		bl,[esi+0480H+3]
   ;	
   ;			asm	shl	ebx,16		//V1Y3
   ;	
	?debug	L 246
		shl		ebx,16		
   ;	
   ;			asm	mov	bl,[esi+0x480+2]
   ;	
	?debug	L 247
		mov		bl,[esi+0480H+2]
   ;	
   ;			asm	add	esi,4
   ;	
	?debug	L 248
		add		esi,4
   ;	
   ;			asm	mov	bh,[ecx+1]	//U1Y2
   ;	
	?debug	L 249
		mov		bh,[ecx+1]	
   ;	
   ;			asm	add	ecx,2
   ;	
	?debug	L 250
		add		ecx,2
   ;	
   ;			asm	mov	es:[edi+704+4],ebx
   ;	
	?debug	L 251
		mov		es:[edi+704+4],ebx
   ;	
   ;			asm	add	edi,8
   ;	
	?debug	L 252
		add		edi,8
   ;	
   ;			asm	dec	ebp
   ;	
	?debug	L 253
		dec		ebp
   ;	
   ;			asm	jnz	Move2LineData
   ;	
	?debug	L 254
	jne	short @4@282
   ;	
   ;		_ECX+=976;
   ;	
	?debug	L 255
	add	ecx,large 976
   ;	
   ;		asm	pop	edx
   ;	
	?debug	L 256
		pop		edx
   ;	
   ;		_ESI+=(800+0x480);
   ;	
	?debug	L 257
	add	esi,large 1952
   ;	
   ;		_EDI+=704;
   ;	
	?debug	L 258
	add	edi,large 704
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 259
		dec		edx
   ;	
   ;		asm	jnz	MoveYUY2Data
   ;	
	?debug	L 260
	jne	near ptr  @4@226
   ;	
   ;		asm	pop	ds
   ;	
	?debug	L 261
		pop		ds
   ;	
   ;	}
   ;	
	?debug	L 262
	pop	edi
	pop	esi
	db	066h
	ret
	?debug	E
	?debug	E
DRAWYUY2	endp
   ;	
   ;	void	PASCAL	FAR	DrawYVYU(void)	//YVYU 4:2:2 byte ordering
   ;	
	?debug	L 264
	assume	cs:YUVRGB32_TEXT
DRAWYVYU	proc	far
	?debug	B
	push	esi
	push	edi
	?debug	B
   ;	
   ;	{
   ;		asm	xor	eax,eax
   ;	
	?debug	L 266
		xor		eax,eax
   ;	
   ;		asm	push	ds
   ;	
	?debug	L 267
		push		ds
   ;	
   ;	//	_EDX=VCDHigh;
   ;	//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
   ;	//	_ES=LinearSelSurface;
   ;		asm	mov	ds,OffScrSel;
   ;	
	?debug	L 271
		mov		ds,_OffScrSel
   ;	
   ;		asm 	mov 	esi,[eax+4]
   ;	
	?debug	L 272
 		mov	 	esi,[eax+4]
   ;	
   ;		asm	mov 	ecx,[eax+8]
   ;	
	?debug	L 273
		mov	 	ecx,[eax+8]
   ;	
   ;		asm	mov 	ds,[eax+0x10]	//DS-> Video data
   ;	
	?debug	L 274
		mov	 	ds,[eax+010H]	
   ;	
   ;		///////// Move YUYV Data //////////
   ;		asm	shr	edx,1	//DX=_EBX/2;
   ;	
	?debug	L 276
		shr		edx,1	
@5@226:
   ;	
   ;		MoveYUY2Data:
   ;			_EBP=176/2;
   ;	
	?debug	L 278
	mov	ebp,large 88
   ;	
   ;			asm	push	edx
   ;	
	?debug	L 279
		push		edx
@5@282:
   ;	
   ;			Move2LineData:
   ;			asm	mov	ah,[ecx]	//U0
   ;	
	?debug	L 281
		mov		ah,[ecx]	
   ;	
   ;			asm	mov	bl,[esi+3]	//Y3
   ;	
	?debug	L 282
		mov		bl,[esi+3]	
   ;	
   ;			asm	mov	al,[esi+1]	//Y1
   ;	
	?debug	L 283
		mov		al,[esi+1]	
   ;	
   ;			asm	mov	bh,[ecx+1]	//U1
   ;	
	?debug	L 284
		mov		bh,[ecx+1]	
   ;	
   ;			asm	shl	eax,16		//U0Y1
   ;	
	?debug	L 285
		shl		eax,16		
   ;	
   ;			asm	mov	dh,[ecx]	//U0
   ;	
	?debug	L 286
		mov		dh,[ecx]	
   ;	
   ;			asm	shl	ebx,16		//U1Y3
   ;	
	?debug	L 287
		shl		ebx,16		
   ;	
   ;			asm	mov	dl,[esi+0x480+1]
   ;	
	?debug	L 288
		mov		dl,[esi+0480H+1]
   ;	
   ;			asm	mov	al,[esi]
   ;	
	?debug	L 289
		mov		al,[esi]
   ;	
   ;			asm	mov	bh,[ecx+0x241]	//V1Y2
   ;	
	?debug	L 290
		mov		bh,[ecx+0241H]	
   ;	
   ;			asm	shl	edx,16		//U0Y1
   ;	
	?debug	L 291
		shl		edx,16		
   ;	
   ;			asm	mov	ah,[ecx+0x240]	//V0Y0
   ;	
	?debug	L 292
		mov		ah,[ecx+0240H]	
   ;	
   ;			asm	mov	bl,[esi+2]
   ;	
	?debug	L 293
		mov		bl,[esi+2]
   ;	
   ;			asm	mov	dl,[esi+0x480]
   ;	
	?debug	L 294
		mov		dl,[esi+0480H]
   ;	
   ;			asm	mov	es:[edi+4],ebx		//Y2V1Y3U1
   ;	
	?debug	L 295
		mov		es:[edi+4],ebx		
   ;	
   ;			asm	mov	dh,[ecx+0x240]	//V0Y0
   ;	
	?debug	L 296
		mov		dh,[ecx+0240H]	
   ;	
   ;			asm	mov	es:[edi],eax		//Y0V0Y1U0
   ;	
	?debug	L 297
		mov		es:[edi],eax		
   ;	
   ;			//////////// Line 2 ////////////
   ;			asm	mov	bh,[ecx+1]	//U1
   ;	
	?debug	L 299
		mov		bh,[ecx+1]	
   ;	
   ;			asm	mov	es:[edi+704],edx	//Y0V0Y1U0
   ;	
	?debug	L 300
		mov		es:[edi+704],edx	
   ;	
   ;			asm	mov	bl,[esi+0x480+3]
   ;	
	?debug	L 301
		mov		bl,[esi+0480H+3]
   ;	
   ;			asm	shl	ebx,16		//U1Y3
   ;	
	?debug	L 302
		shl		ebx,16		
   ;	
   ;			asm	mov	bl,[esi+0x480+2]
   ;	
	?debug	L 303
		mov		bl,[esi+0480H+2]
   ;	
   ;			asm	add	esi,4
   ;	
	?debug	L 304
		add		esi,4
   ;	
   ;			asm	mov	bh,[ecx+0x241]	//V1Y2
   ;	
	?debug	L 305
		mov		bh,[ecx+0241H]	
   ;	
   ;			asm	add	ecx,2
   ;	
	?debug	L 306
		add		ecx,2
   ;	
   ;			asm	mov	es:[edi+704+4],ebx	//Y2V1Y3U1
   ;	
	?debug	L 307
		mov		es:[edi+704+4],ebx	
   ;	
   ;			asm	add	edi,8
   ;	
	?debug	L 308
		add		edi,8
   ;	
   ;			asm	dec	ebp
   ;	
	?debug	L 309
		dec		ebp
   ;	
   ;			asm	jnz	Move2LineData
   ;	
	?debug	L 310
	jne	short @5@282
   ;	
   ;		_ECX+=976;
   ;	
	?debug	L 311
	add	ecx,large 976
   ;	
   ;		asm	pop	edx
   ;	
	?debug	L 312
		pop		edx
   ;	
   ;		_ESI+=(800+0x480);
   ;	
	?debug	L 313
	add	esi,large 1952
   ;	
   ;		_EDI+=704;
   ;	
	?debug	L 314
	add	edi,large 704
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 315
		dec		edx
   ;	
   ;		asm	jnz	MoveYUY2Data
   ;	
	?debug	L 316
	jne	near ptr  @5@226
   ;	
   ;		asm	pop	ds
   ;	
	?debug	L 317
		pop		ds
   ;	
   ;	}
   ;	
	?debug	L 318
	pop	edi
	pop	esi
	db	066h
	ret
	?debug	E
	?debug	E
DRAWYVYU	endp
   ;	
   ;	void	PASCAL	FAR	DrawUYVY(void)	//UYVY 4:2:2 byte ordering
   ;	
	?debug	L 319
	assume	cs:YUVRGB32_TEXT
DRAWUYVY	proc	far
	?debug	B
	push	esi
	push	edi
	?debug	B
   ;	
   ;	{
   ;		asm	xor	eax,eax
   ;	
	?debug	L 321
		xor		eax,eax
   ;	
   ;		asm	push	ds
   ;	
	?debug	L 322
		push		ds
   ;	
   ;	//	_EDX=VCDHigh;
   ;	//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
   ;	//	_ES=LinearSelSurface;
   ;		asm	mov	ds,OffScrSel;
   ;	
	?debug	L 326
		mov		ds,_OffScrSel
   ;	
   ;		asm 	mov 	esi,[eax+4]
   ;	
	?debug	L 327
 		mov	 	esi,[eax+4]
   ;	
   ;		asm	mov 	ecx,[eax+8]
   ;	
	?debug	L 328
		mov	 	ecx,[eax+8]
   ;	
   ;		asm	mov 	ds,[eax+0x10]	//DS-> Video data
   ;	
	?debug	L 329
		mov	 	ds,[eax+010H]	
   ;	
   ;		///////// Move YUYV Data //////////
   ;		asm	shr	edx,1	//_EDX=_EBX/2;
   ;	
	?debug	L 331
		shr		edx,1	
@6@226:
   ;	
   ;		MoveYUY2Data:
   ;			_EBP=176/2;
   ;	
	?debug	L 333
	mov	ebp,large 88
   ;	
   ;			asm	push	edx
   ;	
	?debug	L 334
		push		edx
@6@282:
   ;	
   ;			Move2LineData:
   ;			asm	mov	al,[ecx+0x240]	//V0
   ;	
	?debug	L 336
		mov		al,[ecx+0240H]	
   ;	
   ;			asm	mov	bl,[ecx+0x241]	//V1
   ;	
	?debug	L 337
		mov		bl,[ecx+0241H]	
   ;	
   ;			asm	mov	ah,[esi+1]
   ;	
	?debug	L 338
		mov		ah,[esi+1]
   ;	
   ;			asm	mov	bh,[esi+3]
   ;	
	?debug	L 339
		mov		bh,[esi+3]
   ;	
   ;			asm	shl	eax,16		//[Y1V0][0]
   ;	
	?debug	L 340
		shl		eax,16		
   ;	
   ;			asm	mov	dl,[ecx+0x240]	//V0
   ;	
	?debug	L 341
		mov		dl,[ecx+0240H]	
   ;	
   ;			asm	shl	ebx,16		//[Y3V1][0]
   ;	
	?debug	L 342
		shl		ebx,16		
   ;	
   ;			asm	mov	dh,[esi+0x480+1]	//Y1
   ;	
	?debug	L 343
		mov		dh,[esi+0480H+1]	
   ;	
   ;			asm	shl	edx,16		//[Y1V0][0]
   ;	
	?debug	L 344
		shl		edx,16		
   ;	
   ;			asm	mov	ah,[esi]
   ;	
	?debug	L 345
		mov		ah,[esi]
   ;	
   ;			asm	mov	bh,[esi+2]
   ;	
	?debug	L 346
		mov		bh,[esi+2]
   ;	
   ;			asm	mov	al,[ecx]	//[Y0U0]
   ;	
	?debug	L 347
		mov		al,[ecx]	
   ;	
   ;			asm	mov	es:[edi],eax		//U0Y0V0Y1
   ;	
	?debug	L 348
		mov		es:[edi],eax		
   ;	
   ;			asm	mov	bl,[ecx+1]	//[Y2U1]
   ;	
	?debug	L 349
		mov		bl,[ecx+1]	
   ;	
   ;			asm	mov	es:[edi+4],ebx		//U1Y2V1Y3
   ;	
	?debug	L 350
		mov		es:[edi+4],ebx		
   ;	
   ;			asm	mov	dh,[esi+0x480]
   ;	
	?debug	L 351
		mov		dh,[esi+0480H]
   ;	
   ;			asm	mov	dl,[ecx]		//[Y0U0]
   ;	
	?debug	L 352
		mov		dl,[ecx]		
   ;	
   ;			asm	mov	bl,[ecx+0x241]	//V1
   ;	
	?debug	L 353
		mov		bl,[ecx+0241H]	
   ;	
   ;			asm	mov	es:[edi+704],edx	//U0Y0V0Y1
   ;	
	?debug	L 354
		mov		es:[edi+704],edx	
   ;	
   ;			asm	mov	bh,[esi+0x480+3]	//Y3
   ;	
	?debug	L 355
		mov		bh,[esi+0480H+3]	
   ;	
   ;			asm	shl	ebx,16		//[Y3V1][0]
   ;	
	?debug	L 356
		shl		ebx,16		
   ;	
   ;			asm	mov	bh,[esi+0x480+2]
   ;	
	?debug	L 357
		mov		bh,[esi+0480H+2]
   ;	
   ;			asm	add	esi,4
   ;	
	?debug	L 358
		add		esi,4
   ;	
   ;			asm	mov	bl,[ecx+1]		//[Y2U1]
   ;	
	?debug	L 359
		mov		bl,[ecx+1]		
   ;	
   ;			asm	add	ecx,2
   ;	
	?debug	L 360
		add		ecx,2
   ;	
   ;			asm	mov	es:[edi+704+4],ebx	//U1Y2V1Y3
   ;	
	?debug	L 361
		mov		es:[edi+704+4],ebx	
   ;	
   ;			asm	add	edi,8
   ;	
	?debug	L 362
		add		edi,8
   ;	
   ;			asm	dec	ebp
   ;	
	?debug	L 363
		dec		ebp
   ;	
   ;			asm	jnz	Move2LineData
   ;	
	?debug	L 364
	jne	short @6@282
   ;	
   ;		_ECX+=976;
   ;	
	?debug	L 365
	add	ecx,large 976
   ;	
   ;		asm	pop	edx
   ;	
	?debug	L 366
		pop		edx
   ;	
   ;		_ESI+=(800+0x480);
   ;	
	?debug	L 367
	add	esi,large 1952
   ;	
   ;		_EDI+=704;
   ;	
	?debug	L 368
	add	edi,large 704
   ;	
   ;		asm	dec	edx
   ;	
	?debug	L 369
		dec		edx
   ;	
   ;		asm	jnz	MoveYUY2Data
   ;	
	?debug	L 370
	jne	near ptr  @6@226
   ;	
   ;		asm	pop	ds
   ;	
	?debug	L 371
		pop		ds
   ;	
   ;	}
   ;	
	?debug	L 372
	pop	edi
	pop	esi
	db	066h
	ret
	?debug	E
	?debug	E
DRAWUYVY	endp
	?debug	C E9
	?debug	C FA00000000
YUVRGB32_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
_DATA	ends
YUVRGB32_TEXT	segment byte public use32 'CODE'
YUVRGB32_TEXT	ends
	extrn	_OffScrSel:word
	public	DRAWYVU9
	public	DRAWIF09
	public	DRAWUYVY
	public	DRAWYVYU
	public	DRAWYUY2
	public	DRAWYVU12
_s@	equ	s@
	?debug	C EA0109
	?debug	C EB0A5F4F666653637253656C0400
	?debug	C E31800000023010500
	?debug	C EC084452415759565539181800
	?debug	C E31900000023010500
	?debug	C EC084452415749463039191800
	?debug	C E31A00000023010500
	?debug	C EC0844524157555956591A1800
	?debug	C E31B00000023010500
	?debug	C EC0844524157595659551B1800
	?debug	C E31C00000023010500
	?debug	C EC0844524157595559321C1800
	?debug	C E31D00000023010500
	?debug	C EC094452415759565531321D1800
	?debug	C E60548445256520A06000548484F4F4B0C060006+
	?debug	C 48414343454C0A060004484457500A0600074843+
	?debug	C 5552534F520A0600054849434F4E0A060005484D+
	?debug	C 454E550A06000448574E440A060009484D455441+
	?debug	C 46494C450A060008434F4C4F525245460C060005+
	?debug	C 48464F4E540A0600084850414C455454450A0600+
	?debug	C 044852474E0A0600064842525553480A06000448+
	?debug	C 50454E0A060007484249544D41500A0600074847+
	?debug	C 44494F424A0A0600034844430A06000548525352+
	?debug	C 430A0600054846494C4504060005485441534B0A+
	?debug	C 060007484D4F44554C450A06000948494E535441+
	?debug	C 4E43450A060004485354520A06000441544F4D0A+
	?debug	C 06000B4C4F43414C48414E444C450A06000C474C+
	?debug	C 4F42414C48414E444C450A060006484C4F43414C+
	?debug	C 0A06000748474C4F42414C0A06000648414E444C+
	?debug	C 450A0600074C524553554C54060600064C504152+
	?debug	C 414D0606000657504152414D0A06000455494E54+
	?debug	C 0A06000544574F52440C060004574F52440A0600+
	?debug	C 044259544508060004424F4F4C040600
	end
