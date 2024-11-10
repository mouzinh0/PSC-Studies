    .text
    .global less_than
less_than:
    mov     (%rdi), %eax       # Load *(int *)a into %eax (32-bit integer)
    movsxd  %eax, %rax         # Sign-extend %eax to %rax (64-bit)
    mov     %rsi, %rcx         # Move b (context) to %rcx (64-bit)
    cmp     %rcx, %rax         # Compare %rax (a) with %rcx (b)
    setl    %al                # Set %al to 1 if a < b
    movzbl  %al, %eax          # Zero-extend %al to %eax
    ret
	.section .note.GNU-stack
