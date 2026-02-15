//
// Created by shobhit on 9/1/25.
//

#ifndef LLVM_LIB_TARGET_MRISC32_MRISC32FRAMELOWERING_H
#define LLVM_LIB_TARGET_MRISC32_MRISC32FRAMELOWERING_H

#include "MRISC32.h"

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm
{
class MachineInstrBuilder;
class MCCFIInstruction;
class MRISC32Subtarget;
class MRISC32RegisterInfo;
class MRISC32Subtarget;

class MRISC32FrameLowering : public TargetFrameLowering {
public:
    const MRISC32Subtarget &STI;
    const TargetInstrInfo &TII;
    const MRISC32RegisterInfo *TRI;

    explicit MRISC32FrameLowering(const MRISC32Subtarget &STI);

    void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  
    void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

    bool hasFPImpl(const MachineFunction &MF) const override;
};
}
#endif // LLVM_MRISC32_MRISC32FRAMELOWERING_H
