	.file	"foo.cpp"
	.text
	.globl	_Z3foov
	.type	_Z3foov, @function
_Z3foov:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	-1(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNK5thingIjE2idEv
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	_Z3foov, .-_Z3foov
	.section	.text._ZNK5thingIjE2idEv,"axG",@progbits,_ZNK5thingIjE2idEv,comdat
	.align 2
	.weak	_ZNK5thingIjE2idEv
	.type	_ZNK5thingIjE2idEv, @function
_ZNK5thingIjE2idEv:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	$3840, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	_ZNK5thingIjE2idEv, .-_ZNK5thingIjE2idEv
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
