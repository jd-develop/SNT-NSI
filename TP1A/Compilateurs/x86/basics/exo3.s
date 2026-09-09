# Prints a string of unknown length
.data

# The string
unknown: .string "Chaine de caractères\n"
null: .string ""  # empty string to compare chars to the null char

.text

    .globl _start

_start:
    # Current index in the string
    mov $0, %r8
    # Adress of the string
    lea unknown(%rip), %r9
    # We move the current char into r10b to check if it’s 0
    movb (%r9, %r8, 1), %r10b
    cmp %r10b, null(%rip)
    je end

# prints the current char
nextchar:
    # writes 1 char to stdout
    lea (%r9, %r8, 1), %rsi
    mov $1, %rax
    mov $1, %rdi
    mov $1, %rdx
    syscall
    # increases the index
    inc %r8
    # checks if the next char is 0
    movb (%r9, %r8, 1), %r10b
    cmp %r10b, null(%rip)
    jne nextchar

end:
    # exit
    mov $60, %rax
    mov $0, %rdi
    syscall

