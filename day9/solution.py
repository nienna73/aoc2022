
def moveHead(head, direction, distance):
    if direction == "U":
        head[1] = head[1] + 1
    if direction == "L":
        head[0] = head[0] - 1
    if direction == "R":
        head[0] = head[0] + 1
    if direction == "D":
        head[1] = head[1] - 1
    return head

def isTouching(head, tail):
    if head == tail:
        return True
    if head[1] == tail[1] and head[0] + 1 == tail[0]:
        return True

    if head[1] == tail[1] and head[0] - 1 == tail[0]:
        return True

    if head[1] + 1 == tail[1] and head[0] == tail[0]:
        return True

    if head[1] - 1 == tail[1] and head[0] == tail[0]:
        return True

    if head[1] + 1 == tail[1] and head[0] + 1 == tail[0]:
        return True

    if head[1] - 1 == tail[1] and head[0] + 1 == tail[0]:
        return True

    if head[1] + 1 == tail[1] and head[0] - 1 == tail[0]:
        return True

    if head[1] - 1 == tail[1] and head[0] - 1 == tail[0]:
        return True

    return False

def moveTail(head, tail):
    if isTouching(head, tail):
        return tail

    if head[0] - tail[0] < 0:
        tail[0] -= 1
    elif head[0] - tail[0] > 0:
        tail[0] += 1

    if head[1] - tail[1] < 0:
        tail[1] -= 1
    elif head[1] - tail[1] > 0:
        tail[1] += 1
    return tail


def main():
    with open("input.txt") as f:
        values = f.readlines()

    print("Running simulation...")

    head = [0,0]
    tail1 = [0,0]
    tail2 = [0,0]
    tail3 = [0,0]
    tail4 = [0,0]
    tail5 = [0,0]
    tail6 = [0,0]
    tail7 = [0,0]
    tail8 = [0,0]
    tail9 = [0,0]
    seen = [tail1[:]]
    for value in values:
        value = value.strip('\n')
        split_values = value.split(' ')
        direction = split_values[0]
        distance = split_values[1]
        i = 0
        while i < int(distance):
            head = moveHead(head, direction, distance)
            tail1 = moveTail(head, tail1)
            tail2 = moveTail(tail1, tail2)
            tail3 = moveTail(tail2, tail3)
            tail4 = moveTail(tail3, tail4)
            tail5 = moveTail(tail4, tail5)
            tail6 = moveTail(tail5, tail6)
            tail7 = moveTail(tail6, tail7)
            tail8 = moveTail(tail7, tail8)
            tail9 = moveTail(tail8, tail9)

            if tail9 not in seen:
                seen.append(tail9[:])
            i += 1

    print(len(seen))


if __name__ == "__main__":
    main()