//
// Created by shobhit on 8/31/25.
//

#include "MRISC32TargetMachine.h"
#include "MRISC32.h"
#include "MRISC32TargetObjectFile.h"
#include "MRISC32Subtarget.h"
#include "MRISC32TargetTransformInfo.h"
#include "TargetInfo/MRISC32TargetInfo.h" // For getTheMRISC32Target.
#include "llvm/CodeGen/GlobalISel/IRTranslator.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelect.h"
#include "llvm/CodeGen/GlobalISel/Legalizer.h"
#include "llvm/CodeGen/GlobalISel/RegBankSelect.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/CodeGen/MachineScheduler.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/InitializePasses.h"  // For initializeGlobalISel.
#include "llvm/MC/TargetRegistry.h" // For RegisterTargetMachine.
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/CodeGen.h" // For CodeGenOptLevel.
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Compiler.h" // For LLVM_EXTERNAL_VISIBILITY.
#include <memory>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMRISC32Target() {
  // Register the target so that external tools can instantiate it.
  RegisterTargetMachine<MRISC32TargetMachine> X(getTheMRISC32Target());

  PassRegistry &PR = *PassRegistry::getPassRegistry();
  //initializeMRISC32SimpleConstantPropagationPass(PR);
  //initializeMRISC32MandatoryPreLegalizerCombinerPass(PR);
  //initializeMRISC32MandatoryPostLegalizerCombinerPass(PR);
  initializeGlobalISel(PR);
}

static std::unique_ptr<TargetLoweringObjectFile> createTLOF(const Triple &TT) {
  if (TT.isOSBinFormatELF())
    return std::make_unique<MRISC32_ELFTargetObjectFile>();
  // Other format not supported yet.
  return nullptr;
}

// TODO: Share this with Clang.
static const char *MRISC32DataLayoutStr =
    "e-p:16:16:16-n16:32-i32:32:32-i16:16:16-i1:8:8-f32:32:32-v32:32:32";

MRISC32TargetMachine::MRISC32TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT) 
                       : CodeGenTargetMachineImpl(T, MRISC32DataLayoutStr, TT, CPU, FS, Options,
                         // Use the simplest relocation by default.
                         RM ? *RM : Reloc::Static,
                         CM ? *CM : CodeModel::Small,
                         OL),
                         TLOF(createTLOF(getTargetTriple())) {
  initAsmInfo();
  this->Options.ExceptionModel = ExceptionHandling::None;
}

const MRISC32Subtarget* MRISC32TargetMachine::getSubtargetImpl(const Function &F) const {
    Attribute CPUAttr = F.getFnAttribute("target-cpu");
    Attribute FSAttr = F.getFnAttribute("target-features");

    StringRef CPU = CPUAttr.isValid() ? CPUAttr.getValueAsString() : TargetCPU;
    StringRef FS = FSAttr.isValid() ? FSAttr.getValueAsString() : TargetFS;

    // Eventually, we'll want to hook up a different subtarget based on at the
    // target feature, target cpu, and tune cpu attached to F, but as of now,
    // the target doesn't support anything fancy so we just have one subtarget
    // for everything.
    if (!Subtarget)
        Subtarget =
            std::make_unique<MRISC32Subtarget>(TargetTriple, CPU, FS, *this);
    return Subtarget.get();
}

TargetPassConfig* MRISC32TargetMachine::createPassConfig(PassManagerBase &PM) {
    return new MRISC32PassConfig(*this, PM);
}

TargetTransformInfo MRISC32TargetMachine::getTargetTransformInfo(const Function &F) const {
    return TargetTransformInfo(std::make_unique<MRISC32TTIImpl>(this, F));
}

MRISC32PassConfig::MRISC32PassConfig(TargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

/***bool MRISC32PassConfig::addInstSelector() {
  addPass(createMRISC32ISelDAG(getMRISC32TargetMachine()));
  return false;
}***/

void MRISC32PassConfig::addIRPasses() {
  // Add the regular IR passes before putting our passes.
  TargetPassConfig::addIRPasses();
  //if (getOptLevel() != CodeGenOptLevel::None)
    //addPass(createMRISC32SimpleConstantPropagationPassForLegacyPM());
}

bool MRISC32PassConfig::addIRTranslator() {
    addPass(new IRTranslator(getOptLevel()));
    return false;
}

bool MRISC32PassConfig::addLegalizeMachineIR() {
  addPass(new Legalizer());
  return false;
}

bool MRISC32PassConfig::addRegBankSelect() {
    addPass(new RegBankSelect());
    return false;
}
  
bool MRISC32PassConfig::addGlobalInstructionSelect() {
    addPass(new InstructionSelect(getOptLevel()));
    return false;
}