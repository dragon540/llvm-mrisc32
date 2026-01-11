//
// Created by shobhit on 1/12/26.
//
#include "MCTargetDesc/MRISC32MCTargetDesc.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
//#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
//#include "llvm/MC/MCObjectTargetWriter.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

namespace {
class MRISC32AsmBackend : public MCAsmBackend {
  Triple TheTriple;

public:
  MRISC32AsmBackend(const Triple &TT)
      : MCAsmBackend(llvm::endianness::little), TheTriple(TT) {}

  // Pure virtual: must be implemented
  unsigned getNumFixupKinds() const override { return 0; }

  // Pure virtual: must be implemented
  bool writeNopData(raw_ostream &OS, uint64_t Count, const MCSubtargetInfo *STI) const override {
    // For a 32-bit RISC, usually a 4-byte NOP.
    // Return true if you handled it, false otherwise.
    if (Count == 0) return true;
    if (Count % 4 != 0) return false;
    for (uint64_t i = 0; i < Count; i += 4)
        support::endian::write<uint32_t>(OS, 0x00000013, llvm::endianness::little); // Example NOP
    return true;
  }

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved,
                  const MCSubtargetInfo *STI) const override;

  std::unique_ptr<MCObjectTargetWriter> createObjectTargetWriter() const override {
    // Passes the OS format to your ELF writer creator
    return createMRISC32ELFObjectWriter(TheTriple.isOSBinFormatMachO());
  }
};

// Logic for applying fixups (relocations) to the instruction encoding
void MRISC32AsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                                  const MCValue &Target,
                                  MutableArrayRef<char> Data, uint64_t Value,
                                  bool IsResolved,
                                  const MCSubtargetInfo *STI) const {
  if (!Value)
    return;

  MCFixupKindInfo Info = getFixupKindInfo(Fixup.getKind());
  // Shift the value into position.
  Value <<= Info.TargetOffset;

  unsigned NumBytes = (Info.TargetSize + 7) / 8;
  uint32_t Offset = Fixup.getOffset();
  assert(Offset + NumBytes <= Data.size() && "Invalid fixup offset!");

  for (unsigned i = 0; i != NumBytes; ++i) {
    Data[Offset + i] |= static_cast<uint8_t>((Value >> (i * 8)) & 0xff);
  }
}
} // end anonymous namespace

// Factory function called by TargetRegistry
MCAsmBackend *llvm::createMRISC32AsmBackend(const Target &T,
                                            const MCSubtargetInfo &STI,
                                            const MCRegisterInfo &MRI,
                                            const MCTargetOptions &Options) {
  return new MRISC32AsmBackend(STI.getTargetTriple());
}