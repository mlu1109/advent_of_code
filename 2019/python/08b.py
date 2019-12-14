values = open('08.in', 'r').read()[:-1]

width = 25
height = 6
no_of_layers = len(values) // (width * height)
layers = []

for i in range(0, no_of_layers):
    start = i * width * height
    end = (i + 1) * width * height
    layers.append([x for x in values[start:end]])

merged = ['2'] * (width * height)
for layer in layers:
    for i in range(0, width * height):
        if merged[i] == '2':
            if layer[i] == '1':
                merged[i] = '*'
            elif layer[i] == '0':
                merged[i] = ' '

for i in range(0, height):
    print(''.join(merged[i * width:(i + 1) * width]))