	.file	"unlink.c"
	.section	.rodata
.LC0:
	.string	"zzz"
.LC1:
	.string	"hello"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$160, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$420, %edx
	movl	$578, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	open
	movl	%eax, -152(%rbp)
	call	getchar
	movl	$.LC0, %edi
	call	unlink
	call	getchar
	movl	-152(%rbp), %eax
	movl	$5, %edx
	movl	$.LC1, %esi
	movl	%eax, %edi
	call	write
	call	getchar
	movl	-152(%rbp), %eax
	movl	$0, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	lseek
	leaq	-144(%rbp), %rcx
	movl	-152(%rbp), %eax
	movl	$128, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -148(%rbp)
	movl	-148(%rbp), %eax
	cltq
	movb	$0, -144(%rbp,%rax)
	leaq	-144(%rbp), %rax
	movq	%rax, %rdi
	call	puts
	call	getchar
	movl	-152(%rbp), %eax
	movl	%eax, %edi
	call	close
	call	getchar
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L3
	call	__stack_chk_fail
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.6) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
