section text      ;lol lol aff aff
minha_macro: macro
add lol
sub lol
output lol
end
macro2: macro
add n2
sub n2
end
if label1
copy n1, n2
rot: add n2
add n3
minha_macro
copy n2 n3
mult aff
macro2
load n3
output n3
jmp rot2
rot2: stop
stop
section data
n1: space
n2: space 4
n3: space
lol: space
label1: equ 1
label2: equ 0
aff: const 446
