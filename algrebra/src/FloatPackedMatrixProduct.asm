    global FloatPackedMatrixProduct_
    section .text

FloatPackedMatrixProduct_:
    ; check n size
    cmp edi, 0
    jle InvalidSize

    ; callee-saved registers
    push rbx

    ; save B start address
    mov r11, rdx

    ; euclidean division of n by 4
    mov eax, edi
    cdq
    mov r8d, 4
    idiv r8d
    ; move remainder to other register
    mov rbx, rdx

    ; i = 0, r8 = (n-i)
    mov r8d, edi
    ; edi -> rdi = n*4 (4 is size of int), using zero-extension of mov
    mov r8, rdi
    shl rdi, 2

RowIter:
    ; k = 0, r10 = (n-k)
    mov r10, rdi
    ; load B start address
    mov rdx, r11

VectIter:
    ; j = 0, r9 = (n/4-j)
    mov r9, rax
    ; load and duplicate A[i,k] into xmm0 : xmm0 = [A_ik, A_ik, A_ik, A_ik]
    vmovss xmm0, [rsi]
    punpckldq xmm0, xmm0
    punpcklqdq xmm0, xmm0

ColIterQuo:
    ; xmm1 = B[k,j:j+4]
    vmovaps xmm1, [rdx]
    ; xmm2 = A[i,k]*B[k,j:j+4]
    vmulps xmm2, xmm0, xmm1
    ; xmm2 += C[i,j:j+4]
    vaddps xmm2, xmm2, [rcx]
    ; C[i,j:j+4] = xmm2
    vmovaps [rcx], xmm2

    add r11, 16
    add rcx, 16
    ; j++
    dec r9
    jnz ColIterQuo

    ; r9 = (n%4-j)
    add r9, rbx
    jz EndColIter

ColIterRem:
    ; xmm1 = B[k,j:j+4]
    vmovss xmm1, [rdx]
    ; xmm2 = A[i,k]*B[k,j]
    vmulss xmm2, xmm0, xmm1
    ; xmm2 += C[i,j]
    vaddss xmm2, xmm2, [rcx]
    ; C[i,j] = xmm2
    vmovss [rcx], xmm2

    add rdx, 4
    add rcx, 4
    ; j++
    dec r9
    jnz ColIterRem

EndColIter:
    sub rcx, rdi
    add rsi, 4
    sub r10, 4
    jnz VectIter

    add rcx, rdi
    sub r8, 4
    jnz RowIter

    pop rbx
    xor eax, eax
    ret

InvalidSize:
    mov eax, 1
    ret
