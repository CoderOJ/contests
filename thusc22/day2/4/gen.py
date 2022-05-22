from random import *
from sys import argv

n = int(argv[1])
print(n)
for i in range(n):
    # print(*[1 if randrange(j // 100 + 1) == 0 else 0 for j in range(n)])
    print(*[1 if i < j else 0 for j in range(n)])
