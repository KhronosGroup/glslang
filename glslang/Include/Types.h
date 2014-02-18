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

#ifndef _TYPES_INCLUDED
#define _TYPES_INCLUDED

#include "../Include/Common.h"
#include "../Include/BaseTypes.h"

namespace glslang {

const int GlslangMaxTypeLength = 200;  // TODO: need to print block/struct one member per line, so this can stay bounded

//
// Details within a sampler type
//
enum TSamplerDim {
    EsdNone,
    Esd1D,
    Esd2D,
    Esd3D,
    EsdCube,
    EsdRect,
    EsdBuffer,
    EsdNumDims
};

struct TSampler {
    TBasicType type : 8;  // type returned by sampler
    TSamplerDim dim : 8;
    bool    arrayed : 1;
    bool     shadow : 1;
    bool         ms : 1;
    bool      image : 1;
    bool   external : 1;  // GL_OES_EGL_image_external

    void clear()
    {
        type = EbtVoid;
        dim = EsdNone;
        arrayed = false;
        shadow = false;
        ms = false;
        image = false;
        external = false;
    }

    void set(TBasicType t, TSamplerDim d, bool a = false, bool s = false, bool m = false)
    {
        type = t;
        dim = d;
        arrayed = a;
        shadow = s;
        ms = m;
        image = false;
        external = false;
    }

    void setImage(TBasicType t, TSamplerDim d, bool a = false, bool s = false, bool m = false)
    {
        type = t;
        dim = d;
        arrayed = a;
        shadow = s;
        ms = m;
        image = true;
        external = false;
    }

    bool operator==(const TSampler& right) const
    {
        return type == right.type &&
                dim == right.dim &&
            arrayed == right.arrayed &&
             shadow == right.shadow &&
                 ms == right.ms &&
              image == right.image &&
           external == right.external;
    }

    TString getString() const
    {
        TString s;

        switch (type) {
        case EbtFloat:               break;
        case EbtInt:  s.append("i"); break;
        case EbtUint: s.append("u"); break;
        default:  break;  // some compilers want this
        }
        if (image)
            s.append("image");
        else
            s.append("sampler");
        if (external) {
            s.append("ExternalOES");
            return s;
        }
        switch (dim) {
        case Esd1D:      s.append("1D");     break;
        case Esd2D:      s.append("2D");     break;
        case Esd3D:      s.append("3D");     break;
        case EsdCube:    s.append("Cube");   break;
        case EsdRect:    s.append("2DRect"); break;
        case EsdBuffer:  s.append("Buffer"); break;
        default:  break;  // some compilers want this
        }
        if (ms)
            s.append("MS");
        if (arrayed)
            s.append("Array");
        if (shadow)
            s.append("Shadow");

        return s;
    }
};

//
// Need to have association of line numbers to types in a list for building structs.
//
class TType;
struct TTypeLoc {
    TType* type;
    TSourceLoc loc;
};
typedef TVector<TTypeLoc> TTypeList;

typedef TVector<TString*> TIdentifierList;

//
// TODO: memory: TArraySizes can be replaced by something smaller.
// Almost all arrays could be handled by two sizes each fitting
// in 16 bits, needing a real vector only in the cases where there
// are more than 3 sizes or a size needing more than 16 bits.
//
// The type is a pointer, so that it can be non-allocated and zero
// for the vast majority of non-array types.  Note that means if it
// is used, it will be containing at least one size.

struct TArraySizes {
    POOL_ALLOCATOR_NEW_DELETE(GetThreadPoolAllocator())

