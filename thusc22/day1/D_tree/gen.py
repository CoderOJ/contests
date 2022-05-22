from random import *

n = 500000
m = 100000
k = 5
print(n, m, k)
print(*[randrange(1, i) for i in range(2, n + 1)])
print("1" * (n - 1))
for i in range(m):
    print(2, randrange(1, n + 1), randrange(1, n + 1), "1" * k)
