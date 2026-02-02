//===----------------------------------------------------------------------===//
//
// This file provides MRISC32 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/MRISC32MCTargetDesc.h"
#include "MCTargetDesc/MRISC32InstPrinter.h"
#include "MCTargetDesc/MRISC32MCAsmInfo.h"
#include "MCTargetDesc/MRISC32TargetStreamer.h"
#include "TargetInfo/MRISC32TargetInfo.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/Support/Compiler.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/Support/FormattedStream.h"

#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "MRISC32GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "MRISC32GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "MRISC32GenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createMRISC32MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitMRISC32MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createMRISC32MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitMRISC32MCRegisterInfo(X, MRISC32::r11 /* RAReg doesn't exist */);
  return X;
}

static MCSubtargetInfo *createMRISC32MCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createMRISC32MCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCAsmInfo *createMRISC32MCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TheTriple,
                                       const MCTargetOptions &Options) {
  MCAsmInfo *MAI;
  //if (TheTriple.isOSBinFormatMachO())
  //  MAI = new H2BLBMCAsmInfoDarwin(TheTriple, Options);
  if (TheTriple.isOSBinFormatELF())
    MAI = new MRISC32MCAsmInfoELF(TheTriple, Options);
  else
    report_fatal_error("Binary format not supported");

  return MAI;
}

static MCStreamer *
createMRISC32MCStreamer(const Triple &T, MCContext &Ctx,
                    std::unique_ptr<MCAsmBackend> &&MAB,
                    std::unique_ptr<MCObjectWriter> &&OW,
                    std::unique_ptr<MCCodeEmitter> &&Emitter) {
  return createELFStreamer(Ctx, std::move(MAB), std::move(OW),
                           std::move(Emitter));
}

static MCStreamer *createMRISC32AsmStreamer(
    MCContext &Ctx,
    std::unique_ptr<formatted_raw_ostream> OS,
    std::unique_ptr<MCInstPrinter> InstPrint,
    std::unique_ptr<MCCodeEmitter> MCE,
    std::unique_ptr<MCAsmBackend> MAB) {

  // Notice we pass the 'OS' and 'InstPrint' here now
  auto *S = createAsmStreamer(Ctx, std::move(OS), std::move(InstPrint),
                          std::move(MCE), std::move(MAB));
  if (!S) llvm::errs() << "ERROR: createAsmStreamer returned NULL!\n";
  return S;
}

static MCInstPrinter *createMRISC32MCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new MRISC32InstPrinter(MAI, MII, MRI);
  return nullptr;
}

static MCTargetStreamer *createMRISC32AsmTargetStreamer(
    MCStreamer &S, formatted_raw_ostream &OS, MCInstPrinter *InstPrint) {
  return new MRISC32TargetStreamer(S);
}

namespace {

class MRISC32MCInstrAnalysis : public MCInstrAnalysis {
public:
  explicit MRISC32MCInstrAnalysis(const MCInstrInfo *Info)
      : MCInstrAnalysis(Info) {}

  bool evaluateBranch(const MCInst &Inst, uint64_t Addr, uint64_t Size,
                      uint64_t &Target) const override {
    // The target is the 3rd operand of cond inst and the 1st of uncond inst.
    int32_t Imm;

    Imm = 0; // remove this line later
    /***if (isConditionalBranch(Inst)) {
      if (Inst.getOpcode() == ::JCOND)
        Imm = (short)Inst.getOperand(0).getImm();
      else
        Imm = (short)Inst.getOperand(2).getImm();
    } else if (isUnconditionalBranch(Inst)) {
      if (Inst.getOpcode() == BPF::JMP)
        Imm = (short)Inst.getOperand(0).getImm();
      else
        Imm = (int)Inst.getOperand(0).getImm();
    } else
      return false;
    ***/
    Target = Addr + Size + Imm * Size;
    return true;
  }
};

} // end anonymous namespace

static MCInstrAnalysis *createMRISC32InstrAnalysis(const MCInstrInfo *Info) {
  return new MRISC32MCInstrAnalysis(Info);
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMRISC32TargetMC() {
  Target &TheTarget = getTheMRISC32Target();
  
  // Register the MC asm info.
  //RegisterMCAsmInfo<> X(*T);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheTarget, createMRISC32MCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheTarget, createMRISC32MCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheTarget,
                                            createMRISC32MCSubtargetInfo);
  // Register the MCAsmInfo
  TargetRegistry::RegisterMCAsmInfo(TheTarget, createMRISC32MCAsmInfo);

  // Register the object streamer
  //TargetRegistry::RegisterELFStreamer(*TheTarget, createMRISC32MCStreamer);

  // LOGGING TO CONSOLE
  llvm::errs() << "MRISC32: Registering Streamers for target: " << TheTarget.getName() << "\n";

  TargetRegistry::RegisterAsmStreamer(TheTarget, createMRISC32AsmStreamer);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(TheTarget, createMRISC32MCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheTarget, createMRISC32AsmTargetStreamer);

  // Register the MC instruction analyzer.
  //TargetRegistry::RegisterMCInstrAnalysis(*TheTarget, createMRISC32InstrAnalysis);

  // Register the MC code emitter
  TargetRegistry::RegisterMCCodeEmitter(TheTarget, createMRISC32MCCodeEmitter);
  //TargetRegistry::RegisterMCCodeEmitter(getTheMRISC32beTarget(),
  //                                     createMRISC32beMCCodeEmitter);

  // Register the ASM Backend
  TargetRegistry::RegisterMCAsmBackend(TheTarget, createMRISC32AsmBackend);
  //TargetRegistry::RegisterMCAsmBackend(getTheMRISC32beTarget(),
  //                                     createMRISC32beAsmBackend);

  /**if (sys::IsLittleEndianHost) {
    TargetRegistry::RegisterMCCodeEmitter(getTheMRISC32Target(),
                                          createMRISC32MCCodeEmitter);
    TargetRegistry::RegisterMCAsmBackend(getTheMRISC32Target(),
                                         createMRISC32AsmBackend);
  } else {
    TargetRegistry::RegisterMCCodeEmitter(getTheMRISC32Target(),
                                          createMRISC32beMCCodeEmitter);
    TargetRegistry::RegisterMCAsmBackend(getTheMRISC32Target(),
                                         createMRISC32beAsmBackend);
  }**/
}
