//
// Created by shobhit on 8/31/25.
//

#include "MRISC32TargetMachine.h"

MRISC32TargetMachine::MRISC32TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT) 
                       : CodeGenTargetMachineImpl(T, computeDataLayout(TT), TT, CPU, FS, Options,
                         getEffectiveRelocModel(RM),
                         getEffectiveCodeModel(CM, CodeModel::Small), OL),
                         TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
                         Subtarget(TT, std::string(CPU), std::string(FS), *this) 
                        {}

TargetPassConfig* MRISC32TargetMachine::createPassConfig(PassManagerBase &PM) {
    return new MRISC32PassConfig(*this, PM);
}

TargetTransformInfo MRISC32TargetMachine::getTargetTransformInfo(const Function &F) const {
    return TargetTransformInfo(std::make_unique<MRISC32TTIImpl>(this, F));
}