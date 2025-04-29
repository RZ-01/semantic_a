.code
0x5bb0489fb5f0	var a
0x5bb0489fb910	label max
0x5bb0489fb710	formal x
0x5bb0489fb810	formal y
0x5bb0489fc2c0	begin
0x5bb0489fbaa0	t0 = x > y
0x5bb0489fc200	ifz t0 goto L2
0x5bb0489fbb60	return x
0x5bb0489fc240	goto L0
0x5bb0489fc280	label L2
0x5bb0489fbcf0	t1 = x == y
0x5bb0489fc080	ifz t1 goto L1
0x5bb0489fbdb0	return x
0x5bb0489fc0c0	goto L0
0x5bb0489fc100	label L1
0x5bb0489fbe40	return y
0x5bb0489fbf40	goto L0
0x5bb0489fbf80	label L0
0x5bb0489fc300	end
0x5bb0489fc420	label main
0x5bb0489fdfa0	begin
0x5bb0489fc730	var c
0x5bb0489fc770	var a
0x5bb0489fc600	a = 2
0x5bb0489fc870	var x
0x5bb0489fc8d0	input a
0x5bb0489fc960	output a
0x5bb0489fcc60	ifz a goto L3
0x5bb0489fcb40	var b
0x5bb0489fcad0	b = a
0x5bb0489fcca0	label L3
0x5bb0489fd1d0	t3 = c * 3
0x5bb0489fcf90	t2 = 1 + 3
0x5bb0489fd2b0	t4 = t2 + t3
0x5bb0489fd4a0	t5 = t4 - 6
0x5bb0489fd510	a = t5
0x5bb0489fd580	b = a
0x5bb0489fdb80	label L4
0x5bb0489fd800	t6 = a > 0
0x5bb0489fdcc0	ifz t6 goto L5
0x5bb0489fda80	var d
0x5bb0489fda10	d = 10
0x5bb0489fdbc0	goto L4
0x5bb0489fdd00	label L5
0x5bb0489fde70	var t7
0x5bb0489fdeb0	actual b
0x5bb0489fdef0	actual a
0x5bb0489fdf30	t7 = call max
0x5bb0489fdfe0	end
