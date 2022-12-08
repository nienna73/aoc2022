def setup():
    lines = []
    with (open("test-input.txt")) as f:
        lines = f.readlines()
    return lines

def toMatrix():
    matrix = []
    lines = setup()
    matrix = [[int(l) for l in line if l != "\n"] for line in lines]
    return matrix


def canSee(matrix, i, j):
    # check for edge
    if (i == len(matrix) - 1):
        return 1
    if (j == len(matrix[0]) - 1):
        return 1
    if i == 0:
        return 1
    if j == 0:
        return 1

    val = matrix[i][j]
    k = j
    n = i

    # check bottom
    while n < len(matrix):
        if matrix[n][j] > val:
            return 0
        n += 1

    # check right
    while k < len(matrix[0]):
        if matrix[i][k] > val:
            return 0
        k += 1

    k = j
    n = i
    # check top
    while n > 0:
        if matrix[n][j] > val:
            return 0
        n -= 1

    # check left
    while k > 0:
        if matrix[i][k] > val:
            return 0
        k -= 1
    
    return 1

def findSeen(matrix):
    seen = 0
    for (i, line) in enumerate(matrix):
        for (j, tree) in enumerate(line):
            seen += canSee(matrix, i, j)

    return seen


if __name__ == "__main__":
    matrix = toMatrix()
    seen = findSeen(matrix)
    print(seen)
