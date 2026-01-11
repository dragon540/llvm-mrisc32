//
// Created by shobhit on 1/10/26.
//

#include "MRISC32TargetStreamer.h"

using namespace llvm;

MRISC32TargetStreamer::MRISC32TargetStreamer(MCStreamer &S)
    : MCTargetStreamer(S) {}
