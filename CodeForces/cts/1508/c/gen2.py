from random import *

n = 200000
m = n - 1
print(n,m)

for i in range(2, n+1):
    print(randrange(1, i), i, randrange(1e9-10, 1e9))
