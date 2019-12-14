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
        elif direction == 'D':
            dy = cur_y + steps
            new_coords = [(cur_x, y) for y in range(cur_y + 1, dy + 1)]
        elif direction == 'U':
            dy = cur_y - steps
            new_coords = reversed([(cur_x, y) for y in range(dy, cur_y)])
        else:
            raise Exception('Invalid state')
        coords.extend(new_coords)
    return coords
    
a_path = traverse(wire_path[0])
b_path = traverse(wire_path[1])
a_coords = set(a_path)
b_coords = set(b_path)
intersection = [x for x in a_coords if x in b_coords and x != (0,0)]

def count_steps_to(path, coordinates):
    return [path.index(coord) for coord in coordinates]

a_steps = count_steps_to(a_path, intersection)
b_steps = count_steps_to(b_path, intersection)

sum_steps = [a_steps[i] + b_steps[i] for i in range(0, len(a_steps))]
print(min(sum_steps))