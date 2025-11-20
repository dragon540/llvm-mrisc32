add_llvm_component_library(LLVMMRISC32Info
  MRISC32TargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  TextAPI

  ADD_TO_COMPONENT
  MRISC32
  )