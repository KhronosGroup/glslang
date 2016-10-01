//
//Copyright (C) 2016 LunarG, Inc.
//
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
//FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
//COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//POSSIBILITY OF SUCH DAMAGE.
//

#include "../Include/Common.h"
#include "iomapper.h"
#include "LiveTraverser.h"
#include "localintermediate.h"

#include "gl_types.h"

#include <unordered_set>
#include <unordered_map>

//
// Map IO bindings.
//
// High-level algorithm for one stage:
//
// 1. Traverse all code (live+dead) to find the explicitly provided bindings.
//
// 2. Traverse (just) the live code to determine which non-provided bindings
//    require auto-numbering.  We do not auto-number dead ones.
//
// 3. Traverse all the code to apply the bindings:
//    a. explicitly given bindings are offset according to their type
//    b. implicit live bindings are auto-numbered into the holes, using
//       any open binding slot.
//    c. implicit dead bindings are left un-bound.
//

   
namespace glslang {

// Map of IDs to bindings
typedef std::unordered_map<unsigned int, int> TBindingMap;
typedef std::unordered_set<int> TUsedBindings;


// This traverses the AST to determine which bindings are used, and which are implicit
// (for subsequent auto-numbering)
class TBindingTraverser : public TLiveTraverser {
public:
    TBindingTraverser(const TIntermediate& i, TBindingMap& bindingMap, TUsedBindings& usedBindings,
                      bool traverseDeadCode = false) :
        TLiveTraverser(i, traverseDeadCode, true, true, false),
        bindingMap(bindingMap),
        usedBindings(usedBindings)
    { }

protected:
    virtual void visitSymbol(TIntermSymbol* base) {
        if (base->getQualifier().storage == EvqUniform)
            addUniform(*base);
    }

    // Return the right binding base given the variable type.
    int getBindingBase(const TType& type) {
        if (type.getBasicType() == EbtSampler) {
            const TSampler& sampler = type.getSampler();
            if (sampler.isPureSampler())
                return intermediate.getShiftSamplerBinding();
            if (sampler.isTexture())
                return intermediate.getShiftTextureBinding();
        }

        if (type.getQualifier().isUniformOrBuffer())
            return intermediate.getShiftUboBinding();

        return -1;  // not a type with a binding
    }

    // Mark a given base symbol ID as being bound to 'binding'
    void markBinding(const TIntermSymbol& base, int binding) {
        bindingMap[base.getId()] = binding;

        if (binding >= 0) {
            // const TType& type = base.getType();
            const unsigned int size = 1; // type.isArray() ? type.getCumulativeArraySize() : 1;

            for (unsigned int offset=0; offset<size; ++offset)
                usedBindings.insert(binding + offset);
        }
    }

    // Mark the bindings that are given explicitly, and set ones that need
    // implicit bindings to -1 for a subsequent pass.  (Can't happen in this
    // pass because explicit bindings in dead code reserve the location).
    virtual void addUniform(TIntermSymbol& base)
    {
        // Skip ones we've already seen.
        if (bindingMap.find(base.getId()) != bindingMap.end())
            return;

        const TType& type = base.getType();
        const int bindingBase = getBindingBase(type);

        // Return if it's not a type we bind
        if (bindingBase == -1)
            return;

        if (type.getQualifier().hasBinding()) {
            // It has a binding: keep that one.
            markBinding(base, type.getQualifier().layoutBinding + bindingBase);
        } else if (!traverseAll) {
            // Mark it as something we need to dynamically create a binding for,
            // only if we're walking just the live code.  We don't auto-number
            // in dead code.
            markBinding(base, -1);
        }
    }

    TBindingMap&         bindingMap;
    TUsedBindings&       usedBindings;
};


// This traverses the AST and applies binding maps it's given.
class TIoMappingTraverser : public TBindingTraverser {
public:
    TIoMappingTraverser(TIntermediate& i, TBindingMap& bindingMap, TUsedBindings& usedBindings,
                        bool traverseDeadCode) :
        TBindingTraverser(i, bindingMap, usedBindings, traverseDeadCode)
    { }

protected:
    void addUniform(TIntermSymbol& base) override
    {
        // Skip things we don't intend to bind.
        if (bindingMap.find(base.getId()) == bindingMap.end())
            return;

        const int existingBinding = bindingMap[base.getId()];

        // Apply existing binding, if we were given one or already made one up.
        if (existingBinding != -1) {
            base.getWritableType().getQualifier().layoutBinding = existingBinding;
            return;
        }

        if (intermediate.getAutoMapBindings()) {
            // Otherwise, find a free spot for it.
            const int freeBinding = getFreeBinding(base.getType(), getBindingBase(base.getType()));

            markBinding(base, freeBinding);
            base.getWritableType().getQualifier().layoutBinding = freeBinding;
        }
    }

    // Search for N free consecutive binding slots in [base, base+required).
    // E.g, if we want to reserve consecutive bindings for flattened arrays.
    bool hasNFreeSlots(int base, int required) {
        for (int binding = base; binding < (base + required); ++binding)
            if (usedBindings.find(binding) != usedBindings.end())
                return false;
        
        return true;
    }

    // Find a free binding spot 
    int getFreeBinding(const TType&, int nextBinding) {
        while (!hasNFreeSlots(nextBinding, 1))
            ++nextBinding;

        return nextBinding;
    }
};

// Map I/O variables to provided offsets, and make bindings for
// unbound but live variables.
//
// Returns false if the input is too malformed to do this.
bool TIoMapper::addStage(EShLanguage, TIntermediate& intermediate)
{
    // Trivial return if there is nothing to do.
    if (intermediate.getShiftSamplerBinding() == 0 &&
        intermediate.getShiftTextureBinding() == 0 &&
        intermediate.getShiftUboBinding() == 0 &&
        intermediate.getAutoMapBindings() == false)
        return true;

    if (intermediate.getNumEntryPoints() != 1 || intermediate.isRecursive())
        return false;

    TIntermNode* root = intermediate.getTreeRoot();
    if (root == nullptr)
        return false;

    // The lifetime of this data spans several passes.
    TBindingMap   bindingMap;
    TUsedBindings usedBindings;

    TBindingTraverser it_binding_all(intermediate, bindingMap, usedBindings, true);
    TBindingTraverser it_binding_live(intermediate, bindingMap, usedBindings, false);
    TIoMappingTraverser it_iomap(intermediate, bindingMap, usedBindings, true);

    // Traverse all (live+dead) code to find explicit bindings, so we can avoid those.
    root->traverse(&it_binding_all);

    // Traverse just live code to find things that need implicit bindings.
    it_binding_live.pushFunction(intermediate.getEntryPointMangledName().c_str());

    while (! it_binding_live.functions.empty()) {
        TIntermNode* function = it_binding_live.functions.back();
        it_binding_live.functions.pop_back();
        function->traverse(&it_binding_live);
    }

    // Bind everything that needs a binding and doesn't have one.
    root->traverse(&it_iomap);

    return true;
}

} // end namespace glslang
