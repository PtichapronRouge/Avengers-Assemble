    global MatrixProduct_
    section .text

MatrixProduct_:
    ; save callee-saved buffers
    push r14
    push r15
    ; erase temp buffers
    xor r15, r15
    ; save save B start address
    mov r14, rdx

    ;; check n size
    ;cmp rdi, 0
    ;jle InvalidSize

    ; i = 0
    xor r8, r8

RowIter:
    ; k = 0
    xor r10, r10
    ; load B start address
    mov rdx, r14

VectIter:
    ; j = 0
    xor r9, r9

ColIter:
    ; eax = A[i,k]*B[k,j]
    mov eax, [rsi]
    imul eax, [rdx]
    ; C[i,j] += eax
    add [rcx + r15*4], eax

    ; j++
    inc r9
    ; n*k+j ++
    add rdx, 4
    ; n*i+j ++
    inc r15
    ; j < n ?
    cmp r9, rdi
    jl ColIter

    ; k++
    inc r10
    ; n*i + j -= n
    sub r15, rdi
    ; n*i+k ++
    add rsi, 4
    ; k < n ?
    cmp r10, rdi
    jl VectIter

    ; i++
    inc r8
    ; n*i +j += n
    add r15, rdi
    ; i < n ?
    cmp r8, rdi
    jl RowIter

End:
    xor eax, eax
    pop r15
    pop r14
    ret
