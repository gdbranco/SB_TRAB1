SECTION TEXT
resto_macro: macro
store RESTO
output RESTO
end

input B

loop:
load B
div DOIS
store QUOT
load QUOT
mult DOIS
store VOLTA
load B
sub VOLTA
resto_macro
load QUOT
store B
jmpp loop

stop

SECTION DATA
B: SPACE
DOIS: CONST 2
QUOT: SPACE
resto: SPACE
volta: space
offset: const 1
lol: EqU 1
