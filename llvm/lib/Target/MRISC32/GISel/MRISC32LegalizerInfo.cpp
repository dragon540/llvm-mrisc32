#include "MRISC32LegalizerInfo.h"
#include "MRISC32Subtarget.h"

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
        // Add this to your LegalizerInfo constructor
    }
