//
// Created by shobhit on 8/31/25.
//

#ifndef LLVM_MRISC32_MRISC32REGISTERINFO_H
#define LLVM_MRISC32_MRISC32REGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "MRISC32GenRegisterInfo.inc"

namespace llvm
{
class MRISC32RegisterInfo : public MRISC32GenRegisterInfo
{
  public:
    MRISC32RegisterInfo();

    const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF);

    BitVector getReservedRegs(const MachineFunction &MF) const override;

    Register getFrameRegister(const MachineFunction &MF) const override;

    bool eliminateFrameIndex(MachineBasicBlock::iterator MI, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;
};
}

#endif // LLVM_MRISC32_MRISC32REGISTERINFO_H
