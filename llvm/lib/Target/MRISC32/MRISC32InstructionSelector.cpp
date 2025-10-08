#include "MRISC32RegisterBankInfo.h"
#include "MRISC32Subtarget.h"
#include "MRISC32TargetMachine.h"
#include "llvm/CodeGen/GlobalISel/GIMatchTableExecutorImpl.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "m68k-isel"

using namespace llvm;

#define GET_GLOBALISEL_PREDICATE_BITSET
#include "MRISC32GenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATE_BITSET

namespace {

class MRISC32InstructionSelector : public InstructionSelector {
public:
  MRISC32InstructionSelector(const MRISC32TargetMachine &TM, const MRISC32Subtarget &STI,
                          const MRISC32RegisterBankInfo &RBI);

  bool select(MachineInstr &I) override;
  static const char *getName() { return DEBUG_TYPE; }

private:
  bool selectImpl(MachineInstr &I, CodeGenCoverage &CoverageInfo) const;

  const MRISC32TargetMachine &TM;
  const MRISC32InstrInfo &TII;
  const MRISC32RegisterInfo &TRI;
  const MRISC32RegisterBankInfo &RBI;

#define GET_GLOBALISEL_PREDICATES_DECL
#include "MRISC32GenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATES_DECL

#define GET_GLOBALISEL_TEMPORARIES_DECL
#include "MRISC32GenGlobalISel.inc"
#undef GET_GLOBALISEL_TEMPORARIES_DECL
};

} // end anonymous namespace

#define GET_GLOBALISEL_IMPL
#include "MRISC32GenGlobalISel.inc"
#undef GET_GLOBALISEL_IMPL

MRISC32InstructionSelector::MRISC32InstructionSelector(
    const MRISC32TargetMachine &TM, const MRISC32Subtarget &STI,
    const MRISC32RegisterBankInfo &RBI)
    : InstructionSelector(), TM(TM), TII(*STI.getInstrInfo()),
      TRI(*STI.getRegisterInfo()), RBI(RBI),

#define GET_GLOBALISEL_PREDICATES_INIT
#include "MRISC32GenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATES_INIT
#define GET_GLOBALISEL_TEMPORARIES_INIT
#include "MRISC32GenGlobalISel.inc"
#undef GET_GLOBALISEL_TEMPORARIES_INIT
{
}

bool MRISC32InstructionSelector::select(MachineInstr &I) {
  // Certain non-generic instructions also need some special handling.
  if (!isPreISelGenericOpcode(I.getOpcode()))
    return true;

  if (selectImpl(I, *CoverageInfo))
    return true;

  return false;
}

namespace llvm {
InstructionSelector *
createMRISC32InstructionSelector(const MRISC32TargetMachine &TM,
                              const MRISC32Subtarget &Subtarget,
                              const MRISC32RegisterBankInfo &RBI) {
  return new MRISC32InstructionSelector(TM, Subtarget, RBI);
}
} // end namespace llvm
