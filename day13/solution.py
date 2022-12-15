def getLines(inputFile):
    with open(inputFile) as f:
        lines = f.readlines()
    return lines

def removeBlanks(lines):
    ret = []
    for line in lines:
        if line != '\n':
            ret.append(line.strip('\n'))
    return ret

def findNextNum(line, index):
    i = index
    while i < len(line):
        try:
            return int(line[i])
        except:
            i += 1
    return -1

def getIndexes(lines):
    indexes = []
    i = 0
    while i < len(lines):
        line1 = lines[i]
        line2 = lines[i+1]
        i += 2
        j = 0
        while j < len(line1) and j < len(line2):
            num1 = findNextNum(line1, j)
            num2 = findNextNum(line2, j)
            if num1 < num2:
                if i/2 not in indexes:
                    indexes.append(i/2)
                j = len(line1)
            elif num1 > num2:
                break
            elif len(line1) < len(line2):
                if i/2 not in indexes:
                    indexes.append(i/2)
            j += 1

    return indexes


if __name__ == '__main__':
    lines = getLines("input.txt")
    lines = removeBlanks(lines)
    indexes = getIndexes(lines)
    s = sum(indexes)
    print(s)
    print(indexes)