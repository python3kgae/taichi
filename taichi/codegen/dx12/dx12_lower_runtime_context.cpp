

#include "dx12_llvm_passes.h"

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Instructions.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Transforms/Utils/ModuleUtils.h"

#include "taichi/program/compile_config.h"
#include "taichi/runtime/llvm/llvm_context.h"

using namespace llvm;
using namespace taichi::lang::directx12;

#define DEBUG_TYPE "dxil-taichi-runtime-context-lower"

namespace {

class TaichiRuntimeContextLower : public ModulePass {
 public:
  bool runOnModule(Module &M) override;

  TaichiRuntimeContextLower() : ModulePass(ID) {
    initializeTaichiRuntimeContextLowerPass(*PassRegistry::getPassRegistry());
  }

  static char ID;  // Pass identification.
 private:
};
char TaichiRuntimeContextLower::ID = 0;

class TaichiRuntimeContextLowerImpl {
 public:
  TaichiRuntimeContextLowerImpl() {
  }
  bool run(Module &M) {
    // TODO: lower taichi RuntimeContext into DXIL resources.
    return true;
  }
};

}  // end anonymous namespace

INITIALIZE_PASS(TaichiRuntimeContextLower,
                DEBUG_TYPE,
                "Lower taichi RuntimeContext",
                false,
                false)

bool TaichiRuntimeContextLower::runOnModule(Module &M) {
  TaichiRuntimeContextLowerImpl Impl;
  return Impl.run(M);
}

llvm::ModulePass *llvm::createTaichiRuntimeContextLowerPass() {
  return new TaichiRuntimeContextLower();
}

namespace llvm {
TaichiRuntimeContextLowerPass::TaichiRuntimeContextLowerPass() {
}
PreservedAnalyses TaichiRuntimeContextLowerPass::run(
    Module &M,
    ModuleAnalysisManager &AM) {
  TaichiRuntimeContextLowerImpl Impl;
  if (Impl.run(M))
    return PreservedAnalyses::none();
  return PreservedAnalyses::all();
}
}  // namespace llvm