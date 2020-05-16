    global SAXPY_
    section .text

; SAXPY_(N, a, x, sx, y, sy) : y <- ax + y
; strides are currently not handled
; edi, xmm0, esi, rdx, rcx, r8
SAXPY_:
; Validate arguments
    cmp edi, 0
    jle InvalidSize
    test rsi, 0x0f
    jnz NotAligned; jump if x is not aligned
    test rcx, 0x0f
    jnz NotAligned; jump if y is not aligned

; computes euclidean division of n by 4 (for AVX-2)
    mov r10d, edi
    and r10d, 0x3   ; r10d = n%4
    shr edi, 2      ; edi = n/4
    jz RemIter

; broadcast a and saves it
    vbroadcastss xmm0, xmm0 ; xmm0 = (a,a,a,a)

QuoIter:
; load data and increase address
    vmovaps xmm1, [rsi]      ; xmm1 = x[127:0]
    vmovaps xmm2, [rcx]      ; xmm2 = y[127:0]
    add rsi, 16
; perform actual operation (packed)
    vmulps xmm1, xmm0, xmm1  ; xmm1 = a*x[127:0]
    vaddps xmm1, xmm1, xmm2  ; xmm1 = a*x + y
; save result
    vmovaps [rcx], xmm1      ; y <- a*x + y
    add rcx, 16
; decrease counter
    dec edi
    jnz QuoIter

    test r10d, r10d
    jz Done

RemIter:
; perform computation (scalar)
    vmulss xmm1, xmm0, [rsi] ; xmm1 = a*x
    add rsi, 4
    vaddss xmm1, xmm1, [rcx] ; xmm1 = a*x + y
    vmovss [rcx], xmm1        ; y <- a*x + y
    add rcx, 4
; decrease counter
    dec r10d
    jnz RemIter

Done:
; set error code and return
    xor eax, eax
    ret

InvalidSize:
    mov eax, 1
    ret

NotAligned:
    mov eax, 2
    ret
