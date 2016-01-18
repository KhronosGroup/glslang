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
#include <deque>
#include <unordered_map>
#include <unordered_set>

using spv::Block;
using spv::Id;
using BlockSet = std::unordered_set<Id>;
using IdToBool = std::unordered_map<Id, bool>;

namespace {
// True if any of prerequisites have not yet been visited.  May add new,
// zero-initialized, values to visited, but doesn't modify any existing values.
bool delay(const BlockSet& prereqs, IdToBool& visited) {
  return std::any_of(prereqs.begin(), prereqs.end(),
                     [&visited](Id b) { return !visited[b]; });
}
}

void spv::inReadableOrder(Block* root, std::function<void(Block*)> callback) {
  // Prerequisites for a merge block; must be completed prior to visiting the
  // merge block.
  std::unordered_map<Id, BlockSet> prereqs;
  IdToBool visited;             // Whether a block has already been visited.
  std::deque<Block*> worklist;  // DFS worklist
  worklist.push_back(root);
  while (!worklist.empty()) {
    Block* current = worklist.front();
    worklist.pop_front();
    // Nodes may be pushed repeadetly (before they're first visited) if they
    // have multiple predecessors.  Skip the already-visited ones.
    if (visited[current->getId()]) continue;
    if (delay(prereqs[current->getId()], visited)) {
      // Not every prerequisite has been visited -- push it off for later.
      worklist.push_back(current);
      continue;
    }
    callback(current);
    visited[current->getId()] = true;
    if (auto merge = current->getMergeInstruction()) {
      Id mergeId = merge->getIdOperand(0);
      auto& mergePrereqs = prereqs[mergeId];
      // Delay visiting merge blocks until all branches are visited.
      for (const auto succ : current->getSuccessors())
        if (succ->getId() != mergeId) mergePrereqs.insert(succ->getId());
    }
    for (auto succ : current->getSuccessors()) {
      if (!visited[succ->getId()]) worklist.push_back(succ);
    }
  }
}
