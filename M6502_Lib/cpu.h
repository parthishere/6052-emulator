#ifndef __cpu_h__

#define __cpu_h__

#include <iostream>


using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem{
    static constexpr u32 MAX_MEM = 1024*64; // 64kb
    Byte Data[MAX_MEM]; 

    void init(){
        for (u32 i=0; i< MAX_MEM; i++){
            Data[i] = 0;
        }
    }

    Byte operator[](u32 address) const {
        if (address < MAX_MEM)
            return Data[address];
        else
            return 0;
    }

    Byte& operator[](u32 address) {
        
        return Data[address];
    }
    
    // void operator+(u32 address) const{
        
    // }
}; 

struct CPU{
    
    Word PC;
    Word SP;


    Byte A, X, Y ;// Registers

    Byte C : 1; // Carry flag 
    Byte Z : 1; // Zero flag
    Byte I : 1; // Inturrupt disable 
    Byte D : 1; // Decimal mode flag 
    Byte B : 1; // Break command flag
    Byte V : 1; // Overflow flag
    Byte N : 1; // Negative flag

    void reset(Mem& memory){
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = B = I = D = V = N = 0;
        A = X = Y = 0;
        memory.init();

    }

    Byte Fetch(u32& cycles, Mem& memory){
        Byte data = memory[PC];
        PC++;
        cycles--;
        return data;
    }

    static constexpr Byte 
        INS_LDA_IM = 0xA9;

    void execute(u32 cycles, Mem& memory){
        while(cycles > 0){
            Byte value;
            Byte instruction = Fetch(cycles, memory);
            switch(instruction){
                case INS_LDA_IM:
                    value = Fetch(cycles, memory);
                    A = value;
                    Z = (A == 0);
                    N = (A & 0b10000000) > 0;

                    break;
                default:
                    std::cout << "instuction not handled !!: " << instruction << std::endl;

            }
        }
    }

};

#endif