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

n,m = 800, 300
w = 3000
print(n,m)
for i in range(n):
    randSeq(m,w)
q = 50000
print(q)
for i in range(q):
    ty = get(3)
    print('MIN')
    x1,y1 = get(n)-1, get(m)-1
    x2,y2 = get(n)-1, get(m)-1
    if x1>x2:
        x1,x2 = x2,x1
    if y1>y2:
        y1,y2 = y2,y1
    # while (x2-x1)>2*(y2-y1) or (y2-y1)>2*(x2-x1):
    #     x1,y1 = get(n)-1, get(m)-1
    #     x2,y2 = get(n)-1, get(m)-1
    #     if x1>x2:
    #         x1,x2 = x2,x1
    #     if y1>y2:
    #         y1,y2 = y2,y1
    print(x1,y1, x2,y2, end="")
