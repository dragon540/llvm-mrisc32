

#ifndef LLVM_LIB_TARGET_MRISC32_GLSEL_MRISC32REGISTERBANKINFO_H
#define LLVM_LIB_TARGET_MRISC32_GLSEL_MRISC32REGISTERBANKINFO_H

#include "llvm/CodeGen/RegisterBankInfo.h"

#define GET_REGBANK_DECLARATIONS
#include "MRISC32GenRegisterBank.inc"

namespace llvm {

class TargetRegisterInfo;

class MRISC32kGenRegisterBankInfo : public RegisterBankInfo {
protected:
#define GET_TARGET_REGBANK_CLASS
#include "MRISC32GenRegisterBank.inc"
};

/// This class provides the information for the target register banks.
class MRISC32RegisterBankInfo final : public MRISC32GenRegisterBankInfo {
  const PartialMapping PartMappings[];
  const ValueMapping ValMappings[];
public:
  MRISC32RegisterBankInfo(const TargetRegisterInfo &TRI);

  const InstructionMapping &
  getInstrMapping(const MachineInstr &MI) const override;

  const RegisterBank &
        MRISC32RegisterBankInfo::getRegBankFromRegClass(const TargetRegisterClass &RC,
                                                    LLT Ty) const override;
};
} // end namespace llvm
#endif
