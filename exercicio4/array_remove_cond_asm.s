    .text
    .global array_remove_cond
    .extern memmove
array_remove_cond:
    # Save callee-saved registers
    push    %r12
    push    %r13
    push    %r14
    push    %r15
    push    %rbx

    # Move arguments to callee-saved registers
    mov     %rdi, %r12         # %r12 = array (current)
    mov     %rsi, %r14         # %r14 = size
    mov     %rdx, %r15         # %r15 = eval function pointer
    mov     %rcx, %rbx         # %rbx = context
    lea     (%rdi, %r14, 8), %r13  # %r13 = last = array + size * 8

    # Main loop
loop_start:
    cmp     %r13, %r12        # Compare current and last
    jae     loop_end           # If current >= last, exit loop

    # Prepare arguments for eval(*current, context)
    mov     (%r12), %rdi       # %rdi = *current
    mov     %rbx, %rsi         # %rsi = context

    # Stack is already aligned; call eval function
    call    *%r15              # Call eval via %r15

    # Check return value of eval
    test    %eax, %eax
    je      move_next          # If eval == 0, move to next element

    # Remove element
    # Calculate nbytes = last - current - 8
    mov     %r13, %rax         # %rax = last
    sub     %r12, %rax         # %rax = last - current
    sub     $8, %rax           # %rax = nbytes = last - current - 8

    # Check if there are bytes to move
    cmp     $0, %rax
    jle     adjust_pointers    # If nbytes <= 0, skip memmove

    # Prepare arguments for memmove(current, current + 8, nbytes)
    mov     %r12, %rdi         # dest = current
    lea     8(%r12), %rsi      # src = current + 8
    mov     %rax, %rdx         # n = nbytes

    # Stack is aligned; call memmove
    call    memmove@PLT

adjust_pointers:
    dec     %r14               # size -= 1
    sub     $8, %r13           # last -= sizeof(void*)
    # current remains the same after removal
    jmp     loop_start

move_next:
    add     $8, %r12           # current += sizeof(void*)
    jmp     loop_start

loop_end:
    # Restore callee-saved registers and stack
    mov     %r14, %rax         # Return value = size
    pop     %rbx
    pop     %r15
    pop     %r14
    pop     %r13
    pop     %r12
    ret

    .section .note.GNU-stack
