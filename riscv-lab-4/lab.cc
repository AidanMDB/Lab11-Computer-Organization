#include "lab.h"
#include <stdint.h>
#include <stdio.h>

void setControl(uint32_t instBits, ControlSignals& outputSignals) {
  uint32_t OpCode = instBits & 0x7F;  // grabs last 7 values for OpCode
  switch(OpCode) {                      // checks which type the opcode matches
    case 0x03:                      // lw,
      outputSignals.Branch = Zero;
      outputSignals.MemRead = One;
      outputSignals.MemtoReg = One;
      outputSignals.ALUOp = 0b00;
      outputSignals.MemWrite = Zero;
      outputSignals.ALUSrc = One;
      outputSignals.RegWrite = One;
      break;
    case 0x13:                      // addi
      outputSignals.Branch = Zero;
      outputSignals.MemRead = Zero;
      outputSignals.MemtoReg = Zero;
      outputSignals.ALUOp = 0b10;
      outputSignals.MemWrite = Zero;
      outputSignals.ALUSrc = One;
      outputSignals.RegWrite = One;
      break;
    case 0x33:                      // add, sub
      outputSignals.Branch = Zero;
      outputSignals.MemRead = Zero;
      outputSignals.MemtoReg = Zero;
      outputSignals.ALUOp = 0b10;
      outputSignals.MemWrite = Zero;
      outputSignals.ALUSrc = Zero;
      outputSignals.RegWrite = One;
      break;
    case 0x23:                      // sw
      outputSignals.Branch = Zero;
      outputSignals.MemRead = Zero;
      outputSignals.MemtoReg = DC;
      outputSignals.ALUOp = 0b00;
      outputSignals.MemWrite = One;
      outputSignals.ALUSrc = One;
      outputSignals.RegWrite = Zero;
      break;
    case 0x63:                      // beq
      outputSignals.Branch = One;
      outputSignals.MemRead = Zero;
      outputSignals.MemtoReg = DC;
      outputSignals.ALUOp =0b01;
      outputSignals.MemWrite = Zero;
      outputSignals.ALUSrc = Zero;
      outputSignals.RegWrite = Zero;
      break;
  }

}

// Assume that the lower 32-bits of instBits contain the instruction.
uint32_t getExtendedBits(uint32_t instBits) {
  uint32_t returnVal = 0;
  uint32_t opcode = instBits & 0x7F;    // grabs the opcode
  if (opcode == 0x03 | opcode == 0x13) {                 // if its a lw or addi opcode
    // uint32_t bit_32nd = instBits >> 31;
    // for (int i = 0; i < 20; i++) {
    //   instBits = (instBits >> 1) | bit_32nd;
    // }
    returnVal = instBits >> 20;
    if (instBits & 0x80000000) returnVal |= 0xFFFFF000;
  }
  else if (opcode == 0x23) {            // if its a sw opcode
    uint32_t bits_11_7 = instBits & 0x780;    // grabs bits 11-0
    bits_11_7 = bits_11_7 >> 6;               // grabs bits 11-7
    bits_11_7 = bits_11_7 & 0xf;
    instBits = instBits & 0xFFFFFFF0;   // grabs everything except for the last 4 values
    returnVal = instBits & bits_11_7;   // combines 
  }
  else if (opcode == 0x63) {                      // if its beq
    uint32_t bits_30_25 = instBits & 0x7E000000;
    bits_30_25 = bits_30_25 >> 20;
    uint32_t bits_11_8 = instBits & 0x00000F00;
    bits_11_8 = bits_11_8 >> 7;
    uint32_t bit_7 = instBits & 0x00000080;
    bit_7 = bit_7 << 4;
    // returnVal = instBits & 0xFFFFFFFE;            // puts a 0 in the last bit place
    returnVal = returnVal | bits_11_8;
    returnVal = returnVal | bits_30_25;
    returnVal = returnVal | bit_7;
    if (instBits & 0x80000000) {
      returnVal |= 0xFFFFF000;
    }
    else {
      returnVal |= 0x00000000;
    }
  }
  return returnVal;
}
