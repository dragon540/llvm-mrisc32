

#include "llvm/CodeGen/RegisterBankInfo.h"

#define GET_REGBANK_DECLARATIONS
#include "MRISC32GenRegisterBank.inc"
#undef GET_REGBANK_DECLARATIONS

namespace llvm {

class TargetRegisterInfo;

class MRISC32kGenRegisterBankInfo : public RegisterBankInfo {
protected:
#define GET_TARGET_REGBANK_CLASS
#include "MRISC32GenRegisterBank.inc"
#undef GET_TARGET_REGBANK_CLASS
};

/// This class provides the information for the target register banks.
class MRISC32RegisterBankInfo final : public MRISC32GenRegisterBankInfo {
public:
  MRISC32RegisterBankInfo(const TargetRegisterInfo &TRI);

  const InstructionMapping &
  getInstrMapping(const MachineInstr &MI) const override;
};

}