#include "llvm/CodeGen/AsmPrinter.h"

namespace llvm 
{
class MRISC32AsmPrinter : public AsmPrinter {
public:
    static char ID;

    explicit RISCVAsmPrinter(TargetMachine &TM,
                            std::unique_ptr<MCStreamer> Streamer)
        : AsmPrinter(TM, std::move(Streamer), ID) {}

    StringRef getPassName() const override { return "MRISC32 Assembly Printer"}; 

    void emitInstruction(const MachineInstr *MI) override;

    void printInst(const MCInst *MI, uint64_t Address,
                   StringRef Annot, const MCSubtargetInfo &STI,
                   raw_ostream &O) override;

    void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O) override;
};
}
