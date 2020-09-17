import math

n,m = map(int,input().split())
for i in range(n):
    l,r,d = map(int,input().split())
    a = l*d
    print(math.gcd(a,m))

