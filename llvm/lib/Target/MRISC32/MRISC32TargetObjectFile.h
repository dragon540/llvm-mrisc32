//
// Created by shobhit on 1/8/26.
//

#ifndef LLVM_LIB_TARGET_MRISC32_MRISC32TARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_MRISC32_MRISC32TARGETOBJECTFILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {
/// This implementation is used for MRISC32 ELF targets (Linux in particular).
class MRISC32_ELFTargetObjectFile : public TargetLoweringObjectFileELF {
public:
  MRISC32_ELFTargetObjectFile();
};

}
#endif // LLVM_LIB_TARGET_MRISC32_MRISC32TARGETOBJECTFILE_H
