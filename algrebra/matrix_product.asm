    global MatrixProduct_
    section .text

; C = A*B
MatrixProduct_:
    cmp rdi, 0
    jle InvalidSize
    xor eax, eax

    xor r8, r8   ; row iterator

    ;xor r12, r12 
    xor r13, r13 ; C iterator

RowIter:
    ; k = 0
    xor r10, r10
    mov r12, rdx ; B iterator

VectIter:
    ; j = 0
    xor r9, r9

ColIter:
    ; r13 = j + r*n = r9 + rdi*r8
    mov r13, rdi
    imul r13, r8
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
    ; else
    ; k++
    inc r10
    add rsi, 4
    ; if k < n, repeat
    cmp r10, rdi
    jl VectIter

    inc r8
    cmp r8, rdi
    jl RowIter

InvalidSize:
    mov eax, 1

End:
    ret

