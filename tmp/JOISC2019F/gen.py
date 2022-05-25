from random import *

n = 2000
w = 500
m1 = 500000
m2 = 500000
print(n, m1, m2)

for i in range(m1):
    print(randrange(n), randrange(n), randrange(w))
for i in range(m2):
    print(randrange(n), randrange(n), randrange(w))
