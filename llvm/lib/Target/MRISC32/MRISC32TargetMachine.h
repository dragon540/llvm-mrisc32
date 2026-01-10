//
// Created by shobhit on 8/31/25.
//

#ifndef LLVM_LIB_TARGET_MRISC32_MRISC32TARGETMACHINE_H
#define LLVM_LIB_TARGET_MRISC32_MRISC32TARGETMACHINE_H

#include "MRISC32Subtarget.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <memory>
#include <optional>

#include "MRISC32Subtarget.h"

namespace llvm
{
class MRISC32TargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  mutable std::unique_ptr<MRISC32Subtarget> Subtarget;

  public:
  MRISC32TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT);

  const MRISC32Subtarget *getSubtargetImpl(const Function &F) const override;

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetTransformInfo getTargetTransformInfo(const Function &F) const override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

class MRISC32PassConfig : public TargetPassConfig {
public:
  MRISC32PassConfig(TargetMachine &TM, PassManagerBase &PM);

  MRISC32TargetMachine &getMRISC32TargetMachine() const {
    return getTM<MRISC32TargetMachine>();
  }
  
  //bool addInstSelector() override;

  void addIRPasses() override;
  
  bool addIRTranslator() override;
  
  bool addLegalizeMachineIR() override;
  
  bool addRegBankSelect() override;
  
  bool addGlobalInstructionSelect() override;
};

}

#endif // LLVM_LIB_TARGET_MRISC32_MRISC32TARGETMACHINE_H
