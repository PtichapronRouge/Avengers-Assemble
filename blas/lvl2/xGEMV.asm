    global SGEMV_
    section .text

; XGEMV_(M, N, alpha, A, X, beta, y)
SGEMV_:
; validate arguments
    cmp edi, 0
    jle InvalidSize
    cmp esi, 0
    jle InvalidSize
    ;test rcx, 0x0f
    ;jnz NotAligned
    ;test r8, 0x0f
    ;jnz NotAligned
    ;test r9, 0x0f
    ;jnz NotAligned

RowIter:
    ; restore x start address
    mov r9, rcx
    ; restore N value
    mov r11d, esi

    ; computes beta * y[i]
    vmulss xmm2, xmm1, [r8]

    ; sum = 0
    vxorps xmm3, xmm3

ColIter:
    vmovss xmm4, [r9]
    add r9, 4
    ;vmovss xmm5, [rdx]
    vfmadd231ss xmm3, xmm4, [rdx]
    add rdx, 4

    dec r11d
    jnz ColIter

    ; final addition
    vfmadd231ss xmm2, xmm0, xmm3
    vmovss [r8], xmm2
    add r8, 4

    dec edi
    jnz RowIter

    xor eax, eax
    ret

InvalidSize:
    mov eax, 1
    ret
