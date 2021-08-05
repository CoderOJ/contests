k = int(input())

if k == 1000:
    print(500)
    for i in range(500):
        print(*[i * 2 + 1, i * 2 + 2] * 250)
    exit(0)

if k == 1:
    print(1)
    print(1)
    exit(0)

n = k // 2 + 1
if n % 2:
    n += 1
ans = [[0 for i in range(n)] for i in range(n)]
for i in range(n):
    for j in range(n):
        ans[i][j] = (i + j) % n + (i % 2) * n + 1
for i in range(n):
    for j in range(n):
        if ans[i][j] > k:
            ans[i][j] -= n
print(n)
for i in ans:
    print(*i)
