//
// Created by shobhit on 8/31/25.
//

#ifndef LLVM_MRISC32_MRISC32SUBTARGET_H
#define LLVM_MRISC32_MRISC32SUBTARGET_H

#include "MRISC32RegisterInfo.h"
#include "MRISC32InstrInfo.h"
#include "MRISC32FrameLowering.h"
#include "MRISC32ISelLowering.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"
#include "llvm/CodeGen/RegisterBankInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "MRISC32GenSubtargetInfo.inc"

namespace llvm
{
class MRISC32Subtarget : public MRISC32GenSubtargetInfo {
      MRISC32RegisterInfo   RegisterInfo;
      MRISC32InstrInfo      InstrInfo;
      MRISC32FrameLowering  FL;
      MRISC32TargetLowering TL;

   public:
      MRISC32Subtarget(const Triple &TT, const std::string &CPU,
                       const std::string &FS, const TargetMachine &TM);

      MRISC32Subtarget &initializeSubtargetDependencies(StringRef CPU,
                                                        StringRef FS);

      const MRISC32RegisterInfo *getRegisterInfo() const override;

      const MRISC32InstrInfo *getInstrInfo() const override;

      const MRISC32FrameLowering *getFrameLowering() const override;

      const MRISC32TargetLowering *getTargetLowering() const override;

      const CallLowering *getCallLowering() const override;

      const LegalizerInfo *getLegalizerInfo() const override;

      const RegisterBankInfo *getRegBankInfo() const override;

      InstructionSelector *getInstructionSelector() const override;

   protected:
      std::unique_ptr<CallLowering> CallLoweringInfo;
      std::unique_ptr<InstructionSelector> InstSelector;
      std::unique_ptr<LegalizerInfo> Legalizer;
      std::unique_ptr<RegisterBankInfo> RegBankInfo;
};
}
#endif // LLVM_MRISC32_MRISC32SUBTARGET_H
