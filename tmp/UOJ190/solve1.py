dic = [ "y", "f", "r", "b", "k", "g", "i", "m", "u", "j", "v", "p", "h", "a", "t", "d", "s", "n", "e", "l", "o", "z", "c", "x", "w", "q", ]

input()
for i in range(int(input())):
    print("".join(map(lambda x: dic[ord(x) - ord("a")], input())))
