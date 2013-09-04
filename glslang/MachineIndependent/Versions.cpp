//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//Copyright (C) 2012-2013 LunarG, Inc.
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

//
// Help manage multiple profiles, versions, extensions etc.
//
// These don't return error codes, as the presumption is parsing
// will always continue as if the feature were present, and there
// is no error recovery needed to enable that.
//

#include "ParseHelper.h"

namespace glslang {

const char* StageName[EShLangCount] = {
    "vertex",
    "tessellation control",
    "tessellation evaluation",
    "geometry",
    "fragment",
    "compute"
};

const char* ProfileName[EProfileCount] = {
    "none",
    "core",
    "compatibility",
    "es"
};

//
// If only some profiles support a feature, use requireProfile() to specify
// which subset allows the feature.  If the current profile is not present,
// give an error message.
//
void TParseContext::requireProfile(TSourceLoc loc, EProfileMask profileMask, const char *featureDesc)
{
    if (((1 << profile) & profileMask) == 0)
        error(loc, "not supported with this profile:", featureDesc, ProfileName[profile]);
}

//
// If only some stages support a feature, use requireStage() to specify
// which subset allows the feature.  If the current stage is not present,
// give an error message.
//
void TParseContext::requireStage(TSourceLoc loc, EShLanguageMask languageMask, const char *featureDesc)
{
    if (((1 << language) & languageMask) == 0)
        error(loc, "not supported in this stage:", featureDesc, StageName[language]);
}

//
// Within a profile, if a feature requires a version level or extension, use
// ProfileRequires().  This only checks if the current profile matches
// the passed-in profile.
//

// one that takes multiple extensions
void TParseContext::profileRequires(TSourceLoc loc, EProfile callingProfile, int minVersion, int numExtensions, const char* extensions[], const char *featureDesc)
{
    if (profile == callingProfile) {
        bool okay = false;
        if (version >= minVersion)
            okay = true;
        for (int i = 0; i < numExtensions; ++i) {
            TBehavior behavior = extensionBehavior[extensions[i]];
            switch (behavior) {
            case EBhWarn:
                infoSink.info.message(EPrefixWarning, ("extension " + TString(extensions[i]) + " is being used for " + featureDesc).c_str(), loc);
                // fall through
            case EBhRequire:
            case EBhEnable:
                okay = true;
                break;
            default: break; // some compilers want this
            }
        }

        if (! okay)
            error(loc, "not supported for this version or the enabled extensions", featureDesc, "");
    }
}

// one that takes a single extension
void TParseContext::profileRequires(TSourceLoc loc, EProfile callingProfile, int minVersion, const char* extension, const char *featureDesc)
{
    profileRequires(loc, callingProfile, minVersion, extension ? 1 : 0, &extension, featureDesc);
}

//
// Within a profile, see if a feature is deprecated and error or warn based on whether
// a future compatibility context is being use.
//
void TParseContext::checkDeprecated(TSourceLoc loc, EProfile callingProfile, int depVersion, const char *featureDesc)
{
    if (profile == callingProfile) {
        if (version >= depVersion) {
            if (forwardCompatible)
                error(loc, "deprecated, may be removed in future release", featureDesc, "");
            else if (! (messages & EShMsgSuppressWarnings))
                infoSink.info.message(EPrefixWarning, (TString(featureDesc) + " deprecated in version " +
                                                       String(depVersion) + "; may be removed in future release").c_str(), loc);
        }
    }
}

//
// Within a profile, see if a feature has now been removed and if so, give an error.
// The version argument is the first version no longer having the feature.
//
void TParseContext::requireNotRemoved(TSourceLoc loc, EProfile callingProfile, int removedVersion, const char *featureDesc)
{
    if (profile == callingProfile) {
        if (version >= removedVersion) {
            const int maxSize = 60;
            char buf[maxSize];
            snprintf(buf, maxSize, "%s profile; removed in version %d", ProfileName[profile], removedVersion);
            error(loc, "no longer supported in", featureDesc, buf);
        }
    }
}

void TParseContext::fullIntegerCheck(TSourceLoc loc, const char* op)
{   
    profileRequires(loc, ENoProfile, 130, 0, op); 
    profileRequires(loc, EEsProfile, 300, 0, op);
}

void TParseContext::doubleCheck(TSourceLoc loc, const char* op)
{   
    requireProfile(loc, (EProfileMask)(ECoreProfileMask | ECompatibilityProfileMask), op);
    profileRequires(loc, ECoreProfile, 400, 0, op);
    profileRequires(loc, ECompatibilityProfile, 400, 0, op);
}

} // end namespace glslang
