// Table description to define different MRISC32 instruction formats

class MRISC32Inst<dag outs, dag ins, string asmString> : Instruction {
    dag OutOperandList = outs;
    dag InOperandList = ins;
    field bits<32> Inst;
    let Namespace = "MRISC32";
    let AsmString = asmString;
    let Size = 4;
}

def imm15 : Operand<i32> { let EncoderMethod = "getImmOpValue"; }
def imm18 : Operand<i32> { let EncoderMethod = "getImmOpValue"; }
def imm21 : Operand<i32> { let EncoderMethod = "getImmOpValue"; }

class FmtA<bits<10> opcode, dag outs, dag ins, string asmString> 
     : MRISC32Inst<outs, ins, asmString> 
{
    bits<5> regA;
    bits<5> regB;
    bits<1> V = {0b0};
    bits<2> T = {0b00};

    let Inst{31-28} = 0b0000;
    let Inst{27-26} = opcode{9-8};
    let Inst{25-21} = regA;
    let Inst{20-16} = regB;
    let Inst{15}    = V;
    let Inst{14-9}  = opcode{7-2};
    let Inst{8-7}   = T;
    let Inst{6-2}   = 0b00000;
    let Inst{1-0}   = opcode{1-0};
}

class FmtB<bits<9> opcode, dag outs, dag ins, string asmString> 
     : MRISC32Inst<outs, ins, asmString> 
{
    bits<5> regA;
    bits<5> regB;
    bits<5> regC;
    bits<2> V = {0b00};
    bits<2> T = {0b00};

    let Inst{31-28} = 0b0000;
    let Inst{27-26} = opcode{8-7};
    let Inst{25-21} = regA;
    let Inst{20-16} = regB;
    let Inst{15-14} = V;
    let Inst{13-9}  = regC;
    let Inst{8-7}   = T;
    let Inst{6-0}   = opcode{6-0};
}

class FmtC<bits<6> opcode, dag outs, dag ins, string asmString> 
     : MRISC32Inst<outs, ins, asmString> 
{
    bits<5>  regA;
    bits<5>  regB;
    bits<1>  V = {0b0};
    bits<15> imm;

    let Inst{31-26} = opcode;
    let Inst{25-21} = regA;
    let Inst{20-16} = regB;
    let Inst{15}    = V;
    let Inst{14-0}  = imm;
}

class FmtD<bits<3> opcode, dag outs, dag ins, string asmString> 
     : MRISC32Inst<outs, ins, asmString> 
{
    bits<5>  regA;
    bits<21> imm;

    let Inst{31-29} = 0b110;
    let Inst{28-26} = opcode;
    let Inst{25-21} = regA;
    let Inst{20-0}  = imm;
}

class FmtE<bits<3> opcode, dag outs, dag ins, string asmString> 
     : MRISC32Inst<outs, ins, asmString> 
{
    bits<5>  regA;
    bits<18> imm;

    let Inst{31-26} = 0b110111;
    let Inst{25-21} = regA;
    let Inst{20-18} = opcode;
    let Inst{17-0}  = imm;
}

