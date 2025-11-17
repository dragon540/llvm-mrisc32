//===----------------------------------------------------------------------===//
//
// This file provides MRISC32 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MRISC32_MCTARGETDESC_MRISC32MCTARGETDESC_H
#define LLVM_LIB_TARGET_MRISC32_MCTARGETDESC_MRISC32MCTARGETDESC_H

#include "llvm/Config/config.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;

MCCodeEmitter *createMRISC32MCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
MCCodeEmitter *createMRISC32beMCCodeEmitter(const MCInstrInfo &MCII,
                                        MCContext &Ctx);

MCAsmBackend *createMRISC32AsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                  const MCRegisterInfo &MRI,
                                  const MCTargetOptions &Options);
MCAsmBackend *createMRISC32beAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                    const MCRegisterInfo &MRI,
                                    const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter> createBPFELFObjectWriter(uint8_t OSABI);
} // namespace llvm

// Defines symbolic names for MRISC32 registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "MRISC32GenRegisterInfo.inc"

// Defines symbolic names for the MRISC32 instructions.
//
#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "MRISC32GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "MRISC32GenSubtargetInfo.inc"

#endif
