

#include "MRISC32CallLowering.h"
#include "MRISC32ISelLowering.h"
#include "MRISC32InstrInfo.h"
#include "MRISC32Subtarget.h"
#include "MRISC32TargetMachine.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/TargetCallingConv.h"

using namespace llvm;

MRISC32CallLowering::MRISC32CallLowering(const MRISC32TargetLowering &TLI)
    : CallLowering(&TLI) {}

bool MRISC32CallLowering::lowerReturn(MachineIRBuilder &MIRBuilder, const Value *Val,
                   ArrayRef<Register> VRegs, FunctionLoweringInfo &FLI,
                   Register SwiftErrorVReg) const {
        
        // generate instructions to pack result into appropriate registers
        if (!RetVal)
        return true; // void return

        // Return value in R0
        MIRBuilder.buildCopy(XYZ::R0, VRegs[0]);
        MIRBuilder.buildInstr(MRISC32::RET);
        return true;
}

bool MRISC32CallLowering::canLowerReturn(MachineFunction &MF, CallingConv::ID CallConv,
                      SmallVectorImpl<BaseArgInfo> &Outs,
                      bool IsVarArg) const {
            return true;
}

bool MRISC32CallLowering::lowerFormalArguments(MachineIRBuilder &MIRBuilder, const Function &F,
                    ArrayRef<ArrayRef<Register>> VRegs,
                    FunctionLoweringInfo &FLI) const {
        
        // generate instructions to unpack formal arguments from some abi defined registers
        MachineFunction &MF = MIRBuilder.getMF();
        MachineRegisterInfo &MRI = MF.getRegInfo();
        const auto &DL = F.getDataLayout();
        auto &TLI = *getTLI<M68kTargetLowering>();

        unsigned int i=0;
        for(auto &Arg : F.args()) {
                ArgInfo OrigArg{VRegs[i], Arg, i};
                setArgFlags(OrigArg, i + AttributeList::FirstArgIndex, DL, F);
                splitToValueTypes(OrigArg, SplitArgs, DL, F.getCallingConv());
                ++i;
        }

                // Copy from physical registers to virtual ones (the function’s args)
        for (unsigned i = 0; i < ArgLocs.size(); ++i) {
                CCValAssign &VA = ArgLocs[i];
                assert(VA.isRegLoc() && "Only register args supported for now!");
                Register ArgReg = VRegs[i][0];
                MIRBuilder.buildCopy(ArgReg, Register(VA.getLocReg()));
        }

        return true;
}

bool MRISC32CallLowering::lowerCall(MachineIRBuilder &MIRBuilder,
                    CallLoweringInfo &Info) const {

        // generate instructions to put arguments into appropriate registers
        // call to callee
        // instructions to unpack the result from appropraite registers

        return false;
}