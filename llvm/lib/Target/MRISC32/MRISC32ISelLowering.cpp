//
// Created by shobhit on 9/1/25.
//

#include "MRISC32ISelLowering.h"
#include "MRISC32.h"
#include "MRISC32Subtarget.h"
#include "MRISC32TargetMachine.h"

using namespace llvm;

MRISC32TargetLowering::MRISC32TargetLowering(const TargetMachine &TM,
                                     const MRISC32Subtarget &STI)
    : TargetLowering(TM), Subtarget(STI) {
  // For now, assume i32 is legal and maps to GPRs.
  addRegisterClass(MVT::i32, &MRISC32::GPRRegClass);

  // Tell LLVM that load/store/add/sub are legal in GlobalISel.
  // (You’ll extend this later.)
  setOperationAction(ISD::ADD, MVT::i32, Legal);
  //setOperationAction(ISD::SUB, MVT::i32, Legal);
}
