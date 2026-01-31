#include "MRISC32LegalizerInfo.h"
#include "MRISC32Subtarget.h"

using namespace llvm;

MRISC32LegalizerInfo::MRISC32LegalizerInfo(const MRISC32Subtarget &ST) :
    LegalizerInfo() {
        getLegacyLegalizerInfo().computeTables();
        // Allow constants, additions, and returns
        getActionDefinitionsBuilder(TargetOpcode::G_CONSTANT).legalFor({LLT::scalar(32)});
        getActionDefinitionsBuilder(TargetOpcode::G_ADD).legalFor({LLT::scalar(32)});
    }
