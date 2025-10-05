//===----------------------------------------------------===//
// This is the entry point for MRISC32 target
//===----------------------------------------------------===//

include "llvm/Target/Target.td"

include "MRISC32RegisterInfo.td"
include "MRISC32InstrInfo.td"

def MRISC32InstrInfo : InstrInfo;

def MRISC32 : Target {
    let InstructionSet = MRISC32InstrInfo;
}