//===---------------------------------------------===//
// This file describes the MRISC32 instructions
//===---------------------------------------------===//

def ADD : Instr<(outs GPR:$dst), (ins GPR:$src1, GPR:$src2),
                "ADD $dst $src1 $src2", []>;
