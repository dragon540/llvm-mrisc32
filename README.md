# LLVM for MRISC32 ISA

This is a fork of llvm for supporting the MRISC32 ISA.

## Build process

```$ cd llvm-mrisc32```

```$ cmake -S llvm -B build -G Ninja -DLLVM_ENABLE_PROJECTS="llvm;clang;lld" -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=MRISC32 -DCMAKE_BUILD_TYPE=Release -DLLVM_PARALLEL_COMPILE_JOBS=3 -DLLVM_PARALLEL_LINK_JOBS=2```

```$ cmake --build build```
