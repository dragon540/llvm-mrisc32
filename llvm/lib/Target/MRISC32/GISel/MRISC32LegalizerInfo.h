#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"

namespace llvm {

class MRISC32Subtarget;

class MRISC32LegalizerInfo : public LegalizerInfo {
public:
  MRISC32LegalizerInfo(const MRISC32Subtarget &ST);
};
} // end namespace llvm