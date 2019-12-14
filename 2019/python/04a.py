values = open('04.in', 'r').read().split('-')
a, b = [int(x) for x in values]

def two_adjacent(x):
    _x = str(x)
    for i in range(0, len(_x) - 1):
        if _x[i] == _x[i + 1]:
            return True
    return False

def increasing(x):
    _x = [_x for _x in str(x)]
    _x_sorted = sorted(_x)
    return _x == _x_sorted

def is_valid(x):
    if not two_adjacent(x):
        return False
    if not increasing(x):
        return False
    return True

valid = 0
for x in range(a, b + 1):
    if is_valid(x):
        valid += 1

print(valid)

