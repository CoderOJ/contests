n = int(input())
p = [int(x) for x in input().split()]
q = [int(x) for x in input().split()]
a = [p[i] + q[i] for i in range(n)]
b = [p[i] - q[i] for i in range(n)]

def calc(a):
    a = sorted(a)
    return sum(map(lambda i: a[i] * (i - (n - i - 1)), range(n))) * 2

print(calc(p) + calc(q) - (calc(a) + calc(b)) // 2)