    TArraySizes() : maxArraySize(0) { }
    int getSize() { return sizes.front(); }  // TArraySizes only exists if there is at least one dimension
    void setSize(int s) { sizes.push_back(s); }
    bool isArrayOfArrays() { return sizes.size() > 1; }
protected:
    TVector<int> sizes;
    friend class TType;
    int maxArraySize; // for tracking maximum referenced index, before an explicit size is given
};

//
// Following are a series of helper enums for managing layouts and qualifiers,
// used for TPublicType, TType, others.
//

enum TLayoutPacking {
    ElpNone,
    ElpShared,      // default, but different than saying nothing
    ElpStd140,
    ElpStd430,
    ElpPacked
    // If expanding, see bitfield width below
};

enum TLayoutMatrix {
    ElmNone,
    ElmRowMajor,
    ElmColumnMajor  // default, but different than saying nothing
    // If expanding, see bitfield width below
};

// Union of geometry shader and tessellation shader geometry types.
// They don't go into TType, but rather have current state per shader or
// active parser type (TPublicType).
enum TLayoutGeometry {
    ElgNone,
    ElgPoints,
    ElgLines,
    ElgLinesAdjacency,
    ElgLineStrip,
    ElgTriangles,
    ElgTrianglesAdjacency,
    ElgTriangleStrip,
    ElgQuads,
    ElgIsolines,
};

enum TVertexSpacing {
    EvsNone,
    EvsEqual,
    EvsFractionalEven,
    EvsFractionalOdd
};

enum TVertexOrder {
    EvoNone,
    EvoCw,
    EvoCcw
};

class TQualifier {
public:
    void clear()
    {
        storage   = EvqTemporary;
        precision = EpqNone;
        invariant = false;
        centroid  = false;
        smooth    = false;
        flat      = false;
        nopersp   = false;
        patch     = false;
        sample    = false;
        shared    = false;
        coherent  = false;
        volatil   = false;
        restrict  = false;
        readonly  = false;
        writeonly = false;
        clearLayout();
    }
    TStorageQualifier   storage   : 6;
    TPrecisionQualifier precision : 3;
    bool invariant : 1;
    bool centroid  : 1;
    bool smooth    : 1;
    bool flat      : 1;
    bool nopersp   : 1;
    bool patch     : 1;
    bool sample    : 1;
    bool shared    : 1;
    bool coherent  : 1;
    bool volatil   : 1;
    bool restrict  : 1;
    bool readonly  : 1;
    bool writeonly : 1;

    bool isMemory() const
    {
        return shared || coherent || volatil || restrict || readonly || writeonly;
    }
    bool isInterpolation() const
    {
        return flat || smooth || nopersp;
    }
    bool isAuxiliary() const
    {
        return centroid || patch || sample;
    }

    bool isPipeInput() const
    {
        switch (storage) {
        case EvqVaryingIn:
        case EvqFragCoord:
        case EvqPointCoord:
        case EvqFace:
        case EvqVertexId:
        case EvqInstanceId:
            return true;
        default:
            return false;
        }
    }

    bool isPipeOutput() const
    {
        switch (storage) {
        case EvqPosition:
        case EvqPointSize:
        case EvqClipVertex:
        case EvqVaryingOut:
        case EvqFragColor:
        case EvqFragDepth:
            return true;
        default:
            return false;
        }
    }

    bool isUniform() const
    {
        switch (storage) {
        case EvqUniform:
        case EvqBuffer:
            return true;
        default:
            return false;
        }
    }

    bool isIo() const
    {
        switch (storage) {
        case EvqUniform:
        case EvqBuffer:
        case EvqVaryingIn:
        case EvqFragCoord:
        case EvqPointCoord:
        case EvqFace:
        case EvqVertexId:
        case EvqInstanceId:
        case EvqPosition:
        case EvqPointSize:
        case EvqClipVertex:
        case EvqVaryingOut:
        case EvqFragColor:
        case EvqFragDepth:
            return true;
        default:
            return false;
        }
    }

    // Implementing an embedded layout-qualifier class here, since C++ can't have a real class bitfield
    void clearLayout()
    {
        layoutMatrix = ElmNone;
        layoutPacking = ElpNone;
        layoutOffset = -1;
        layoutAlign = -1;

        layoutLocation = layoutLocationEnd;
        layoutComponent = layoutComponentEnd;
        layoutBinding = layoutBindingEnd;
        layoutStream = layoutStreamEnd;

        layoutXfbBuffer = layoutXfbBufferEnd;
        layoutXfbStride = layoutXfbStrideEnd;
        layoutXfbOffset = layoutXfbOffsetEnd;
    }
    bool hasLayout() const
    {
        return hasUniformLayout() || 
               hasLocation() ||
               hasBinding() ||
               hasStream() ||
               hasXfb();
    }
    TLayoutMatrix  layoutMatrix  : 3;
    TLayoutPacking layoutPacking : 4;
    int layoutOffset;
    int layoutAlign;

