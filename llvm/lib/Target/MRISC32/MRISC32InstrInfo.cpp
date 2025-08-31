//
// Created by shobhit on 8/31/25.
//

#include "MRISC32InstrInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "MRISC32GenInstrInfo.inc"

MRISC32InstrInfo::MRISC32InstrInfo(const MRISC32RegisterInfo &RI)
    : MRISC32GenInstrInfo(), RI(RI) {}

void MRISC32InstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                   MachineBasicBlock::iterator I,
                                   const DebugLoc &DL,
                                   Register DestReg, Register SrcReg,
                                   bool KillSrc, bool RenamableDest,
                                   bool RenamableSrc) const {
  if (DestReg == SrcReg)
    return;

  report_fatal_error("copyPhysReg not implemented yet");
  // We may want to define some kind of mov instruction to use here 
}

void MRISC32InstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                           MachineBasicBlock::iterator I,
                                           Register SrcReg, bool isKill,
                                           int FrameIndex,
                                           const TargetRegisterClass *RC,
                                           const TargetRegisterInfo *TRI,
                                           Register VReg,
                                           MachineInstr::MIFlag Flag) const {
  // We may have to define some kind of store instruction before building this
  // Something to replace STri                                          
  BuildMI(MBB, I, DebugLoc(), get(MRISC32::STri))
      .addReg(SrcReg, getKillRegState(isKill))
      .addFrameIndex(FrameIndex)
      .addImm(0); // offset
}

void MRISC32InstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                            MachineBasicBlock::iterator I,
                                            Register DestReg, int FrameIndex,
                                            const TargetRegisterClass *RC,
                                            const TargetRegisterInfo *TRI,
                                            Register VReg,
                                            MachineInstr::MIFlag Flag) const {
  // We may have to define some kind of load instruction before building this
  // Something to replace LDri          
  BuildMI(MBB, I, DebugLoc(), get(MRISC32::LDri), DestReg)
      .addFrameIndex(FrameIndex)
      .addImm(0); // offset
}




