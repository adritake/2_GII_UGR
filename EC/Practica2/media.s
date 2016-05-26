.section .data
	.macro linea
	#	.int 1,-2,1,-2
	#	.int 1,2,-3,-4
	# .int 0x7fffffff,0x7fffffff,0x7fffffff,0x7fffffff
	#	.int 0x80000000,0x80000000,0x80000000,0x80000000
	#	.int 0xf0000000,0xe0000000,0xe0000000,0xd0000000
		.int -1,-1,-1,-1


	.endm

	.macro linea0
		.int 0,-1,-1,-1
	#	.int 0,-2,-1,-1
	#	.int 1,-2,-1,-1
	#	.int 19,-2,-1,-1
	#	.int 32,-2,-1,-1
	#	.int 50,-2,-1,-1
	#	.int 63,-2,-1,-1
	#	.int 64,-2,-1,-1
	#	.int 70,-2,-1,-1
	#	.int 95,-2,-1,-1
	#	.int -31,-2,-1,-1
	#	.int -10,-2,-1,-1
	#	.int 0,-2,-1,-1

	.endm

lista:		linea0

		.irpc i,1234567#8
					linea
		.endr

longlista:	.int (.-lista)/4
media:	.int 0x89ABCDEF
resto:	.int 0x01234567
formato:	.ascii "media =   %8d \t resto =   %8d \n"
					.ascii "hexadec 0x%08x \t resto = 0x%08x\n\0"

.section .text

main:	.global main

	mov    $lista, %ebx
	mov longlista, %ecx
	call suma
	mov %eax, media
	mov %edx, resto

	push resto
	push media
	push resto
	push media
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
