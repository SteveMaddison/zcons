;
; Test Program
;

; Tile indices
tile_letter_a:	equ 	18
tile_number_0:	equ 	54

tile_border_tl:	equ	1
tile_border_lr:	equ	2
tile_border_tr:	equ	3
tile_border_tb:	equ	4
tile_border_bl:	equ	5
tile_border_br:	equ	6
tile_border_sr:	equ	7
tile_border_sl:	equ	8

tile_body:	equ	9
tile_head_up:	equ	10
tile_head_down:	equ	11
tile_head_left:	equ	12
tile_head_right:equ	13

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

vram_x:		equ	40
vram_y:		equ	30

screen_border_x:equ	1
screen_border_y:equ	1

screen_cols:	equ 	vram_x-(screen_border_x*2)
screen_rows:	equ 	vram_y-(screen_border_y*2)
screen_top_left:equ	vram_base + vram_x + screen_border_x

; variables
ram_base:		equ	0x8000
snake_buffer:		equ	ram_base
snake_buffer_size:	equ	(screen_cols-2)*(screen_rows-2)

snake_head:		equ	snake_buffer+snake_buffer_size-1
snake_tail:		equ	snake_head+2

score:			equ	snake_tail+2
var_end:		equ	score+2

; Start main program
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
txt_score:	defm	"SCORE 00000000\0"
txt_high:	defm	"HIGH 00000000\0"

pad_to_nim:	defm	"0123456789"

; 0x0066
nmi_handler:
		retn
start:
		ld	a,0
		call	clear_vram
draw_logo:
		ld      hl,screen_top_left	; get vram to place map
		ld	de,vram_x*8
		add	hl,de
		ld	de,(screen_cols-18)/2
		add	hl,de
		push	hl			; hl < de
		pop	de
		ld	hl,logo_map
		call	draw_map

flash_push_start:
write_push_start:
		ld      hl,screen_top_left	; write text
		ld	de,vram_x*20
		add	hl,de
		ld	de,(screen_cols-10)/2
		add	hl,de
		push	hl
		pop	de
		ld	hl,txt_push_start
		call	write_text

		ld	b,30
loop_written:
		call	wait_vsync
		in	a,(p1_port_l)
		and	a,control_start
		jp	nz,start_pushed
		djnz	loop_written
clear_push_start:
		ld      hl,screen_top_left	; clear text
		ld	de,vram_x*20
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
		call	wait_vsync
		in	a,(p1_port_l)
		and	a,control_start
		jp	nz,start_pushed
		djnz	loop_cleared

		jp	flash_push_start

; Draw border, animated.
;+== SCORE 00000000 (=) HIGH 00000000 ==+
;0123456789012345678901234567890123456789
start_pushed:
		call	wait_vsync
		ld	a,0
		call	clear_vram
draw_border:
		ld	hl,screen_top_left+2
		ld	de,screen_top_left+screen_cols-3
		ld	(hl),tile_border_sr
		ld	a,tile_border_sl
		ld	(de),a
;		call	wait_vsync

		dec	hl
		inc	de
		ld	(hl),tile_border_lr
		ld	a,tile_border_lr
		ld	(de),a
;		call	wait_vsync

		dec	hl
		inc	de
		ld	(hl),tile_border_tl
		ld	a,tile_border_tr
		ld	(de),a

		ld	b,screen_rows-2
		ld	hl,screen_top_left+vram_x
draw_border_down:
;		call	wait_vsync
		ld	(hl),tile_border_tb
		ld	de,vram_x
		add	hl,de
		ld	de,(screen_border_x*2)+1
		sbc	hl,de
		ld	(hl),tile_border_tb
		add	hl,de
		djnz	draw_border_down
draw_border_bottom_corners:
;		call	wait_vsync
		ld	(hl),tile_border_bl
		ld	de,screen_cols-1
		add	hl,de
		ld	(hl),tile_border_br

		dec	hl
		push	hl
		ld	de,screen_cols-3
		sbc	hl,de
		pop	de
		ld	b,(screen_cols/2)-1
		ld	a,tile_border_lr
draw_border_bottom:
;		call	wait_vsync
		ld	(hl),a
		ld	(de),a
		inc	hl
		dec	de
		djnz	draw_border_bottom

start_game:		
		call	wait_vsync
		ld	hl,0
		ld	(score),hl
		call	draw_scores
init_new_snake:
		ld	hl,snake_buffer		; point head and tail to first
		ld	(snake_head),hl		; slot in buffer.
		ld	(snake_tail),hl
		ld	de,screen_top_left+(vram_x*screen_rows/2)+(screen_cols/2)
		ld	hl,snake_head
		ld	(hl),e
		inc	hl
		ld	(hl),d
		push	de
		pop	hl
		ld	(hl),tile_head_right
loop:
		jp	loop	

draw_scores:
		ld	de,screen_top_left+4
		ld	hl,txt_score
		call	write_text

		ld	hl,(score)
		ld	de,screen_top_left+4+6+8
		call	write_number

		ld	de,screen_top_left+screen_cols-17
		ld	hl,txt_high
		call	write_text

		ret

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
		ld	hl,vram_x
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
		cp	0
		jp	z,write_text_end

		cp	65
		jp	nc,is_letter
		cp	48
		jp	nc,is_number
no_char:
		ld	a,0
		jp	write_char
is_number:	
		sub	a,48
		add	a,tile_number_0
		jp	write_char
is_letter:	
		sub	a,65
		add	a,tile_letter_a
		jp	write_char
write_char:
		ld	(de),a
		inc	hl
		inc	de
		jp	write_text
write_text_end:
		ret

; DE: VRAM offset of rightmost digit.
; HL: 16-bit number 
write_number:
		push	de		; save VRAM address
		push	hl
		pop	bc
write_number_div:
		ld	de,10		; set divisor
		call	int_div_16
		ld	a,tile_number_0
		add	a,l
		pop	de
		ld	(de),a
		dec	de
		push	de		; for next time
		ld	a,b
		or	c
		jp	nz,write_number_div
write_number_end:
		pop	de
		ret

; Divide two 16-bit integers with 16-bit result
; In:   BC = dividend, DE = divisor
; Out:  BC = quotient, HL = remainder
int_div_16:
                push    af
                ld      hl,0
                ld      a,b
                ld      b,16
int_div_16_loop:
                rl      c
                rla
                adc     hl,hl
                sbc     hl,de
                jr      nc,int_div_16_no_add
                add     hl,de
int_div_16_no_add:
                djnz    int_div_16_loop
                rl      c
                rla
                cpl
                ld      b,a
                ld      a,c
                cpl
                ld      c,a
                pop     af
                ret

; A: tile to clear with
clear_vram:
		ld	hl,vram_base
		ld	b,vram_x
		ld	d,vram_y
clear_vram_loop:
		ld	(hl),a
		inc	hl
    		djnz	clear_vram_loop
		dec	d
		ld	b,vram_x
		jp	nz,clear_vram_loop
		ret	

wait_vsync:
		halt
		ret

; Screen maps
logo_map:
		defb	18, 6	; x, y
		defb	144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161
		defb	162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179
		defb	180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197
		defb	198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215
		defb	216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233
		defb	234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251
