.data

o: .string "O"
retour: .string "\n"

.text
    .globl _start

_start:
    mov $20, %r8

    bouclelignes:
        mov %r8, %r10

        bouclecaracteres:
            mov $1, %rdi
            mov $1, %rdx
            mov $1, %rax
            lea o(%rip), %rsi
            syscall
            dec %r10
            jnz bouclecaracteres

        mov $1, %rdi
        mov $1, %rdx
        mov $1, %rax
        lea retour(%rip), %rsi
        syscall

        dec %r8
        jnz bouclelignes

    mov $60, %rax
    mov $0, %rdi
    syscall

