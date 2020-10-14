# 垃圾到不能再垃圾的题。。。
# 人生苦短我用python
# 
#
# 也没什么用

x,y,z = map(int, input().split())
y -= 1

def get(n,d):
    return str(d) + "*" + str(n) + "=" + str(n*d)

# The total length of "1*d 2*d ... n*d"
def getMulLen(n,d):
    base,l,res = 1,1,0
    while True:
        low,upp = base-1, min(base*10-1, n*d)
        res += (upp // d - low // d) * l
        base *= 10
        l += 1
        if base > n*d:
            break
    return res

def getLenBef(n,d):
    trash = 3*n-1 + len(str(d)) * n
    return trash + getMulLen(n,1) + getMulLen(n,d)

def getAns(d,le):
    l,r = 1,1024
    while getLenBef(r,d) < le:
        l,r = l*1024, r*1024
    while l<r:
        mid = (l+r)//2
        if getLenBef(mid,d) >= le:
            r = mid
        else:
            l = mid+1
    return l

def solve(d,pre,le):
    s = getAns(d,pre)
    pos = pre -  getLenBef(s-1,d) - 1
    ans = ""
    while len(ans) < le+pos:
        ans = ans + get(s,d) + " "
        s += 1
    return ans[pos:le+pos] 

for i in range(x,x+5):
    print( solve(i,y,z) )
