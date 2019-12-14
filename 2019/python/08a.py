values = open('08.in', 'r').read()[:-1]

width = 25
height = 6
no_of_layers = len(values) // (width * height)

layers = []
for i in range(0, no_of_layers):
    start = i * width * height
    end = (i + 1) * width * height
    layers.append([x for x in values[start:end]])

min_i = 0
for i in range(0, no_of_layers):
    if layers[i].count('0') < layers[min_i].count('0'):
        min_i = i

print(layers[min_i].count('1') * layers[min_i].count('2'))