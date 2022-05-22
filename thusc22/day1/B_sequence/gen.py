from random import *

n = 100000
m = 100000
w = 10 ** 9

print(n, m)
print(*[randrange(-w, w) for i in range(n)])
print(*[randrange(-w, w) for i in range(m)])
