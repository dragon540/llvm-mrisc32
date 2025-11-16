

#include "MRISC32RegisterBankInfo.h"
#include "MRISC32InstrInfo.h" // For the register classes
#include "MRISC32Subtarget.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterBank.h"
#include "llvm/CodeGen/RegisterBankInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_TARGET_REGBANK_IMPL
#include "MRISC32GenRegisterBank.inc"

using namespace llvm;

namespace llvm {
namespace MRISC32 {
const MRISC32RegisterBankInfo::PartialMapping PartMappings[] = {
    {0, 32, GPRBRegBank}
};

enum PartialMappingIdx {
  PMI_GPR32 = 0
};

const MRISC32RegisterBankInfo::ValueMapping ValMappings[] = {
    {nullptr, 0},

    {&PartMappings[PMI_GPR32], 1},
    {&PartMappings[PMI_GPR32], 1},
    {&PartMappings[PMI_GPR32], 1}
};

enum ValueMappingIdx {
  InvalidIdx = 0,
  GPRB32Idx = 1
};
}
}

MRISC32RegisterBankInfo::MRISC32RegisterBankInfo(const TargetRegisterInfo &TRI) 
    : MRISC32RegisterBankInfo() {}

const InstructionMapping &MRISC32RegisterBankInfo::getInstrMapping(const MachineInstr &MI) const {
    const unsigned Opc = MI.getOpcode();
    if(!isPreISelGenericOpcode(Opc) || Opc == TargetOpcode::G_PHI) {
        const InstructionMapping &Mapping = getInstrMappingImpl(MI);
        if(Mapping.isValid()) {
            return Mapping;
        }
    }

    const MachineFunction &MF = *MI.getParent()->getParent();
    const MachineRegisterInfo &MRI = MF.getRegInfo();

    unsigned NumOperands = MI.getNumOperands();

    const ValueMapping *GPR32ValueMapping =
        &ValMappings[GPRB32Idx];

    switch(Opc) {
        case TargetOpcode::G_ADD:
        case TargetOpcode::G_SUB:
        {
            LLT Ty = MRI.getType(MI.getOperand(0).getReg());
            //TypeSize Size = Ty.getSizeInBits();

            const ValueMapping *Mapping = GPR32ValueMapping;
            return getInstructionMapping(DefaultMappingID, 1, Mapping, NumOperands);
        }

        default:
        {
            SmallVector<const ValueMapping *, 4> OpdsMapping(NumOperands);

            // By default map all scalars to GPR.
            for (unsigned Idx = 0; Idx < NumOperands; ++Idx) {
                auto &MO = MI.getOperand(Idx);
                if (!MO.isReg() || !MO.getReg())
                    continue;
                LLT Ty = MRI.getType(MO.getReg());
                if (!Ty.isValid())
                    continue;

                OpdsMapping[Idx] =
                    Ty.getSizeInBits() == 16 ? GPR16ValueMapping : GPR32ValueMapping;
            }
            return getInstructionMapping(DefaultMappingID, /*Cost=*/1,
                                        getOperandsMapping(OpdsMapping), NumOperands);
        }
        llvm_unreachable("Switch should have covered everything");
    }
}

const RegisterBank &
        MRISC32RegisterBankInfo::getRegBankFromRegClass(const TargetRegisterClass &RC,
                                                    LLT Ty) const {
        switch (RC.getID()) {
        default:
            llvm_unreachable("Register class not supported");
        //case MRISC32::GPR16RegClassID:
        case MRISC32::GPRRegClassID:
        //case MRISC32::GPR16spRegClassID:
        //case MRISC32::OnlySPRegClassID:
            return getRegBank(MRISC32::GPRRegBankID);
        }
};

