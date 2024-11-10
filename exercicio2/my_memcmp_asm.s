# If the return value < 0, it indicates str1 is less than str2.
# If the return value > 0, it indicates str2 is less than str1.
# If the return value == 0, it represents str1 is equivalent to the str2.

.section .text
.global my_memcmp
my_memcmp:
    # Entrada: rdi = ptr1, rsi = ptr2, rdx = num
    push %rbx                  # register needs saving

    testq %rdx, %rdx            
    jz .end                    # If num is zero return

    movq %rdi, %rax             # %rax = ptr1
    movq %rsi, %rbx             # %rbx = ptr2
    movq %rdx, %rcx             # %rcx = num

.align_loop:
    cmpq $8, %rcx               # num < 8 jump
    jb .compare_bytes           

    movq (%rax), %r8            # 8 bytes de ptr1 em %r8
    movq (%rbx), %r9            # 8 bytes de ptr2 em %r9
    cmpq %r8, %r9               
    jne .compare_bytes          # Not equal jump

    addq $8, %rax               # Adress step ptr1 por 8 bytes (move pointer)
    addq $8, %rbx               # Adress step ptr2 por 8 bytes
    subq $8, %rcx               # num -= 8
    jmp .align_loop             # Loop

.compare_bytes:
    testq %rcx, %rcx            # Check num , if any bits left to check
    jz .equal                   # If Zero jump

    movzbq (%rax), %r8          # 1 byte de ptr1
    movzbq (%rbx), %r9          # 1 byte de ptr2
    cmpq %r8, %r9               
    jne .not_equal              # If Not Equal jump

    incq %rax                   # Adress step ptr1 por 1 byte (move pointer)
    incq %rbx                   # Adress step ptr2 por 1 byte
    decq %rcx                   # num -= 1
    jmp .compare_bytes          # Loop

.not_equal:
    movq %r8, %rax              # r8 - r9 === ptr1 - ptr2
    subq %r9, %rax
    jmp .end

.equal:
    xorq %rax, %rax             # Retornar 0 (iguais)

.end:
    pop %rbx
    ret
	.section	.note.GNU-stack
