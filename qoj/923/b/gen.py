from random import *

n = 20
print(n)
a = list(range(1, n + 1)) + list(range(1, n + 1))
shuffle(a)
print(*a)
