from functools import lru_cache
from sys import setrecursionlimit

setrecursionlimit(10 ** 5)

@lru_cache(10 ** 5)
def calc(x):
    if x == 1:
        return 0
    else:
        l = 1
        r = x // 2
        f = lambda k: x - 1 + k + calc(k) + calc(x - k)
        s = x // 100 + 1
        return min(map(f, range(l, r + 1, s)))

s = 1000
for i in range(s, 45 * 10 ** 3, s):
    print(i, calc(i))
