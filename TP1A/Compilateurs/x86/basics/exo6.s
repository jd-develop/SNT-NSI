# calcul de %r8 factorielle

.text
    .globl _start

_start:
    mov $10, %r8
    mov $1, %r9  # résultat
    jz affichage

bouclefact:
    imul %r8, %r9
    sub $1, %r8
    jnz bouclefact

affichage:
boucleaffichage:  # while r9 != 0
    mov %r9, %rax
    mov $10, %rbx
    mov $0, %rdx
    idiv %rbx
# %rax = r9/10
# %rdx = r9 % 10
# on veut afficher %rdx et mettre r9 à rax
# on met r9 à rax
    mov %rax, %r9
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

# on vérifie que r9 ne soit pas nul
    test %r9, %r9
    jnz boucleaffichage

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
    mov $60, %rax
    mov $0, %rdi
    syscall
