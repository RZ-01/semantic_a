	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4
	JMP main

	# 0x5e584be5ad80	label max

max:

	# 0x5e584be5abe0	formal a


	# 0x5e584be5acc0	formal b


	# 0x5e584be5b2d0	begin


	# 0x5e584be5af00	var t0


	# 0x5e584be5af40	t0 = a > b

    LOD R5,(R2+8)
    LOD R6,(R2-4)
    LOD R7,(R2-8)
    LOD R5,R6
    SUB R5,R7
    TST R5
    LOD R5,1
    LOD R3,R1+24
    JGZ R3
    LOD R5,0

	# 0x5e584be5b1d0	ifz t0 goto L0

    STO (R2+8),R5
    LOD R6,(R2+8)
    TST R6
    JEZ L0

	# 0x5e584be5b000	return a

    LOD R7,(R2-4)
    LOD R4,R7
    LOD R3,(R2+4)
    LOD R2,(R2)
    JMP R3

	# 0x5e584be5b210	goto L1

	JMP L1

	# 0x5e584be5b250	label L0

L0:

	# 0x5e584be5b090	return b

    LOD R5,(R2-8)
    LOD R4,R5
    LOD R3,(R2+4)
    LOD R2,(R2)
    JMP R3

	# 0x5e584be5b290	label L1

L1:

	# 0x5e584be5b310	end

    LOD R3,(R2+4)
    LOD R2,(R2)
    JMP R3

	# 0x5e584be5b3f0	label main

main:

	# 0x5e584be5e410	begin


	# 0x5e584be5b610	var result


	# 0x5e584be5b5a0	result = 1

    LOD R5,1

	# 0x5e584be5b860	var i


	# 0x5e584be5b7f0	i = 2

    LOD R6,2

	# 0x5e584be5b9a0	var n


	# 0x5e584be5ba30	input n

    LOD R7,(R2+16)
    IN
    LOD R7,R15

	# 0x5e584be5c2c0	label L2

    STO (R2+8),R5
    STO (R2+12),R6
    STO (R2+16),R7
L2:

	# 0x5e584be5bb90	var t1


	# 0x5e584be5bbd0	t1 = i <= n

    LOD R5,(R2+20)
    LOD R6,(R2+12)
    LOD R7,(R2+16)
    LOD R5,R6
    SUB R5,R7
    TST R5
    LOD R5,0
    LOD R3,R1+24
    JGZ R3
    LOD R5,1

	# 0x5e584be5c300	ifz t1 goto L3

    STO (R2+20),R5
    LOD R6,(R2+20)
    TST R6
    JEZ L3

	# 0x5e584be5bd80	var t2


	# 0x5e584be5bdc0	t2 = result * i

    LOD R7,(R2+24)
    LOD R8,(R2+8)
    LOD R9,(R2+12)
    LOD R7,R8
    MUL R7,R9

	# 0x5e584be5be30	result = t2


	# 0x5e584be5c000	var t3


	# 0x5e584be5bfc0	t3 = i


	# 0x5e584be5c0a0	var t4


	# 0x5e584be5c0e0	t4 = i + 1

    LOD R8,(R2+32)
    LOD R10,(R2+12)
    LOD R11,1
    LOD R8,R10
    ADD R8,R11

	# 0x5e584be5c150	i = t4


	# 0x5e584be5c340	goto L2

    STO (R2+8),R7
    STO (R2+12),R8
    STO (R2+28),R9
	JMP L2

	# 0x5e584be5c380	label L3

L3:

	# 0x5e584be5c5a0	var j


	# 0x5e584be5c530	j = 0

    LOD R5,0

	# 0x5e584be5cf60	label L4

    STO (R2+36),R5
L4:

	# 0x5e584be5c7b0	var t5


	# 0x5e584be5c7f0	t5 = j < 9

    LOD R5,(R2+40)
    LOD R6,(R2+36)
    LOD R7,9
    LOD R5,R6
    SUB R5,R7
    TST R5
    LOD R5,1
    LOD R3,R1+24
    JLZ R3
    LOD R5,0

	# 0x5e584be5cfa0	ifz t5 goto L5

    STO (R2+40),R5
    LOD R6,(R2+40)
    TST R6
    JEZ L5

	# 0x5e584be5ccc0	var t8


	# 0x5e584be5cd00	t8 = result * i

    LOD R7,(R2+44)
    LOD R8,(R2+8)
    LOD R9,(R2+12)
    LOD R7,R8
    MUL R7,R9

	# 0x5e584be5cd70	result = t8


	# 0x5e584be5cfe0	label L6

    STO (R2+8),R7
