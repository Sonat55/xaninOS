
[org 0x7c00] ;there we start execution
[bits 16]; <-- 16bit real mode



jmp _loadSector


;/------------------------------------------/
;|this filed is not used by ustar           |
;|this filed is created to handle easier FS |
;/------------------------------------------/

USTAR_START:
db "OFF"
dd 0x0000

USTAR_FILE_ENTRIES:
db "ENTR"
db 0x0



_loadSector:

;change text mode resolution


;mov ax,0003h
;int 10h


;mov ax,1111h
;xor bl,bl
;int 10h

;load sectors
;please read "notes" section from Ralf Brown article about int 0x13

;mov bp, 3
int13_read:

mov ah,0x0
mov ax,0x2000
mov es,ax

mov ah,0x2
mov al,0x40
mov ch,0x0
mov cl,0x2 ; we dont want to copy first sector
mov dh,0x0
mov bx,0x0
int 0x13
;dec bp
;cmp bp,0
;jne int13_read

mov ah,0xe
mov si,str

print_msg:
lodsb
cmp al,0
je jmp_ker_load
int 0x10
jmp print_msg



jmp_ker_load:
jmp word 0x2000:0000


disk_num: dw 0x0
str: db "ERROR your computer doesnt support fully int13 xaninOS cant be loaded",0

regs_90x60:
; MISC
	db 0E7h
; SEQuencer
	db 03h, 01h, 03h, 00h, 02h
; CRTC
	db  6Bh, 59h,  5Ah, 82h, 60h,  8Dh, 0Bh,  3Eh,
	db  00h, 47h,  06h, 07h, 00h,  00h, 00h,  00h,
	db 0EAh, 0Ch, 0DFh, 2Dh, 08h, 0E8h, 05h, 0A3h,
	db 0FFh
; GC (no)
; AC (no)

times 510 - ($-$$) db 0x0

dw 0xaa55
