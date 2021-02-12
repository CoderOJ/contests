n, k = map(int, input().split())
n += 1
a = list( map(int, input().split()) )

wei = 1
tot = 0
for i in a:
    tot += wei * i
    wei += wei

wei = 1
ans = 0
for i in range(len(a)):
    if tot % wei != 0:
        break
    if abs(a[i] - tot // wei) <= k and (a[i]-tot//wei != 0 or i != len(a)-1):
        ans += 1
    wei *= 2

print(ans)