                 unsigned int layoutLocation         : 7;
    static const unsigned int layoutLocationEnd =   0x3F;

                 unsigned int layoutComponent        : 3;
    static const unsigned int layoutComponentEnd =     4;

                 unsigned int layoutBinding          : 8;
    static const unsigned int layoutBindingEnd =    0xFF;

                 unsigned int layoutStream           : 8;
    static const unsigned int layoutStreamEnd =     0xFF;

                 unsigned int layoutXfbBuffer        : 4;
    static const unsigned int layoutXfbBufferEnd =   0xF;

                 unsigned int layoutXfbStride       : 10;
    static const unsigned int layoutXfbStrideEnd = 0x3FF;

                 unsigned int layoutXfbOffset       : 10;
    static const unsigned int layoutXfbOffsetEnd = 0x3FF;

    bool hasUniformLayout() const
    {
        return hasMatrix() ||
               hasPacking() ||
               hasOffset() ||
               hasAlign();
    }
    bool hasMatrix() const
    {
        return layoutMatrix != ElmNone;
    }
    bool hasPacking() const
    {
        return layoutPacking != ElpNone;
    }
    bool hasOffset() const
    {
        return layoutOffset != -1;
    }
    bool hasAlign() const
    {
        return layoutAlign != -1;
    }
    bool hasLocation() const
    {
        return layoutLocation  != layoutLocationEnd ||
               layoutComponent != layoutComponentEnd;
    }
    bool hasBinding() const
    {
        return layoutBinding != layoutBindingEnd;
    }
    bool hasStream() const
    {
        return layoutStream != layoutStreamEnd;
    }
    bool hasXfb() const
    {
        return hasXfbBuffer() ||
               hasXfbStride() ||
               hasXfbOffset();
    }
    bool hasXfbBuffer() const
    {
        return layoutXfbBuffer != layoutXfbBufferEnd;
    }
    bool hasXfbStride() const
    {
        return layoutXfbStride != layoutXfbStrideEnd;
    }
    bool hasXfbOffset() const
    {
        return layoutXfbOffset != layoutXfbOffsetEnd;
    }
    static const char* getLayoutPackingString(TLayoutPacking packing)
    {
        switch (packing) {
        case ElpPacked:   return "packed";
        case ElpShared:   return "shared";
        case ElpStd140:   return "std140";
        case ElpStd430:   return "std430";
        default:          return "none";
        }
    }
    static const char* getLayoutMatrixString(TLayoutMatrix m)
    {
        switch (m) {
        case ElmColumnMajor: return "column_major";
        case ElmRowMajor:    return "row_major";
        default:             return "none";
        }
    }
    static const char* getGeometryString(TLayoutGeometry geometry)
    {
        switch (geometry) {
        case ElgPoints:             return "points";
        case ElgLines:              return "lines";
        case ElgLinesAdjacency:     return "lines_adjancency";
        case ElgLineStrip:          return "line_strip";
        case ElgTriangles:          return "triangles";
        case ElgTrianglesAdjacency: return "triangles_adjacency";
        case ElgTriangleStrip:      return "triangle_strip";
        case ElgQuads:              return "quads";
        case ElgIsolines:           return "isolines";
        default:                    return "none";
        }
    }
    static const char* getVertexSpacingString(TVertexSpacing spacing)
    {
        switch (spacing) {
        case EvsEqual:              return "equal_spacing";
        case EvsFractionalEven:     return "fractional_even_spacing";
        case EvsFractionalOdd:      return "fractional_odd_spacing";
        default:                    return "none";
        }
    }
    static const char* getVertexOrderString(TVertexOrder order)
    {
        switch (order) {
        case EvoCw:                 return "cw";
        case EvoCcw:                return "ccw";
        default:                    return "none";
        }
    }
    static int mapGeometryToSize(TLayoutGeometry geometry)
    {
        switch (geometry) {
        case ElgPoints:             return 1;
        case ElgLines:              return 2;
        case ElgLinesAdjacency:     return 4;
        case ElgTriangles:          return 3;
        case ElgTrianglesAdjacency: return 6;
        default:                    return 0;
        }
    }
};

// Qualifiers that don't need to be keep per object.  They have shader scope, not object scope.
// So, they will not be part of TType, TQualifier, etc.
struct TShaderQualifiers {
    TLayoutGeometry geometry; // geometry/tessellation shader in/out primitives
    bool pixelCenterInteger;  // fragment shader
    bool originUpperLeft;     // fragment shader
    int invocations;          // 0 means no declaration
    int vertices;             // both for tessellation "vertices" and geometry "max_vertices"
    TVertexSpacing spacing;
    TVertexOrder order;
    bool pointMode;

