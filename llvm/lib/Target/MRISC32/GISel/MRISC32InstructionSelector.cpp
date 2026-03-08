#include "MRISC32RegisterBankInfo.h"
#include "MRISC32Subtarget.h"
#include "MRISC32TargetMachine.h"
#include "llvm/CodeGen/GlobalISel/GIMatchTableExecutorImpl.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "mrisc32-isel"

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
  if (!isPreISelGenericOpcode(I.getOpcode()))
    return true;

  unsigned Opcode = I.getOpcode();
  MachineRegisterInfo &MRI = I.getMF()->getRegInfo();

  // MANUALLY FORCE FOLDING FOR MEMORY OPS
  if (Opcode == TargetOpcode::G_LOAD || Opcode == TargetOpcode::G_STORE) {
    Register AddrReg = I.getOperand(1).getReg();
    MachineInstr *AddrDef = MRI.getVRegDef(AddrReg);

    // If the address is a G_FRAME_INDEX, merge it into this instruction
    if (AddrDef && AddrDef->getOpcode() == TargetOpcode::G_FRAME_INDEX) {
      int FI = AddrDef->getOperand(1).getIndex();
      unsigned NewOpc = (Opcode == TargetOpcode::G_STORE) ? MRISC32::STW_C : MRISC32::LDW_C;
      
      I.setDesc(TII.get(NewOpc));
      I.getOperand(1).ChangeToFrameIndex(FI);
      I.addOperand(MachineOperand::CreateImm(0)); // Placeholder for eliminateFrameIndex
      
      return constrainSelectedInstRegOperands(I, TII, TRI, RBI);
    }
  }

  if (selectImpl(I, *CoverageInfo))
    return true;

  // FALLBACK FOR REMAINING FRAME_INDEX (Materialization)
  if (Opcode == TargetOpcode::G_FRAME_INDEX) {
    int FI = I.getOperand(1).getIndex();
    I.setDesc(TII.get(MRISC32::ADD_C));
    I.getOperand(1).ChangeToFrameIndex(FI);
    I.addOperand(MachineOperand::CreateImm(0));
    return constrainSelectedInstRegOperands(I, TII, TRI, RBI);
  }

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
