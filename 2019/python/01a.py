#!/usr/bin/python3

values = open('01.in', 'r').readlines()
module_masses = [int(x) for x in values]
result = sum([x//3 - 2 for x in module_masses])
print(result)