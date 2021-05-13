n = 1000005
phi = [i for i in range(n)]
for i in range(1,n):
    for j in range(2 * i, n, i):
        phi[j] -= phi[i]

input()
for i in range(int(input())):
    n, m = map(int, input().split())
    ans = 0
    for i in range(1, n + 1):
        ans += phi[i] * (n // i) * (m // i)
    print(ans)
