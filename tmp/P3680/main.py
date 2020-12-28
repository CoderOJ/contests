def isAllT(s):
    for c in s:
        if c != 'T':
            return False
    return True

def calcEdge(c):
    if c == 'T':
        return 2.5
    elif c == 'C':
        return 1 + pi / 2
    else:
        return 3



from math import *
n = int(input())
s = input()

if n == 1:
    if s[0] == 'T':
        print(3)
    elif s[0] == 'C':
        print(pi)
    else:
        print(4)
    exit()

if isAllT(s):
    print(2 * n + 1)
    exit()

ans = 2 * (n - 2)
ans += calcEdge(s[0])
ans += calcEdge(s[-1])

if s[0] == 'T':
    posLen = 0.5
    pos = 1
    while True:
        if s[pos] == 'T':
            posLen += 1
        elif s[pos] == 'S':
            dy = 1 - sqrt(3) / 2 
            ans -= posLen
            ans += sqrt( posLen**2 + dy**2 )
            break
        elif s[pos] == 'C':
            posLen += 0.5
            ans -= posLen
            newLen = sqrt( posLen**2 + (sqrt(3)/2-0.5) ** 2 - 0.5**2 )
            ans += newLen
            ans += (atan(posLen / (sqrt(3)/2-0.5)) - atan(newLen / 0.5)) * 0.5
            break
        pos += 1

if s[-1] == 'T':
    posLen = 0.5
    pos = n - 2
    while True:
        if s[pos] == 'T':
            posLen += 1
        elif s[pos] == 'S':
            dy = 1 - sqrt(3) / 2 
            ans -= posLen
            ans += sqrt( posLen**2 + dy**2 )
            break
        elif s[pos] == 'C':
            posLen += 0.5
            ans -= posLen
            newLen = sqrt( posLen**2 + (sqrt(3)/2-0.5) ** 2 - 0.5**2 )
            ans += newLen
            ans += (atan(posLen / (sqrt(3)/2-0.5)) - atan(newLen / 0.5)) * 0.5
            break
        pos -= 1

print(ans)
