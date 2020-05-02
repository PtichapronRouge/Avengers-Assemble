    global MatrixProduct_
    section .text

MatrixProduct_:
    ; save callee-saved buffers
    push r14
    ; rdi = n (4 is size of int)
    imul rdi, 4
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
    sub r9, 4
    ; j == n ?
    jnz ColIter

    ; n*i + j -= n
    sub rcx, rdi
    ; n*i+k ++
    add rsi, 4
    ; k++
    sub r10, 4
    ; k == n ? 
    jnz VectIter

    ; n*i +j += n
    add rcx, rdi
    ; i++
    sub r8, 4
    ; i == n ?
    jnz RowIter

End:
    xor eax, eax
    pop r14
    ret
