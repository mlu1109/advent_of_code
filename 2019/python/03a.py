#!/usr/bin/python3

values = open('03.in', 'r').read().split('\n')

wire_path = [
    values[0].split(','),
    values[1].split(',')
]

def traverse(path, start=(0,0)):
    coords = [start]
    for action in path:
        steps = int(action[1:])
        direction = action[0]
        cur_x, cur_y = coords[-1]
        if direction == 'R':
            dx = cur_x + steps
            new_coords = [(x, cur_y) for x in range(cur_x + 1, dx + 1)]
        elif direction == 'L':
            dx = cur_x - steps
            new_coords = reversed([(x, cur_y) for x in range(dx, cur_x)])
        elif direction == 'U':
            dy = cur_y - steps
            new_coords = reversed([(cur_x, y) for y in range(dy, cur_y)])
        elif direction == 'D':
            dy = cur_y + steps
            new_coords = [(cur_x, y) for y in range(cur_y, dy + 1)]
        else:
            raise Exception('Invalid state')
        coords.extend(new_coords)
    return coords

a_coords = set(traverse(wire_path[0]))
b_coords = set(traverse(wire_path[1]))
a_coords.remove((0, 0))
b_coords.remove((0, 0))
intersection = [x for x in a_coords if x in b_coords]
distances = [abs(x) + abs(y) for (x, y) in intersection]
print(min(distances))
