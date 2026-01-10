//
// Created by shobhit on 1/10/26.
//

#ifndef LLVM_LIB_TARGET_MRISC32_MCTARGETDESC_MRISC32MCASMINFO_H
#define LLVM_LIB_TARGET_MRISC32_MCTARGETDESC_MRISC32MCASMINFO_H
#include "llvm/MC/MCAsmInfoDarwin.h"
#include "llvm/MC/MCAsmInfoELF.h"
namespace llvm {

class Triple;

class MRISC32MCAsmInfoELF : public MCAsmInfoELF {
public:
  explicit MRISC32MCAsmInfoELF(const Triple &TT, const MCTargetOptions &Options);
};

class MRISC32MCAsmInfoDarwin : public MCAsmInfoDarwin {
public:
  explicit MRISC32MCAsmInfoDarwin(const Triple &TT,
                                const MCTargetOptions &Options);
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_MRISC32_MCTARGETDESC_MRISC32MCASMINFO_H
