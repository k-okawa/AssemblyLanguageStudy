# 条件分岐

main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$1, -4(%rbp)
	cmpl	$1, -4(%rbp)
	jg	.L2
	addl	$1, -4(%rbp)
	jmp	.L3
.L2:
	subl	$1, -4(%rbp)
.L3:
	movl	$0, %eax
	popq	%rbp
	ret

main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$1, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jg	.L2
	addl	$1, -4(%rbp)
	jmp	.L3
.L2:
	subl	$1, -4(%rbp)
.L3:
	movl	$0, %eax
	popq	%rbp
	ret