    void init()
    {
        geometry = ElgNone;
        originUpperLeft = false;
        pixelCenterInteger = false;
        invocations = 0;        // 0 means no declaration
        vertices = 0;
        spacing = EvsNone;
        order = EvoNone;
        pointMode = false;
    }

    // Merge in characteristics from the 'src' qualifier.  They can override when
    // set, but never erase when not set.
    void merge(const TShaderQualifiers& src)
    {
        if (src.geometry != ElgNone)
            geometry = src.geometry;
        if (src.pixelCenterInteger)
            pixelCenterInteger = src.pixelCenterInteger;
        if (src.originUpperLeft)
            originUpperLeft = src.originUpperLeft;
        if (src.invocations != 0)
            invocations = src.invocations;
        if (src.vertices != 0)
            vertices = src.vertices;
        if (src.spacing != EvsNone)
            spacing = src.spacing;
        if (src.order != EvoNone)
            order = src.order;
        if (src.pointMode)
            pointMode = true;
    }
};

//
// TPublicType is just temporarily used while parsing and not quite the same
// information kept per node in TType.  Due to the bison stack, it can't have
// types that it thinks have non-trivial constructors.  It should
// just be used while recognizing the grammar, not anything else.
// Once enough is known about the situation, the proper information
// moved into a TType, or the parse context, etc.
//
class TPublicType {
public:
    TBasicType basicType;
    TSampler sampler;
    TQualifier qualifier;
    TShaderQualifiers shaderQualifiers;
    int vectorSize : 4;
    int matrixCols : 4;
    int matrixRows : 4;
    TArraySizes* arraySizes;
    const TType* userDef;
    TSourceLoc loc;

    void initType(TSourceLoc l)
    {
        basicType = EbtVoid;
        vectorSize = 1;
        matrixRows = 0;
        matrixCols = 0;
        arraySizes = 0;
        userDef = 0;
        loc = l;
    }

    void initQualifiers(bool global = false)
    {
        qualifier.clear();
        if (global)
            qualifier.storage = EvqGlobal;
    }

    void init(TSourceLoc loc, bool global = false)
    {
        initType(loc);
        sampler.clear();
        initQualifiers(global);
        shaderQualifiers.init();
    }

    void setVector(int s)
    {
        matrixRows = 0;
        matrixCols = 0;
        vectorSize = s;
    }

    void setMatrix(int c, int r)
    {
        matrixRows = r;
        matrixCols = c;
        vectorSize = 0;
    }

    bool isScalar()
    {
        return matrixCols == 0 && vectorSize == 1 && arraySizes == 0 && userDef == 0;
    }
};

typedef std::map<TTypeList*, TTypeList*> TStructureMap;
typedef std::map<TTypeList*, TTypeList*>::const_iterator TStructureMapIterator;

//
// Base class for things that have a type.
//
class TType {
public:
    POOL_ALLOCATOR_NEW_DELETE(GetThreadPoolAllocator())

