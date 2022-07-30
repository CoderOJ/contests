input = __import__('sys').stdin.readline

def get_game():
    n, m = map(int,input().split())

    up = input()
    down = input()

    if up[0] == "D": 
        up, down = down, up

    ls = []
    rs = []

    j = 0
    for c in down:
        if c == "D": 
            ls.append(j)
        else: 
            j += 1

    j = 0
    for c in up:
        if c == "D": 
            rs.append(j-1)
        else: 
            j+= 1

    j = m - 1
    while len(ls) > 1 and j > 0:
        ls.pop()
        rs.pop()
        j -= 1
        while j < ls[-1]: 
            ls.pop()
            rs.pop()
        j = min(j, rs[-1])
    return j, len(ls)-1

n = int(input())

h = 0
v = 0
for BOArsD in range(n):
    ch, cv = get_game()
    h += ch
    v += cv

print("First" if h > v else "Second")
