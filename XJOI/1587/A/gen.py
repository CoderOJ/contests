import random
n,m = 1000,1000
RANGE=int(1000)

out=open('in',"w")

def get():
    return random.randrange(RANGE)+1

out.write('{} {} {}\n'.format(n,m,random.randrange(n*m)+1))
for i in range(n):
    for j in range(m):
        out.write("{} ".format(get()))
    out.write('\n')

        
