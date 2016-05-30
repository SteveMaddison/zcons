;
; Test Program
;

; Tile indices
tile_letter_a:	equ 	18
tile_number_0:	equ 	54

; Controller staes
control_up:	equ	0x01
control_down:	equ	0x02
control_left:	equ	0x04
control_right:	equ	0x08
control_a:	equ	0x10
control_start:	equ	0x20
control_b:	equ	0x10
control_c:	equ	0x20

; Conrtoller IO ports
p1_port_l:	equ	0x20
p1_port_h:	equ	0x21

p2_port_l:	equ	0x22
p2_port_h:	equ	0x23

; screen co-ordinates
vram_base:	equ	0xf000

screen_cols:	equ 	40
screen_rows:	equ 	30


init:		org	0			; program starts at 0x0000
		ei				; enable interrupts
		ld	sp,0x0000		; first push will make this 0xfffe
		jp	start

title:		defm	"Snake Game\0"
version:	defm	"0.0.1\0"

txt_push_start:	defm	"PUSH START\0"
txt_game_over:	defm	"GAME OVER\0"
txt_high_scores:
		defm	"HIGH SCORES\0"
txt_ready:	defm	"READY\0"

pad_to_nim:	defm	"0123456789"
		defm	"0123456789"
		defm	"0123456789"
		defm	"012345678"

; 0x0066
nmi_handler:
		retn
start:
draw_logo:
		ld      hl,vram_base		; get start P1 map
		ld	de,screen_cols*10
		add	hl,de
		ld	de,(screen_cols-18)/2
		add	hl,de
		push	hl			; hl < de
		pop	de
		ld	hl,logo_map
		call	draw_map

flash_push_start:
write_push_start:
		ld      hl,vram_base		; write text
		ld	de,screen_cols*20
		add	hl,de
		ld	de,(screen_cols-10)/2
		add	hl,de
		push	hl
		pop	de
		ld	hl,txt_push_start
		call	write_text

		ld	b,30
loop_written:
		call	wait_for_vsync
		djnz	loop_written
clear_push_start:
		ld      hl,vram_base		; clear text
		ld	de,screen_cols*20
		add	hl,de
		ld	de,(screen_cols-10)/2
		add	hl,de

		ld	b,10
clear_letter:
		ld	(hl),0
		inc hl
		djnz	clear_letter

		ld	b,30
loop_cleared:
		call	wait_for_vsync
		djnz	loop_cleared

		jp	flash_push_start

; DE: VRAM offset of top-left corner.
; HL: address of map data (x size, y size, data...)
draw_map:
		ld	b,(hl)			; x size
		inc	hl
		ld	c,(hl)			; y size
		inc	hl
draw_map_row:
		push	bc			; remember x size
		push	de			; remember start of row
draw_map_col:
		ld	a,(hl)
		ld	(de),a
		inc	de
		inc	hl
		djnz	draw_map_col	

		pop	de			; get start of row
		push	hl			; move down one row
		ld	hl,screen_cols
		add	hl,de
		push	hl
		pop	de
		pop	hl

		pop	af			; get x size back in B, but
		ld	b,a			; without affecting C
		dec	c
		jp	nz,draw_map_row

		ret

; DE: VRAM offset of top-left corner.
; HL: address of text, NUL-terminated 
write_text:
		ld	a,(hl)
		or	a,0
		jp	z,write_text_end

		sub	a,65			; ASCII 'A'
		jp	nc,is_letter
		ld	a,0
		jp	write_char
is_letter:	
		add	a,tile_letter_a
write_char:
		ld	(de),a
		inc	hl
		inc	de
		jp	write_text
write_text_end:
		ret

wait_for_vsync:
		halt
		ret

; Screen maps
logo_map:
		defb	18, 6						; x, y
		defb	144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161
		defb	162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179
		defb	180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197
		defb	198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215
		defb	216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233
		defb	234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251
