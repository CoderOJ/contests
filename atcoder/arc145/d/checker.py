from sys import argv

n, m = map(int, open(argv[1]).readline().split())
s = list(map(int, open(argv[2]).readline().split()))

assert len(s) == n
assert sum(s) == m

for i in range(n):
    assert abs(s[i]) <= 10 ** 7

s = sorted(s)
for i in range(n):
    ds = sorted(list(map(lambda x: abs(x - s[i]), s)))
    for i in range(n - 1):
        if ds[i] == ds[i + 1]:
            print("error", i, ds)
