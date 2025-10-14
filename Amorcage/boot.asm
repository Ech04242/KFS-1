MBALIGN equ 1 << 0 ; Alignement des pages
MEMINFO equ 1 << 1 ; permet d'avoir la carte de memoire
MBFLAGS equ MBALIGN | MEMINFO ; Gere le flag multiboot
MAGIC equ 0x1BADB002 ; permet a grub de trouver le header
CHECKSUM equ -(MAGIC + MBFLAGS)

; Ces valeures sont documentes dans le standart de multiboot et serons cherches par le bootloader.
section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top


	extern kernel_main
	call kernel_main

	cli
.hang:	hlt
	jmp .hang
.end:

; outb.asm
global outb
section .text
outb:
    ; paramètres : 
    ;   port = [esp + 4]
    ;   value = [esp + 8]

    mov dx, [esp + 4]    ; charger le port dans dx
    mov al, [esp + 8]    ; charger la valeur dans al
    out dx, al           ; écrire sur le port

    ret