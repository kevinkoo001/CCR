//===- lib/MC/MCNullStreamer.cpp - Dummy Streamer Implementation ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/StringRef.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"

using namespace llvm;

namespace {

  class MCNullStreamer : public MCStreamer {
  public:
    MCNullStreamer(MCContext &Context) : MCStreamer(Context) {}

    /// @name MCStreamer Interface
    /// @{

    bool hasRawTextSupport() const override { return true; }
    void EmitRawTextImpl(StringRef String) override {}

    bool EmitSymbolAttribute(MCSymbol *Symbol,
                             MCSymbolAttr Attribute) override {
      return true;
    }

    void EmitCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                          unsigned ByteAlignment) override {}
    void EmitZerofill(MCSection *Section, MCSymbol *Symbol = nullptr,
                      uint64_t Size = 0, unsigned ByteAlignment = 0,
                      SMLoc Loc = SMLoc()) override {}
    void EmitGPRel32Value(const MCExpr *Value) override {}
    void BeginCOFFSymbolDef(const MCSymbol *Symbol) override {}
    void EmitCOFFSymbolStorageClass(int StorageClass) override {}
    void EmitCOFFSymbolType(int Type) override {}
    void EndCOFFSymbolDef() override {}
	
	void setObjTmpName(std::string tmpFileName) override {} // Koo
  };

}

MCStreamer *llvm::createNullStreamer(MCContext &Context) {
  return new MCNullStreamer(Context);
}
