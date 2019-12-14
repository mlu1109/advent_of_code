from enum import IntEnum

values = open('07.in', 'r').read().split(',')
program = [int(x) for x in values]

class Computer:
    class AddressingMode(IntEnum):
        POSITION = 0
        IMMEDIATE = 1
    
    class Opcode(IntEnum):
        ADD = 1
        MUL = 2
        INPUT = 3
        OUTPUT = 4
        JUMP_IF_TRUE = 5
        JUMP_IF_FALSE = 6
        LESS_THAN = 7
        EQUALS = 8
        HALT = 99

    def __init__(self, program, _input):
        self.pos = 0
        self.memory = [x for x in program]
        self.input = _input
    
    def get_read(self, mode, param):
        if mode == Computer.AddressingMode.POSITION:
            return self.memory[param]
        elif mode == Computer.AddressingMode.IMMEDIATE:
            return param
        else:
            raise Exception(f'Invalid addressing mode: {mode}')
    
    def get_write(self, mode, param):
        if mode == Computer.AddressingMode.POSITION:
            return param
        else:
            raise Exception(f'Invalid addressing mode: {mode}')

    """
    ABCDE
    1002

    DE - two-digit opcode,      02 == opcode 2
     C - mode of 1st parameter,  0 == position mode
     B - mode of 2nd parameter,  1 == immediate mode
     A - mode of 3rd parameter,  0 == position mode,
                                      omitted due to being a leading zero
    """
    def run(self):
        output = []
        while True:
            # Parse instruction
            instr = self.memory[self.pos]
            de_op =  instr % 100
            c_mode = instr % 1000   // 100
            b_mode = instr % 10000  // 1000
            a_mode = instr % 100000 // 10000
            try:
                c_param = self.memory[self.pos + 1]
                b_param = self.memory[self.pos + 2]
                a_param = self.memory[self.pos + 3]
            except IndexError:
                pass
            # Execute instruction
            if de_op == Computer.Opcode.ADD:
                p1 = self.get_read(c_mode, c_param)
                p2 = self.get_read(b_mode, b_param)
                p3 = self.get_write(a_mode, a_param)
                self.memory[p3] = p1 + p2
                self.pos += 4
            elif de_op == Computer.Opcode.MUL:
                p1 = self.get_read(c_mode, c_param)
                p2 = self.get_read(b_mode, b_param)
                p3 = self.get_write(a_mode, a_param)
                self.memory[p3] = p1 * p2
                self.pos += 4
            elif de_op == Computer.Opcode.INPUT:
                p1 = self.get_write(c_mode, c_param)
                if self.input:
                    self.memory[p1] = self.input[0]
                    self.input = self.input[1:]
                else:
                    self.memory[p1] = input('Input: ')
                self.pos += 2
            elif de_op == Computer.Opcode.OUTPUT:
                p1 = self.get_read(c_mode, c_param)
                output.append(p1)
                print(f'OUT {p1}')
                self.pos += 2
            elif de_op == Computer.Opcode.JUMP_IF_TRUE:
                p1 = self.get_read(c_mode, c_param)
                p2 = self.get_read(b_mode, b_param)
                if p1 != 0:
                    self.pos = p2
                else:
                    self.pos += 3
            elif de_op == Computer.Opcode.JUMP_IF_FALSE:
                p1 = self.get_read(c_mode, c_param)
                p2 = self.get_read(b_mode, b_param)
                if p1 == 0:
                    self.pos = p2
                else:
                    self.pos += 3
            elif de_op == Computer.Opcode.LESS_THAN:
                p1 = self.get_read(c_mode, c_param)
                p2 = self.get_read(b_mode, b_param)
                p3 = self.get_write(a_mode, a_param)
                self.memory[p3] = p1 < p2
                self.pos += 4
            elif de_op == Computer.Opcode.EQUALS:
                p1 = self.get_read(c_mode, c_param)
                p2 = self.get_read(b_mode, b_param)
                p3 = self.get_write(a_mode, a_param)
                self.memory[p3] = p1 == p2
                self.pos += 4
            elif de_op == Computer.Opcode.HALT:
                print(f'HALT')
                break
            else:
                raise Exception(f'Invalid opcode {de_op} at position {self.pos}')
        return output

def run_acs(phase_setting, program):
    out = [0]
    for i in range(0, 5):
        out = Computer(program, [phase_setting[i], out[0]]).run()
    return out[0]


from itertools import permutations 
phase_settings = list(permutations(range(0, 5))) 
signals = [run_acs(x, program) for x in phase_settings]

print(max(signals))
