from functools import reduce

T = int(input())
for i in range(T):
    input()
    xor_sum = reduce(lambda x, y : x ^ y, map(lambda x: x % 4, map(int, input().split())))
    print("first" if xor_sum else "second")
