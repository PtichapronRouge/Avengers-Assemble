    global FloatPackedDotProduct_
    section .text

FloatPackedDotProduct_:
    ; check n size
    cmp edi, 0
    jle InvalidSize
    ; save B vector start address
    mov r10, rdx

    ; i index, r8 = n-i
    mov r8d, edi

    ; Computes euclidean division of n
    mov r11d, 4
    mov eax, edi
    cdq
    idiv r11d ; rax = n/4, rdx = n%4
    ; moves remainder in other register
    mov r11, rdx

RowIter:
    ; j index, r9 = n/4 - j
    mov r9d, eax
    mov rdx, r10

    ; xmm2 = sum = 0
    vxorps xmm2, xmm2

ColIterQuo:
    ; packed scalar product A[i, j:j+4]*x[j:j+4]
    vmovaps xmm0, [rsi]
    vmulps xmm0, [rdx]
    vaddps xmm2, xmm0, xmm2

    ; j ++
    add rsi, 16
    add rdx, 16
    dec r9d
    jnz ColIterQuo

    ; xmm2 packed sum reduction to scalar
    vhaddps xmm2, xmm2, xmm2
    vhaddps xmm2, xmm2, xmm2

    ; r9 = n%4 - j
    add r9d, r11d
    jz EndRowIter

ColIterRem:
    ; scalar product A[i,j]*x[j]
    vmovss xmm0, [rsi]
    vmulss xmm0, [rdx]
    vaddss xmm2, xmm0, xmm2

    ; j ++
    add rsi, 4
    add rdx, 4
    dec r9d
    jnz ColIterRem

EndRowIter:
    ; write sum to resuls y[i]
    movss [rcx], xmm2

    ; i ++
    add rcx, 4
    dec r8d
    jnz RowIter

    xor eax, eax
    ret

InvalidSize:
    mov eax, 1
    ret
