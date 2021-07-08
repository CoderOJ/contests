n = 1192
a = []
for i in range(n):
    l, r = map(int, input().split())
    a.append((r-l+1, l, r))

a.sort()
for x in a:
    print(*x)
