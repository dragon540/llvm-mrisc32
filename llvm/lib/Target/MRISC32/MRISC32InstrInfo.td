//===---------------------------------------------===//
// This file describes the MRISC32 instructions
//===---------------------------------------------===//

include "MRISC32InstrFormats.td"


/***
* ADD instruction
* Opcode: 22
* Format B and C
***/
def ADD_B : FmtB<22, (outs GPRDst:$regA), (ins GPR:$regB, GPR:$regC), "add $regA, $regB, $regC">;
def ADD_C : FmtC<22, (outs GPRDst:$regA), (ins GPR:$regB, imm15:$imm), "add $regA, $regB, #$imm">;

def : Pat<(add GPR:$regB, GPR:$regC),
          (ADD_B GPR:$regB, GPR:$regC)>;
def : Pat<(add GPR:$regB, imm:$imm),
          (ADD_C GPR:$regB, imm:$imm)>;

def : GINodeEquiv<G_ADD, add>;

/***
* SUB instruction
* Opcode: 23
* Format B and C
***/
def SUB_B : FmtB<23, (outs GPRDst:$regA), (ins GPR:$regC, GPR:$regB), "sub $regA, $regC, $regB">;
def SUB_C : FmtC<23, (outs GPRDst:$regA), (ins imm15:$imm, GPR:$regB), "sub $regA, #$imm, $regB">;

def : Pat<(sub GPR:$regC, GPR:$regB),
          (SUB_B GPR:$regC, GPR:$regB)>;
def : Pat<(sub imm:$imm, GPR:$regC),
          (SUB_C imm:$imm, GPR:$regC)>;

def : GINodeEquiv<G_SUB, sub>;


/***
* MUL instruction
* Opcode: 39
* Format B and C
***/
def MUL_B : FmtB<39, (outs GPRDst:$regA), (ins GPR:$regB, GPR:$regC), "mul $regA, $regB, $regC">;
def MUL_C : FmtC<39, (outs GPRDst:$regA), (ins GPR:$regB, imm15:$imm), "mul $regA, $regB, #$imm">;

def : Pat<(mul GPR:$regB, GPR:$regC),
          (MUL_B GPR:$regB, GPR:$regC)>;
def : Pat<(mul GPR:$regB, imm:$imm),
          (MUL_C GPR:$regB, imm:$imm)>;

def : GINodeEquiv<G_MUL, mul>;

/***
* DIV instruction
* Opcode: 40
* Format B and C
***/
def DIV_B : FmtB<40, (outs GPRDst:$regA), (ins GPR:$regB, GPR:$regC), "div $regA, $regB, $regC">;
def DIV_C : FmtC<40, (outs GPRDst:$regA), (ins GPR:$regB, imm15:$imm), "div $regA, $regB, #$imm">;

def : Pat<(sdiv GPR:$regB, GPR:$regC),
          (DIV_B GPR:$regB, GPR:$regC)>;
def : Pat<(sdiv GPR:$regB, imm:$imm),
          (DIV_C GPR:$regB, imm:$imm)>;

def : GINodeEquiv<G_SDIV, sdiv>;


/**
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

***/
let isPseudo = 1, isCodeGenOnly = 1 in
def ADJCALLSTACKUP   : MRISC32Inst<(outs), (ins), "adjstackup">;
let isPseudo = 1, isCodeGenOnly = 1 in
def ADJCALLSTACKDOWN : MRISC32Inst<(outs), (ins), "adjstackdown">;

def CALL : MRISC32Inst<(outs GPRDst:$dst), (ins GPR:$src1, GPR:$src2), "call target">;

let isReturn = 1, isTerminator = 1, isBarrier = 1 in
def RET : MRISC32Inst<(outs), (ins), "ret">;

def LI : FmtD<6, (outs GPRDst:$regA), (ins imm21:$imm),
                     "ldi $regA, #$imm">;

// Define the SelectionDAG pattern (The "old" bridge)
def : Pat<(imm:$imm), (LI (i32 imm:$imm))>;

def STW_B : FmtB<6, (outs), (ins GPR:$regA, GPR:$regB, GPR:$regC), "stw $regA, [$regB, $regC]">;
def STW_C : FmtC<6, (outs), (ins GPR:$regA, GPR:$regB, imm15:$imm), "stw $regA, [$regB, #$imm]">;

def : Pat<(store i32:$regA, (add GPR:$regB, GPR:$regC)),
          (STW_B GPR:$regA, GPR:$regB, GPR:$regC)>;
def : Pat<(store i32:$regA, (add GPR:$regB, imm:$imm)),
          (STW_C GPR:$regA, GPR:$regB, imm15:$imm)>;

def : GINodeEquiv<G_STORE, st>;

// Define the GlobalISel Equivalence (The "new" bridge)
// This links the generic G_CONSTANT to the concept of 'imm'
def : GINodeEquiv<G_CONSTANT, imm>;

def LDW_B : FmtB<10, (outs GPRDst:$regA), (ins GPR:$regB, GPR:$regC), "ldw $regA, [$regB, $regC]">;
def LDW_C : FmtC<10, (outs GPRDst:$regA), (ins GPR:$regB, imm15:$imm), "ldw $regA, [$regB, #$imm]">;

