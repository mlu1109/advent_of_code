values = open('06.in', 'r').read().split('\n')
direct_orbits = [x.split(')') for x in values if x]

orbits_map = {}
for orbit in direct_orbits:
    if orbit[0] in orbits_map:
        orbits_map[orbit[0]].append(orbit[1])
    else:
        orbits_map[orbit[0]] = [orbit[1]]

def traverse(orbits_map, key='COM', depth=0):
    if key != 'COM':
        depth += 1
    if key in orbits_map:
        _depth = depth
        for obj in orbits_map[key]:
            depth += traverse(orbits_map, obj, _depth)
    return depth

print(traverse(orbits_map))