def calc(n, p):
    res = 1
    k = 0
    while n > k * k:
        res *= n - k * k
        res %= p
        k += 1
    return res


def count(l,r,p):
    cnt = 0
    for i in range(l,r):
        if calc(i, p) == 0:
            cnt += 1
    return cnt

def check(n):
    st = n * n
    ed = n * n + n
    print( count(st,ed,n), "/", ed - st )

def loop(k, c):
    a = dict();
    last = 0
    for i in range(1,c+1):
        cur = count(i, k+i, k)
        if cur == last:
            a[cur] += 1
        else:
            last = cur
            a[cur] = 1
    print(a)
