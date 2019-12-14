#!/usr/bin/python3

values = open('02.in', 'r').read().split(',')
program = [int(x) for x in values]

class IntCode:
    def __init__(self, program):
        self.pos = 0
        self.memory = [x for x in program]
        self.program = [x for x in program]

    def op_add(self):
        in_pos_1 = self.program[self.pos + 1]
        in_pos_2 = self.program[self.pos + 2]
        out_pos = self.program[self.pos + 3]
        self.program[out_pos] = self.program[in_pos_1] + self.program[in_pos_2]
    
    def op_mul(self):
        in_pos_1 = self.program[self.pos + 1]
        in_pos_2 = self.program[self.pos + 2]
        out_pos = self.program[self.pos + 3]
        self.program[out_pos] = self.program[in_pos_1] * self.program[in_pos_2]

    def run(self):
        opcode = self.program[self.pos]
        while opcode != 99:
            if opcode == 1:
                self.op_add()
            elif opcode == 2:
                self.op_mul()
            else:
                raise Exception('Invalid state')
            self.pos += 4
            opcode = self.program[self.pos]
        return

def solve():
    for noun in range(0, 100):
        for verb in range(0, 100):
            print((noun, verb))
            cpu = IntCode(program)
            cpu.program[1] = noun
            cpu.program[2] = verb
            try:
                cpu.run()
                if cpu.program[0] == 19690720:
                    return 100 * noun + verb
            except:
                pass

print(solve())
