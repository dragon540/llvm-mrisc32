//===-- MRISC32TargetInfo.h - MRISC32 Target Implementation -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MRISC32_TARGETINFO_MRISC32TARGETINFO_H
#define LLVM_LIB_TARGET_MRISC32_TARGETINFO_MRISC32TARGETINFO_H

namespace llvm {
// Forward declaration.
class Target;

Target &getTheMRISC32Target();
} // namespace llvm.

#endif // LLVM_LIB_TARGET_MRISC32_TARGETINFO_MRISC32TARGETINFO_H