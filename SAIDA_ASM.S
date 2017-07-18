
.data
lit0:
	.long 0 
lit1:
	.long 1 
lit10:
	.long 10 
temporariaLindha_1:
	.long 0
temporariaLindha_0:
	.long 0
.LC0:
	.string "%d"
a:
	.long 0
.LC1:
	.string " Digite um numero: \n"

	## TAC_BEGIN_FUNC
	.text
	.globl main
main:
	.cfi_startproc
	pushq	%rbp

	## TAC_ADD
	movl $10, %eax
	addl $1, %eax
	movl %eax, temporariaLindha_1(%rip)

	## TAC_MOVE
	movl temporariaLindha_1(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: STRING
	movl $.LC1, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_END_FUNC
	popq	%rbp
	ret
	.cfi_endproc
