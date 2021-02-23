n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))

aid = [0] * (n+1)
for i in range(n):
    aid[a[i]] = i

bid = [0] * (n+1)
for i in range(n):
    bid[b[i]] = i


def solve(al, ar, bl, br):    
    if al == ar:
        return 0
    l_root = a[al + 1]
    r_root = b[br - 1]
    if l_root == r_root:
        return solve(al+1, ar, bl, br-1) + 1
    else:
        return solve(al+1, aid[r_root]-1, bl, bid[l_root]) + solve(aid[r_root], ar, bid[l_root]+1, br-1)

print(2 ** solve(0,n-1, 0,n-1))
