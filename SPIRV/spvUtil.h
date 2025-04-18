#pragma once
#ifndef spvUtil_H
#define spvUtil_H

#include "spirv.hpp11"

namespace spv {
__inline uint32_t operator&(uint32_t value, spv::MemoryAccessMask mask) { return value & (unsigned)mask; }

__inline bool operator==(uint32_t word, spv::FPEncoding encoding) { return word == (unsigned)encoding; }
__inline bool operator!=(uint32_t word, spv::FPEncoding encoding) { return !(word == encoding); }

__inline bool operator==(uint32_t word, spv::Decoration decoration) { return word == (unsigned)decoration; }
__inline bool operator!=(uint32_t word, spv::Decoration decoration) { return !(word == decoration); }

__inline bool operator==(uint32_t word, spv::Op op) { return word == (unsigned)op; }
__inline bool operator!=(uint32_t word, spv::Op op) { return !(word == op); }

__inline bool operator==(uint32_t word, spv::StorageClass storage) { return word == (unsigned)storage; }
__inline bool operator!=(uint32_t word, spv::StorageClass storage) { return !(word == storage); }

__inline bool anySet(spv::MemoryAccessMask value, spv::MemoryAccessMask mask)
{
    return (value & mask) != spv::MemoryAccessMask::MaskNone;
}

__inline bool anySet(spv::ImageOperandsMask value, spv::ImageOperandsMask mask)
{
    return (value & mask) != spv::ImageOperandsMask::MaskNone;
}

__inline bool anySet(spv::MemorySemanticsMask value, spv::MemorySemanticsMask mask)
{
    return (value & mask) != spv::MemorySemanticsMask::MaskNone;
}

__inline void addMask(uint32_t& word, spv::TensorAddressingOperandsMask mask) { word |= (unsigned)mask; }

__inline void addMask(spv::CooperativeMatrixOperandsMask& word, spv::CooperativeMatrixOperandsMask mask)
{
    word = word | mask;
}
}

#endif // spvUtil_H
