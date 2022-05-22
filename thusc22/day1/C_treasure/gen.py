from random import *

n = 1000000

es = []
es.append((0, 1))
es.append((1, 2))
es.append((2, 3))
for i in range(4, n):
    u1 = randrange(min(i // 2, 10))
    u2 = randrange(min(i // 2, 100))
    while u1 == u2:
        u1 = randrange(min(i // 2, 10))
        u2 = randrange(min(i // 2, 100))
    es.append((i - u1 * 2 - 1, i))
    es.append((i - u2 * 2 - 1, i))

m = len(es)
print(1, n, m, randrange(n))
for u, v in es:
    print(u, v)
