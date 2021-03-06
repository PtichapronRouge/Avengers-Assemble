    global SAXPY_
    section .text

; SAXPY_(N, a, x, sx, y, sy) : y <- ax + y
; edi, xmm0, esi, rdx, rcx, r8
SAXPY_:
; Validate arguments
    cmp edi, 0
    jle InvalidSize
    test rsi, 0x0f
    jnz NotAligned; jump if x is not aligned
    test rcx, 0x0f
    jnz NotAligned; jump if y is not aligned

; multiply strides by 4 = sizeof(float)
    shl rdx, 2
    shl r8, 2

; When stride is > 1, jump directly to RemIter, packed operations impossible ?
    cmp edx, 4
    jg RemIter
    cmp r8d, 4
    jg RemIter

; computes euclidean division of n by 4 (for AVX-2)
    mov eax, edi
    and edi, 0x3   ; edi = n%4
    shr eax, 2     ; eax = n/4
    jz RemIter

; broadcast a and saves it
    vbroadcastss xmm0, xmm0 ; xmm0 = (a,a,a,a)

QuoIter:
; load data and increase address
    vmovaps xmm2, [rcx]             ; xmm2 = y[127:0]
; perform actual operation (packed)
    vfmadd231ps xmm2, xmm0, [rsi]   ; xmm2 = a*x + y
    add rsi, 16

; save result
    vmovaps [rcx], xmm2             ; y <- a*x + y
    add rcx, 16
; decrease counter
    dec eax
    jnz QuoIter

    test edi, edi
    jz Done

RemIter:
; perform computation (scalar)
    vmovss xmm1, [rcx]              ; xmm1 = y
    vfmadd231ss xmm1, xmm0, [rsi]   ; xmm1 = a*x + y
    add rsi, rdx
; save result
    vmovss [rcx], xmm1              ; y <- a*x + y
    add rcx, r8
; decrease counter
    dec edi
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
