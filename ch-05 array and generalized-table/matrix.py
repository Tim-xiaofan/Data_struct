#!/usr/bin/python
#!/usr/bin/env python
#matix.py
import numpy as np #need "np." as prefix
M= np.mat([[3,4,9,5], 
	[0,-1,10,-5],
	[2,7,0,6]])
print("M = \n", M)
N = np.mat([[1,2],
    [1,3],
    [-2,4],
    [5,9]])
print("N = \n", N)
print("matrix: M * N = \n", M * N)
print("matrix: 2 * N = \n", 2 * N)
print("matrix: N.T = \n", N.T)
print("matrix: N.I = \n", N.I)
