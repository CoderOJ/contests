import random as rd
import numpy as npy
from numpy.linalg import *
from math import *

pob = 0.1
max_n = 10
RESERVE = 1500
best = [0] * RESERVE


def rand_graph(n):
    es = [(u,v) for v in range(n) for u in range(v)]
    return list(filter(lambda x: rd.random() < pob, es))

def count(es, n):
    deg = [[0] * n for i in range(n)]
    for (u, v) in es:
        deg[u][u] += 1
        deg[v][v] += 1
        deg[u][v] -= 1
        deg[v][u] -= 1
    deg = deg[:-1]
    for i in range(len(deg)):
        deg[i] = deg[i][:-1]
    return int(round(det(npy.array(deg))))

uv_to_c = [[0] * max_n for i in range(max_n)]
cur = 40
for i in range(max_n):
    for j in range(i + 1, max_n):
        uv_to_c[i][j] = chr(cur)
        cur += 1


def encode(es):
    r = ""
    for (u,v) in es:
        r += uv_to_c[u][v]
    return '"' + r + '",'


while pob < 1.01:
    n = rd.randrange(3, max_n + 1)
    es = rand_graph(n)
    c = count(es, n)
    if c < RESERVE:
        if best[c] == 0:
            best[c] = (n, es)
        elif best[c][0] > n:
            best[c] = (n, es)
    pob += 0.000001

for i in range(len(best)):
    if best[i] != 0:
        print(encode(best[i][1]))
    else:
        print('"",')
