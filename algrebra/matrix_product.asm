    global MatrixProduct_
    section .text

; C = A*B
MatrixProduct_:
    cmp rdi, 0
    jle InvalidSize

    mov r8, rdi ; row iterator

    xor r13, r13 ; C iterator
    mov r14, rdi

RowIter:
    ; k = 0
    mov r10, rdi
    mov r12, rdx ; B iterator

VectIter:
    ; j = 0
    mov r9, rdi
    mov r13, r14

ColIter:
    ; r13 = j + i*n = n + (*n) - (n-j)
    sub r13, r9

    ; C[n*i+j] += A[n*i+k]*B[n*k+j]
    mov  eax, [rsi]
    imul eax, [r12]
    add  [rcx + r13*4], eax

    ; j++
    add r12, 4

    ; if j < n, repeat
    dec r9
    jnz ColIter

    ; k++
    add rsi, 4
    ; if k < n, repeat
    dec r10
    jnz VectIter

    add r14, rdi
    dec r8
    jnz RowIter

    xor eax, eax
    jmp End

InvalidSize:
    mov eax, 1

End:
    ret

