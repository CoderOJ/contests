from random import *

def randstring(n):
    return "".join([choice("qt") for i in range(n)])

n = 1000
m = 1000
l = 499
L = 2000

print(n, m)
for i in range(n):
    print(*[randstring(l) for i in range(L // (l + 1))])
for i in range(n):
    print("{},".format(randrange(1, n + 1)), end = "")
    print(*[randstring(l) for i in range(L // (l + 1))])
