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
         InstrInfo(*this),
         FrameLowering(*this),
         TLInfo(TM, *this),
         RegInfo(*this)
{
    initializeSubtargetFeatures(StringRef CPU, StringRef FS) {
}


void MRISC32Subtarget::initializeSubtargetFeatures(StringRef CPU, StringRef FS) {
    // For now, nothing special — later you can parse CPU and features here
}


