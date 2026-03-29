#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"
#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "llvm/CodeGen/GlobalISel/GISelChangeObserver.h"

namespace llvm {

class MRISC32Subtarget;

class MRISC32LegalizerInfo : public LegalizerInfo {
public:
  MRISC32LegalizerInfo(const MRISC32Subtarget &ST);

  bool legalizeCustom(LegalizerHelper &Helper, MachineInstr &MI, LostDebugLocObserver &LocObserver) const override;
  bool legalizeAdd(MachineInstr &MI, MachineRegisterInfo &MRI, MachineIRBuilder &MIRBuilder, GISelChangeObserver &Observer) const;
};
} // end namespace llvm