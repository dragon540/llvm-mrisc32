# LLVM Backend for MRISC32 ISA

This is a fork of LLVM for supporting the MRISC32 ISA. 

This project uses LLVM's GlobalISel framework for instruction selection.

## 

## Build Steps

```
$ cd llvm-mrisc32
$ cmake -S llvm -B build -G Ninja -DLLVM_ENABLE_PROJECTS="llvm;clang;lld" -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=MRISC32 -DCMAKE_BUILD_TYPE=Release -DLLVM_PARALLEL_COMPILE_JOBS=3 -DLLVM_PARALLEL_LINK_JOBS=2
$ cmake --build build
```

## MRISC32 ISA Documentation

Official Project Page of the MRISC32 ISA: https://gitlab.com/mrisc32

Authoritative ISA: https://gitlab.com/mrisc32/mrisc32/-/releases/permalink/latest/downloads/mrisc32-instruction-set-manual.pdf
