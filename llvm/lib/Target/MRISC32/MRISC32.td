//===----------------------------------------------------===//
// This is the entry point for MRISC32 target
//===----------------------------------------------------===//

include "llvm/Target/Target.td"

include "MRISC32RegisterInfo.td"

include "MRISC32InstrInfo.td"

def MRISC32InstrInfo : InstrInfo;

def MRISC32RegInfo : RegisterInfo;

def MRISC32 : target {
    let InstructionSet = MRISC32InstrInfo;
}