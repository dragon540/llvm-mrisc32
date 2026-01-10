//
// Created by shobhit on 1/8/26.
//

#ifndef LLVM_LIB_TARGET_MRISC32_MRISC32TARGETTRANSFORMINFO_H
#define LLVM_LIB_TARGET_MRISC32_MRISC32TARGETTRANSFORMINFO_H

#include "MRISC32Subtarget.h"
#include "MRISC32TargetMachine.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"

namespace llvm {
class MRISC32TTIImpl : public BasicTTIImplBase<MRISC32TTIImpl> {
  using BaseT = BasicTTIImplBase<MRISC32TTIImpl>;
  using TTI = TargetTransformInfo;

  friend BaseT;

  // Supply the minimum required APIs.
  const MRISC32Subtarget &ST;
  const MRISC32TargetLowering &TLI;

  const MRISC32Subtarget *getST() const { return &ST; }
  const MRISC32TargetLowering *getTLI() const { return &TLI; }

public:
  explicit MRISC32TTIImpl(const MRISC32TargetMachine *TM, const Function &F)
      : BaseT(TM, F.getDataLayout()), ST(*TM->getSubtargetImpl(F)),
        TLI(*ST.getTargetLowering()) {}

  /// \name Vector TTI Implementations
  /// @{
  //unsigned getLoadVectorFactor(unsigned VF, unsigned LoadSize,
  //                             unsigned ChainSizeInBytes,
  //                             VectorType *VecTy) const;
  /// @}

  //InstructionCost getIntrinsicInstrCost(const IntrinsicCostAttributes &ICA,
  //                                      TTI::TargetCostKind CostKind);
};
}
#endif // LLVM_LIB_TARGET_MRISC32_MRISC32TARGETTRANSFORMINFO_H
