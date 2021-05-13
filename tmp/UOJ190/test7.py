from math import gcd

n = 10

def make_query(n):
    res = []
    for i in range(n):
        for j in range (n):
            res.append([i + 1, j + 1])
    return res

def get_det_table(n):
    table = [[0] * n for i in range(n)]
    for i in range(n):
        for j in range(n):
            table[i][j] = int(input())
    for i in range(n):
        for j in range(n-1, 0, -1):
            table[i][j] -= table[i][j-1]
    for i in range(n):
        for j in range(n-1, 0, -1):
            table[j][i] -= table[j - 1][i]
    return table

t = get_det_table(n)
for a in t:
    for i in a:
        print("%4d" % i, end = "")
    print()

print()

for i in range(n):
    for j in range(n):
        print("%4d" % (gcd(i + 1, j + 1)), end = "")
    print()
