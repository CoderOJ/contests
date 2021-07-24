import random 
def get(u):
    return random.randrange(u)+1

def randInter(n):
    l, r = get(n), get(n)
    if l > r:
        l, r = r, l
    return [l, r]

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
    b = set()
    for i in range(n-1):
        b.add( (get(i+1), i+2) )
    while len(b) < m:
        u,v = randInter(n)
        while u == v:
            u,v = randInter(n)
        b.add( (u,v) )
    for a in b:
        print(*a)

def randGraphCW(n,m,w):
    b = []
    for i in range(n-1):
        b.append( [i+2,get(i+1)] )
    for i in range(m-n+1):
        u,v = get(n),get(n)
        b.append( [u,v] )
    random.shuffle(b)
    for i in range(m):
        print(b[i][0],b[i][1],get(w))

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

def randChar(c):
    return chr(ord('a') + get(c) - 1)

def randString(n, c):
    return ''.join([randChar(c) for i in range(n)])

n = 8
m = 10
print(n, m)
randGraphCUW(n, m)
