import random
import math

def get(u):
    return random.randrange(u)+1

L=1e2
R=1e6
M=1e8
D=200
PD=1e8

n,m = 16,get(M)
print(n,m)

pd=get(PD)
while math.gcd(pd,m) != 1:
    pd=get(PD)

for i in range(n):
    l = get(L)
    r = l + get(R)
    d = get(D)*pd
    if math.gcd(d,m) != 1:
        continue
    print(l,r,d)
