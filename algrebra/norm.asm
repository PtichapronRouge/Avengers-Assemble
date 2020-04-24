    global VectorNorm_
    section .text

VectorNorm_:
    xor rax, rax
    cmp edi, 0
    jle End

Iter:
    mov rcx, [rsi]
    imul rcx, rcx
    add rax, rcx
    add rsi, 4
    dec edi
    jnz Iter

End:
    ret

