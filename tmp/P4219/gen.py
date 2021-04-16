from random import *

n = 100000
q = 100000
print(n, q+n-1)

fa = [0] * (n+5)

for i in range(2, n+1):
    fa[i] = randrange(1, i)
    print('A', fa[i], i)

for i in range(q):
    u = randrange(1,n+1)
    print('Q', fa[u], u)
