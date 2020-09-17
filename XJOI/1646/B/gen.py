import random 
def get(u):
    return random.randrange(u)+1

def randTree(n):
    for i in range(2,n+1):
        print(get(i-1),i)

def randSeq(n,w):
    for i in range(n):
        print(get(w), end=' ')
    print('')

def randPerm(n):
    a = [(i+1) for i in range(n)]
    random.shuffle(a)
    for i in a:
        print(i,end=' ')
    print('')

def randGraphCUW(n,m):
    b = []
    for i in range(n-1):
        b.append( [i+2,get(i+1)] )
    for i in range(m-n+1):
        u,v = get(n),get(n)
        b.append( [u,v] )
    random.shuffle(b)
    for i in range(m):
        print(b[i][0],b[i][1])

def randGraphCW(n,m,w):
    b = []
    for i in range(n-1):
        b.append( [i+2,get(i+1)] )
    for i in range(m-n+1):
        u,v = get(n),get(n)
        b.append( [u,v] )
    for i in range(m):
        print(b[i][0],b[i][1],get(w-100)+100)

def randGraphUCUW(n,m):
    b = []
    for i in range(m):
        u,v = get(n),get(n)
        b.append( [u,v] )
    random.shuffle(b)
    for i in range(m):
        print(b[i][0],b[i][1])

def randGraphUCW(n,m,w):
    b = []
    for i in range(m):
        u,v = get(n),get(n)
        b.append( [u,v] )
    random.shuffle(b)
    for i in range(m):
        print(b[i][0],b[i][1],get(w))

def randUS(n):
    m = n//3
    a = []
    for i in range(m): a.append(get(n))
    a.sort()
    b = []
    for i in range(len(a)):
        if i == 0 or a[i] != a[i-1]:
            b.append(a[i])
    return b

n,m,w = 100000, 200000, 10000
a = randUS(n)
k = len(a)
print(n,m,k)
randGraphCW(n,m,w)
for i in range(k):
    print(a[i], end=' ')
print()
