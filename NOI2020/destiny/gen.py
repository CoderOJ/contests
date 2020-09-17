import random

n = 500
m = 15
print(n)

def get(u):
    return random.randrange(u)+1

for i in range(2,n+1):
    print(get(i-1),i)

print(m)
for i in range(m):
    print(1,get(n))
