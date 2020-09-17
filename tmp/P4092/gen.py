import random
n,m = 10,10
print("{} {}".format(n,m))
for i in range(n-1):
    a = i+2
    b = random.randrange(i+1)+1
    print("{} {}".format(a,b))
qr = ['Q','C']
for i in range(m):
    print("{} {}".format(qr[random.randrange(2)], random.randrange(n)+1))
