from queue import Queue

values = open('06.in', 'r').read().split('\n')
orbits = [x.split(')') for x in values if x] 
orbits_rev = [list(reversed(x)) for x in orbits]

def get_map(orbits):
    _map = {}
    for obj in orbits:
        if obj[0] in _map:
            _map[obj[0]].append(obj[1])
        else:
            _map[obj[0]] = [obj[1]]
    return _map

out_map = get_map(orbits)
in_map = get_map(orbits_rev)
edges = {}
for key, value in out_map.items():
    if key in edges:
        edges[key].extend(value)
    else:
        edges[key] = value

for key, value in in_map.items():
    if key in edges:
        edges[key].extend(value)
    else:
        edges[key] = value

def bfs(edges, start='YOU', end='SAN'):
    q = Queue()
    visited = set(start)
    parents = {}
    q.put(start)
    while not q.empty():
        v = q.get()
        if v == end:
            path = []
            cur = end
            while (cur != start):
                path.append(cur)
                cur = parents[cur]
            path.append(start)
            return path
        for _v in edges[v]:
            if _v not in visited:
                parents[_v] = v
                q.put(_v)
                visited.add(_v)
        
print(len(bfs(edges)) - 3)
        