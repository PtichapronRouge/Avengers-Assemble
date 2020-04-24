    global MatrixProduct_
    section .text

; C = A*B
MatrixProduct_:
    cmp rdi, 0
    jle InvalidSize
    xor eax, eax

    mov r8, rdi ; row iterator

    ;xor r12, r12
    xor r13, r13 ; C iterator
    xor r14, r14

RowIter:
    ; k = 0
    mov r10, rdi
    mov r12, rdx ; B iterator

VectIter:
    ; j = 0
    xor r9, r9

ColIter:
    ; r13 = j + i*n = r9 + rdi*r8
    mov r13, r14
    add r13, r9

    ; C[n*i+j] += A[n*i+k]*B[n*k+j]
    mov  eax, [rsi]
    imul eax, [r12]
    add  [rcx + r13*4], eax

    ; j++
    inc r9
    add r12, 4

    ; if j < n, repeat
    cmp r9, rdi
    jl ColIter

    ; k++
    add rsi, 4
    ; if k < n, repeat
    dec r10
    jnz VectIter

    add r14, rdi
    dec r8
    jnz RowIter

InvalidSize:
    mov eax, 1

End:
    ret

