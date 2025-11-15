//===----------------------------------------------------===//
// This is the entry point for MRISC32 target
//===----------------------------------------------------===//

include "llvm/Target/Target.td"

include "MRISC32RegisterInfo.td"
include "MRISC32InstrInfo.td"
include "GISel/MRISC32RegisterBanks.td"
//include "MRISC32Subtarget.td"
//include "MRISC32Sched.td"


def MRISC32InstrInfo : InstrInfo;

def MRISC32 : Target {
    let InstructionSet = MRISC32InstrInfo;
    //let GlobalISel = 1;
}