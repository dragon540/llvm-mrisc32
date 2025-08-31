//
// Created by shobhit on 9/1/25.
//

#ifndef LLVM_MRISC32_MRISC32ISELLOWERING_H
#define LLVM_MRISC32_MRISC32ISELLOWERING_H

#include "llvm/CodeGen/TargetLowering.h"
#include "MRISC32Subtarget.h"

namespace llvm
{
class MRISC32Subtarget;

class MRISC32TragetLowering : public TargetLowering {
public:
  explicit MRISC32TargetLowering(const TargetMachine &TM, const MRISC32Subtarget &STI);
};
}
#endif // LLVM_MRISC32_MRISC32ISELLOWERING_H
