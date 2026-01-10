//
// Created by shobhit on 1/8/26.
//

#include "MRISC32TargetTransformInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
//#include "llvm/IR/IntrinsicsH2B.h"

using namespace llvm;

#define DEBUG_TYPE "mrisc32tti"

/***unsigned MRISC32TTIImpl::getLoadVectorFactor(unsigned VF, unsigned LoadSize,
                                           unsigned ChainSizeInBytes,
                                           VectorType *VecTy) const {
  // We support <2 x i16> loads.
  unsigned ElemSize = VecTy->getScalarSizeInBits();
  if (ElemSize != 16)
    return 0;

  return std::min(VF, 2u);
}

InstructionCost
H2BLBTTIImpl::getIntrinsicInstrCost(const IntrinsicCostAttributes &ICA,
                                    TTI::TargetCostKind CostKind) {
  // Extending the input values of a widening multiply is more expensive than a
  // regular instruction.
  // For code size, though, this is the same.
  if (CostKind != TargetTransformInfo::TCK_CodeSize &&
      ICA.getID() == Intrinsic::h2blb_widening_smul)
    return TargetTransformInfo::TCC_Expensive;

  return BaseT::getIntrinsicInstrCost(ICA, CostKind);
}***/
