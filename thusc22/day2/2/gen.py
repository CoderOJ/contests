from random import *

m = 10000
n = 20

def randstring(n):
    return "".join([choice("qwertyuiopassdfghjklzxcvbnm") for i in range(n)])

urls = [str(i) for i in range(m)]

print(m, n)
for i in range(n):
    print(choice(urls))

es = [[] for i in range(m)]
for i in range(m * 50):
    u, v = randrange(m), randrange(m)
    es[u].append(v)

for i in range(m):
    print(urls[i] + "," + " ".join(map(lambda x: urls[x], es[i])))
