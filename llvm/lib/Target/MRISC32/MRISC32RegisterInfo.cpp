//
// Created by shobhit on 8/31/25.
//

#include "MRISC32RegisterInfo.h"

#define GET_REGINFO_TARGET_DESC
#include "MRISC32GenRegisterInfo.inc"

using namespace llvm;

MRISC32RegisterInfo::MRISC32RegisterInfo()
    : MRISC32GenRegisterInfo() {}

const MCPhysReg *MRISC32RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) {
    static const MCPhysReg CalleeSavedRegs[] = { 0 }; // Terminator
    return CalleeSavedRegs;
}

BitVector MRISC32RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
    BitVector Reserved(getNumRegs());
    // Example: Reserve R0 if R0 is hardwired to zero
    Reserved.set(MRISC32::R0); 
    return Reserved;
}

Register MRISC32RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
    return MRISC32::R28;
}

bool MRISC32RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator MI, int SPAdj,
                                              unsigned FIOperandNum,
                                              RegScavenger *RS = nullptr) const {

    // For now: leave unimplemented stub that returns false
    llvm_unreachable("eliminateFrameIndex not yet implemented");
    return false;
}


