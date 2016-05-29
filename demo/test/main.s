;
; Test Program
;

; Tile indices
tile_letter_1:	equ 	28
tile_letter_2:	equ 	29

tile_up:	equ     1
tile_down:	equ     2
tile_left:	equ     3
tile_right:	equ     4
tile_a:		equ     5
tile_b:		equ     6
tile_c:		equ     7
tile_start:	equ     8

tile_selected:	equ     16			; offset to highlighted tile

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

controller_y:	equ	5

p1_map_left:	equ	4
p2_offset:	equ	(screen_cols/2)-1


init:		org	0			; program starts at 0x0000
		di				; turn off interrupts
		ld	sp,0x0000		; first push will make this 0xfffe
		jp	start

title:		defm	"Test Program\0"
version:	defm	"0.0.1\0"


start:		
init_screen:
draw_controller_map_for_p1:
                ld      hl,vram_base		; get start P1 map
		ld	de,screen_cols*controller_y
		add	hl,de
		ld	de,p1_map_left
		add	hl,de
		push	hl			; hl < de
		pop	de
		ld	hl,controller_map
		call	draw_map
draw_controller_map_for_p2:
		ld      hl,vram_base		; get start P2 map
		ld	de,screen_cols*controller_y
		add	hl,de
		ld	de,p1_map_left+p2_offset
		add	hl,de
		push	hl			; hl < de
		pop	de
		ld	hl,controller_map
		call	draw_map
draw_controller_numbers_over_maps:
		ld      hl,vram_base		; get start P1 map
		ld	de,screen_cols*controller_y
		add	hl,de
		ld	de,p1_map_left+5
		add	hl,de
		ld	(hl),tile_letter_1
		ld	de,p2_offset
		add	hl,de
		ld	(hl),tile_letter_2

draw_p1_controls:
                ld      hl,vram_base		; get start P1 map
		ld	de,screen_cols*controller_y
		add	hl,de
		ld	de,p1_map_left
		add	hl,de

check_p1_start:
		ld	de,8
		add	hl,de
                in      a,(p1_port_l)
                and     control_start
                jp      nz,p1_start_not_pressed
p1_start_pressed:
                ld      (hl),tile_start
		inc	hl
                ld      (hl),tile_start+1
		inc	hl
                ld      (hl),tile_start+2
                jp	check_p1_up
p1_start_not_pressed:                
                ld      (hl),tile_start+tile_selected
		inc	hl
                ld      (hl),tile_start+tile_selected+1
		inc	hl
                ld      (hl),tile_start+tile_selected+2

check_p1_up:
		ld	de,screen_cols-9
		add	hl,de
                in      a,(p1_port_l)
                and     control_up
                jp      nz,p1_up_not_pressed
p1_up_pressed:
                ld      (hl),tile_up
                jp	check_p1_left
p1_up_not_pressed:                
                ld      (hl),tile_up+tile_selected

check_p1_left:
		ld	de,screen_cols-1
		add	hl,de
                in      a,(p1_port_h)
                and     control_left
                jp      nz,p1_left_not_pressed
p1_left_pressed:
                ld      (hl),tile_left
                jp	check_p1_right
p1_left_not_pressed:                
                ld      (hl),tile_left+tile_selected
		
check_p1_right:
		inc	hl
		inc	hl
                in      a,(p1_port_h)
                and     control_right
                jp      nz,p1_right_not_pressed
p1_right_pressed:
                ld      (hl),tile_right
                jp	check_p1_a
p1_right_not_pressed:                
                ld      (hl),tile_right+tile_selected

check_p1_a:
		ld	de,5
		add	hl,de
                in      a,(p1_port_l)
                and     control_a
                jp      nz,p1_a_not_pressed
p1_a_pressed:
                ld      (hl),tile_a
                jp	check_p1_b
p1_a_not_pressed:                
                ld      (hl),tile_a+tile_selected

check_p1_b:
		inc	hl
		inc	hl
                in      a,(p1_port_h)
                and     control_b
                jp      nz,p1_b_not_pressed
p1_b_pressed:
                ld      (hl),tile_b
                jp	check_p1_c
p1_b_not_pressed:                
                ld      (hl),tile_b+tile_selected

