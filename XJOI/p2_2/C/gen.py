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

def getInter(n):
    l,r = get(n), get(n)
    if l > r:
        l,r = r,l
    return l,r

print(0)

n = 50000
m = 50000
q = 100000
w = 1000000

state = [False for i in range(m+1)]
trace = [0 for i in range(m+1)]

print(n,m,q)

for i in range(1,q+1):
    opt = get(100)
    if opt == 1:
        # this is a modify operation
        # rand an position and revert it
        pos = get(m)
        if state[pos] == False:
            # do not have one, then add one
            trace[pos] = i
            state[pos] = True
            l,r = getInter(n)
            p,q = get(n), get(n)
            print('I', l,r,pos,p,q)
        else:
            state[pos] = False
            caseId = trace[pos]
            print('D', caseId)
    else:
        x = get(n)
        l,r = 1,m
        print('Q', x,l,r)
