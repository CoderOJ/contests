l, s0 = map(int, input().split())
n = 0
for i in range(l):
    n = n * 10 + (s0 // 1024) % 10
    s0 = (747796405 * s0 - 1403630843) % 4294967296

t = 11
ans = 0
while t <= n:
    ans += n // t
    t = t * 10 + 1

print(ans)
