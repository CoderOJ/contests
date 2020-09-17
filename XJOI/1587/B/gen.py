n,p,q = 3000,792,1001
print(n,p,q)

import random
def get(u):
    return random.randrange(u)+1

for i in range(2,n+1):
    print(get(i-1),i)

