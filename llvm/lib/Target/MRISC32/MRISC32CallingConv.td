
def CC_MRISC32_Common : CallingConv<[
    CCIfType<[i32], CCAssignToReg<[r1, r2, r3, r4, 
                                  r5, r6, r7, r8]>>
]>;

def RetCC_MRISC32 : CallingConv<[
    CCIfType<[i32], CCAssignToReg<[r1]>>
]>;

def CSR : CalleeSavedRegs<(add r16, r17, r18, r19, r20, r21, 
                               r22, r23, r24, r25, r26, r27,
                               r28, r29, r30, r31)>;