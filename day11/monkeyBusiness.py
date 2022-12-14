class Monkey():
    items = []
    itemsInspected = 0
    operation = '-'
    factor = 'n'
    test = -1
    ifTrue = 0
    ifFalse = 0

def monkeySetup(lines):
    monkeys = []
    monkey = Monkey()
    for line in lines:
        line = line.strip('\n')
        if "Monkey" in line:
            monkey = Monkey()
        elif "items" in line:
            line = line.split(':')
            items = line[1].split(', ')
            items = [int(i) for i in items]
            monkey.items = items
        elif "Operation:" in line:
            line = line.split()
            operation = line[-2]
            monkey.operation = operation
            factor = line[-1]
            if factor != "old":
                monkey.factor = int(factor)
            else:
                monkey.factor = factor
        elif "Test:" in line:
            line = line.split()
            factor = line[-1]
            if factor != "old":
                monkey.test = int(factor)
            else:
                monkey.test = factor
        elif "true" in line:
            line = line.split()
            monkey.ifTrue = int(line[-1])
        elif "false" in line:
            line = line.split()
            monkey.ifFalse = int(line[-1])
        else:
            monkeys.append(monkey)

    monkeys.append(monkey)
    return monkeys

def runSimulation(monkeys, rounds=10000):
    i = 0
    while i < rounds:
        for monkey in monkeys:
            for item in monkey.items:
                monkey.itemsInspected += 1
                if monkey.factor == "old":
                    factor = item
                else:
                    factor = monkey.factor
                if monkey.operation == '+':
                    item = item + factor
                elif monkey.operation == '*':
                    item = item * factor

                if item % monkey.test == 0:
                    monkeys[monkey.ifTrue].items.append(item)
                else:
                    monkeys[monkey.ifFalse].items.append(item)
            monkey.items = []
        print("finished round", i)
        i += 1


    return monkeys



if __name__ == '__main__':
    with open("input.txt") as f:
        lines = f.readlines()
    monkeys = monkeySetup(lines)
    monkeys = runSimulation(monkeys)
    for monkey in monkeys:
        print(monkey.itemsInspected)
