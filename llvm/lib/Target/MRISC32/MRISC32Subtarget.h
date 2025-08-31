//
// Created by shobhit on 8/31/25.
//

#ifndef LLVM_MRISC32_MRISC32SUBTARGET_H
#define LLVM_MRISC32_MRISC32SUBTARGET_H

#include "MRISC32FrameLowering.h"
#include "MRISC32ISelLowering.h"
#include "MRISC32InstrInfo.h"
#include "MRISC32RegisterInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "MRISC32GenSubtargetInfo.inc"

namespace llvm
{
class MRISC32Subtarget : public MRISC32GenSubtargetInfo {
      MRISC32InstrInfo InstrInfo;
      MRISC32FrameLowering FrameLowering;
      MRISC32TargetLowering TLInfo;
      MRISC32RegisterInfo RegInfo;

   public:
      MRISC32Subtarget(const Triple &TT, const std::string &CPU,
                       const std::string &FS, const TargetMachine &TM);

      MRISC32Subtarget &initializeSubtargetDependencies(StringRef CPU,
                                                        StringRef FS);

      const MRISC32InstrInfo *getInstrInfo() const override { return &InstrInfo; }

      const MRISC32FrameLowering *getFrameLowering() const override {
            return &FrameLowering;
      }

      const MRISC32TargetLowering *getTargetLowering() const override {
            return &TLInfo;
      }

      const MRISC32RegisterInfo *getRegisterInfo() const override {
            return &InstrInfo.getRegisterInfo();
      }
};
}
#endif // LLVM_MRISC32_MRISC32SUBTARGET_H
