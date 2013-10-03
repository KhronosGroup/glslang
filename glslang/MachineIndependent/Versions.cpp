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
// These don't return error codes, as the presumption is parsing will 
// always continue as if the tested feature were enabled, and thus there
// is no error recovery needed.
//

//
// HOW TO add a feature enabled by an extension.
//
// To add a new hypothetical "Feature F" to the front end, where an extension
// "XXX_extension_X" can be used to enable the feature, do the following.
// 
// 1) Understand that specific features are what are error-checked for, not
//    extensions:  A specific Feature F might be enabled by an extension, or a 
//    particular version in a particular profile, or a stage, or combinations, etc.
//    
//    The basic mechanism is to use the following to "declare" all the things that 
//    enable/disable Feature F, in a code path that implements Feature F:
//    
//        requireProfile()
//        profileRequires()
//        requireStage()
//        checkDeprecated()
//        requireNotRemoved()
//    
//    Typically, only the first two calls are needed.  They go into a code path that 
//    implements Feature F, and will log the proper error/warning messages.  Parsing 
//    will then always continue as if the tested feature was enabled.
//    
//    There is typically no if-testing or conditional parsing, just insertion of requirements.
// 
// 2) Add extension initialization to TParseContext::initializeExtensionBehavior(),
//    the first function below:
// 
//     extensionBehavior["XXX_extension_X"] = EBhDisable;
// 
// 3) Insert a profile check in the feature's path (unless all profiles support the feature,
//    for some version level).  That is, call requireProfile() to constrain the profiles, e.g.:
// 
//         // ... in a path specific to Feature F...
//         requireProfile(loc,
//                        ECoreProfile | ECompatibilityProfile,
//                        "Feature F");
// 
// 4) For each profile that supports the feature, insert version/extension checks:
// 
//    The mostly likely scenario is that Feature F can only be used with a
//    particular profile if XXX_extension_X is present or the version is
//    high enough that the core specification already incorporated it.
// 
//        // following the requireProfile() call...
//        profileRequires(loc, 
//                        ECoreProfile | ECompatibilityProfile,
//                        420, // 0 if no version incorporated the feature into the core spec.
//                        "XXX_extension_X", // can be a list of extensions that all add the feature
//                        "Feature F");
// 
//    This allows the feature if either A) one of the extensions is enabled or
//    B) the version is high enough.  If no version yet incorporates the feature
//    into core, pass in 0.
// 
//    This can be called multiple times, if different profiles support the
//    feature starting at different version numbers or with different 
//    extensions.
// 
//    This must be called for each profile allowed by the initial call to requireProfile().
// 
//    Profiles are all masks, which can be "or"-ed together.
// 
//        ENoProfile
//        ECoreProfile
//        ECompatibilityProfile
//        EEsProfile
// 
//    The ENoProfile profile is only for desktop, before profiles showed up in version 150;
//    All other #version with no profile default to either es or core, and so have profiles.
// 
//    You can select all but a particular profile using ~.  The following basically means "desktop":
// 
//        ~EEsProfile
//

#include "ParseHelper.h"

