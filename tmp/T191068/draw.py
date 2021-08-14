n, m = map(int, input().split())
val = [0] + list(map(int, input().split()))
for i in range(1, n):
    u, v = map(int, input().split())
    print("{}_{} {}_{}".format(u, val[u], v, val[v]));
