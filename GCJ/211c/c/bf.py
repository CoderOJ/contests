def trim(n):
    while len(n) > 1 and n[0] == "0":
        n = n[1:]
    return n

def noting(n):
    return trim("".join(map(lambda c: "1" if c == "0" else "0", n)))

def doubling(n):
    return n + "0"

def dfs(u, to, limit):
    if limit < 0:
        return 100
    if u == to:
        return 0
    return min(dfs(noting(u), to, limit-1), dfs(doubling(u), to, limit - 1)) + 1

def main():
    a, b = input().split()
    res = dfs(a, b, 13)
    if res >= 100:
        return "IMPOSSIBLE"
    return res

T = int(input())
for i in range(T):
    print("Case #{}: {}".format(i + 1, main()))
