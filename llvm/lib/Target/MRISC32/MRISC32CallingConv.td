

def CC_MRISC32_Common : CallingConv<[
    CCIfType<[i32], CCAssignToReg<R1, R2, R3, R4, 
                                  R5, R6, R7, R8>>
]>;

def RetCC_MRISC32 : CallingConv<[
    CCIfType<[i32], CCAssignToReg<R1, R2, R3, R4, 
                                  R5, R6, R7, R8>>
]>;

def CSR : CalleeSavedRegs<add(R16, R17, R18, R18, R19, R20,
                              R21, R22, R23, R24, R25, R26)>;