    // for "empty" type (no args) or simple scalar/vector/matrix
    explicit TType(TBasicType t = EbtVoid, TStorageQualifier q = EvqTemporary, int vs = 1, int mc = 0, int mr = 0) :
                            basicType(t), vectorSize(vs), matrixCols(mc), matrixRows(mr), arraySizes(0),
                            structure(0), fieldName(0), typeName(0)
                            {
                                sampler.clear();
                                qualifier.clear();
                                qualifier.storage = q;
                            }
    // for explicit precision qualifier
    TType(TBasicType t, TStorageQualifier q, TPrecisionQualifier p, int vs = 1, int mc = 0, int mr = 0) :
                            basicType(t), vectorSize(vs), matrixCols(mc), matrixRows(mr), arraySizes(0),
                            structure(0), fieldName(0), typeName(0)
                            {
                                sampler.clear();
                                qualifier.clear();
                                qualifier.storage = q;
                                qualifier.precision = p;
                                assert(p >= 0 && p <= EpqHigh);
                            }
    // for turning a TPublicType into a TType
    explicit TType(const TPublicType& p) :
                            basicType(p.basicType), vectorSize(p.vectorSize), matrixCols(p.matrixCols), matrixRows(p.matrixRows), arraySizes(p.arraySizes),
                            structure(0), fieldName(0), typeName(0)
                            {
                                if (basicType == EbtSampler)
                                    sampler = p.sampler;
                                else
                                    sampler.clear();
                                qualifier = p.qualifier;
                                if (p.userDef) {
                                    structure = p.userDef->getStruct();
                                    typeName = NewPoolTString(p.userDef->getTypeName().c_str());
                                }
                            }
    // to efficiently make a dereferenced type
    // without ever duplicating the outer structure that will be thrown away
    // and using only shallow copy
    TType(const TType& type, int derefIndex)
                            {
                                if (! type.isArray() && (type.basicType == EbtStruct || type.basicType == EbtBlock)) {
                                    // do a structure dereference
                                    const TTypeList& memberList = *type.getStruct();
                                    shallowCopy(*memberList[derefIndex].type);
                                    return;
                                } else {
                                    // do an array/vector/matrix dereference
                                    shallowCopy(type);
                                    dereference();
                                }
                            }
    // for making structures, ...
    TType(TTypeList* userDef, const TString& n) :
                            basicType(EbtStruct), vectorSize(1), matrixCols(0), matrixRows(0),
                            arraySizes(0), structure(userDef), fieldName(0)
                            {
                                sampler.clear();
                                qualifier.clear();
                                typeName = NewPoolTString(n.c_str());
                            }
    // For interface blocks
    TType(TTypeList* userDef, const TString& n, const TQualifier& q) : 
                            basicType(EbtBlock), vectorSize(1), matrixCols(0), matrixRows(0),
                            qualifier(q), arraySizes(0), structure(userDef), fieldName(0)
                            {
                                sampler.clear();
                                typeName = NewPoolTString(n.c_str());
                            }
    virtual ~TType() {}
    
    // Not for use across pool pops; it will cause multiple instances of TType to point to the same information.
    // This only works if that information (like a structure's list of types) does not change and 
    // the instances are sharing the same pool. 
    void shallowCopy(const TType& copyOf)
    {
        basicType = copyOf.basicType;
        sampler = copyOf.sampler;
        qualifier = copyOf.qualifier;
        vectorSize = copyOf.vectorSize;
        matrixCols = copyOf.matrixCols;
        matrixRows = copyOf.matrixRows;
        arraySizes = copyOf.arraySizes;
        structure = copyOf.structure;
        fieldName = copyOf.fieldName;
        typeName = copyOf.typeName;
    }

    void deepCopy(const TType& copyOf)
    {
        shallowCopy(copyOf);

        if (arraySizes) {
            arraySizes = new TArraySizes;
            *arraySizes = *copyOf.arraySizes;
        }

        if (structure) {
            structure = new TTypeList;
            TStructureMapIterator iter;
            for (unsigned int i = 0; i < copyOf.structure->size(); ++i) {
                TTypeLoc typeLoc;
                typeLoc.loc = (*copyOf.structure)[i].loc;
                typeLoc.type = new TType();
                typeLoc.type->deepCopy(*(*copyOf.structure)[i].type);
                structure->push_back(typeLoc);
            }
        }

        if (fieldName)
            fieldName = NewPoolTString(copyOf.fieldName->c_str());
        if (typeName)
            typeName = NewPoolTString(copyOf.typeName->c_str());
    }
    
    TType* clone()
    {
        TType *newType = new TType();
        newType->deepCopy(*this);

        return newType;
    }

    // Merge type from parent, where a parentType is at the beginning of a declaration,
    // establishing some charastics for all subsequent names, while this type
    // is on the individual names.
    void mergeType(const TPublicType& parentType)
    {
        // arrayness is currently the only child aspect that has to be preserved
        setElementType(parentType.basicType, parentType.vectorSize, parentType.matrixCols, parentType.matrixRows, parentType.userDef);
        qualifier = parentType.qualifier;
        sampler = parentType.sampler;
        if (parentType.arraySizes)
            setArraySizes(parentType.arraySizes);
        if (parentType.userDef)
            setTypeName(parentType.userDef->getTypeName());
    }

