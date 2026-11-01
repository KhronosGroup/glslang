//
// Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
// Copyright (C) 2012-2013 LunarG, Inc.
// Copyright (C) 2017 ARM Limited.
// Copyright (C) 2015-2018 Google, Inc.
// Modifications Copyright (C) 2020 Advanced Micro Devices, Inc. All rights reserved.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
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
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

//
// Symbol table for parsing.  Most functionality and main ideas
// are documented in the header file.
//

#include "SymbolTable.h"

namespace glslang {

//
// TType helper function needs a place to live.
//

TType::~TType() {}

//
// Recursively generate mangled names.
//
void TType::buildMangledName(TString& mangledName) const
{
    if (isTensorARM())
        mangledName += 'T';
    else if (isMatrix())
        mangledName += 'm';
    else if (isVector())
        mangledName += 'v';

    if (isCoopVecNV())
        mangledName += "coopvec";

    switch (basicType) {
    case EbtFloat:              mangledName += 'f';      break;
    case EbtInt:                mangledName += 'i';      break;
    case EbtUint:               mangledName += 'u';      break;
    case EbtBool:               mangledName += 'b';      break;
    case EbtDouble:             mangledName += 'd';      break;
    case EbtFloat16:            mangledName += "f16";    break;
    case EbtBFloat16:           mangledName += "bf16";   break;
    case EbtFloatE5M2:          mangledName += "fe5m2";  break;
    case EbtFloatE4M3:          mangledName += "fe4m3";  break;
    case EbtFloatE2M1:          mangledName += "fe2m1";  break;
    case EbtFloatE3M2:          mangledName += "fe3m2";  break;
    case EbtFloatE2M3:          mangledName += "fe2m3";  break;
    case EbtFloatUE8M0:         mangledName += "fue8m0";  break;
    case EbtFloatMXINT8:        mangledName += "fmxint8";break;
    case EbtInt8:               mangledName += "i8";     break;
    case EbtUint8:              mangledName += "u8";     break;
    case EbtInt16:              mangledName += "i16";    break;
    case EbtUint16:             mangledName += "u16";    break;
    case EbtInt64:              mangledName += "i64";    break;
    case EbtUint64:             mangledName += "u64";    break;
    case EbtAtomicUint:         mangledName += "au";     break;
    case EbtAccStruct:          mangledName += "as";     break;
    case EbtRayQuery:           mangledName += "rq";     break;
    case EbtSpirvType:          mangledName += "spv-t";  break;
    case EbtHitObjectNV:        mangledName += "ho";     break;
    case EbtHitObjectEXT:       mangledName += "ho";     break;
    case EbtTensorLayoutNV:     mangledName += "tl";     break;
    case EbtTensorViewNV:       mangledName += "tv";     break;
    case EbtSampler:
        switch (sampler.type) {
        case EbtFloat16: mangledName += "f16"; break;
        case EbtInt:   mangledName += "i"; break;
        case EbtUint:  mangledName += "u"; break;
        case EbtInt64:   mangledName += "i64"; break;
        case EbtUint64:  mangledName += "u64"; break;
        default: break; // some compilers want this
        }
        if (sampler.isImageClass())
            mangledName += "I";  // a normal image or subpass
        else if (sampler.isPureSampler())
            mangledName += "p";  // a "pure" sampler
        else if (!sampler.isCombined())
            mangledName += "t";  // a "pure" texture
        else
            mangledName += "s";  // traditional combined sampler
        if (sampler.isArrayed())
            mangledName += "A";
        if (sampler.isShadow())
            mangledName += "S";
        if (sampler.isExternal())
            mangledName += "E";
        if (sampler.isYuv())
            mangledName += "Y";
        switch (sampler.dim) {
        case Esd2D:       mangledName += "2";  break;
        case Esd3D:       mangledName += "3";  break;
        case EsdCube:     mangledName += "C";  break;
        case Esd1D:       mangledName += "1";  break;
        case EsdRect:     mangledName += "R2"; break;
        case EsdBuffer:   mangledName += "B";  break;
        case EsdSubpass:  mangledName += "P";  break;
        default: break; // some compilers want this
        }

#ifdef ENABLE_HLSL
        if (sampler.hasReturnStruct()) {
            // Name mangle for sampler return struct uses struct table index.
            mangledName += "-tx-struct";

            char text[16]; // plenty enough space for the small integers.
            snprintf(text, sizeof(text), "%u-", sampler.getStructReturnIndex());
            mangledName += text;
        } else {
            switch (sampler.getVectorSize()) {
            case 1: mangledName += "1"; break;
            case 2: mangledName += "2"; break;
            case 3: mangledName += "3"; break;
            case 4: break; // default to prior name mangle behavior
            }
        }
#endif

        if (sampler.isMultiSample())
            mangledName += "M";
        break;
    case EbtReference:
        // Mangle by the block name alone, not by the referent's members. The parser rejects a
        // second block with the same name, so the name already identifies the type. Recursing
        // into the referent the way the struct case does would not terminate: a buffer reference
        // block may legally name itself or another block that refers back to it, which a struct
        // cannot do.
        mangledName += "bref-";
        if (typeName)
            mangledName += *typeName;
        break;
    case EbtStruct:
    case EbtBlock:
        if (basicType == EbtStruct)
            mangledName += "struct-";
        else
            mangledName += "block-";
        if (typeName)
            mangledName += *typeName;
        for (unsigned int i = 0; i < structure->size(); ++i) {
            if ((*structure)[i].type->getBasicType() == EbtVoid)
                continue;
            mangledName += '-';
            (*structure)[i].type->buildMangledName(mangledName);
        }
        break;
    default:
        break;
    }

    if (getVectorSize() > 0)
        mangledName += static_cast<char>('0' + getVectorSize());
    else {
        mangledName += static_cast<char>('0' + getMatrixCols());
        mangledName += static_cast<char>('0' + getMatrixRows());
    }

    if (typeParameters) {
        const int maxSize = 11;
        char buf[maxSize];
        for (int i = 0; i < typeParameters->arraySizes->getNumDims(); ++i) {
            if (typeParameters->arraySizes->getDimNode(i)) {
                if (typeParameters->arraySizes->getDimNode(i)->getAsSymbolNode())
                    snprintf(buf, maxSize, "s%lld", typeParameters->arraySizes->getDimNode(i)->getAsSymbolNode()->getId());
                else
                    snprintf(buf, maxSize, "s%p", typeParameters->arraySizes->getDimNode(i));
            } else
                snprintf(buf, maxSize, "%d", typeParameters->arraySizes->getDimSize(i));
            mangledName += '<';
            mangledName += buf;
            mangledName += '>';
        }
    }

    if (arraySizes) {
        const int maxSize = 11;
        char buf[maxSize];
        for (int i = 0; i < arraySizes->getNumDims(); ++i) {
            if (arraySizes->getDimNode(i)) {
                if (arraySizes->getDimNode(i)->getAsSymbolNode())
                    snprintf(buf, maxSize, "s%lld", arraySizes->getDimNode(i)->getAsSymbolNode()->getId());
                else
                    snprintf(buf, maxSize, "s%p", (void*)(arraySizes->getDimNode(i)));
            } else
                snprintf(buf, maxSize, "%d", arraySizes->getDimSize(i));
            mangledName += '[';
            mangledName += buf;
            mangledName += ']';
        }
    }
}

TString TType::getCompleteString(bool syntactic, bool getQualifiers, bool getPrecision, bool getType, TString name,
                                 TString structName) const
{
    TString typeString;

    const auto appendStr  = [&](const char* s)  { typeString.append(s); };
    const auto appendUint = [&](unsigned int u) { typeString.append(std::to_string(u).c_str()); };
    const auto appendInt  = [&](int i)          { typeString.append(std::to_string(i).c_str()); };

    if (getQualifiers) {
      if (qualifier.hasSpirvDecorate())
        appendStr(qualifier.getSpirvDecorateQualifierString().c_str());

      if (qualifier.hasLayout()) {
        // To reduce noise, skip this if the only layout is an xfb_buffer
        // with no triggering xfb_offset.
        TQualifier noXfbBuffer = qualifier;
        noXfbBuffer.layoutXfbBuffer = TQualifier::layoutXfbBufferEnd;
        if (noXfbBuffer.hasLayout()) {
          appendStr("layout(");
          if (qualifier.hasAnyLocation()) {
            appendStr(" location=");
            appendUint(qualifier.layoutLocation);
            if (qualifier.hasComponent()) {
              appendStr(" component=");
              appendUint(qualifier.layoutComponent);
            }
            if (qualifier.hasIndex()) {
              appendStr(" index=");
              appendUint(qualifier.layoutIndex);
            }
          }
          if (qualifier.hasSet()) {
            appendStr(" set=");
            appendUint(qualifier.layoutSet);
          }
          if (qualifier.hasBinding()) {
            appendStr(" binding=");
            appendUint(qualifier.layoutBinding);
          }
          if (qualifier.hasStream()) {
            appendStr(" stream=");
            appendUint(qualifier.layoutStream);
          }
          if (qualifier.hasMatrix()) {
            appendStr(" ");
            appendStr(TQualifier::getLayoutMatrixString(qualifier.layoutMatrix));
          }
          if (qualifier.hasPacking()) {
            appendStr(" ");
            appendStr(TQualifier::getLayoutPackingString(qualifier.layoutPacking));
          }
          if (qualifier.hasOffset()) {
            appendStr(" offset=");
            appendInt(qualifier.layoutOffset);
          }
          if (qualifier.hasAlign()) {
            appendStr(" align=");
            appendInt(qualifier.layoutAlign);
          }
          if (qualifier.hasFormat()) {
            appendStr(" ");
            appendStr(TQualifier::getLayoutFormatString(qualifier.layoutFormat));
          }
          if (qualifier.hasXfbBuffer() && qualifier.hasXfbOffset()) {
            appendStr(" xfb_buffer=");
            appendUint(qualifier.layoutXfbBuffer);
          }
          if (qualifier.hasXfbOffset()) {
            appendStr(" xfb_offset=");
            appendUint(qualifier.layoutXfbOffset);
          }
          if (qualifier.hasXfbStride()) {
            appendStr(" xfb_stride=");
            appendUint(qualifier.layoutXfbStride);
          }
          if (qualifier.hasAttachment()) {
            appendStr(" input_attachment_index=");
            appendUint(qualifier.layoutAttachment);
          }
          if (qualifier.hasSpecConstantId()) {
            appendStr(" constant_id=");
            appendUint(qualifier.layoutSpecConstantId);
          }
          if (qualifier.layoutPushConstant)
            appendStr(" push_constant");
          if (qualifier.layoutBufferReference)
            appendStr(" buffer_reference");
          if (qualifier.layoutDescriptorBufferType)
            appendStr(" buffer_type");
          if (qualifier.hasBufferReferenceAlign()) {
            appendStr(" buffer_reference_align=");
            appendUint(1u << qualifier.layoutBufferReferenceAlign);
          }

          if (qualifier.layoutPassthrough)
            appendStr(" passthrough");
          if (qualifier.layoutViewportRelative)
            appendStr(" layoutViewportRelative");
          if (qualifier.layoutSecondaryViewportRelativeOffset != -2048) {
            appendStr(" layoutSecondaryViewportRelativeOffset=");
            appendInt(qualifier.layoutSecondaryViewportRelativeOffset);
          }

          if (qualifier.layoutShaderRecord)
            appendStr(" shaderRecordNV");
          if (qualifier.layoutFullQuads)
            appendStr(" full_quads");
          if (qualifier.layoutQuadDeriv)
            appendStr(" quad_derivatives");
          if (qualifier.layoutHitObjectShaderRecordNV)
            appendStr(" hitobjectshaderrecordnv");
          if (qualifier.layoutHitObjectShaderRecordEXT)
            appendStr(" hitobjectshaderrecordext");

          if (qualifier.hasBank()) {
            appendStr(" bank=");
            appendUint(qualifier.layoutBank);
          }
          if (qualifier.hasMemberOffset()) {
            appendStr(" member_offset=");
            appendInt(qualifier.layoutMemberOffset);
          }

          if (qualifier.layoutBindlessSampler)
              appendStr(" layoutBindlessSampler");
          if (qualifier.layoutBindlessImage)
              appendStr(" layoutBindlessImage");

          if (qualifier.layoutDescriptorHeap)
              appendStr(" descriptor_heap");
          if (qualifier.layoutDescriptorStride != TQualifier::layoutDescriptorStrideEnd) {
              appendStr(" descriptor_stride=");
              appendInt(qualifier.layoutDescriptorStride);
          }
          if (qualifier.layoutDescriptorSize != TQualifier::layoutDescriptorSizeEnd) {
              appendStr(" descriptor_size=");
              appendInt(qualifier.layoutDescriptorSize);
          }
          if (qualifier.layoutHeapOffset || qualifier.layoutHeapOffsetNode) {
              appendStr(" heap_offset=");
              if (qualifier.layoutHeapOffsetNode)
                  appendStr("<constant-expression>");
              else
                  appendInt(qualifier.layoutHeapOffset);
          }

          appendStr(")");
        }
      }

      if (qualifier.invariant)
        appendStr(" invariant");
      if (qualifier.noContraction)
        appendStr(" noContraction");
      if (qualifier.centroid)
        appendStr(" centroid");
      if (qualifier.smooth)
        appendStr(" smooth");
      if (qualifier.flat)
        appendStr(" flat");
      if (qualifier.nopersp)
        appendStr(" noperspective");
      if (qualifier.explicitInterp)
        appendStr(" __explicitInterpAMD");
      if (qualifier.pervertexNV)
        appendStr(" pervertexNV");
      if (qualifier.pervertexEXT)
          appendStr(" pervertexEXT");
      if (qualifier.perPrimitiveNV)
        appendStr(" perprimitiveNV");
      if (qualifier.perViewNV)
        appendStr(" perviewNV");
      if (qualifier.perTaskNV)
        appendStr(" taskNV");
      if (qualifier.patch)
        appendStr(" patch");
      if (qualifier.sample)
        appendStr(" sample");
      if (qualifier.coherent)
        appendStr(" coherent");
      if (qualifier.devicecoherent)
        appendStr(" devicecoherent");
      if (qualifier.queuefamilycoherent)
        appendStr(" queuefamilycoherent");
      if (qualifier.workgroupcoherent)
        appendStr(" workgroupcoherent");
      if (qualifier.subgroupcoherent)
        appendStr(" subgroupcoherent");
      if (qualifier.shadercallcoherent)
        appendStr(" shadercallcoherent");
      if (qualifier.nonprivate)
        appendStr(" nonprivate");
      if (qualifier.volatil)
        appendStr(" volatile");
      if (qualifier.nontemporal)
        appendStr(" nontemporal");
      if (qualifier.restrict)
        appendStr(" restrict");
      if (qualifier.readonly)
        appendStr(" readonly");
      if (qualifier.writeonly)
        appendStr(" writeonly");
      if (qualifier.specConstant)
        appendStr(" specialization-constant");
      if (qualifier.nonUniform)
        appendStr(" nonuniform");
      if (qualifier.isNullInit())
        appendStr(" null-init");
      if (qualifier.isSpirvByReference())
        appendStr(" spirv_by_reference");
      if (qualifier.isSpirvLiteral())
        appendStr(" spirv_literal");
      appendStr(" ");
      appendStr(getStorageQualifierString());
    }
    if (getType) {
      if (syntactic) {
        if (getPrecision && qualifier.precision != EpqNone) {
          appendStr(" ");
          appendStr(getPrecisionQualifierString());
        }
        if (isVector() || isMatrix()) {
          appendStr(" ");
          switch (basicType) {
          case EbtDouble:
            appendStr("d");
            break;
          case EbtInt:
            appendStr("i");
            break;
          case EbtUint:
            appendStr("u");
            break;
          case EbtBool:
            appendStr("b");
            break;
          case EbtFloat:
          default:
            break;
          }
          if (isVector()) {
            appendStr("vec");
            appendInt(vectorSize);
          } else {
            appendStr("mat");
            appendInt(matrixCols);
            appendStr("x");
            appendInt(matrixRows);
          }
        } else if (isStruct() && structure) {
            appendStr(" ");
            appendStr(structName.c_str());
            appendStr("{");
            bool hasHiddenMember = true;
            for (size_t i = 0; i < structure->size(); ++i) {
              if (!(*structure)[i].type->hiddenMember()) {
                if (!hasHiddenMember)
                  appendStr(", ");
                typeString.append((*structure)[i].type->getCompleteString(syntactic, getQualifiers, getPrecision, getType, (*structure)[i].type->getFieldName()));
                hasHiddenMember = false;
              }
            }
            appendStr("}");
        } else {
            appendStr(" ");
            switch (basicType) {
            case EbtDouble:
              appendStr("double");
              break;
            case EbtInt:
              appendStr("int");
              break;
            case EbtUint:
              appendStr("uint");
              break;
            case EbtBool:
              appendStr("bool");
              break;
            case EbtFloat:
              appendStr("float");
              break;
            default:
              appendStr("unexpected");
              break;
            }
        }
        if (name.length() > 0) {
          appendStr(" ");
          appendStr(name.c_str());
        }
        if (isArray()) {
          for (int i = 0; i < (int)arraySizes->getNumDims(); ++i) {
            int size = arraySizes->getDimSize(i);
            if (size == UnsizedArraySize && i == 0 && arraySizes->isVariablyIndexed())
              appendStr("[]");
            else {
              if (size == UnsizedArraySize) {
                appendStr("[");
                if (i == 0)
                  appendInt(arraySizes->getImplicitSize());
                appendStr("]");
              }
              else {
                appendStr("[");
                appendInt(arraySizes->getDimSize(i));
                appendStr("]");
              }
            }
          }
        }
      }
      else {
        if (isArray()) {
          for (int i = 0; i < (int)arraySizes->getNumDims(); ++i) {
            int size = arraySizes->getDimSize(i);
            if (size == UnsizedArraySize && i == 0 && arraySizes->isVariablyIndexed())
              appendStr(" runtime-sized array of");
            else {
              if (size == UnsizedArraySize) {
                appendStr(" unsized");
                if (i == 0) {
                  appendStr(" ");
                  appendInt(arraySizes->getImplicitSize());
                }
              }
              else {
                appendStr(" ");
                appendInt(arraySizes->getDimSize(i));
              }
              appendStr("-element array of");
            }
          }
        }
        if (isParameterized()) {
          if (isCoopMatKHR()) {
            appendStr(" ");
            appendStr("coopmat");
          }
          if (isTensorLayoutNV()) {
            appendStr(" ");
            appendStr("tensorLayoutNV");
          }
          if (isTensorViewNV()) {
            appendStr(" ");
            appendStr("tensorViewNV");
          }
          if (isCoopVecNV()) {
            appendStr(" ");
            appendStr("coopvecNV");
          }
          if (isLongVector()) {
            appendStr(" ");
            appendStr("vector");
          }

          appendStr("<");
          for (int i = 0; i < (int)typeParameters->arraySizes->getNumDims(); ++i) {
            appendInt(typeParameters->arraySizes->getDimSize(i));
            if (i != (int)typeParameters->arraySizes->getNumDims() - 1)
              appendStr(", ");
          }
          appendStr(">");
        }
        if (getPrecision && qualifier.precision != EpqNone) {
          appendStr(" ");
          appendStr(getPrecisionQualifierString());
        }
        if (isMatrix()) {
          appendStr(" ");
          appendInt(matrixCols);
          appendStr("X");
          appendInt(matrixRows);
          appendStr(" matrix of");
        }
        else if (isVector()) {
          appendStr(" ");
          appendInt(vectorSize);
          appendStr("-component vector of");
        }

        appendStr(" ");
        typeString.append(getBasicTypeString());

        if (qualifier.builtIn != EbvNone) {
          appendStr(" ");
          appendStr(getBuiltInVariableString());
        }

        // Add struct/block members
        if (isStruct() && structure) {
          appendStr("{");
          bool hasHiddenMember = true;
          for (size_t i = 0; i < structure->size(); ++i) {
            if (!(*structure)[i].type->hiddenMember()) {
              if (!hasHiddenMember)
                appendStr(", ");
              typeString.append((*structure)[i].type->getCompleteString());
              typeString.append(" ");
              typeString.append((*structure)[i].type->getFieldName());
              hasHiddenMember = false;
            }
          }
          appendStr("}");
        }
      }
    }

    return typeString;
}

TType::TType(const TType& type, int derefIndex, bool rowMajor)
{
                            if (type.isArray()) {
                                shallowCopy(type);
                                if (type.getArraySizes()->getNumDims() == 1) {
                                    arraySizes = nullptr;
                                } else {
                                    // want our own copy of the array, so we can edit it
                                    arraySizes = new TArraySizes;
                                    arraySizes->copyDereferenced(*type.arraySizes);
                                }
                            } else if (type.basicType == EbtStruct || type.basicType == EbtBlock) {
                                // do a structure dereference
                                const TTypeList& memberList = *type.getStruct();
                                shallowCopy(*memberList[derefIndex].type);
                                return;
                            } else {
                                // do a vector/matrix dereference
                                shallowCopy(type);
                                if (matrixCols > 0) {
                                    // dereference from matrix to vector
                                    if (rowMajor)
                                        vectorSize = matrixCols;
                                    else
                                        vectorSize = matrixRows;
                                    matrixCols = 0;
                                    matrixRows = 0;
                                    if (vectorSize == 1)
                                        vector1 = true;
                                } else if (isVector()) {
                                    // dereference from vector to scalar
                                    vectorSize = 1;
                                    vector1 = false;
                                } else if (isCoopMat() || isCoopVecNV() || isLongVector()) {
                                    coopmatNV = false;
                                    coopmatKHR = false;
                                    coopmatKHRuse = 0;
                                    coopmatKHRUseValid = false;
                                    coopvecNV = false;
                                    longVector = false;
                                    typeParameters = nullptr;
                                } else if (isTileAttachmentQCOM()) {
                                    tileAttachmentQCOM = false;
                                    typeParameters = nullptr;
                                }
                            }
                        }

void TType::shallowCopy(const TType& copyOf)
{
    basicType = copyOf.basicType;
    sampler = copyOf.sampler;
    qualifier = copyOf.qualifier;
    vectorSize = copyOf.vectorSize;
    matrixCols = copyOf.matrixCols;
    matrixRows = copyOf.matrixRows;
    vector1 = copyOf.vector1;
    arraySizes = copyOf.arraySizes;  // copying the pointer only, not the contents
    fieldName = copyOf.fieldName;
    typeName = copyOf.typeName;
    if (isStruct()) {
        structure = copyOf.structure;
    } else {
        referentType = copyOf.referentType;
    }
    typeParameters = copyOf.typeParameters;
    spirvType = copyOf.spirvType;
    coopmatNV = copyOf.isCoopMatNV();
    coopmatKHR = copyOf.isCoopMatKHR();
    coopmatKHRuse = copyOf.coopmatKHRuse;
    coopmatKHRUseValid = copyOf.coopmatKHRUseValid;
    coopvecNV = copyOf.isCoopVecNV();
    longVector = copyOf.isLongVector();
    tileAttachmentQCOM = copyOf.tileAttachmentQCOM;
    tensorRankARM = copyOf.tensorRankARM;
}

bool TType::sameStructType(const TType& right, int* lpidx, int* rpidx) const
{
    // Initialize error to general type mismatch.
    if (lpidx != nullptr) {
        *lpidx = -1;
        *rpidx = -1;
    }

    // Most commonly, they are both nullptr, or the same pointer to the same actual structure
    // TODO: Why return true when neither types are structures?
    if ((!isStruct() && !right.isStruct()) ||
        (isStruct() && right.isStruct() && structure == right.structure))
        return true;

    if (!isStruct() || !right.isStruct())
        return false;

    // Structure names have to match
    if (*typeName != *right.typeName)
        return false;

    // There are inconsistencies with how gl_PerVertex is setup. For now ignore those as errors if they
    // are known inconsistencies.
    bool isGLPerVertex = *typeName == "gl_PerVertex";

    // Both being nullptr was caught above, now they both have to be structures of the same number of elements
    if (lpidx == nullptr &&
        (structure->size() != right.structure->size() && !isGLPerVertex)) {
        return false;
    }

    // Compare the names and types of all the members, which have to match
    for (size_t li = 0, ri = 0; li < structure->size() || ri < right.structure->size(); ++li, ++ri) {
        if (lpidx != nullptr) {
            *lpidx = static_cast<int>(li);
            *rpidx = static_cast<int>(ri);
        }
        if (li < structure->size() && ri < right.structure->size()) {
            if ((*structure)[li].type->getFieldName() == (*right.structure)[ri].type->getFieldName()) {
                if (*(*structure)[li].type != *(*right.structure)[ri].type)
                    return false;
            } else {
                // Skip hidden members
                if ((*structure)[li].type->hiddenMember()) {
                    ri--;
                    continue;
                } else if ((*right.structure)[ri].type->hiddenMember()) {
                    li--;
                    continue;
                }
                // If one of the members is something that's inconsistently declared, skip over it
                // for now.
                if (isGLPerVertex) {
                    if (isInconsistentGLPerVertexMember((*structure)[li].type->getFieldName())) {
                        ri--;
                        continue;
                    } else if (isInconsistentGLPerVertexMember((*right.structure)[ri].type->getFieldName())) {
                        li--;
                        continue;
                    }
                } else {
                    return false;
                }
            }
        // If we get here, then there should only be inconsistently declared members left
        } else if (li < structure->size()) {
            if (!(*structure)[li].type->hiddenMember() && !isInconsistentGLPerVertexMember((*structure)[li].type->getFieldName())) {
                if (lpidx != nullptr) {
                    *rpidx = -1;
                }
                return false;
            }
        } else {
            if (!(*right.structure)[ri].type->hiddenMember() && !isInconsistentGLPerVertexMember((*right.structure)[ri].type->getFieldName())) {
                if (lpidx != nullptr) {
                    *lpidx = -1;
                }
                return false;
            }
        }
    }

    return true;
}

void TType::deepCopy(const TType& copyOf, TMap<TTypeList*,TTypeList*>& copiedMap)
{
    shallowCopy(copyOf);

    // GL_EXT_spirv_intrinsics
    if (copyOf.qualifier.spirvDecorate) {
        qualifier.spirvDecorate = new TSpirvDecorate;
        *qualifier.spirvDecorate = *copyOf.qualifier.spirvDecorate;
    }

    if (copyOf.spirvType) {
        spirvType = new TSpirvType;
        *spirvType = *copyOf.spirvType;
    }

    if (copyOf.arraySizes) {
        arraySizes = new TArraySizes;
        *arraySizes = *copyOf.arraySizes;
    }

    if (copyOf.typeParameters) {
        typeParameters = new TTypeParameters;
        typeParameters->arraySizes = new TArraySizes;
        *typeParameters->arraySizes = *copyOf.typeParameters->arraySizes;
        if (copyOf.typeParameters->spirvType) {
            *typeParameters->spirvType = *copyOf.typeParameters->spirvType;
        }
        typeParameters->basicType = copyOf.basicType;
    }

    if (copyOf.isStruct() && copyOf.structure) {
        auto prevCopy = copiedMap.find(copyOf.structure);
        if (prevCopy != copiedMap.end())
            structure = prevCopy->second;
        else {
            structure = new TTypeList;
            copiedMap[copyOf.structure] = structure;
            for (unsigned int i = 0; i < copyOf.structure->size(); ++i) {
                TTypeLoc typeLoc;
                typeLoc.loc = (*copyOf.structure)[i].loc;
                typeLoc.type = new TType();
                typeLoc.type->deepCopy(*(*copyOf.structure)[i].type, copiedMap);
                structure->push_back(typeLoc);
            }
        }
    }

    if (copyOf.fieldName)
        fieldName = NewPoolTString(copyOf.fieldName->c_str());
    if (copyOf.typeName)
        typeName = NewPoolTString(copyOf.typeName->c_str());
}

//
// Dump functions.
//

void TSymbol::dumpExtensions(TInfoSink& infoSink) const
{
    int numExtensions = getNumExtensions();
    if (numExtensions) {
        infoSink.debug << " <";

        for (int i = 0; i < numExtensions; i++)
            infoSink.debug << getExtensions()[i] << ",";

        infoSink.debug << ">";
    }
}

void TVariable::dump(TInfoSink& infoSink, bool complete) const
{
    if (complete) {
        infoSink.debug << getName().c_str() << ": " << type.getCompleteString();
        dumpExtensions(infoSink);
    } else {
        infoSink.debug << getName().c_str() << ": " << type.getStorageQualifierString() << " "
                       << type.getBasicTypeString();

        if (type.isArray())
            infoSink.debug << "[0]";
    }

    infoSink.debug << "\n";
}

void TFunction::dump(TInfoSink& infoSink, bool complete) const
{
    if (complete) {
        infoSink.debug << getName().c_str() << ": " << returnType.getCompleteString() << " " << getName().c_str()
                       << "(";

        int numParams = getParamCount();
        for (int i = 0; i < numParams; i++) {
            const TParameter &param = parameters[i];
            infoSink.debug << param.type->getCompleteString() << " "
                           << (param.type->isStruct() ? "of " + param.type->getTypeName() + " " : "")
                           << (param.name ? *param.name : "") << (i < numParams - 1 ? "," : "");
        }

        infoSink.debug << ")";
        dumpExtensions(infoSink);
    } else {
        infoSink.debug << getName().c_str() << ": " << returnType.getBasicTypeString() << " "
                       << getMangledName().c_str() << "n";
    }

    infoSink.debug << "\n";
}

void TAnonMember::dump(TInfoSink& TInfoSink, bool) const
{
    TInfoSink.debug << "anonymous member " << getMemberNumber() << " of " << getAnonContainer().getName().c_str()
                    << "\n";
}

void TSymbolTableLevel::dump(TInfoSink& infoSink, bool complete) const
{
    tLevel::const_iterator it;
    for (it = level.begin(); it != level.end(); ++it)
        (*it).second->dump(infoSink, complete);
}

void TSymbolTable::dump(TInfoSink& infoSink, bool complete) const
{
    for (int level = currentLevel(); level >= 0; --level) {
        infoSink.debug << "LEVEL " << level << "\n";
        table[level]->dump(infoSink, complete);
    }
}

//
// Functions have buried pointers to delete.
//
TFunction::~TFunction()
{
    for (TParamList::iterator i = parameters.begin(); i != parameters.end(); ++i)
        delete (*i).type;
}

//
// Symbol table levels are a map of pointers to symbols that have to be deleted.
//
TSymbolTableLevel::~TSymbolTableLevel()
{
    for (tLevel::iterator it = level.begin(); it != level.end(); ++it) {
        const TString& name = it->first;
        auto retargetIter = std::find_if(retargetedSymbols.begin(), retargetedSymbols.end(),
                                      [&name](const std::pair<TString, TString>& i) { return i.first == name; });
        if (retargetIter == retargetedSymbols.end())
            delete (*it).second;
    }


    delete [] defaultPrecision;
}

//
// Change all function entries in the table with the non-mangled name
// to be related to the provided built-in operation.
//
void TSymbolTableLevel::relateToOperator(const char* name, TOperator op)
{
    tLevel::const_iterator candidate = level.lower_bound(name);
    while (candidate != level.end()) {
        const TString& candidateName = (*candidate).first;
        TString::size_type parenAt = candidateName.find_first_of('(');
        if (parenAt != candidateName.npos && candidateName.compare(0, parenAt, name) == 0) {
            TFunction* function = (*candidate).second->getAsFunction();
            function->relateToOperator(op);
        } else
            break;
        ++candidate;
    }
}

// Make all function overloads of the given name require an extension(s).
// Should only be used for a version/profile that actually needs the extension(s).
void TSymbolTableLevel::setFunctionExtensions(const char* name, int num, const char* const extensions[])
{
    tLevel::const_iterator candidate = level.lower_bound(name);
    while (candidate != level.end()) {
        const TString& candidateName = (*candidate).first;
        TString::size_type parenAt = candidateName.find_first_of('(');
        if (parenAt != candidateName.npos && candidateName.compare(0, parenAt, name) == 0) {
            TSymbol* symbol = candidate->second;
            symbol->setExtensions(num, extensions);
        } else
            break;
        ++candidate;
    }
}

// Call the callback function to determine the required extensions
void TSymbolTableLevel::setFunctionExtensionsCallback(const char* name, std::function<std::vector<const char *>(const char *)> const &func)
{
    tLevel::const_iterator candidate = level.lower_bound(name);
    while (candidate != level.end()) {
        const TString& candidateName = (*candidate).first;
        TString::size_type parenAt = candidateName.find_first_of('(');
        if (parenAt != candidateName.npos && candidateName.compare(0, parenAt, name) == 0) {
            TSymbol* symbol = candidate->second;

            auto exts = func(candidateName.c_str());
            symbol->setExtensions(exts.size(), exts.data());
        } else
            break;
        ++candidate;
    }
}

// Make a single function require an extension(s). i.e., this will only set the extensions for the symbol that matches 'name' exactly.
// This is different from setFunctionExtensions, which uses std::map::lower_bound to effectively set all symbols that start with 'name'.
// Should only be used for a version/profile that actually needs the extension(s).
void TSymbolTableLevel::setSingleFunctionExtensions(const char* name, int num, const char* const extensions[])
{
    if (auto candidate = level.find(name); candidate != level.end()) {
        candidate->second->setExtensions(num, extensions);
    }
}

//
// Make all symbols in this table level read only.
//
void TSymbolTableLevel::readOnly()
{
    for (tLevel::iterator it = level.begin(); it != level.end(); ++it)
        (*it).second->makeReadOnly();
}

//
// Copy a symbol, but the copy is writable; call readOnly() afterward if that's not desired.
//
TSymbol::TSymbol(const TSymbol& copyOf)
{
    name = NewPoolTString(copyOf.name->c_str());
    mangledName = NewPoolTString(copyOf.mangledName->c_str());
    uniqueId = copyOf.uniqueId;
    writable = true;
}

TVariable::TVariable(const TVariable& copyOf) : TSymbol(copyOf)
{
    type.deepCopy(copyOf.type);
    userType = copyOf.userType;

    // we don't support specialization-constant subtrees in cloned tables, only extensions
    constSubtree = nullptr;
    extensions = nullptr;
    memberExtensions = nullptr;
    if (copyOf.getNumExtensions() > 0)
        setExtensions(copyOf.getNumExtensions(), copyOf.getExtensions());
    if (copyOf.hasMemberExtensions()) {
        for (int m = 0; m < (int)copyOf.type.getStruct()->size(); ++m) {
            if (copyOf.getNumMemberExtensions(m) > 0)
                setMemberExtensions(m, copyOf.getNumMemberExtensions(m), copyOf.getMemberExtensions(m));
        }
    }

    if (! copyOf.constArray.empty()) {
        assert(! copyOf.type.isStruct());
        TConstUnionArray newArray(copyOf.constArray, 0, copyOf.constArray.size());
        constArray = newArray;
    }
}

TVariable* TVariable::clone() const
{
    TVariable *variable = new TVariable(*this);

    return variable;
}

TFunction::TFunction(const TFunction& copyOf) : TSymbol(copyOf)
{
    for (unsigned int i = 0; i < copyOf.parameters.size(); ++i) {
        TParameter param{};
        parameters.push_back(param);
        (void)parameters.back().copyParam(copyOf.parameters[i]);
    }

    extensions = nullptr;
    if (copyOf.getNumExtensions() > 0)
        setExtensions(copyOf.getNumExtensions(), copyOf.getExtensions());
    returnType.deepCopy(copyOf.returnType);
    mangledName = copyOf.mangledName;
    op = copyOf.op;
    defined = copyOf.defined;
    prototyped = copyOf.prototyped;
    implicitThis = copyOf.implicitThis;
    variadic = copyOf.variadic;
    illegalImplicitThis = copyOf.illegalImplicitThis;
    defaultParamCount = copyOf.defaultParamCount;
    spirvInst = copyOf.spirvInst;
    functionControl = copyOf.functionControl;
}

TFunction* TFunction::clone() const
{
    TFunction *function = new TFunction(*this);

    return function;
}

TAnonMember* TAnonMember::clone() const
{
    // Anonymous members of a given block should be cloned at a higher level,
    // where they can all be assured to still end up pointing to a single
    // copy of the original container.
    assert(0);

    return nullptr;
}

TSymbolTableLevel* TSymbolTableLevel::clone() const
{
    TSymbolTableLevel *symTableLevel = new TSymbolTableLevel();
    symTableLevel->anonId = anonId;
    symTableLevel->thisLevel = thisLevel;
    symTableLevel->retargetedSymbols.clear();
    for (auto &s : retargetedSymbols) {
        symTableLevel->retargetedSymbols.push_back({s.first, s.second});
    }
    std::vector<bool> containerCopied(anonId, false);
    tLevel::const_iterator iter;
    for (iter = level.begin(); iter != level.end(); ++iter) {
        const TAnonMember* anon = iter->second->getAsAnonMember();
        if (anon) {
            // Insert all the anonymous members of this same container at once,
            // avoid inserting the remaining members in the future, once this has been done,
            // allowing them to all be part of the same new container.
            if (! containerCopied[anon->getAnonId()]) {
                TVariable* container = anon->getAnonContainer().clone();
                container->changeName(NewPoolTString(""));
                // insert the container and all its members
                symTableLevel->insert(*container, false);
                containerCopied[anon->getAnonId()] = true;
            }
        } else {
            const TString& name = iter->first;
            auto retargetIter = std::find_if(retargetedSymbols.begin(), retargetedSymbols.end(),
                                          [&name](const std::pair<TString, TString>& i) { return i.first == name; });
            if (retargetIter != retargetedSymbols.end())
                continue;
            symTableLevel->insert(*iter->second->clone(), false);
        }
    }
    // Now point retargeted symbols to the newly created versions of them
    for (auto &s : retargetedSymbols) {
        TSymbol* sym = symTableLevel->find(s.second);
        if (!sym)
            continue;
        symTableLevel->insert(s.first, sym);
    }

    return symTableLevel;
}

void TSymbolTable::copyTable(const TSymbolTable& copyOf)
{
    assert(adoptedLevels == copyOf.adoptedLevels);

    uniqueId = copyOf.uniqueId;
    noBuiltInRedeclarations = copyOf.noBuiltInRedeclarations;
    separateNameSpaces = copyOf.separateNameSpaces;
    for (unsigned int i = copyOf.adoptedLevels; i < copyOf.table.size(); ++i)
        table.push_back(copyOf.table[i]->clone());
}

void TSymbolTable::relateToOperator(const char* name, TOperator op)
{
    for (unsigned int level = 0; level < table.size(); ++level)
        table[level]->relateToOperator(name, op);
}

void TSymbolTable::setFunctionExtensions(const char* name, int num, const char* const extensions[])
{
    for (unsigned int level = 0; level < table.size(); ++level)
        table[level]->setFunctionExtensions(name, num, extensions);
}

void TSymbolTable::setFunctionExtensionsCallback(const char* name,
                                                 std::function<std::vector<const char*>(const char*)> const& func)
{
    for (unsigned int level = 0; level < table.size(); ++level)
        table[level]->setFunctionExtensionsCallback(name, func);
}

void TSymbolTable::setSingleFunctionExtensions(const char* name, int num, const char* const extensions[])
{
    for (unsigned int level = 0; level < table.size(); ++level)
        table[level]->setSingleFunctionExtensions(name, num, extensions);
}

void TSymbolTable::setVariableExtensions(const char* name, int numExts, const char* const extensions[])
{
    TSymbol* symbol = find(TString(name));
    if (symbol == nullptr)
        return;

    symbol->setExtensions(numExts, extensions);
}

void TSymbolTable::setVariableExtensions(const char* blockName, const char* name, int numExts,
                                         const char* const extensions[])
{
    TSymbol* symbol = find(TString(blockName));
    if (symbol == nullptr)
        return;
    TVariable* variable = symbol->getAsVariable();
    assert(variable != nullptr);

    const TTypeList& structure = *variable->getAsVariable()->getType().getStruct();
    for (int member = 0; member < (int)structure.size(); ++member) {
        if (structure[member].type->getFieldName().compare(name) == 0) {
            variable->setMemberExtensions(member, numExts, extensions);
            return;
        }
    }
}

} // end namespace glslang
