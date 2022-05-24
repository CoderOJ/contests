from random import *

n = 43 * 10 ** 3
u = list(range(n))
shuffle(u)

print(n)
for i in range(n):
    print(i + 1, n + u[i] + 1)
