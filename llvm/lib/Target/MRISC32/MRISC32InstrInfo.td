//===---------------------------------------------===//
// This file describes the MRISC32 instructions
//===---------------------------------------------===//

class MRISC32Inst<dag outs, dag ins, string asmString> : Instruction {
    dag OutOperandList = outs;
    dag InOperandList = ins;
    field bits<32> Inst;
    //let Inst{31-0} = (outs GPR:$dst), (ins GPR:$src1, GPR:$src2);
    let Inst{31-0} = 0b00000000000000000000000000000000;
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
let isPseudo = 1, isCodeGenOnly = 1 in
def ADJCALLSTACKUP   : MRISC32Inst<(outs), (ins), "adjstackup">;
let isPseudo = 1, isCodeGenOnly = 1 in
def ADJCALLSTACKDOWN : MRISC32Inst<(outs), (ins), "adjstackdown">;

def CALL : MRISC32Inst<(outs GPR:$dst), (ins GPR:$src1, GPR:$src2), "call target">;

let isReturn = 1, isTerminator = 1, isBarrier = 1 in
def RET : MRISC32Inst<(outs), (ins), "ret">;


// 1. Define the LI instruction using your base class
def LI : MRISC32Inst<(outs GPR:$dst), (ins i32imm:$imm),
                     "LI $dst, $imm"> {
  // For now
  let Inst{31-26} = 0b000001; 
}

// Define the SelectionDAG pattern (The "old" bridge)
def : Pat<(imm:$imm), (LI (i32 imm:$imm))>;

// Define the GlobalISel Equivalence (The "new" bridge)
// This links the generic G_CONSTANT to the concept of 'imm'
def : GINodeEquiv<G_CONSTANT, imm>;
