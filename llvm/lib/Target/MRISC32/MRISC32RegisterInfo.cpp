//
// Created by shobhit on 8/31/25.
//

#include "MRISC32RegisterInfo.h"
#include "MRISC32Subtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_REGINFO_TARGET_DESC
#include "MRISC32GenRegisterInfo.inc"
using namespace llvm;

MRISC32RegisterInfo::MRISC32RegisterInfo()
    : MRISC32GenRegisterInfo(MRISC32::R0) {}

const MCPhysReg *MRISC32RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
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


