/*
	void rotate_right(unsigned long value[], size_t n);
*/

.text
.global rotate_right

rotate_right:
    # callee-saved 
    pushq %rbx
    pushq %rbp

    movq 8(%rdi), %rbx         # value[0] em %rbx
    movq (%rdi), %rax          # value[1] em %rax
    movq %rsi, %rcx            # n em %rcx
    movq $64, %rbp             # 64 em %rbp 

    # Limita n a 127 bits (caso seja maior)
    andq $127, %rcx            # n = n % 128

    testq %rcx, %rcx           # Verifica se n == 0
    jz .done                   # Se n == 0, return


    cmpq %rbp, %rcx
    je .rotate

.shift:
    movq %rax, %rdx            # Temp com value[1] em %rdx
    shrd %cl, %rbx, %rax       # Desloca %rbx para %rax para completar value[0] >> n
    shrq %cl, %rbx             # Desloca %rbx para direita para completar value[1]

    cmpq $64, %rcx           # Verifica se n < 64
    jb .done  

.rotate:
    movq %rbx, %r9             # %r9 = value[0]
    movq %rax, %rbx            # %rbx = value[1]
    movq %r9, %rax             # %rax = value[0]

.done:
    # Restaura os registradores salvos e retorna
    movq %rbx, 8(%rdi)         # Atualiza value[0] no array
    movq %rax, (%rdi)          # Atualiza value[1] no array
    popq %rbp
    popq %rbx
    ret
	.section	.note.GNU-stack

