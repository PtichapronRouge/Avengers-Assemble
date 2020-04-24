    global Scalar_
    section .text

Scalar_:
    xor eax, eax
    cmp edi, 0
    jle End

Iter:
    mov  ecx, [rsi]
    imul ecx, [rdx]
    add  eax, ecx
    add  rsi, 4
    add  rdx, 4
    dec  edi
    jnz  Iter

End:
    ret

