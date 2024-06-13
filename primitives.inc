	defcode "DROP", 0, DROP
		inc sp
		NEXT

	defcode "SWAP", 0, SWAP_
		pop hl
		ld a, h
		ld h, l
		ld l, a
		push hl
		NEXT

	defcode "DUP", 0, DUP
		ld hl, sp + 0
		ld a, [hld]
		ld [hl], a
		ld sp, hl
		NEXT
	
	defcode "OVER", 0, OVER
		ld hl, sp + 1
		ld a, [hld]
		dec hl
		ld [hl], a
		ld sp, hl
		NEXT
	
	defcode "ROT", 0, ROT
		pop af
		dec sp
		pop hl
		push af
		push hl
		inc sp
		NEXT

	defcode "-ROT", 0, NROT
		dec sp
		pop af
		pop hl
		push af
		inc sp
		push hl
		NEXT
	
	defcode "2DROP", 0, TWODROP
		inc sp
		inc sp
		NEXT

	defcode "2DUP", 0, TWODUP
		pop hl
		push hl
		push hl
		NEXT
	
	defcode "2SWAP", 0, TWOSWAP
		pop af
		pop hl
		push af
		push hl
		NEXT
	
	defcode "?DUP", 0, QDUP
		ld hl, sp + 0
		ld a, [hl]
		and a, a ; cp a, 0
		jr z, .after_dup
		dec hl
		ld [hl], a
		dec sp
		.after_dup:
		NEXT

	defcode "1+", 0, INCR
		ld hl, sp + 0
		inc [hl]
		NEXT

	defcode "1-", 0, DECR
		ld hl, sp + 0
		dec [hl]
		NEXT
	
	defcode "2+", 0, INCR2
		ld hl, sp + 0
		inc [hl]
		inc [hl]
		NEXT
	
	defcode "2-", 0, DECR2
		ld hl, sp + 0
		dec [hl]
		dec [hl]
		NEXT
	
	defcode "+", 0, ADD_
		ld hl, sp + 0
		ld a, [hli]
		add a, [hl]
		NEXT

	; defcode "*", 0, MUL_
	; defcode "/MOD", 0, DIVMOD
	
	defcode "=", 0, EQU_
		pop hl
		ld a, h
		cp l
		ld a, 1
		jr z, .save_result
		ld a, 0
		.save_result
		ld [hl], a
		dec sp
		NEXT

	defcode "<>", 0, NEQU
		pop hl
		ld a, h
		cp l
		ld a, 1
		jr nz, .save_result
		ld a, 0
		.save_result
		ld [hl], a
		dec sp
		NEXT

	;defcode "<",1,,LT
	;defcode ">",1,,GT
	;defcode "<=",2,,LE
	;defcode ">=",2,,GE

	defcode "0=", 0, ZEQU
		ld hl, sp + 0
		ld a, [hl]
		and a, a
		ld a, 1
		jp z, .save_results
		ld a, 0
		.save_results
		ld [hl], a
		NEXT
	
	defcode "0<>", 0, ZNEQU
		ld hl, sp + 0
		ld a, [hl]
		and a, a
		ld a, 1
		jp nz, .save_results
		ld a, 0
		.save_results
		ld [hl], a
		NEXT
	
	; defcode "0<",2,,ZLT
	; defcode "0>",2,,ZGT
	; defcode "0<=",3,,ZLE
	; defcode "0>=",3,,ZGE

	defcode "AND", 0, AND_
		pop hl
		ld a, h
		and a, l
		push af
		inc sp
		NEXT

	defcode "OR", 0, OR_
		pop hl
		ld a, h
		or a, l
		push af
		inc sp
		NEXT

	defcode "XOR", 0, XOR_
		pop hl
		ld a, h
		xor a, l
		push af
		inc sp
		NEXT

	defcode "INVERT", 0, INVERT
		ld hl, sp+0
		ld a, [hl]
		cpl
		ld [hl], a
		NEXT
	
	defcode "EXIT", 0, EXIT
		POPRSP de
		NEXT
	
	defcode "LIT", 0, LIT
		; de += 2
		ld hl, 0
		add hl, de
		inc de
		inc de
		ld a, [hl]
		push af
		inc sp
		NEXT
	
	defcode "!", 0, STORE
		ld hl, sp + 2
		ld a, [hl]
		pop hl
		ld [hl], a
		inc sp
		NEXT
	
	defcode "C!", 0, STOREBYTE ; same as !
		jr code_STORE
	
	defcode "@", 0, FETCH
		pop hl
		ld a, [hl]
		dec sp
		ld hl, sp + 0
		ld [hl], a
		NEXT

	defcode "C@", 0, FETCHBYTE ; same as @
		jr code_FETCH
		NEXT

	defcode "+!", 0, ADDSTORE
		ld hl, sp + 2
		ld a, [hl]
		pop hl
		add a, [hl]
		ld [hl], a
		inc sp
		NEXT

	defcode "-!", 0, SUBSTORE
		ld hl, sp + 2
		ld a, [hl]
		pop hl
		sub a, [hl]
		ld [hl], a
		inc sp
		NEXT
	
	defcode "C@C!", 0, CCOPY
		ld hl, sp + 2
		ld a, [hl]
		pop hl
		ld [hl], a
		inc sp
		inc sp
		NEXT

	; defcode "CMOVE",5,,CMOVE

	defcode ">R", 0, TOR
		pop hl
		PUSHRSP hl
		NEXT
	
	defcode "R>", 0, FROMR
		POPRSP hl
		push hl
		NEXT
	
	defcode "RSP@", 0, RSPFETCH
		ld hl, 0
		add hl, bc

		ld a, [hld]
		

		push bc
		NEXT
	
	; defcode "RSP!", 0, RSPSTORE
		