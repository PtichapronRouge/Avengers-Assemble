    global FloatDotProduct_
    section .text

FloatDotProduct_:
    ; check n size
    cmp rdi, 0
    jle InvalidSize
    ; save B vector start address
    mov r10, rdx

    ; i index, r8 = n-i
    mov r8, rdi

RowIter:
    ; j index, r9 = n-j
    mov r9, rdi
    mov rdx, r10

ColIter:
    vmovss xmm0, [rsi]
    vmulss xmm0, [rdx]
    vaddss xmm1, xmm0, [rcx]
    movss [rcx], xmm1

    ; j ++
    add rsi, 4
    add rdx, 4
    dec r9
    jnz ColIter

    ; i ++
    add rcx, 4
    dec r8
    jnz RowIter

    xor eax, eax
    ret

InvalidSize:
    mov eax, 1
    ret
