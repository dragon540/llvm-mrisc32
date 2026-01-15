#include "MCTargetDesc/MRISC32MCTargetDesc.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {

class MRISC32ELFObjectWriter : public MCELFObjectTargetWriter {
public:
  MRISC32ELFObjectWriter(uint8_t OSABI)
      : MCELFObjectTargetWriter(/*Is64Bit=*/false,
                                OSABI,
                                ELF::EM_NONE,
                                /*HasRelocationAddend=*/true) {}

  ~MRISC32ELFObjectWriter() override = default;

protected:
  // This is the most important method for an ELF writer.
  // It maps an LLVM Fixup (like a jump) to an ELF Relocation ID.
  unsigned getRelocType(const MCFixup &Fixup, const MCValue &Target,
                        bool IsPCRel) const override;
};

} // end anonymous namespace

unsigned MRISC32ELFObjectWriter::getRelocType(const MCFixup &Fixup,
                                              const MCValue &Target,
                                              bool IsPCRel) const {
  // Translate the fixup kind into an ELF relocation type.
  // These constants are usually defined in llvm/BinaryFormat/ELF.h
  switch ((unsigned)Fixup.getKind()) {
  case FK_Data_4:
    return ELF::R_CKCORE_ADDR32; // Use your target's specific relocation constants
  //case FK_PCRel_4:
    //return ELF::R_CKCORE_PCREL32;
  default:
    llvm_unreachable("Invalid fixup kind!");
  }
}

// This matches the signature the linker was looking for in your previous error
std::unique_ptr<MCObjectTargetWriter>
llvm::createMRISC32ELFObjectWriter(uint8_t OSABI) {
  return std::make_unique<MRISC32ELFObjectWriter>(OSABI);
}