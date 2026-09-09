.data

x: .string "X"
retour: .string "\n"

.text

.globl _start

_start:
    mov $10, %r8
boucle:
    lea x(%rip), %rsi
    mov $1, %rax
    mov $1, %rdi
    mov $1, %rdx
    syscall
    dec %r8
    jnz boucle
    lea retour(%rip), %rsi
    mov $1, %rax
    mov $1, %rdi
    mov $1, %rdx
    syscall
    mov $60, %rax
    mov $0, %rdi
    syscall

