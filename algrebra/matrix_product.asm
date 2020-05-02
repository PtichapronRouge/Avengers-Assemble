    global MatrixProduct_
    section .text

MatrixProduct_:
    ; save callee-saved buffers
    push r14
    push r15
    ; r15 = n*4
    mov r15, rdi
    imul r15, 4
    ; save save B start address
    mov r14, rdx

    ;; check n size
    ;cmp rdi, 0
    ;jle InvalidSize

    ; i = 0, r8 = (n-i)
    mov r8, rdi

RowIter:
    ; k = 0, rdi = (n-k)
    mov r10, rdi
    ; load B start address
    mov rdx, r14

VectIter:
    ; j = 0, r9 = (n-j) 
    mov r9, rdi

ColIter:
    ; eax = A[i,k]*B[k,j]
    mov eax, [rsi]
    imul eax, [rdx]
    ; C[i,j] += eax
    add [rcx], eax

    ; n*k+j ++
    add rdx, 4
    ; n*i+j ++
    add rcx, 4
    ; j++
    dec r9
    ; j == n ?
    jnz ColIter

    ; n*i + j -= n
    sub rcx, r15
    ; n*i+k ++
    add rsi, 4
    ; k++
    dec r10
    ; k == n ? 
    jnz VectIter

    ; n*i +j += n
    add rcx, r15
    ; i++
    dec r8
    ; i == n ?
    jnz RowIter

End:
    xor eax, eax
    pop r15
    pop r14
    ret
