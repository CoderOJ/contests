def trim(n):
    while len(n) > 1 and n[0] == "0":
        n = n[1:]
    return n

def noting(n):
    return trim("".join(map(lambda c: "1" if c == "0" else "0", n)))

def doubling(n):
    if n == "0":
        return "0"
    return n + "0"

def doit(f, t, param):
    pos = param[0] if len(param) >= 1 else " "
    ans = 0
    for c in param:
        if c != pos:
            f = noting(f)
            ans += 1
        f = doubling(f)
        ans += 1
        pos = c
    if pos == "1":
        f = noting(f)
        ans += 1

    while len(f) > len(t):
        f = noting(noting(f))
        ans += 2
    if f == t:
        return ans
    return 10 ** 100

def main():
    a, b = input().split()
    ans = 10 ** 100
    lb = len(b)
    for i in range(lb+1):
        ans = min(ans, doit(a, b, b[lb-i:]))
        ans = min(ans, doit(noting(a), b, b[lb-i:]) + 1)
    if ans >= 10 ** 100:
        return "IMPOSSIBLE"
    return ans

T = int(input())
for i in range(T):
    print("Case #{}: {}".format(i + 1, main()))
