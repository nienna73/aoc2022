def findCommon(line1, line2, line3):
    for c in line1:
        if c in line2 and c in line3:
            return c

with open("input.txt") as f:
    lines = f.readlines()

alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
print(alphabet.index('a'))

i = 0
while i < len(lines):
    line1 = lines[i]
    line2 = lines[i+1]
    line3 = lines[i+2]
    common = findCommon(line1, line2, line3)
    print(common)
    i += 3
