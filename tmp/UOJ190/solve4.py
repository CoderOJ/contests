input()
for i in range(int(input())):
    n, m = map(int, input().split())

    fa = [i for i in range(n + 1)]
    def __get(fa, u):
        if u == fa[u]:
            return u
        fa[u] = __get(fa, fa[u])
        return fa[u]
    get = lambda x: __get(fa, x)

    for i in range(m):
        u, v = map(int, input().split())
        fa[get(u)] = get(v)

    cnt = [0] * (n + 1)
    for i in range(1, n+1):
        cnt[get(i)] += 1

    ans = 0
    for i in range(1, n + 1):
        ans += cnt[i] ** 2

    print(ans)
