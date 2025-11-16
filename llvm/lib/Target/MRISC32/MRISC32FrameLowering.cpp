//
// Created by shobhit on 9/1/25.
//

#include "MRISC32FrameLowering.h"

using namespace llvm;

void MRISC32FrameLowering::emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const {

}
  
void MRISC32FrameLowering::emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const {
    
}

bool MRISC32FrameLowering::hasFPImpl(const MachineFunction &MF) const {
    return false;
}