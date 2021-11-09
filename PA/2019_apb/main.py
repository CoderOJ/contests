def calc(n: str) -> int:
    def split_count(n):
        if n >= 19:
            return 0
        elif n >= 10:
            return 19 - n
        else:
            return n + 1

    if len(n) == 0:
        return 1
    elif len(n) == 1:
        return split_count(int(n))
    else:
        if n[:1] == "0":
            return split_count(int(n[:1])) * calc(n[1:])
        else:
            return split_count(int(n[:1])) * calc(n[1:]) + split_count(int(n[:2])) * calc(n[2:])

print(calc(input()))
