;
; Test Program
;

; Tile indices
tile_letter_1:	equ 	28
tile_letter_2:	equ 	29

tile_up:        equ     1
tile_down:      equ     2
tile_left:      equ     3
tile_right:     equ     4
tile_a:         equ     5
tile_b:         equ     6
tile_c:         equ     7
tile_start:     equ     8

tile_selected:  equ     16			; offset to highlighted tile

; screen co-ordinates
vram_base_h:	equ	0xf0
vram_base_l:	equ	0x00

screen_cols:	equ 	40
screen_rows:	equ 	30

controller_y:	equ	5

p1_left:	equ	4
p2_offset:	equ	screen_cols/2


init:		org	0			; program starts at 0x0000
		di				; turn off interrupts
		ld	sp,0x0000		; first push will make this 0xfffe
		jp	start

title:		defm	"Test Program\0"
version:	defm	"0.0.1\0"


start:		
init_screen:
                ld      d,vram_base_h
                ld      e,vram_base_l
		ld	hl,controller_map
		call	draw_map

done:
                in      a,(0x20)
                and     0x01
                jp      nz,not_pressed
pressed:
                ld      (hl),tile_up
                jp	done
not_pressed:                
                ld      (hl),tile_up+tile_selected
                jp	done

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
		ld	h,0
		ld	l,screen_cols
		add	hl,de
		push	hl
		pop	de
		pop	hl

		pop	af			; get x size back in B, but
		ld	b,a			; without affecting C
		dec	c
		jp	nz,draw_map_row

		pop	bc
		ret

; Screen maps
controller_map:
		defb	13, 4						; x, y
		defb	0,  0, 0, 0, 27, 0,  0,  0,  8,  9, 10,  0,  0	; row 1
		defb	0,  1, 0, 0,  0, 0,  0, 11,  0, 11,  0, 11,  0	; row 2
		defb	3, 16, 4, 0,  0, 0, 13,  0, 15,  0, 15,  0, 14	; row 3
		defb	0,  2, 0, 0,  0, 0,  0, 12,  0, 12,  0, 12,  0	; row 4

