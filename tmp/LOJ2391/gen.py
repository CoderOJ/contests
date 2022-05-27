from random import *

n = 4
a = list(range(1, 1 + n * 2))
shuffle(a)

print(n)
for i in range(n):
    l, r = a[i * 2], a[i * 2 + 1]
    if l > r:
        l, r = r, l
    print(l, r)
