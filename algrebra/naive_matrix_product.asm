    global NaiveMatrixProduct_
    section .text

NaiveMatrixProduct_:
    ; prolog
    push r13
    push r14
    push r15

    ;; check n size
    ;cmp rdi, 0
    ;jle InvalidSize

    ; i = 0
    xor r8, r8

RowIter:
    ; j = 0
    xor r9, r9

ColIter:
    ; k = 0
    xor r10, r10

    ; r15 = n*i + j
    mov r15, r8
    imul r15, rdi
    add r15, r9

VectIter:
    ; r13 = n*i + k
    mov r13, r8
    imul r13, rdi
    add r13, r10

    ; r14 = n*k + j
    mov r14, r10
    imul r14, rdi
    add r14, r9

    ; eax = A[i,k]*B[k,j]
    mov eax, [rsi + r13*4]
    imul eax, [rdx + r14*4]
    ; C[i,j] += eax
    add [rcx + r15*4], eax

    ; k++
    inc r10
    ; k < n ?
    cmp r10, rdi
    jl VectIter

    ; j++
    inc r9
    ; j < n ?
    cmp r9, rdi
    jl ColIter

    ; i++
    inc r8
    ; i < n ?
    cmp r8, rdi
    jl RowIter

End:
    xor eax, eax
    pop r15
    pop r14
    pop r13
    ret
