//
// Created by shobhit on 8/31/25.
//

#include "MRISC32RegisterInfo.h"
#include "MRISC32Subtarget.h"
#include "MRISC32InstrInfo.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/Support/ErrorHandling.h"
#include <cassert>
#include <iterator>

#define GET_INSTRINFO_CTOR_DTOR
#include "MRISC32GenInstrInfo.inc"

#define GET_INSTRINFO_ENUM
#include "MRISC32GenInstrInfo.inc"

#define GET_REGINFO_ENUM
#include "MRISC32GenRegisterInfo.inc"

using namespace llvm;

MRISC32InstrInfo::MRISC32InstrInfo()
    : MRISC32GenInstrInfo(MRISC32::ADJCALLSTACKDOWN, MRISC32::ADJCALLSTACKUP) {}

void MRISC32InstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                   MachineBasicBlock::iterator I,
                                   const DebugLoc &DL,
                                   Register DestReg, Register SrcReg,
                                   bool KillSrc, bool RenamableDest,
                                   bool RenamableSrc) const {
  if (DestReg == SrcReg)
    return;

  assert(DestReg != MRISC32::r0 && "Trying copy to register R0");

  // DestReg <-- SrcReg + 0
  BuildMI(MBB, I, DL, get(MRISC32::ADD_B), DestReg)
      .addReg(SrcReg, getKillRegState(KillSrc))
      .addReg(MRISC32::r0);
}

void MRISC32InstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                           MachineBasicBlock::iterator I,
                                           Register SrcReg, bool isKill,
                                           int FrameIndex,
                                           const TargetRegisterClass *RC,
                                           const TargetRegisterInfo *TRI,
                                           Register VReg,
                                           MachineInstr::MIFlag Flag) const {
  BuildMI(MBB, I, DebugLoc(), get(MRISC32::STW_C))
      .addReg(SrcReg, getKillRegState(isKill))
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void MRISC32InstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                            MachineBasicBlock::iterator I,
                                            Register DestReg, int FrameIndex,
                                            const TargetRegisterClass *RC,
                                            const TargetRegisterInfo *TRI,
                                            Register VReg,
                                            MachineInstr::MIFlag Flag) const {
  BuildMI(MBB, I, DebugLoc(), get(MRISC32::LDW_C), DestReg)
      .addFrameIndex(FrameIndex)
      .addImm(0); // offset
}




