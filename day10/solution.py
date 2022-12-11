with open("input.txt") as f:
    values = f.readlines()

moves = 0
x = 1
canSee = []
sprite = [x-1, x, x+1]
foo = []
for val in values:
    val = val.strip()
    valSplit = val.split()
    if len(valSplit) == 1:
        moves += 1
        canSee.append(moves % 40 in sprite)
        foo.append(x)
    else:
        moves += 1
        canSee.append(moves % 40 in sprite)
        foo.append(x)
        moves += 1
        x += int(valSplit[1])
        sprite = [x-1, x, x+1]
        canSee.append(moves % 40 in sprite)
        foo.append(x)

s = 0
s += foo[19] * 20
s += foo[59] * 60
s += foo[99] * 100
s += foo[139] * 140
s += foo[179] * 180
s += foo[219] * 220

print(s)

buffer = ""
i = 0
for val in canSee:
    if i % 40 == 0:
        print(buffer)
        buffer = ""
    if val:
        buffer += "#"
    else:
        buffer += "."
    i += 1

print(buffer)
