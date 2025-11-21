//===-- MRISC32TargetInfo.cpp - MRISC32 Target Implementation -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MRISC32TargetInfo.h"
#include "llvm/MC/TargetRegistry.h" // For RegisterTarget.
#include "llvm/Support/Compiler.h"  // For LLVM_EXTERNAL_VISIBILITY.
#include "llvm/TextAPI/Target.h"    // For Target class.

using namespace llvm;

Target &llvm::getTheMRISC32Target() {
  static Target TheMRISC32Target;
  return TheMRISC32Target;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMRISC32TargetInfo() {
  RegisterTarget<Triple::mrisc32, /*HasJIT=*/false> X(
      getTheMRISC32Target(), /*Name=*/"mrisc32",
      /*Desc=*/"32-bit MRISC",
      /*BackendName=*/"MRISC32");
}