add_llvm_component_group(MRISC32)

set(LLVM_TARGET_DEFINITIONS MRISC32.td)

#tablegen(LLVM MRISC32GenAsmWriter.inc          -gen-asm-writer)
tablegen(LLVM MRISC32GenCallingConv.inc        -gen-callingconv)
tablegen(LLVM MRISC32GenRegisterInfo.inc       -gen-register-info)
tablegen(LLVM MRISC32GenInstrInfo.inc          -gen-instr-info)
tablegen(LLVM MRISC32GenGlobalISel.inc         -gen-global-isel)
tablegen(LLVM MRISC32GenRegisterBank.inc       -gen-register-bank)
#tablegen(LLVM MRISC32GenSubtargetInfo.inc      -gen-subtarget)
#tablegen(LLVM MRISC32GenMCCodeEmitter.inc     -gen-emitter)

add_public_tablegen_target(MRISC32CommonTableGen)

add_llvm_target(MRISC32CodeGen
        MRISC32AsmPrinter.cpp
        MRISC32InstrInfo.cpp
        MRISC32RegisterInfo.cpp
        MRISC32FrameLowering.cpp
        MRISC32ISelLowering.cpp
        MRISC32Subtarget.cpp
        MRISC32TargetMachine.cpp
        GISel/MRISC32CallLowering.cpp
        GISel/MRISC32LegalizerInfo.cpp
        GISel/MRISC32RegisterBankInfo.cpp
        GISel/MRISC32InstructionSelector.cpp

        LINK_COMPONENTS
        AsmPrinter
        MRISC32Desc
        CodeGen
        Core
        MC
        Support
        Target
        GlobalISel

        ADD_TO_COMPONENT
        MRISC32
)
