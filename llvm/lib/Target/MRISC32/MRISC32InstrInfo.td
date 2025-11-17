//===---------------------------------------------===//
// This file describes the MRISC32 instructions
//===---------------------------------------------===//

class MRISC32Inst<dag outs, dag ins, string asmString> : Instruction {
    dag OutOperandList = outs;
    dag InOperandList = ins;
    //let Inst{31-0} = (outs GPR:$dst), (ins GPR:$src1, GPR:$src2);
    let Namespace = "MRISC32";
    let AsmString = asmString;
}

def ADD : MRISC32Inst<(outs GPR:$dst), 
                      (ins GPR:$src1, GPR:$src2), 
                      "ADD $dst, $src1, $src2">;
def : Pat<(add GPR:$src1, GPR:$src2),
          (ADD GPR:$src1, GPR:$src2)>;
def : GINodeEquiv<G_ADD, add>;

def SUB : MRISC32Inst<(outs GPR:$dst), 
                      (ins GPR:$src1, GPR:$src2), 
                      "SUB $dst, $src1, $src2">;

def MUL : MRISC32Inst<(outs GPR:$dst), 
                      (ins GPR:$src1, GPR:$src2), 
                      "MUL $dst, $src1, $src2">;

def DIV : MRISC32Inst<(outs GPR:$dst), 
                      (ins GPR:$src1, GPR:$src2), 
                      "DIV $dst, $src1, $src2">;

// Return the minimum value of two signed integer operands.
def MIN : MRISC32Inst<(outs GPR:$dst), 
                      (ins GPR:$src1, GPR:$src2), 
                      "MIN $dst, $src1, $src2">;

// Return the maximum value of two signed integer operands.
def MAX : MRISC32Inst<(outs GPR:$dst), 
                      (ins GPR:$src1, GPR:$src2), 
                      "MAX $dst, $src1, $src2">;

def LDri : MRISC32Inst<(outs GPR:$dst), 
                      (ins GPR:$src1, GPR:$src2), 
                      "LDri $dst, $src1, $src2">;
def STri : MRISC32Inst<(outs GPR:$dst), 
                      (ins GPR:$src1, GPR:$src2), 
                      "STri $dst, $src1, $src2">;
