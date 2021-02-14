n = int(input())
inner_ab = 0

head_b = 0
tail_a = 0
ht_ba = 0

for i in range(n):
    s = input()
    inner_ab += s.count("AB")
    head_b += s[0] == 'B'
    tail_a += s[-1] == 'A'
    ht_ba += s[0] == 'B' and s[-1] == 'A'

head_b -= ht_ba
tail_a -= ht_ba

ans = 0
if ht_ba > 0:
    if head_b == 0:
        ans += ht_ba - 1
        head_b += 1
    else:
        ans += ht_ba

ans += min(head_b, tail_a)

print(ans + inner_ab)
