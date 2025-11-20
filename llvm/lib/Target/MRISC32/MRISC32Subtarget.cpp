//
// Created by shobhit on 8/31/25.
//

#include "MRISC32Subtarget.h"
#include "MRISC32.h" // For MRISC32::createInstructionSelector.
#include "MRISC32ISelLowering.h"
#include "MRISC32TargetMachine.h"
#include "llvm/CodeGen/MachineScheduler.h" // For MachineSchedPolicy.
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "mrisc32-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "MRISC32GenSubtargetInfo.inc"

MRISC32Subtarget::MRISC32Subtarget(const Triple &TT, const std::string &CPU,
                       const std::string &FS, const TargetMachine &TM) :
         MRISC32GenSubtargetInfo(TT, CPU, FS),
         //RegisterInfo(*this),
         //InstrInfo(*this),
         FrameLowering(*this),
         TLInfo(TM, *this) {

        CallLoweringInfo.reset(new MRISC32CallLowering(*getTargetLowering()));
        Legalizer.reset(new MRISC32LegalizerInfo(*this));
        auto *RBI = new MRISC32RegisterBankInfo(*getRegisterInfo());
        RegBankInfo.reset(RBI);

        InstSelector.reset(createMRISC32InstructionSelector(
            *static_cast<const MRISC32TargetMachine *>(&TM), *this, *RBI));
}


//void MRISC32Subtarget::initializeSubtargetFeatures(StringRef CPU, StringRef FS) {
    // For now, nothing special — can later parse CPU and features here
//}

const MRISC32RegisterInfo *MRISC32Subtarget::getRegisterInfo() const {
    return &RegisterInfo;
}

const MRISC32InstrInfo *MRISC32Subtarget::getInstrInfo() const {
    return &InstrInfo;
}

const MRISC32FrameLowering *MRISC32Subtarget::getFrameLowering() const {
    return &FrameLowering;
}

const MRISC32Subtarget::MRISC32TargetLowering *getTargetLowering() {
    return &TLInfo;
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
