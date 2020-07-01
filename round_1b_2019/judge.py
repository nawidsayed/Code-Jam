
arr = [23,15,99,51,21,100]
g1 = 200
g2 = 55

summ = 0

for i in range(6):
	r = arr[i]
	ind = i+1

	exp = g1 // ind

	summ += r * 2**exp

print(summ % 2**63)



summ = 0

for i in range(6):
	r = arr[i]
	ind = i+1

	exp = g2 // ind

	summ += r * 2**exp

print(summ % 2**63)


	

