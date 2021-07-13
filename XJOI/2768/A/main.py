from math import factorial

def ncr(n, r):
    return factorial(n) // (factorial(r) * factorial(n - r))

for i in range(100):
    a = ncr(*map(int, input().split()))
    b = ncr(*map(int, input().split()))
    if a > b:
        print(1)
    elif a < b:
        print(0)
    else:
        print(2)
