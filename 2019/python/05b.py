from enum import IntEnum

values = open('05.in', 'r').read().split(',')
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

    def __init__(self, program):
        self.pos = 0
        self.memory = [x for x in program]
    
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
                value = int(input('INPUT: '))
                self.memory[p1] = value
                self.pos += 2
            elif de_op == Computer.Opcode.OUTPUT:
                p1 = self.get_read(c_mode, c_param)
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

cpu = Computer(program)
cpu.run()