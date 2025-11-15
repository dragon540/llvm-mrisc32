

#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/ValueTypes.h"

namespace llvm {

class MRISC32TargetLowering;
class MachineInstrBuilder;

class MRISC32CallLowering : public CallLowering {

public:
    MRISC32CallLowering(const MRISC32TargetLowering &TLI);

    bool lowerReturn(MachineIRBuilder &MIRBuilder, const Value *Val,
                   ArrayRef<Register> VRegs, FunctionLoweringInfo &FLI,
                   Register SwiftErrorVReg) const override;

    bool canLowerReturn(MachineFunction &MF, CallingConv::ID CallConv,
                      SmallVectorImpl<BaseArgInfo> &Outs,
                      bool IsVarArg) const override;

    bool lowerFormalArguments(MachineIRBuilder &MIRBuilder, const Function &F,
                            ArrayRef<ArrayRef<Register>> VRegs,
                            FunctionLoweringInfo &FLI) const override;

    bool lowerCall(MachineIRBuilder &MIRBuilder,
                    CallLoweringInfo &Info) const override;
};

}