def gen(a, n):
    res = ""
    for i in range(n):
        res = res + str(a)
        a += 1
    return int(res)

def main():
    n = int(input())
    ans = 10 ** 100
    for length in range(2, 18):
        l, r = 1, 10 ** 20
        while l < r:
            mid = (l + r) // 2
            if gen(mid, length) > n:
                r = mid
            else:
                l = mid + 1
        pos = gen(l, length)
        #  print(length, pos)
        if ans > pos:
            ans = pos
    return ans

T = int(input())
for i in range(T):
    print("Case #{}: {}".format(i + 1, main()))
