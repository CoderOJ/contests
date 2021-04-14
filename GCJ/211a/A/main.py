def main():
    n = int(input())
    a = list(map(int, input().split()))
    last = a[0]
    ans = 0
    for p in a[1:]:
        if p > last:
            last = p
            continue
        if p == last:
            last = p * 10
            ans += 1
            continue
        pl = len(str(p))
        target = last + 1
        if str(target)[:pl] == str(p):
            ans += len(str(target)) - pl
            last = target
        else:
            while p <= last:
                p *= 10
                ans += 1
            last = p
    return ans


T = int(input())
for case in range(T):
    print("Case #{}: {}".format(case+1, main()))
