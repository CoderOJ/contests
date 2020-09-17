import random

def get(u):
    return random.randrange(u)+1

def randTree(n):
    for i in range(2,n+1):
        print(get(i-1),i)

def randSeq(n):
    a = [(i+1) for i in range(n)]
    random.shuffle(a)
    for i in a:
        print(i,end=' ')
    print('')

