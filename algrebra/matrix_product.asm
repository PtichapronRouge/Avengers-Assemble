    global MatrixProduct_
    section .text

; C = A*B
MatrixProduct_:
    cmp rdi, 0
    jle End
    xor r8, r8   ; row iterator

    xor r11, r11 ; A iterator
    xor r12, r12 ; B iterator
    xor r13, r13 ; C iterator

RowIter:
    ; k = 0
    xor r10, r10

VectIter:
    ; j = 0
    xor r9, r9
    ; r11 = k + n*i = r10 + rdi*r8
    mov r11, rdi
    imul r11, r8
    add r11, r10

ColIter:
    ; r12 = j + n*k = r9 + rdi*r10
    mov r12, rdi
    imul r12, r10
    add r12, r9
    ; r13 = j + r*n = r9 + rdi*r8
    mov r13, rdi
    imul r13, r8
    add r13, r9

    ; C[n*i+j] += A[n*i+k]*B[n*k+j]
    mov  eax, [rsi + r11*4]
    imul eax, [rdx + r12*4]
    add  [rcx + r13*4], eax

    ; j++
    inc r9

    ; if j < n, repeat
    cmp r9, rdi
    jl ColIter
    ; else
    ; k++
    inc r10
    ; if k < n, repeat
    cmp r10, rdi
    jl VectIter

    inc r8
    cmp r8, rdi
    jl RowIter

End:
    ret

