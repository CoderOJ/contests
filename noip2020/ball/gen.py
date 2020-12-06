import random

n = 50
m = 400

a = []
for i in range(n):
    for j in range(m):
        a.append(i+1)

random.shuffle(a)

print(n, m)
for i in range(n):
    for j in range(m):
        print(a[i*m+j], end=' ')
    print('')
