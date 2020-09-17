s,t,a,b = 1e3,1e18,1e3,1e5

import random
def get(u):
    if random.randrange(4)==0:
        return 0
    if random.randrange(10)==0:
        return 1
    return random.randrange(u)

print( get(s) , get(t) , get(a) , get(b) )
