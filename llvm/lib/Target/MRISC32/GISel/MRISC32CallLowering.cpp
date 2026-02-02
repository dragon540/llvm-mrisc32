

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
#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "MCTargetDesc/MRISC32MCTargetDesc.h"

using namespace llvm;

MRISC32CallLowering::MRISC32CallLowering(const MRISC32TargetLowering &TLI)
    : CallLowering(&TLI) {}

bool MRISC32CallLowering::lowerReturn(MachineIRBuilder &MIRBuilder, const Value *Val,
                   ArrayRef<Register> VRegs, FunctionLoweringInfo &FLI,
                   Register SwiftErrorVReg) const {
    
    // If there is a return value (VRegs is not empty), move it to R0
    if (!VRegs.empty()) {
        MIRBuilder.buildCopy(MRISC32::r0, VRegs[0]);
    }

    MIRBuilder.buildInstr(MRISC32::RET);
    return true;
}

bool MRISC32CallLowering::canLowerReturn(MachineFunction &MF, CallingConv::ID CallConv,
                      SmallVectorImpl<BaseArgInfo> &Outs,
                      bool IsVarArg) const {
            return true;
}

bool MRISC32CallLowering::lowerFormalArguments(
    MachineIRBuilder &MIRBuilder, const Function &F,
    ArrayRef<ArrayRef<Register>> VRegs, FunctionLoweringInfo &FLI) const {

  // Define calling convention (which physical registers hold args)
  static const MCPhysReg ArgRegs[] = {MRISC32::r0, MRISC32::r1, MRISC32::r2, MRISC32::r3};

  // Map each incoming VReg to a physical register
  for (unsigned i = 0; i < VRegs.size(); ++i) {
    if (i >= 4) return false; // Basic support for first 4 args only for now

    Register VReg = VRegs[i][0];
    MCPhysReg PReg = ArgRegs[i];

    // Add the physical register to the function live-ins
    MIRBuilder.getMBB().addLiveIn(PReg);

    // Create the definition for the virtual register
    MIRBuilder.buildCopy(VReg, Register(PReg));
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