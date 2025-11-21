

#ifndef LLVM_LIB_TARGET_MRISC32_GLSEL_MRISC32REGISTERBANKINFO_H
#define LLVM_LIB_TARGET_MRISC32_GLSEL_MRISC32REGISTERBANKINFO_H

#include "MCTargetDesc/MRISC32MCTargetDesc.h"
#include "llvm/CodeGen/RegisterBankInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGenTypes/LowLevelType.h"

#define GET_REGBANK_DECLARATIONS
#include "MRISC32GenRegisterBank.inc"

namespace llvm {

class TargetRegisterInfo;

class MRISC32GenRegisterBankInfo : public RegisterBankInfo {
protected:
#define GET_TARGET_REGBANK_CLASS
#include "MRISC32GenRegisterBank.inc"
};

/// This class provides the information for the target register banks.
class MRISC32RegisterBankInfo final : public MRISC32GenRegisterBankInfo {
public:
  MRISC32RegisterBankInfo(const TargetRegisterInfo &TRI);

  const InstructionMapping &
  getInstrMapping(const MachineInstr &MI) const override;

  const RegisterBank &
  getRegBankFromRegClass(const TargetRegisterClass &RC,
                         LLT Ty) const override;
};
} // end namespace llvm
#endif