    virtual void dereference()
    {
        if (arraySizes)
            arraySizes = 0;
        else if (matrixCols > 0) {
            vectorSize = matrixRows;
            matrixCols = 0;
            matrixRows = 0;
        } else if (vectorSize > 1)
            vectorSize = 1;
    }

    virtual void setElementType(TBasicType t, int s, int mc, int mr, const TType* userDef)
    {
        basicType = t;
        vectorSize = s;
        matrixCols = mc;
        matrixRows = mr;
        if (userDef)
            structure = userDef->getStruct();
        // leave array information intact.
    }
    virtual void setTypeName(const TString& n) { typeName = NewPoolTString(n.c_str()); }
    virtual void setFieldName(const TString& n) { fieldName = NewPoolTString(n.c_str()); }
    virtual const TString& getTypeName() const
    {
        assert(typeName);    		
        return *typeName;
    }

    virtual const TString& getFieldName() const
    {
        assert(fieldName);
        return *fieldName;
    }

    virtual TBasicType getBasicType() const { return basicType; }
    virtual const TSampler& getSampler() const { return sampler; }
    virtual TQualifier& getQualifier() { return qualifier; }
    virtual const TQualifier& getQualifier() const { return qualifier; }

    virtual int getVectorSize() const { return vectorSize; }
    virtual int getMatrixCols() const { return matrixCols; }
    virtual int getMatrixRows() const { return matrixRows; }

    virtual bool isScalar() const { return vectorSize == 1 && ! isStruct() && ! isArray(); }
    virtual bool isVector() const { return vectorSize > 1; }
    virtual bool isMatrix() const { return matrixCols ? true : false; }
    virtual bool isArray()  const { return arraySizes != 0; }
    virtual bool isStruct() const { return structure != 0; }

    // Recursively checks if the type contains the given basic type
    virtual bool containsBasicType(TBasicType checkType) const
    {
        if (basicType == checkType)
            return true;
        if (! structure)
            return false;
        for (unsigned int i = 0; i < structure->size(); ++i) {
            if ((*structure)[i].type->containsBasicType(checkType))
                return true;
        }
        return false;
    }

    // Recursively check the structure for any arrays, needed for some error checks
    virtual bool containsArray() const
    {
        if (isArray())
            return true;
        if (! structure)
            return false;
        for (unsigned int i = 0; i < structure->size(); ++i) {
            if ((*structure)[i].type->containsArray())
                return true;
        }
        return false;
    }
    int getArraySize() const { return arraySizes->sizes.front(); }
    void shareArraySizes(const TType& type)
    {
        // For when we are sharing existing array descriptors.
        // This allows all references to the same unsized array
        // to be updated at once, by having all of them share the
        // array description.
        *arraySizes = *type.arraySizes;
    }
    void setArraySizes(TArraySizes* s)
    {
        // For when we don't want distinct types sharing the same descriptor.
        arraySizes = new TArraySizes;
        *arraySizes = *s;
    }
    void setArraySizes(const TType& type) { setArraySizes(type.arraySizes); }
    
    void changeArraySize(int s) { arraySizes->sizes.front() = s; }
    void setMaxArraySize (int s) { arraySizes->maxArraySize = s; }
    int getMaxArraySize () const { return arraySizes->maxArraySize; }
    const char* getBasicString() const 
    {
        return TType::getBasicString(basicType);
    }
    
    static const char* getBasicString(TBasicType t)
    {
        switch (t) {
        case EbtVoid:              return "void";
        case EbtFloat:             return "float";
        case EbtDouble:            return "double";
        case EbtInt:               return "int";
        case EbtUint:              return "uint";
        case EbtBool:              return "bool";
        case EbtSampler:           return "sampler/image";
        case EbtStruct:            return "structure";
        case EbtBlock:             return "block";
        default:                   return "unknown type";
        }
    }

