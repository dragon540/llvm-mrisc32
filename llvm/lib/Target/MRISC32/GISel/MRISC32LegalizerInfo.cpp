#include "MRISC32LegalizerInfo.h"
#include "MRISC32Subtarget.h"

using namespace llvm;

MRISC32LegalizerInfo::MRISC32LegalizerInfo(const MRISC32Subtarget &ST) :
    LegalizerInfo() 
    {
        getLegacyLegalizerInfo().computeTables();

        getActionDefinitionsBuilder(TargetOpcode::G_CONSTANT).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_ADD).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_STORE).legalFor({{LLT::scalar(32), LLT::pointer(0, 32)}});
    }