namespace glslang {

//
// Initialize all extensions, almost always to 'disable', as once their features
// are incorporated into a core version, their features are supported through allowing that
// core version, not through a pseudo-enablement of the extension.
//
void TParseContext::initializeExtensionBehavior()
{
    extensionBehavior["GL_ARB_texture_rectangle"] = EBhDisable;
    extensionBehavior["GL_3DL_array_objects"] = EBhDisable;
}

const char* ProfileName(EProfile profile)
{
    switch (profile) {
    case ENoProfile:             return "none";        
    case ECoreProfile:           return "core";
    case ECompatibilityProfile:  return "compatibility";
    case EEsProfile:             return "es";
    default:                     return "unknown profile";
    }
}

//
// When to use requireProfile():
//
//     If only some profiles support a feature.  However, if within a profile the feature 
//     is version or extension specific, follow this call with calls to profileRequires().
//
// Operation:  If the current profile is not one of the profileMask,
// give an error message.
//
void TParseContext::requireProfile(TSourceLoc loc, int profileMask, const char *featureDesc)
{
    if (! (profile & profileMask))
        error(loc, "not supported with this profile:", featureDesc, ProfileName(profile));
}

const char* StageName(EShLanguage stage) 
{
    switch(stage) {
    case EShLangVertex:         return "vertex";
    case EShLangTessControl:    return "tessellation control";
    case EShLangTessEvaluation: return "tessellation evaluation";
    case EShLangGeometry:       return "geometry";
    case EShLangFragment:       return "fragment";
    case EShLangCompute:        return "compute";
    default:                    return "unknown stage";
    }
}

//
// When to use profileRequires():
//
//     If a set of profiles have the same requirements for what version or extensions
//     are needed to support a feature.
//
//     It must be called for each profile that needs protection.  Use requireProfile() first
//     to reduce that set of profiles.
//
// Operation: Will issue warnings/errors based on the current profile, version, and extension
// behaviors.  It only checks extensions when the current profile is one of the profileMask.
//
// A minVersion of 0 means no version of the profileMask support this in core, 
// the extension must be present.
//

// entry point that takes multiple extensions
void TParseContext::profileRequires(TSourceLoc loc, int profileMask, int minVersion, int numExtensions, const char* extensions[], const char *featureDesc)
{
    if (profile & profileMask) {
        bool okay = false;
        if (minVersion > 0 && version >= minVersion)
            okay = true;
        for (int i = 0; i < numExtensions; ++i) {
            TExtensionBehavior behavior = extensionBehavior[extensions[i]];
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

// entry point for the above that takes a single extension
void TParseContext::profileRequires(TSourceLoc loc, int profileMask, int minVersion, const char* extension, const char *featureDesc)
{
    profileRequires(loc, profileMask, minVersion, extension ? 1 : 0, &extension, featureDesc);
}

//
// When to use requireStage()
//
//     If only some stages support a feature.  
//
// Operation: If the current stage is not present, give an error message.
//
void TParseContext::requireStage(TSourceLoc loc, EShLanguageMask languageMask, const char *featureDesc)
{
    if (((1 << language) & languageMask) == 0)
        error(loc, "not supported in this stage:", featureDesc, StageName(language));
}

// If only one stage supports a feature, this can be called.  But, all supporting stages
// must be specified with one call.
void TParseContext::requireStage(TSourceLoc loc, EShLanguage stage, const char *featureDesc)
{
    requireStage(loc, static_cast<EShLanguageMask>(1 << stage), featureDesc);
}

//
// Within a set of profiles, see if a feature is deprecated and give an error or warning based on whether
// a future compatibility context is being use.
//
void TParseContext::checkDeprecated(TSourceLoc loc, int profileMask, int depVersion, const char *featureDesc)
{
    if (profile & profileMask) {
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
// Within a set of profiles, see if a feature has now been removed and if so, give an error.
// The version argument is the first version no longer having the feature.
//
void TParseContext::requireNotRemoved(TSourceLoc loc, int profileMask, int removedVersion, const char *featureDesc)
{
    if (profile & profileMask) {
        if (version >= removedVersion) {
            const int maxSize = 60;
            char buf[maxSize];
            snprintf(buf, maxSize, "%s profile; removed in version %d", ProfileName(profile), removedVersion);
            error(loc, "no longer supported in", featureDesc, buf);
        }
    }
}

//
// Translate from text string of extension's behavior to enum.
//
TExtensionBehavior TParseContext::getExtensionBehavior(const char* behavior)
{
    if (! strcmp("require", behavior))
        return EBhRequire;
    else if (! strcmp("enable", behavior))
        return EBhEnable;
    else if (! strcmp("disable", behavior))
        return EBhDisable;
    else if (! strcmp("warn", behavior))
        return EBhWarn;
    else {
        error(currentLoc, "behavior not supported", "#extension", behavior);
        return EBhDisable;
    }
}

void TParseContext::updateExtensionBehavior(const char* extName, const char* behaviorString)
{
    TExtensionBehavior behavior = getExtensionBehavior(behaviorString);
    TMap<TString, TExtensionBehavior>:: iterator iter;
    TString msg;

    // special case for the 'all' extension
    if (! strcmp(extName, "all")) {
        if (behavior == EBhRequire || behavior == EBhEnable) {
            error(currentLoc, "extension 'all' cannot have 'require' or 'enable' behavior", "#extension", "");
            return;
        } else {
            for (iter = extensionBehavior.begin(); iter != extensionBehavior.end(); ++iter)
                iter->second = behavior;
        }
    } else {
        iter = extensionBehavior.find(TString(extName));
        if (iter == extensionBehavior.end()) {
            switch (behavior) {
            case EBhRequire:
                error(currentLoc, "extension not supported", "#extension", extName);
                break;
            case EBhEnable:
            case EBhWarn:
            case EBhDisable:
                warn(currentLoc, "extension not supported", "#extension", extName);
                break;
            default:
                assert(0 && "unexpected behavior");
            }

            return;
        } else
            iter->second = behavior;
    }
}

//
// Call for any operation needing full GLSL integer data-type support.
//
void TParseContext::fullIntegerCheck(TSourceLoc loc, const char* op)
{
    profileRequires(loc, ENoProfile, 130, 0, op); 
    profileRequires(loc, EEsProfile, 300, 0, op);
}

//
// Call for any operation needing GLSL double data-type support.
//
void TParseContext::doubleCheck(TSourceLoc loc, const char* op)
{
    requireProfile(loc, ECoreProfile | ECompatibilityProfile, op);
    profileRequires(loc, ECoreProfile, 400, 0, op);
    profileRequires(loc, ECompatibilityProfile, 400, 0, op);
}

} // end namespace glslang
