

#include "MRISC32RegisterBankInfo.h"
#include "MRISC32InstrInfo.h" // For the register classes
#include "MRISC32Subtarget.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterBank.h"
#include "llvm/CodeGen/RegisterBankInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_TARGET_REGBANK_IMPL
#include "MRISC32GenRegisterBank.inc"

using namespace llvm;
