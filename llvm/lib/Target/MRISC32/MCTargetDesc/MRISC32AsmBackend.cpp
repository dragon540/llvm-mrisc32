//
// Created by shobhit on 1/12/26.
//
#include "MCTargetDesc/MRISC32MCTargetDesc.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

namespace {
class MRISC32AsmBackend : public MCAsmBackend {
  //bool IsElf;
  Triple TheTriple;

public:
  MRISC32AsmBackend(const Triple &TT)
      : MCAsmBackend(endianness::little), TheTriple(TT) {}

  // Pure virtual: must be implemented
  bool writeNopData(raw_ostream &OS, uint64_t Count, const MCSubtargetInfo *STI) const override {
    if(Count == 0) return true;
    if (Count % 4 == 0) 
    {
      for(uint64_t i = 0; i < Count; i+=4)
      {
        // Writing add r0, r0, 0 as no-op
        OS.write(static_cast<char>(0x00));
        OS.write(static_cast<char>(0x00));
        OS.write(static_cast<char>(0x00));
        OS.write(static_cast<char>(0x16));
      }
    }
    return false;
  }

  void applyFixup(const MCFragment &, const MCFixup &Fixup,
                  const MCValue &Target, uint8_t *Data, uint64_t Value,
                  bool IsResolved) override;

  std::unique_ptr<MCObjectTargetWriter> createObjectTargetWriter() const override {
    // Passes the OS format to your ELF writer creator
    return createMRISC32ELFObjectWriter(TheTriple.isOSBinFormatMachO());
  }
};

// Logic for applying fixups (relocations) to the instruction encoding
void MRISC32AsmBackend::applyFixup(const MCFragment &, const MCFixup &Fixup,
                  				   const MCValue &Target, uint8_t *Data, uint64_t Value,
                  				   bool IsResolved) {
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
  //return new MRISC32AsmBackend(true, STI.getTargetTriple());
  const Triple &TheTriple = STI.getTargetTriple();
  return new MRISC32AsmBackend(TheTriple);
}