    TString getCompleteString() const
    {
        const int maxSize = GlslangMaxTypeLength;
        char buf[maxSize];
        char* p = &buf[0];
        char* end = &buf[maxSize];

        if (qualifier.hasLayout()) {
            // To reduce noise, skip this if the only layout is an xfb_buffer
            // with no triggering xfb_offset.
            TQualifier noXfbBuffer = qualifier;
            noXfbBuffer.layoutXfbBuffer = TQualifier::layoutXfbBufferEnd;
            if (noXfbBuffer.hasLayout()) {
                p += snprintf(p, end - p, "layout(");
                if (qualifier.hasLocation()) {
                    p += snprintf(p, end - p, "location=%d ", qualifier.layoutLocation);
                    if (qualifier.layoutComponent != qualifier.layoutComponentEnd)
                        p += snprintf(p, end - p, "component=%d ", qualifier.layoutComponent);
                }
                if (qualifier.hasBinding())
                    p += snprintf(p, end - p, "binding=%d ", qualifier.layoutBinding);
                if (qualifier.hasStream())
                    p += snprintf(p, end - p, "stream=%d ", qualifier.layoutStream);
                if (qualifier.hasMatrix())
                    p += snprintf(p, end - p, "%s ", TQualifier::getLayoutMatrixString(qualifier.layoutMatrix));
                if (qualifier.hasPacking())
                    p += snprintf(p, end - p, "%s ", TQualifier::getLayoutPackingString(qualifier.layoutPacking));
                if (qualifier.hasOffset())
                    p += snprintf(p, end - p, "offset=%d ", qualifier.layoutOffset);
                if (qualifier.hasAlign())
                    p += snprintf(p, end - p, "align=%d ", qualifier.layoutAlign);

                if (qualifier.hasXfbBuffer() && qualifier.hasXfbOffset())
                    p += snprintf(p, end - p, "xfb_buffer=%d ", qualifier.layoutXfbBuffer);
                if (qualifier.hasXfbOffset())
                    p += snprintf(p, end - p, "xfb_offset=%d ", qualifier.layoutXfbOffset);
                if (qualifier.hasXfbStride())
                    p += snprintf(p, end - p, "xfb_stride=%d ", qualifier.layoutXfbStride);
                p += snprintf(p, end - p, ") ");
            }
        }

        if (qualifier.invariant)
            p += snprintf(p, end - p, "invariant ");
        if (qualifier.centroid)
            p += snprintf(p, end - p, "centroid ");
        if (qualifier.smooth)
            p += snprintf(p, end - p, "smooth ");
        if (qualifier.flat)
            p += snprintf(p, end - p, "flat ");
        if (qualifier.nopersp)
            p += snprintf(p, end - p, "noperspective ");
        if (qualifier.patch)
            p += snprintf(p, end - p, "patch ");
        if (qualifier.sample)
            p += snprintf(p, end - p, "sample ");
        if (qualifier.shared)
            p += snprintf(p, end - p, "shared ");
        if (qualifier.coherent)
            p += snprintf(p, end - p, "coherent ");
        if (qualifier.volatil)
            p += snprintf(p, end - p, "volatile ");
        if (qualifier.restrict)
            p += snprintf(p, end - p, "restrict ");
        if (qualifier.readonly)
            p += snprintf(p, end - p, "readonly ");
        if (qualifier.writeonly)
            p += snprintf(p, end - p, "writeonly ");
        if (qualifier.storage != EvqTemporary && qualifier.storage != EvqGlobal)
            p += snprintf(p, end - p, "%s ", getStorageQualifierString());
        if (arraySizes) {
            if (arraySizes->sizes.front() == 0)
                p += snprintf(p, end - p, "unsized array of ");
            else
                p += snprintf(p, end - p, "%d-element array of ", arraySizes->sizes.front());
        }
        if (qualifier.precision != EpqNone)
            p += snprintf(p, end - p, "%s ", getPrecisionQualifierString());
        if (matrixCols > 0)
            p += snprintf(p, end - p, "%dX%d matrix of ", matrixCols, matrixRows);
        else if (vectorSize > 1)
            p += snprintf(p, end - p, "%d-component vector of ", vectorSize);

        *p = 0;
        TString s(buf);
        s.append(getBasicTypeString());

        // Add struct/block members
        if (structure) {
            s.append("{");
            for (size_t i = 0; i < structure->size(); ++i) {
                if ((*structure)[i].type->getBasicType() != EbtVoid) {
                    s.append((*structure)[i].type->getCompleteString());
                    s.append(" ");
                    s.append((*structure)[i].type->getFieldName());
                    if (i < structure->size() - 1)
                        s.append(", ");
                }
            }
            s.append("}");
        }

        return s;
    }

