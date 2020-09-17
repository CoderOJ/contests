import random

n=100
a = [i for i in range(1,n+1)]
b = [i for i in range(1,n+1)]

random.shuffle(a)
random.shuffle(b)

print(n)
for i in a:
    print(i, end=' ')
print('')
for i in b:
    print(i, end=' ')
print('')
