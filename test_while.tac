.code
0x12f1040f0	label main
0x12f105020	begin
0x12f104270	var i
0x12f104220	i = 0
0x12f1043b0	var j
0x12f104360	j = 0
0x12f104ea0	label L3
0x12f104520	var t0
0x12f104550	t0 = i < 3
0x12f104ed0	ifz t0 goto L0
0x12f1046a0	j = 0
0x12f104b80	label L2
0x12f1047b0	var t1
0x12f1047e0	t1 = j < 5
0x12f104bb0	ifz t1 goto L1
0x12f104890	goto L1
0x12f1048f0	output j
0x12f104a50	var t2
0x12f104a80	t2 = j + 1
0x12f104ad0	j = t2
0x12f104be0	goto L2
0x12f104c10	label L1
0x12f104c70	output i
0x12f104d70	var t3
0x12f104da0	t3 = i + 1
0x12f104df0	i = t3
0x12f104f00	goto L3
0x12f104f30	label L0
0x12f104ff0	return 0
0x12f105050	end
