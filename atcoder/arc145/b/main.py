n, a, b = map(int, input().split())

if n < a:
    print(0)
elif a <= b:
    print(max(0, n - a + 1))
else:
    nq, nr = (n + 1) // a, (n + 1) % a
    print((nq - 1) * b + min(b, nr))
