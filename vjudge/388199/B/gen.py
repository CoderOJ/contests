import random

x=100

def get():
    return random.randrange(x)+1

n,m = 5,5
print("{} {}".format(n,m))
for i in range(n-1):
    u = i+2
    v = get() % (i+1) + 1
    print("{} {} {}".format(u,v,get()))

for i in range(m):
    rx = get()%2
    if rx==0:
        print("0 {} {}".format( get()%(n-1) +1 , get()) )
    else:
        print("1 {} {}".format( get()%(n-1) +1 , get()%(n-1) +1) )
