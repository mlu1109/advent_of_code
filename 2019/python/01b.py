#!/usr/bin/python3

values = open('01.in', 'r').readlines()
module_masses = [int(x) for x in values]
fuel_masses = [x//3 - 2 for x in module_masses]
fuel_masses_sum = sum(fuel_masses)
while fuel_masses:
    fuel_masses = [x//3 - 2 for x in fuel_masses if x//3 - 2 > 0]
    fuel_masses_sum += sum(fuel_masses)
print(fuel_masses_sum)
     