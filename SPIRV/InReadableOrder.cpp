// The SPIR-V spec requires code blocks to appear in an order satisfying the
// dominator-tree direction (ie, dominator before the dominated).  This is,
// actually, easy to achieve: any pre-order CFG traversal algorithm will do it.
// Because such algorithms visit a block only after traversing some path to it
// from the root, they necessarily visit the block's idom first.
//
// But not every graph-traversal algorithm outputs blocks in an order that
// appears logical to human readers.  The problem is that unrelated branches may
// be interspersed with each other, and merge blocks may come before some of the
// branches being merged.
//
// A good, human-readable order of blocks may be achieved by performing
// depth-first search but delaying merge nodes until after all their branches
// have been visited.  This is implemented below by the inReadableOrder()
// function.

#include "spvIR.h"

#include <algorithm>
#include <cassert>
#include <deque>
#include <unordered_map>

using spv::Block;
using spv::Id;

namespace {
// Traverses CFG in a readable order, invoking a pre-set callback on each block.
// Use by calling visit() on the root block.
class ReadableOrderTraverser {
 public:
  explicit ReadableOrderTraverser(std::function<void(Block*)> callback)
      : callback_(callback) {}

  // Visits the block if it hasn't been visited already and isn't currently
  // being delayed.  Invokes callback(block), then descends into its successors.
  // Delays merge-block processing until all the branches have been completed.
  void visit(Block* block) {
    assert(block);
    if (visited_[block] || delayed_[block]) return;
    callback_(block);
    visited_[block] = true;
    Block* mergeBlock = nullptr;
    auto mergeInst = block->getMergeInstruction();
    if (mergeInst) {
      Id mergeId = mergeInst->getIdOperand(0);
      mergeBlock =
          block->getParent().getParent().getInstruction(mergeId)->getBlock();
      delayed_[mergeBlock] = true;
    }
    for (const auto succ : block->getSuccessors())
      if (succ != mergeBlock) visit(succ);
    if (mergeBlock) {
      delayed_[mergeBlock] = false;
      visit(mergeBlock);
    }
  }

 private:
  std::function<void(Block*)> callback_;
  // Whether a block has already been visited or is being delayed.
  std::unordered_map<Block*, bool> visited_, delayed_;
};
}

void spv::inReadableOrder(Block* root, std::function<void(Block*)> callback) {
  ReadableOrderTraverser(callback).visit(root);
}