    TString getBasicTypeString() const
    {
        if (basicType == EbtSampler)
            return sampler.getString();
        else
            return getBasicString();
    }

    const char* getStorageQualifierString() const { return GetStorageQualifierString(qualifier.storage); }
    const char* getPrecisionQualifierString() const { return GetPrecisionQualifierString(qualifier.precision); }
    TTypeList* getStruct() { return structure; }
    TTypeList* getStruct() const { return structure; }

    int computeNumComponents() const
    {
        int components = 0;

        if (getBasicType() == EbtStruct || getBasicType() == EbtBlock) {
            for (TTypeList::iterator tl = getStruct()->begin(); tl != getStruct()->end(); tl++)
                components += ((*tl).type)->computeNumComponents();
        } else if (matrixCols)
            components = matrixCols * matrixRows;
        else
            components = vectorSize;

        if (isArray()) {
            // this function can only be used in paths that don't allow unsized arrays
            assert(getArraySize() > 0);
            components *= getArraySize();
        }

        return components;
    }

    // append this type's mangled name to the passed in 'name'
    void appendMangledName(TString& name)
    {
        buildMangledName(name);
        name += ';' ;
    }

    // Do two structure types match?  They could be declared independently,
    // in different places, but still might satisfy the definition of matching.
    // From the spec:
    //
    // "Structures must have the same name, sequence of type names, and 
    //  type definitions, and member names to be considered the same type. 
    //  This rule applies recursively for nested or embedded types."
    //
    bool sameStructType(const TType& right) const
    {
        // Most commonly, they are both 0, or the same pointer to the same actual structure
        if (structure == right.structure)
            return true;

        // Both being 0 was caught above, now they both have to be structures of the same number of elements
        if (structure == 0 || right.structure == 0 ||
            structure->size() != right.structure->size())
            return false;

        // Structure names have to match
        if (*typeName != *right.typeName)
            return false;

        // Compare the names and types of all the members, which have to match
        for (unsigned int i = 0; i < structure->size(); ++i) {
            if ((*structure)[i].type->getFieldName() != (*right.structure)[i].type->getFieldName())
                return false;

            if (*(*structure)[i].type != *(*right.structure)[i].type)
                return false;
        }

        return true;
    }

    // See if two types match, in all aspects except arrayness
    bool sameElementType(const TType& right) const
    {
        return basicType == right.basicType && sameElementShape(right);
    }

    // See if two type's arrayness match
    bool sameArrayness(const TType& right) const
    {
        return ((arraySizes == 0 && right.arraySizes == 0) ||
                (arraySizes && right.arraySizes && arraySizes->sizes == right.arraySizes->sizes));
    }

    // See if two type's elements match in all ways except basic type
    bool sameElementShape(const TType& right) const
    {
        return    sampler == right.sampler    &&
               vectorSize == right.vectorSize &&
               matrixCols == right.matrixCols &&
               matrixRows == right.matrixRows &&
               sameStructType(right);
    }

    // See if two types match in all ways (just the actual type, not qualification)
    bool operator==(const TType& right) const
    {
        return sameElementType(right) && sameArrayness(right);
    }

    bool operator!=(const TType& right) const
    {
        return ! operator==(right);
    }

protected:
    // Require consumer to pick between deep copy and shallow copy.
    TType(const TType& type);
    TType& operator=(const TType& type);

    void buildMangledName(TString&);

    TBasicType basicType : 8;
    int vectorSize       : 4;
    int matrixCols       : 4;
    int matrixRows       : 4;
    TSampler sampler;
    TQualifier qualifier;

    TArraySizes* arraySizes;

    TTypeList* structure;       // 0 unless this is a struct
    TString *fieldName;         // for structure field names
    TString *typeName;          // for structure type name
};

} // end namespace glslang

#endif // _TYPES_INCLUDED_
