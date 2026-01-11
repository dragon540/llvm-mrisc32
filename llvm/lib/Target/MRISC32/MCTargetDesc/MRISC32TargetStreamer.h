//
// Created by shobhit on 1/10/26.
//

#ifndef LLVM_LIB_MRISC32_MCTARGETDESC_MRISC32TARGETSTREAMER_H
#define LLVM_LIB_MRISC32_MCTARGETDESC_MRISC32TARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {

class MRISC32TargetStreamer : public MCTargetStreamer {
public:
  MRISC32TargetStreamer(MCStreamer &S);

  // Example: If your ISA needs a special directive at the start of functions
  virtual void emitTargetAttributes() {}
};

} // end namespace llvm

#endif // LLVM_LIB_MRISC32_MCTARGETDESC_MRISC32TARGETSTREAMER_H
