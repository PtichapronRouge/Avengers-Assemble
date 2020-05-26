    global SDOT_
    section .text

; SDOT_(N, x, sx, y, sy) <- x^T y
SDOT_:
; set result to 0
    vxorps xmm0, xmm0
; validate arguments
    cmp edi, 0
    jle Done
    test rsi, 0x0f
    jnz Done
    test rcx, 0x0f
    jnz Done

; multiply strides by 4 = sizeof(float)
    shl rdx, 2
    shl r8, 2

; when stride is > 1, jump directly to remIter
    cmp edx, 4
    jg RemIter
    cmp r8d, 4
    jg RemIter

; computes euclidean division of N by 4
    mov eax, edi
    and edi, 0x3    ; edi = n%4
    shr eax, 2      ; eax = n/4
    jz RemIter

QuoIter:
    vmovaps xmm1, [rsi]
    add rsi, 16
    vmovaps xmm2, [rcx]
    add rcx,  16
    vfmadd231ps xmm0, xmm1, xmm2

    dec eac
    jnz QuoIter

    vhaddps xmm0, xmm0
    vhaddps xmm0, xmm0

    test edi, edi
    jz Done

RemIter:
    vmovss xmm1, [rsi]
    add rsi, rdx
    vmovss xmm2, [rcx]
    add rcx, r8

    vfmadd231ss xmm0, xmm1, xmm2

    dec edi
    jnz RemIter

Done:
    ret


