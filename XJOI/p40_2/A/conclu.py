def mu(x):
    if x == 1:
        return 1
    res = 0
    for i in range(1,x): 
        if 

def f(a,b):
    if a % b != 0:
        return 0
    if a < b:
        return 0
    if a == b:
        return 1
    ans = 0
    for d in range(2,b+1): 
        if b % d == 0:
            l = a // d
            p = b // d
            for e in range(p, l+1):
                if l % e == 0:
                    ans += f(e,p)
    return ans

def g(a,b):
    ans = 0
    for c in range(1,a+1):
        if a % c == 0:
            ans += f(c,b)
    return ans

