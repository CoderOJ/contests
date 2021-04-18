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
    random.shuffle(b)
    for i in range(m):
        print(b[i][0],b[i][1],get(w))

def randGraphUCUW(n,m):
    added = set()
    b = []
    for i in range(m):
        u,v = get(n),get(n)
        while (u,v) in added:
            u,v = get(n),get(n)
        added.add((u,v))
        added.add((v,u))
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

n = 5
m = 4
q = 3

print(n,m,q)
randPerm(n)
randGraphUCUW(n,m)

cut = set()
for i in range(q):
    opt = get(2)
    if len(cut) == m:
        opt = 1
    if opt == 1:
        print(opt, get(n))
    else:
        uid = get(n)
        while uid in cut:
            uid = get(n)
        cut.add(uid)
        print(opt, uid)
