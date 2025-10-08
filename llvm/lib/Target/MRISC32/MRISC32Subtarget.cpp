//
// Created by shobhit on 8/31/25.
//

#include "MRISC32Subtarget.h"

using namespace llvm;

#define DEBUG_TYPE "mrisc32-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "MRISC32GenSubtargetInfo.inc"

MRISC32Subtarget::MRISC32Subtarget(const Triple &TT, const std::string &CPU,
                       const std::string &FS, const TargetMachine &TM) :
         MRISC32GenSubtargetInfo(TT, CPU, FS),
         RegisterInfo(*this),
         InstrInfo(*this),
         FrameLowering(*this),
         TLInfo(TM, *this) {

        CallLoweringInfo.reset(new BPFCallLowering(*getTargetLowering()));
        Legalizer.reset(new BPFLegalizerInfo(*this));
         auto *RBI = new BPFRegisterBankInfo(*getRegisterInfo());
        RegBankInfo.reset(RBI);

        InstSelector.reset(createBPFInstructionSelector(
            *static_cast<const BPFTargetMachine *>(&TM), *this, *RBI));
}


void MRISC32Subtarget::initializeSubtargetFeatures(StringRef CPU, StringRef FS) {
    // For now, nothing special — can later parse CPU and features here
}

const MRISC32Subtarget::MRISC32RegisterInfo *getRegisterInfo() {
    return &RegisterInfo;
}

const MRISC32Subtarget::MRISC32InstrInfo *getInstrInfo() {
    return &InstrInfo;
}

const MRISC32Subtarget::MRISC32FrameLowering *getFrameLowering() {
    return &FL;
}

const MRISC32Subtarget::MRISC32TargetLowering *getTargetLowering() {
    return &TL;
}

const CallLowering *MRISC32Subtarget::getCallLowering() const {
  return CallLoweringInfo.get();
}

const LegalizerInfo *MRISC32Subtarget::getLegalizerInfo() const {
  return Legalizer.get();
}

const RegisterBankInfo *MRISC32Subtarget::getRegBankInfo() const {
  return RegBankInfo.get();
}

InstructionSelector *MRISC32Subtarget::getInstructionSelector() const {
  return InstSelector.get();
}
