//
// Created by shobhit on 8/31/25.
//

#ifndef LLVM_MRISC32_MRISC32TARGETMACHINE_H
#define LLVM_MRISC32_MRISC32TARGETMACHINE_H

#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"

#include "MRISC32Subtarget.h"

namespace llvm
{
class MRISC32TargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  MRISC32Subtarget Subtarget;

  public:
  MRISC32TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT);

  const MRISC32Subtarget *getSubtargetImpl() const { return &Subtarget; }
  const MRISC32Subtarget *getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetTransformInfo getTargetTransformInfo(const Function &F) const override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
}

#endif // LLVM_MRISC32_MRISC32TARGETMACHINE_H
