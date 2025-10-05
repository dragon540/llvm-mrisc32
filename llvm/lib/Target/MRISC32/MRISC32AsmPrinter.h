#include "llvm/CodeGen/AsmPrinter.h"

class MRISC32AsmPrinter : public AsmPrinter {
public:
    static char ID;

    explicit RISCVAsmPrinter(TargetMachine &TM,
                            std::unique_ptr<MCStreamer> Streamer)
        : AsmPrinter(TM, std::move(Streamer), ID) {}

    StringRef getPassName() const override { return "MRISC32 Assembly Printer"; }

    void emitInstruction(const MachineInstr *MI) override;
}