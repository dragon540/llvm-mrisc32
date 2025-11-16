#include "MRISC32InstrInfo.h"
#include "MRISC32MCInstLower.h"
#include "MCTargetDesc/MRISC32InstPrinter.h"
//#include "TargetInfo/MRISC32TargetInfo.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace
{
class MRISC32AsmPrinter : public AsmPrinter {
public:
    static char ID;

    explicit MRISC32AsmPrinter(TargetMachine &TM,
                            std::unique_ptr<MCStreamer> Streamer)
        : AsmPrinter(TM, std::move(Streamer), ID) {}

    StringRef getPassName() const override { return "MRISC32 Assembly Printer"; }; 

    void emitInstruction(const MachineInstr *MI) override;

    void printInst(const MCInst *MI, uint64_t Address,
                   StringRef Annot, const MCSubtargetInfo &STI,
                   raw_ostream &O) override;

    void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O) override;
};
} // namespace

void MRISC32AsmPrinter::emitInstruction(const MachineInstr *MI)  {
    
}

void MRISC32AsmPrinter::printInst(const MCInst *MI, uint64_t Address,
                                  StringRef Annot, const MCSubtargetInfo &STI,
                                  raw_ostream &O)
{
    
}

void MRISC32AsmPrinter::printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O) {

}