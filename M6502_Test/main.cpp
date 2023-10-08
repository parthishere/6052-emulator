#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "M6502_Lib/cpu.h"


int main(){
    Mem mem;
    CPU cpu;
    cpu.reset(mem);
    mem[0xfffc] = CPU::INS_LDA_IM;
    mem[0xfffd] = 0x42;
    cpu.execute(2, mem);
    
}