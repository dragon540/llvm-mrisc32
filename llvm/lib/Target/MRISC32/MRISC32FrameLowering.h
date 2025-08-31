//
// Created by shobhit on 9/1/25.
//

#ifndef LLVM_MRISC32_MRISC32FRAMELOWERING_H
#define LLVM_MRISC32_MRISC32FRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm
{
class MRISC32FrameLowering : public TargetFrameLowering {
    public:
        explicit MRISC32FrameLowering(const MRISC32Subtarget &sti)
            : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(8), 0) {}

  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
};
}
#endif // LLVM_MRISC32_MRISC32FRAMELOWERING_H
