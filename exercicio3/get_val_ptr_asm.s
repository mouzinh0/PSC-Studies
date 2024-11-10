	.text
	.globl get_val_ptr
get_val_ptr:
    # Arguments:
    # %rdi - items (struct info *)
    # %rsi - item_idx (size_t)
    # %rdx - data_idx (size_t)
    # %rcx - val_idx (size_t)
    # %r8  - mask (short)

    # Compute address of items[item_idx]
    imulq $24, %rsi, %rax          # rax = item_idx * 24 (sizeof(struct info))
    addq %rdi, %rax                # rax = &items[item_idx]

    # Load 'valid' field into %r9d to avoid overwriting %rcx
    movl 16(%rax), %r9d            # r9d = items[item_idx].valid

    testl %r9d, %r9d               # Check if valid == 0
    je .return_null                # If zero, return NULL

    # Load 'data' pointer from items[item_idx]
    movq 8(%rax), %r9              # r9 = items[item_idx].data

    # Compute address of items[item_idx].data[data_idx]
    movq %rdx, %r10                # r10 = data_idx
    shlq $3, %r10                  # r10 = data_idx * 8 (size of a pointer)
    addq %r9, %r10                 # r10 = &items[item_idx].data[data_idx]
    movq (%r10), %rax              # rax = data_ptr (struct data *)

    # Load 'flags_length' word from data_ptr
    movzwq (%rax), %r11            # r11 = flags_length (16 bits zero-extended to 64 bits)

    # Extract 'length' (bits 6-15)
    movq %r11, %r9                 # Copy flags_length to %r9
    shrq $6, %r9                   # r9 = length (flags_length >> 6)

    # Compare val_idx with length
    cmpq %r9, %rcx                 # Compare length and val_idx
    jae .return_null               # If val_idx >= length, return NULL


.val_idx_valid:
    # Extract 'flags' (bits 0-5)
    andq $0x3F, %r11               # r11 = flags (flags_length & 0x3F)

    # Check if flags & mask is zero
    movzwq %r8w, %r8               # Zero-extend mask to 64 bits
    testq %r8, %r11                # Test flags & mask
    je .return_null                # If zero, return NULL

    # Compute address of vals[val_idx]
    leaq 2(%rax), %rax             # rax = data_ptr + 2 (skip flags_length)
    leaq (%rcx,%rcx,1), %rdx       # rdx = val_idx * 2 (size of short)
    addq %rdx, %rax                # rax = &vals[val_idx]

    ret                            # Return address of vals[val_idx]

.return_null:
    xorl %eax, %eax                # Set rax = NULL
    ret                            # Return NULL
	.section	.note.GNU-stack
