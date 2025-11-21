//
// Created by shobhit on 9/1/25.
//

#ifndef LLVM_LIB_TARGET_MRISC32_MRISC32ISELLOWERING_H
#define LLVM_LIB_TARGET_MRISC32_MRISC32ISELLOWERING_H

#include "llvm/CodeGen/TargetLowering.h"

namespace llvm
{
class MRISC32Subtarget;
class MRISC32TargetMachine;

class MRISC32TargetLowering : public TargetLowering {
public:
  const MRISC32Subtarget &Subtarget;
  explicit MRISC32TargetLowering(const TargetMachine &TM, const MRISC32Subtarget &STI);
};
}
#endif // LLVM_LIB_TARGET_MRISC32_MRISC32ISELLOWERING_H
