;
; Test Program
;

init:		org	0			; program starts at 0x0000
		di				; turn off interrupts
		ld	sp,0x0000		; first push will make this 0xfffe
		jp	start

title:		defm	"Test Program\0"
version:	defm	"0.0.1\0"

; Pad to 0x38 for interrupt
padding:	defm	"                          "
;include	"intr.s"

; Includes
;include		"uart.s"

start:		
		ld	a,' '