L6:

	# 0x5e584be5c9c0	var t6


	# 0x5e584be5c980	t6 = j

    LOD R5,(R2+36)

	# 0x5e584be5ca60	var t7


	# 0x5e584be5caa0	t7 = j + 1

    LOD R6,(R2+52)
    LOD R7,(R2+36)
    LOD R8,1
    LOD R6,R7
    ADD R6,R8

	# 0x5e584be5cb10	j = t7


	# 0x5e584be5d020	goto L4

    STO (R2+48),R5
    STO (R2+36),R6
	JMP L4

	# 0x5e584be5d060	label L5

L5:

	# 0x5e584be5d340	var t10


	# 0x5e584be5d210	var t9


	# 0x5e584be5d250	t9 = n + 1

    LOD R5,(R2+60)
    LOD R6,(R2+16)
    LOD R7,1
    LOD R5,R6
    ADD R5,R7

	# 0x5e584be5d380	t10 = i != t9

    LOD R8,(R2+56)
    LOD R9,(R2+12)
    LOD R8,R9
    SUB R8,R5
    TST R8
    LOD R8,0
    LOD R3,R1+24
    JEZ R3
    LOD R8,1

	# 0x5e584be5d710	ifz t10 goto L9

    STO (R2+60),R5
    STO (R2+56),R8
    LOD R6,(R2+56)
    TST R6
    JEZ L9

	# 0x5e584be5d4c0	output "123\n"

    LOD R15,L7
    OUTS

	# 0x5e584be5d750	goto L10

	JMP L10

	# 0x5e584be5d790	label L9

L9:

	# 0x5e584be5d5d0	output "456\n"

    LOD R15,L8
    OUTS

	# 0x5e584be5d7d0	label L10

L10:

	# 0x5e584be5d8e0	output "result="

    LOD R15,L11
    OUTS

	# 0x5e584be5d970	output result

    LOD R15,(R2+8)
    OUTN

	# 0x5e584be5da80	output "\n"

    LOD R15,L12
    OUTS

	# 0x5e584be5db90	output "aaaaa\n"

    LOD R15,L13
    OUTS

	# 0x5e584be5dca0	var a


	# 0x5e584be5dd30	input a

    LOD R5,(R2+64)
    IN
    LOD R5,R15

	# 0x5e584be5de40	output "max(i,a)="

    LOD R15,L14
    OUTS

	# 0x5e584be5e200	var k


	# 0x5e584be5e0a0	var t11


	# 0x5e584be5dfe0	actual i

    LOD R6,(R2+12)
    STO (R2+76),R6

	# 0x5e584be5e020	actual a

    STO (R2+80),R5

	# 0x5e584be5e060	t11 = call max

    STO (R2+64),R5
    STO (R2+12),R6
    LOD R4,R1+40
    STO (R2+88),R4
    STO (R2+84),R2
    ADD R2,84
    JMP max
    LOD R5,(R2+72)
    LOD R5,R4

	# 0x5e584be5e190	k = t11


	# 0x5e584be5e2c0	output k

    LOD R15,R5
    OUTN

	# 0x5e584be5e3d0	output "\n"

    LOD R15,L12
    OUTS

	# 0x5e584be5e450	end

    LOD R3,(R2+4)
    LOD R2,(R2)
    JMP R3

	# tail
EXIT:
	END
L14:
	DBS 109,97,120,40,105,44,97,41,61,0
L13:
	DBS 97,97,97,97,97,10,0
L12:
	DBS 10,0
L11:
	DBS 114,101,115,117,108,116,61,0
L8:
	DBS 52,53,54,10,0
L7:
	DBS 49,50,51,10,0
STATIC:
	DBN 0,0
STACK:
