//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//Copyright (C) 2016 Google, Inc.
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

// Implement the TParseContextBase class.

#include "ParseHelper.h"

extern int yyparse(glslang::TParseContext*);

namespace glslang {

// Select the best matching function for 'call' from 'candidateList'.
//
// Assumptions
//
// There is no exact match, so a selection algorithm needs to run. That is, the
// language-specific handler should check for exact match first, to
// decide what to do, before calling this selector.
//
// Input
//
//  * list of candidate signatures to select from
//  * the call
//  * a predicate function convertible(from, to) that says whether or not type
//    'from' can implicitly convert to type 'to' (it includes the case of what
//    the calling language would consider a matching type with no conversion
//    needed)
//  * a predicate function better(from1, from2, to1, to2) that says whether or
//    not a conversion from <-> to2 is considered better than a conversion
//    from <-> to1 (both in and out directions need testing, as declared by the
//    formal parameter)
//
// Output
//
//  * best matching candidate (or none, if no viable candidates found)
//  * whether there was a tie for the best match (ambiguous overload selection,
//    caller's choice for how to report)
//
const TFunction* TParseContextBase::selectFunction(
    const TVector<const TFunction*> candidateList,
    const TFunction& call,
    std::function<bool(const TType& from, const TType& to)> convertible,
    std::function<bool(const TType& from, const TType& to1, const TType& to2)> better,
    /* output */ bool& tie)
{
// 
// Operation
// 
// 1. Prune the input list of candidates down to a list of viable candidates,
// where each viable candidate has
// 
//  * at least as many parameters as there are calling arguments, with any
//    remaining parameters being optional or having default values
//  * each parameter is true under convertible(A, B), where A is the calling
//    type for in and B is the formal type, and in addition, for out B is the
//    calling type and A is the formal type
// 
// 2. If there are no viable candidates, return with no match.
// 
// 3. If there is only one viable candidate, it is the best match.
//
// 4. If there are multiple viable candidates, select the first viable candidate
// as the incumbent. Compare the incumbent to the next viable candidate, and if
// that candidate is better (bullets below), make it the incumbent. Repeat, with
// a linear walk through the viable candidate list. The final incumbent will be
// returned as the best match. A viable candidate is better than the incumbent if
// 
//  * it has a function argument with a better(...) conversion than the incumbent,
//    for all directions needed by in and out
//  * the incumbent has no argument with a better(...) conversion then the
//    candidate, for either in or out (as needed)
//
// 5. Check for ambiguity by comparing the best match against all other viable
// candidates. If any other viable candidate has a function argument with a
// better(...) conversion than the best candidate (for either in or out
// directions), return that there was a tie for best.
//

    tie = false;

    // 1. prune to viable...
    TVector<const TFunction*> viableCandidates;
    for (auto it = candidateList.begin(); it != candidateList.end(); ++it) {
        const TFunction& candidate = *(*it);

        // to even be a potential match, number of arguments has to match
        if (call.getParamCount() != candidate.getParamCount())
            continue;

        // see if arguments are convertible
        bool viable = true;
        for (int param = 0; param < candidate.getParamCount(); ++param) {
            if (candidate[param].type->getQualifier().isParamInput()) {
                if (! convertible(*call[param].type, *candidate[param].type)) {
                    viable = false;
                    break;
                }
            }
            if (candidate[param].type->getQualifier().isParamOutput()) {
                if (! convertible(*candidate[param].type, *call[param].type)) {
                    viable = false;
                    break;
                }
            }
        }

        if (viable)
            viableCandidates.push_back(&candidate);
    }

    // 2. none viable...
    if (viableCandidates.size() == 0)
        return nullptr;

    // 3. only one viable...
    if (viableCandidates.size() == 1)
        return viableCandidates.front();

    // 4. find best...
    auto betterParam = [&call, &better](const TFunction& can1, const TFunction& can2){
        // is call -> can2 better than call -> can1 for any parameter
        bool hasBetterParam = false;
        for (int param = 0; param < call.getParamCount(); ++param) {
            if (better(*call[param].type, *can1[param].type, *can2[param].type)) {
                hasBetterParam = true;
                break;
            }
        }
        return hasBetterParam;
    };

    const TFunction* incumbent = viableCandidates.front();
    for (auto it = viableCandidates.begin() + 1; it != viableCandidates.end(); ++it) {
        const TFunction& candidate = *(*it);
        if (betterParam(*incumbent, candidate) && ! betterParam(candidate, *incumbent))
            incumbent = &candidate;
    }

    // 5. ambiguity...
    for (auto it = viableCandidates.begin(); it != viableCandidates.end(); ++it) {
        if (incumbent == *it)
            continue;
        const TFunction& candidate = *(*it);
        if (betterParam(*incumbent, candidate))
            tie = true;
    }

    return incumbent;
}

} // end namespace glslang
