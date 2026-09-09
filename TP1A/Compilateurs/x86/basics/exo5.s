# Affiche en décimal petit-boutien l’entier dans %r8

.text
    .globl _start

_start:
    mov $42, %r8

boucle:  # while r8 != 0
    mov %r8, %rax
    mov $10, %rbx
    mov $0, %rdx
    idiv %rbx
# %rax = r8/10
# %rdx = r8 % 10
# on veut afficher %rdx et mettre r8 à rax
# on met r8 à rax
    mov %rax, %r8
# on ajoute 0x30 à rdx pour avoir le bon caractère ASCII
    add $0x30, %rdx
# on déplace rdx dans une zone adressable
    mov %rdx, -4(%rsp)
# on affiche le chiffre
    lea -4(%rsp), %rsi
    mov $1, %rax
    mov $1, %rdi
    mov $1, %rdx
    syscall

# on vérifie que r8 ne soit pas nul
    test %r8, %r8
    jnz boucle

# on affiche un retour-ligne
    movb $10, -4(%rsp)
    lea -4(%rsp), %rsi
    mov $1, %rax
    mov $1, %rdi
    mov $1, %rdx
    syscall

# on quitte
    mov $60, %rax
    mov $0, %rdi
    syscall

