.section .data
	.macro linea
	#	.int -1,-1,-1,-1
	#	.int 1,-2,1,-2
	#	.int 1,2,-3,-4
	#.int 0x7fffffff,0x7fffffff,0x7fffffff,0x7fffffff
	#	.int 0x80000000,0x80000000,0x80000000,0x80000000
	#	.int 0x04000000,0x04000000,0x04000000,0x04000000
	#	.int 0x08000000,0x08000000,0x08000000,0x08000000
	#	.int 0xfc000000,0xfc000000,0xfc000000,0xfc000000
	#	.int 0xf8000000,0xf8000000,0xf8000000,0xf8000000
		.int 0xf0000000,0xe0000000,0xe0000000,0xd0000000
	.endm

lista:	.irpc i,12345678
		linea
	.endr

longlista:	.int (.-lista)/4
media:	.int 0x89ABCDEF
resto:	.int 0x01234567
formato:	.ascii "media =  %8d \t resto =  %8d \n"
					.ascii "hexadec 0x%08x \t resto = 0x%08x\n\0"

.section .text

main:	.global main

	mov    $lista, %ebx
	mov longlista, %ecx
	call suma
	mov %eax, resultado
	mov %edx, resultado+4

	push resultado+4
	push resultado
	push resultado+4
	push resultado
	push $formato
	call printf
	add $20, %esp

	mov $1, %eax
	mov $0, %ebx
	int $0x80

suma:

	mov $0, %edi	#edi y epb son el acumulador
	mov $0, %ebp
	mov $0, %esi	#esi es el indice


bucle:
	mov (%ebx,%esi,4), %eax
	cltd
	add %eax, %edi
	adc %edx, %ebp
	inc  %esi
	cmp  %esi,%ecx

	jne bucle
	mov %edi,%eax
	mov %ebp, %edx
	idiv %ecx


	ret
