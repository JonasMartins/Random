def root_1(a = 10, p = 3, delta = 0.001, nn = 20, i = 1):
	'pth root of a - thru\' successive bifurcation'
#delta is the acceptable accuracy
#p is the exponent - integer
#nn is the maximum number of iterations acceptable
#i is the initial interval used for searching
	b, bp, n = 1, 1, 0
	while bp < a:
		b += i
		bp = b**p
	b1, b2 = b - i, b
	while (b2 - b1 > delta) and (n < nn):
		n += 1
		bm = (b1 + b2)/2.0
		if a > bm**p:b1 = bm
		else: b2 = bm
	print('bm = ', bm, ', p = ', p, 'n = ', n, ', a = ', a)
	return