n, k = input().split()
n = int(n)

if int(k) > int(k[::-1]):
    print(0)
else:
    ans = 0

    k1 = int(k)
    while k1 <= n:
        ans += 1
        k1 *= 10

    if k != k[::-1]:
        k2 = int(k[::-1])
        while k2 <= n:
            ans += 1
            k2 *= 10

    print(ans)
