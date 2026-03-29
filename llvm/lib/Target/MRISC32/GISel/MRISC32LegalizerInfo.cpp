#include "MRISC32LegalizerInfo.h"
#include "MRISC32Subtarget.h"

#include "llvm/CodeGen/GlobalISel/LegalizerHelper.h"

using namespace llvm;

MRISC32LegalizerInfo::MRISC32LegalizerInfo(const MRISC32Subtarget &ST) :
    LegalizerInfo() 
    {
        getLegacyLegalizerInfo().computeTables();

        getActionDefinitionsBuilder(TargetOpcode::G_CONSTANT).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_ADD).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_SUB).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_MUL).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_SDIV).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_SREM).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_AND).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_OR).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_XOR).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_STORE).legalFor({{LLT::scalar(32), LLT::pointer(0, 32)}});
        getActionDefinitionsBuilder(TargetOpcode::G_LOAD).legalFor({{LLT::scalar(32), LLT::pointer(0, 32)}});
        getActionDefinitionsBuilder(TargetOpcode::G_FRAME_INDEX).legalFor({LLT::pointer(0, 32)});
        getActionDefinitionsBuilder({TargetOpcode::G_LOAD, TargetOpcode::G_STORE}).legalForTypesWithMemDesc({
        {LLT::scalar(32), LLT::pointer(0, 32), LLT::scalar(32), 4}, // 32-bit load/store
        {LLT::scalar(32), LLT::pointer(0, 32), LLT::scalar(16), 2}, // 16-bit load/store
        {LLT::scalar(32), LLT::pointer(0, 32), LLT::scalar(8),  1}  // 8-bit load/store
        });
        
        // Handle G_ADD with scalar 64 using custom legalization
        getActionDefinitionsBuilder(TargetOpcode::G_ADD).customFor({LLT::scalar(64)});
    }

bool MRISC32LegalizerInfo::legalizeCustom(LegalizerHelper &Helper, MachineInstr &MI, 
                                            LostDebugLocObserver &LocObserver) const 
{
    MachineIRBuilder &MIRBuilder = Helper.MIRBuilder;
    MachineRegisterInfo &MRI = *MIRBuilder.getMRI();
    GISelChangeObserver &Observer = Helper.Observer;
    switch (MI.getOpcode()) {
        case TargetOpcode::G_ADD:
        return legalizeAdd(MI, MRI, MIRBuilder, Observer);
    }
    llvm_unreachable("expected switch to return");
}

bool MRISC32LegalizerInfo::legalizeAdd(MachineInstr &MI, MachineRegisterInfo &MRI, 
                    MachineIRBuilder &MIRBuilder, GISelChangeObserver &Observer) const 
{
    Register Op1 = MI.getOperand(1).getReg();
    Register Op2 = MI.getOperand(2).getReg();

    LLT scalar32 = LLT::scalar(32);
    LLT scalar1  = LLT::scalar(1);

    auto unmergeOp1 = MIRBuilder.buildUnmerge(scalar32, Op1);
    auto unmergeOp2 = MIRBuilder.buildUnmerge(scalar32, Op2);

    Register lowBitsOp1 = unmergeOp1.getReg(0);
    Register highBitsOp1 = unmergeOp1.getReg(1);

    Register lowBitsOp2 = unmergeOp2.getReg(0);
    Register highBitsOp2 = unmergeOp2.getReg(1);

    Register lowBitsResult = MRI.createVirtualRegister(&MRISC32::GPRRegClass);
    Register highBitsResult = MRI.createVirtualRegister(&MRISC32::GPRRegClass);
    Register carry = MRI.createGenericVirtualRegister(scalar1);
    Register carry32 = MRI.createGenericVirtualRegister(scalar32);

    MIRBuilder.buildAdd(lowBitsResult, lowBitsOp1, lowBitsOp2);

    // carry = (lowBitsResult < low1BitsOp1)
    // NOTE: ICMP_ULT is not yet legalized by the MRISC32 backend
    MIRBuilder.buildICmp(CmpInst::ICMP_ULT, carry, lowBitsResult, lowBitsOp1);

    // extend carry to 32 bits
    MIRBuilder.buildZExt(carry32, carry);

    MIRBuilder.buildAdd(highBitsResult, highBitsOp1, highBitsOp2);
    MIRBuilder.buildAdd(highBitsResult, highBitsResult, carry32);

    // combine into a 64-bit result
    Register ResultReg = MI.getOperand(0).getReg();
    MIRBuilder.buildMergeValues(ResultReg, {lowBitsResult, highBitsResult});

    MI.eraseFromParent();
    return true;
}
