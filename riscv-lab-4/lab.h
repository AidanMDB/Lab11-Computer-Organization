#ifndef LAB4H_
#define LAB4H_

#include <stdint.h>

enum state{
  Unset,
  Zero,
  One, 
  DC
};

struct ControlSignals {
  enum state Branch{Unset};
  enum state MemRead{Unset};
  enum state MemtoReg{Unset};
  uint8_t ALUOp{0b11};
  enum state MemWrite{Unset};
  enum state ALUSrc{Unset};
  enum state RegWrite{Unset};
  //enum state Zero{Unset}; //Implementing Zero requires Register state.
};

extern void setControl(uint32_t instBits, ControlSignals& outputSignals);
extern uint32_t getExtendedBits(uint32_t instBits);

#endif
