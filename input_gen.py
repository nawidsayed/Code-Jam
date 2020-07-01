import numpy as np 

N = 2000000

arr = np.random.uniform(10000000, size=N).astype(int)
with open('input.txt', 'w') as f:
	f.write(str(1))
	f.write('\n')
	f.write(str(N))
	f.write('\n')
	for i in arr:
		f.write(str(i))
		f.write(' ')
	f.write('\n')