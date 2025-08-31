//
// Created by shobhit on 8/31/25.
//

#ifndef LLVM_MRISC32_MRISC32INSTRINFO_H
#define LLVM_MRISC32_MRISC32INSTRINFO_H

#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "MRISC32GenInstrInfo.inc"

namespace llvm
{
class MRISC32InstrInfo : public MRISC32GenInstrInfo {
  public:
    MRISC32InstrInfo();

    const MRISC32RegisterInfo &getRegisterInfo() const {
      return RI;
    }

    void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                     const DebugLoc &DL, Register DestReg, Register SrcReg,
                     bool KillSrc, bool RenamableDest = false,
                     bool RenamableSrc = false) const override;

    void storeRegToStackSlot(
      MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI, Register SrcReg,
      bool isKill, int FrameIndex, const TargetRegisterClass *RC,
      const TargetRegisterInfo *TRI, Register VReg,
      MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const override;

    void loadRegFromStackSlot(
      MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
      Register DestReg, int FrameIndex, const TargetRegisterClass *RC,
      const TargetRegisterInfo *TRI, Register VReg,
      MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const override;

};
}

#endif // LLVM_MRISC32_MRISC32INSTRINFO_H
