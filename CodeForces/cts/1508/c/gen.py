from random import *

n = 620
m = n * (n-1) // 2 - 3
print(n,m)

for i in range(1, n+1):
    for j in range(i+1, n+1):
        if i <= 3 and j <= 3:
            continue
        print(i, j, randrange(1e9-10, 1e9))
