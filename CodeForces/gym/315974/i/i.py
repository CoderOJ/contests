def getPSum(p):
    ans = 0
    s = str(p)
    l = len(s)
    for i in range(l):
        d = int(s[i])
        af = 10 ** (l - i - 1)
        if i > 0:
            ans += int(s[:i]) * af * 45
        ans += af * d * (d - 1) // 2
        ans += d * ((int(s[i+1:]) if i+1 < l else 0)+ 1)
    return ans

goal = int(input())

def tryl(st):
    tg = goal + getPSum(st - 1) 
    l,r = 1, 10 ** 30
    while l < r:
        mid = (l + r) // 2
        if getPSum(mid) < tg:
            l = mid + 1
        else:
            r = mid
    if getPSum(l) == tg:
        print(st, l)
        exit()

st = 1
while True:
    tryl(st)
    st += 1
