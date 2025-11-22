//===-- MRISC32.h - Top-level interface for M68k representation ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the entry points for global functions defined in the
/// MRISC32 target library, as used by the LLVM JIT.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MRISC32_MRISC32_H
#define LLVM_LIB_TARGET_MRISC32_MRISC32_H

namespace llvm {

class FunctionPass;
class InstructionSelector;
class MRISC32RegisterBankInfo;
class MRISC32Subtarget;
class MRISC32TargetMachine;
class PassRegistry;

InstructionSelector *
createMRISC32InstructionSelector(const MRISC32TargetMachine &, const MRISC32Subtarget &,
                              const MRISC32RegisterBankInfo &);

void initializeMRISC32AsmPrinterPass(PassRegistry &);
//void initializeMRISC32DAGToDAGISelLegacyPass(PassRegistry &);
//void initializeMRISC32ExpandPseudoPass(PassRegistry &);
//void initializeMRISC32GlobalBaseRegPass(PassRegistry &);
//void initializeMRISC32CollapseMOVEMPass(PassRegistry &);

} // namespace llvm

#endif // LLVM_LIB_TARGET_MRISC32_MRISC32_H
