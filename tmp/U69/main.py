code = """

# s: parameter 1
# d: parameter 2
# r: return value

if 1 goto main

safe_add:
    # r = s + d
    safe_add_retry:
        x = s + d
        y = s + d
        z = x - y
        if z goto safe_add_retry
    r = x
    if 1 goto safe_add_return

safe_mod:
    # r = s % d
    safe_mod_retry:
        x = s % d
        y = s % d
        z = x - y
        if z goto safe_mod_retry
    r = x
    if 1 goto safe_mod_return

safe_minus_1:
    # r = s - 1
    safe_minus_1_retry:
        x = s - 1
        y = s - 1
        z = x - y
        if z goto safe_minus_1_retry
    r = x
    if 1 goto safe_minus_1_return

main:
    input n
    input m

    a = 0
    b = 1

    loop_n:

        # c = a + b
        s = a
        d = b
        if 1 goto safe_add
        safe_add_return:
        c = r

        # c = c % m
        s = c
        d = m
        if 1 goto safe_mod
        safe_mod_return:
        c = r

        a = b
        b = c

        # n = n - 1
        s = n
        if 1 goto safe_minus_1
        safe_minus_1_return:
        n = r

        if n goto loop_n
        
    output a

""".strip()

line_number = 1
tag_dict = []
result = []

for line in code.split("\n"):
    line = line.strip()
    if line == "" or line.startswith("#"):
        pass
    elif line.endswith(":"):
        tag_name = line[:-1]
        tag_dict.append((tag_name, line_number))
    else:
        result.append(line)
        line_number += 1

for line in result:
    line = line + " "
    for (key, value) in tag_dict:
        line = (" " + str(value) + " ").join(line.split(" " + key + " "))
    print(line.strip())
