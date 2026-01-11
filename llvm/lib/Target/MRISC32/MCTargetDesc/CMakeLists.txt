add_llvm_component_library(LLVMMRISC32Desc
  MRISC32MCTargetDesc.cpp
  MRISC32MCAsmInfo.cpp
  MRISC32TargetStreamer.cpp
  MRISC32AsmBackend.cpp
  MRISC32InstPrinter.cpp
  #MRISC32MCCodeEmitter.cpp
  #MRISC32ELFObjectWriter.cpp

  LINK_COMPONENTS
  MC
  MRISC32Info
  Support
  TargetParser

  ADD_TO_COMPONENT
  MRISC32
  )
