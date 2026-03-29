//
// Created by shobhit on 8/31/25.
//

#include "MRISC32RegisterInfo.h"
#include "MRISC32Subtarget.h"
#include "MCTargetDesc/MRISC32MCTargetDesc.h"
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

#define DEBUG_TYPE "mrisc32-reg-info"

using namespace llvm;

MRISC32RegisterInfo::MRISC32RegisterInfo()
    : MRISC32GenRegisterInfo(MRISC32::r0) {}

const MCPhysReg *MRISC32RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
    return CSR_SaveList; // CSR_SaveList is generated from CSR in MRISC32CallingConv.td
}

BitVector MRISC32RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
    BitVector Reserved(getNumRegs());
    // Example: Reserve R0 if R0 is hardwired to zero
    Reserved.set(MRISC32::r0); 
    Reserved.set(MRISC32::r28); // Frame pointer
    Reserved.set(MRISC32::r29); // Stack pointer
    return Reserved;
}

Register MRISC32RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
    return MRISC32::r28;
}

bool MRISC32RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator MI, int SPAdj,
                                              unsigned FIOperandNum,
                                              RegScavenger *RS = nullptr) const 
{
    MachineInstr &MInstr = *MI;
    MachineFunction &MF = *MInstr.getParent()->getParent();
    const MachineFrameInfo &MFI = MF.getFrameInfo();
    
    // Get the Frame Index and the frame offset
    int FrameIndex = MInstr.getOperand(FIOperandNum).getIndex();
    int Offset = MFI.getObjectOffset(FrameIndex) + MInstr.getOperand(FIOperandNum + 1).getImm();

    // Register being used as the base (Frame Pointer register here)
    Register BaseReg = MRISC32::r28;

    MInstr.getOperand(FIOperandNum).ChangeToRegister(BaseReg, false);
    MInstr.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
    // For now: leave unimplemented stub that returns false
    //llvm_unreachable("eliminateFrameIndex not yet implemented");
    return false;
}
