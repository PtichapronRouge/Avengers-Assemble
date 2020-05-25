    global SNRM2_
    section .text

SNRM2_:
; Set result to 0
    vxorps xmm0, xmm0
; Validate arguments
    cmp edi, 0
    jle Done
    test rsi, 0x0f
    jnz Done ; jump if x is not aligned

; multiply strides by 4 = sizeof(float)
    shl rdx, 2

; When stride is > 1, jump directly to RemIter, packed operations impossible ?
    cmp edx, 4
    jg RemIter

; computes euclidean division of n by 4 (for AVX-2)
    mov eax, edi
    and edi, 0x3   ; edi = n%4
    shr eax, 2     ; eax = n/4
    jz RemIter


QuoIter:
    vmovaps xmm1, [rsi]
    add rsi, 16
    vfmadd231ps xmm0, xmm1, xmm1    ; xmm0 += x[i]*x[i]

    dec eax
    jnz QuoIter

    vhaddps xmm0, xmm0              ; reduce xmm0 to scalar
    vhaddps xmm0, xmm0

    test edi, edi
    jz Done

RemIter:
    vmovss xmm1, [rsi]
    add rsi, rdx
    vfmadd231ss xmm0, xmm1, xmm1    ; xmm0 += x[i]*x[i]

    dec edi
    jnz RemIter

Done:
    ret
