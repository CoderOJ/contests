from random import *

def randString(n):
    return ''.join(['#'for i in range(n)])

n = 200
m = 200
print(n,m)
print(*[randString(m) for i in range(n)], sep='\n')
