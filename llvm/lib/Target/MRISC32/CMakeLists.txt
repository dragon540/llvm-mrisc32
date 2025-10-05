add_llvm_component_group(MRISC32)

set(LLVM_TARGET_DEFINITIONS MRISC32.td)

tablegen(LLVM MRISC32GenRegisterInfo.inc       -gen-register-info)
tablegen(LLVM MRISC32GenInstrInfo.inc          -gen-instr-info)
#tablegen(LLVM MRISC32GenSubtargetInfo.inc     -gen-subtarget)
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
        MRISC32CallLowering.cpp

        LINK_COMPONENTS
        AsmPrinter
        CodeGen
        Core
        MC
        Support
        Target
        GlobalISel

        ADD_TO_COMPONENT
        MRISC32
)
