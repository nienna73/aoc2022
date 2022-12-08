class Directory:
    def __init__(self):
        self.name = ""
        self.children = []
        self.subdirectories = []
        self.parent = ""
        self.size = 0

    def set_name(self, name):
        self.name = name

    def add_child(self, child):
        self.children.append(child)

    def add_subdirectory(self, subdirectory):
        self.subdirectories.append(subdirectory)

    def set_parent(self, parent):
        self.parent = parent

    def get_name(self):
        return self.name

    def get_children(self):
        return self.children
    
    def get_subdirectories(self):
        return self.subdirectories

    def get_parent(self):
        return self.parent

    def get_size(self):
        return self.size

    def increment_size(self, i):
        self.size += i

    def copy(self):
        ret = Directory()
        ret.set_name(self.name)
        ret.set_parent(self.parent)
        for child in self.get_children():
            ret.add_child(child)

        for subdirectory in self.get_subdirectories():
            ret.add_subdirectory(subdirectory)

        return ret


class File:
    def __init__(self):
        self.name = ""
        self.parent = Directory()
        self.size = 0

    def set_name(self, name):
        self.name = name

    def set_parent(self, parent):
        self.parent = parent

    def set_size(self, size):
        self.size = size

    def get_name(self):
        return name

    def get_parent(self):
        return parent

    def get_size(self):
        return size


def readFromFile():
    ret = []
    with open("input.txt") as f:
        ret = f.readlines()

    return ret

def getDirectory(current, name):
    for subdir in current.get_subdirectories():
        if subdir.get_name() == name:
            return subdir

    return None

def initializeDirectory(lines):
    home = Directory()
    home.set_name("home")
    home.set_parent(None)
    current = home
    for line in lines:
        splitline = line.split()
        if ".." in splitline:
            current = current.get_parent()
        elif "/" in splitline:
            current = home
        elif "cd" in splitline:
            name = splitline[2]
            current = getDirectory(current, name)
        elif "dir" in splitline:
            # it's a directory
            dirname = splitline[1]
            newdir = Directory()
            newdir.set_name(dirname)
            newdir.set_parent(current)
            current.add_subdirectory(newdir)
        elif "$" not in splitline:
            # it's a file
            filename = splitline[1]
            size = splitline[0]
            newfile = File()
            newfile.set_name(filename)
            newfile.set_parent(current)
            newfile.set_size(size)
            temp = current
            while temp:
                temp.increment_size(int(size))
                temp = temp.get_parent()

    return home


def findTopSizes(l, total):
    for item in l:
        if item.get_size() <= 100000:
            total += item.get_size()
        total = findTopSizes(item.get_subdirectories(), total)
    return total

def findSmallestBigEnoughFile(l, size, spaceNeeded):
    for item in l:
        if item.get_size() <= size and item.get_size() >= spaceNeeded:
            size = item.get_size()
        size = findSmallestBigEnoughFile(item.get_subdirectories(), size, spaceNeeded)
    return size


if __name__ == '__main__':
    lines = readFromFile()
    home = initializeDirectory(lines)
    total = 0
    total = findTopSizes([home], total)
    print("Part 1 answer: ", total)

    totalDiskSpace = 70000000
    spaceNeeded = 30000000
    freeSpace = totalDiskSpace - home.get_size()
    spaceNeeded = spaceNeeded - freeSpace
    smallestBigEnoughSize = findSmallestBigEnoughFile([home], totalDiskSpace, spaceNeeded)
    print("Part 2 answer: ", smallestBigEnoughSize)
    