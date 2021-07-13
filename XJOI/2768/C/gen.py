import random 
def get(u):
    return random.randrange(u)+1

def randTree(n,w):
    for i in range(2,n+1):
        print(get(i-1),i, get(w))

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

def getInter(n):
    l, r = get(n), get(n)
    if l > r:
        l,r = r,l
    return [l,r]

n = 100000
m = 4000
w = 100000

print(n,m)
randTree(n, w)
for i in range(m):
    opt = get(100)
    if opt != 1:
       print(1, get(n), get(n), get(w)) 
    else:
        st = []
        while len(st) == 0:
            for i in range(1, n+1):
                if get(13) == 1:
                    st.append(i)
        print(2, *getInter(20), len(st), *st)

