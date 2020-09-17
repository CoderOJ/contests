import random

def get(u):
    return random.randrange(u)+1

n = int(1e5)
m = int(2e5)
print(n,m)

s = [i+1 for i in range(n)]
random.shuffle(s)
for i in s:
    print(i, end=' ')
print('')

for i in range(m):
    l,r = get(n),get(n)
    if l>r:
        l,r = r,l
    print(l,r,1,n)
