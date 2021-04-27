def mex(a, b = -1):
    if a != 0 and b != 0:
        return 0
    if a != 1 and b != 1:
        return 1
    return 2

def gen_sg(n, w):
    res = [0] * n
    for i in range(1, n):
        if i >= w:
            res[i] = mex(res[i-1], res[i-w])
        else:
            res[i] = mex(res[i-1])
    return res