check_p1_c:
		inc	hl
		inc	hl
                in      a,(p1_port_h)
                and     control_c
                jp      nz,p1_c_not_pressed
p1_c_pressed:
                ld      (hl),tile_c
                jp	check_p1_down
p1_c_not_pressed:                
                ld      (hl),tile_c+tile_selected

check_p1_down:
		ld	de,screen_cols-10
		add	hl,de
                in      a,(p1_port_l)
                and     control_down
                jp      nz,p1_down_not_pressed
p1_down_pressed:
                ld      (hl),tile_down
		jp	draw_p2_controls
p1_down_not_pressed:                
                ld      (hl),tile_down+tile_selected

draw_p2_controls:
                ld      hl,vram_base		; get start p2 map
		ld	de,screen_cols*controller_y
		add	hl,de
		ld	de,p1_map_left+p2_offset
		add	hl,de

check_p2_start:
		ld	de,8
		add	hl,de
                in      a,(p2_port_l)
                and     control_start
                jp      nz,p2_start_not_pressed
p2_start_pressed:
                ld      (hl),tile_start
		inc	hl
                ld      (hl),tile_start+1
		inc	hl
                ld      (hl),tile_start+2
                jp	check_p2_up
p2_start_not_pressed:                
                ld      (hl),tile_start+tile_selected
		inc	hl
                ld      (hl),tile_start+tile_selected+1
		inc	hl
                ld      (hl),tile_start+tile_selected+2

check_p2_up:
		ld	de,screen_cols-9
		add	hl,de
                in      a,(p2_port_l)
                and     control_up
                jp      nz,p2_up_not_pressed
p2_up_pressed:
                ld      (hl),tile_up
                jp	check_p2_left
p2_up_not_pressed:                
                ld      (hl),tile_up+tile_selected

check_p2_left:
		ld	de,screen_cols-1
		add	hl,de
                in      a,(p2_port_h)
                and     control_left
                jp      nz,p2_left_not_pressed
p2_left_pressed:
                ld      (hl),tile_left
                jp	check_p2_right
p2_left_not_pressed:                
                ld      (hl),tile_left+tile_selected
		
check_p2_right:
		inc	hl
		inc	hl
                in      a,(p2_port_h)
                and     control_right
                jp      nz,p2_right_not_pressed
p2_right_pressed:
                ld      (hl),tile_right
                jp	check_p2_a
p2_right_not_pressed:                
                ld      (hl),tile_right+tile_selected

check_p2_a:
		ld	de,5
		add	hl,de
                in      a,(p2_port_l)
                and     control_a
                jp      nz,p2_a_not_pressed
p2_a_pressed:
                ld      (hl),tile_a
                jp	check_p2_b
p2_a_not_pressed:                
                ld      (hl),tile_a+tile_selected

check_p2_b:
		inc	hl
		inc	hl
                in      a,(p2_port_h)
                and     control_b
                jp      nz,p2_b_not_pressed
p2_b_pressed:
                ld      (hl),tile_b
                jp	check_p2_c
p2_b_not_pressed:                
                ld      (hl),tile_b+tile_selected

check_p2_c:
		inc	hl
		inc	hl
                in      a,(p2_port_h)
                and     control_c
                jp      nz,p2_c_not_pressed
p2_c_pressed:
                ld      (hl),tile_c
                jp	check_p2_down
p2_c_not_pressed:                
                ld      (hl),tile_c+tile_selected

check_p2_down:
		ld	de,screen_cols-10
		add	hl,de
                in      a,(p2_port_l)
                and     control_down
                jp      nz,p2_down_not_pressed
p2_down_pressed:
                ld      (hl),tile_down
		jp	draw_p1_controls
p2_down_not_pressed:                
                ld      (hl),tile_down+tile_selected

		jp	draw_p1_controls



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

; Screen maps
controller_map:
		defb	13, 4						; x, y
		defb	0,  0, 0, 0, 27, 0,  0,  0,  8,  9, 10,  0,  0	; row 1
		defb	0,  1, 0, 0,  0, 0,  0, 11,  0, 11,  0, 11,  0	; row 2
		defb	3, 16, 4, 0,  0, 0, 13,  0, 15,  0, 15,  0, 14	; row 3
		defb	0,  2, 0, 0,  0, 0,  0, 12,  0, 12,  0, 12,  0	; row 4

