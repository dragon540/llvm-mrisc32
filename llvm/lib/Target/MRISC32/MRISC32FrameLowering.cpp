//
// Created by shobhit on 9/1/25.
//

#include "MRISC32FrameLowering.h"

#include "MRISC32InstrInfo.h"
#include "MRISC32Subtarget.h"

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/Support/Alignment.h"
#include "llvm/IR/DebugLoc.h"

#define GET_INSTRINFO_ENUM
#include "MRISC32GenInstrInfo.inc"

#define GET_REGINFO_ENUM
#include "MRISC32GenRegisterInfo.inc"

using namespace llvm;

MRISC32FrameLowering::MRISC32FrameLowering(const MRISC32Subtarget &STI)
   : TargetFrameLowering(StackGrowsDown, Align(8), -4),
     STI(STI),
     TII(*STI.getInstrInfo()),
     TRI(STI.getRegisterInfo()) {}

void MRISC32FrameLowering::emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const {
    MachineBasicBlock::iterator MBBI = MBB.begin();
    MachineFrameInfo &MFI = MF.getFrameInfo();

    uint64_t stackSize = alignTo(MFI.getStackSize(), getStackAlign());
    MFI.setStackSize(stackSize);

    if(stackSize == 0) {
        return;
    }

    DebugLoc DL;

    Register framePointer = MRISC32::r28;
    Register stackPointer = MRISC32::r29;

    BuildMI(MBB, MBBI, DL, TII.get(MRISC32::ADD_C))
        .addReg(stackPointer, RegState::Kill)
        .addReg(stackPointer, RegState::Kill)
        .addImm(-stackSize)
        .setMIFlag(MachineInstr::FrameSetup);

    BuildMI(MBB, MBBI, DL, TII.get(MRISC32::STW_C))
        .addReg(framePointer, RegState::Kill)
        .addReg(stackPointer, RegState::Kill)
        .addImm(stackSize - 4);

    BuildMI(MBB, MBBI, DL, TII.get(MRISC32::ADD_C))
        .addReg(framePointer)
        .addReg(stackPointer)
        .addImm(stackSize);
}
  
void MRISC32FrameLowering::emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const {
    MachineBasicBlock::iterator MBBI = MBB.getFirstTerminator();
    MachineFrameInfo &MFI = MF.getFrameInfo();
    
    uint64_t stackSize = MFI.getStackSize();

    if(stackSize == 0) {
        return;
    }
    
    DebugLoc DL;

    Register framePointer = MRISC32::r28;
    Register stackPointer = MRISC32::r29;

    BuildMI(MBB, MBBI, DL, TII.get(MRISC32::LDW_C))
        .addReg(framePointer, RegState::Kill)
        .addReg(stackPointer, RegState::Kill)
        .addImm(stackSize - 4);

    BuildMI(MBB, MBBI, DL, TII.get(MRISC32::ADD_C))
        .addReg(stackPointer)
        .addReg(stackPointer)
        .addImm(stackSize);

}

bool MRISC32FrameLowering::hasFPImpl(const MachineFunction &MF) const {
    return false;
}