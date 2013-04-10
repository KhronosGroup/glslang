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

    void clear()
    {
        type = EbtVoid;
        dim = EsdNone;
        arrayed = false;
        shadow = false;
        ms = false;
        image = false;
    }

    void set(TBasicType t, TSamplerDim d, bool a = false, bool s = false, bool m = false)
    {
        type = t;
        dim = d;
        arrayed = a;
        shadow = s;
        ms = m;
        image = false;
    }

    void setImage(TBasicType t, TSamplerDim d, bool a = false, bool s = false, bool m = false)
    {
        type = t;
        dim = d;
        arrayed = a;
        shadow = s;
        ms = m;
        image = true;
    }

    bool operator==(const TSampler& right) const
    {
        return type == right.type &&
                dim == right.dim &&
            arrayed == right.arrayed &&
             shadow == right.shadow &&
                 ms == right.ms &&
              image == right.image;
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
struct TTypeLine {
    TType* type;
    int line;
};
typedef TVector<TTypeLine> TTypeList;

inline TTypeList* NewPoolTTypeList()
{
	void* memory = GlobalPoolAllocator.allocate(sizeof(TTypeList));
	return new(memory) TTypeList;
}

//
// TODO: TArraySizes memory: This could be replaced by something smaller.
// Almost all arrays could be handled by two sizes each fitting
// in 16 bits, needing a real vector only in the cases where there
// are more than 3 sizes or a size needing more than 16 bits.
//
// The type is a pointer, so that it can be non-allocated and zero
// for the vast majority of non-array types.  Note that means if it
// is used, it will be containing at least one size.

typedef TVector<int>* TArraySizes;

inline TArraySizes NewPoolTArraySizes()
{
    void* memory = GlobalPoolAllocator.allocate(sizeof(TVector<int>));
    return new(memory) TVector<int>;
}

//
// TPublicType (coming up after some dependent declarations)
// is a workaround for a problem with the yacc stack,  It can't have
// types that it thinks have non-trivial constructors.  It should
// just be used while recognizing the grammar, not anything else.  Pointers
// could be used, but also trying to avoid lots of memory management overhead.
//
// Not as bad as it looks, there is no actual assumption that the fields
// match up or are named the same or anything like that.
//

enum TLayoutPacking {
    ElpNone,
    ElpShared,      // default, but different than saying nothing
    ElpStd140,
    ElpStd430,
    ElpPacked       // see bitfield width below
};

enum TLayoutMatrix {
    ElmNone,
    ElmRowMajor,
    ElmColumnMajor  // default, but different than saying nothing
};  // see bitfield width below

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

    bool isMemory()
    {
        return coherent || volatil || restrict || readonly || writeonly;
    }
    bool isInterpolation()
    {
        return flat || smooth || nopersp;
    }
    bool isAuxillary()
    {
        return centroid || patch || sample;
    }

    // Implementing an embedded layout-qualifier class here, since C++ can't have a real class bitfield
    void clearLayout()
    {
        layoutMatrix = ElmNone;
        layoutPacking = ElpNone;
        layoutSlotLocation = layoutLocationEnd;
    }
    bool hasLayout() const
    {
        return layoutMatrix != ElmNone ||
               layoutPacking != ElpNone ||
               layoutSlotLocation != layoutLocationEnd;
    }
    TLayoutMatrix  layoutMatrix       : 3;
    TLayoutPacking layoutPacking      : 4;
    unsigned int   layoutSlotLocation : 7;  // ins/outs should have small numbers, buffer offsets could be large
    static const unsigned int layoutLocationEnd = 0x3F;
    bool hasLocation() const
    {
        return layoutSlotLocation != layoutLocationEnd;
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
};

class TPublicType {
public:
    TBasicType type;
    TSampler sampler;
    TQualifier qualifier;
    int vectorSize : 4;
    int matrixCols : 4;
    int matrixRows : 4;
    TArraySizes arraySizes;
    const TType* userDef;
    int line;

    void initType(int ln = 0)
    {
        type = EbtVoid;
        vectorSize = 1;
        matrixRows = 0;
        matrixCols = 0;
        arraySizes = 0;
        userDef = 0;
        line = ln;
    }

    void initQualifiers(bool global = false)
    {
        qualifier.clear();
        if (global)
            qualifier.storage = EvqGlobal;
    }

    void init(int line = 0, bool global = false)
    {
        initType(line);
        sampler.clear();
        initQualifiers(global);
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
    POOL_ALLOCATOR_NEW_DELETE(GlobalPoolAllocator)
    TType(TBasicType t, TStorageQualifier q = EvqTemporary, int vs = 1, int mc = 0, int mr = 0) :
                            type(t), vectorSize(vs), matrixCols(mc), matrixRows(mr), arraySizes(0),
                            structure(0), structureSize(0), maxArraySize(0), arrayInformationType(0),
                            fieldName(0), mangled(0), typeName(0)
                            {
                                sampler.clear();
                                qualifier.clear();
                                qualifier.storage = q;
                            }
    TType(TBasicType t, TStorageQualifier q, TPrecisionQualifier p, int vs = 1, int mc = 0, int mr = 0) :
                            type(t), vectorSize(vs), matrixCols(mc), matrixRows(mr), arraySizes(0),
                            structure(0), structureSize(0), maxArraySize(0), arrayInformationType(0),
                            fieldName(0), mangled(0), typeName(0)
                            {
                                sampler.clear();
                                qualifier.clear();
                                qualifier.storage = q;
                                qualifier.precision = p;
                                assert(p >= 0 && p <= EpqHigh);
                            }
    explicit TType(const TPublicType &p) :
                            type(p.type), vectorSize(p.vectorSize), matrixCols(p.matrixCols), matrixRows(p.matrixRows), arraySizes(p.arraySizes),
                            structure(0), structureSize(0), maxArraySize(0), arrayInformationType(0), fieldName(0), mangled(0), typeName(0)
                            {
                                sampler = p.sampler;
                                qualifier = p.qualifier;
                                if (p.userDef) {
                                    structure = p.userDef->getStruct();
                                    typeName = NewPoolTString(p.userDef->getTypeName().c_str());
                                }
                            }
    TType(TTypeList* userDef, const TString& n, TStorageQualifier blockQualifier = EvqGlobal) :
                            type(EbtStruct), vectorSize(1), matrixCols(0), matrixRows(0), arraySizes(0),
                            structure(userDef), maxArraySize(0), arrayInformationType(0), fieldName(0), mangled(0)
                            {
                                sampler.clear();
                                qualifier.clear();
                                // is it an interface block?
                                if (blockQualifier != EvqGlobal) {
                                    qualifier.storage = blockQualifier;
                                    type = EbtBlock;
                                }
								typeName = NewPoolTString(n.c_str());
                            }
	TType() {}
    virtual ~TType() {}

	TType(const TType& type) { *this = type; }

	void copyType(const TType& copyOf, const TStructureMap& remapper)
	{
		type = copyOf.type;
        sampler = copyOf.sampler;
		qualifier = copyOf.qualifier;
		vectorSize = copyOf.vectorSize;
		matrixCols = copyOf.matrixCols;
		matrixRows = copyOf.matrixRows;

        if (copyOf.arraySizes) {
            arraySizes = NewPoolTArraySizes();
            *arraySizes = *copyOf.arraySizes;
        } else
            arraySizes = 0;

		TStructureMapIterator iter;
		if (copyOf.structure) {
	        if ((iter = remapper.find(structure)) == remapper.end()) {
				// create the new structure here
				structure = NewPoolTTypeList();
				for (unsigned int i = 0; i < copyOf.structure->size(); ++i) {
					TTypeLine typeLine;
					typeLine.line = (*copyOf.structure)[i].line;
					typeLine.type = (*copyOf.structure)[i].type->clone(remapper);
					structure->push_back(typeLine);
				}
			} else {
				structure = iter->second;
			}
		} else
			structure = 0;

		fieldName = 0;
		if (copyOf.fieldName)
			fieldName = NewPoolTString(copyOf.fieldName->c_str());
		typeName = 0;
		if (copyOf.typeName)
			typeName = NewPoolTString(copyOf.typeName->c_str());
		
		mangled = 0;
		if (copyOf.mangled)
			mangled = NewPoolTString(copyOf.mangled->c_str());

		structureSize = copyOf.structureSize;
		maxArraySize = copyOf.maxArraySize;
		assert(copyOf.arrayInformationType == 0);
		arrayInformationType = 0; // arrayInformationType should not be set for builtIn symbol table level
	}

	TType* clone(const TStructureMap& remapper)
	{
		TType *newType = new TType();
		newType->copyType(*this, remapper);

		return newType;
	}

    virtual void dereference()
    {
        if (arraySizes) {
            arraySizes = 0;
            maxArraySize = 0;
        } else if (matrixCols > 0) {
            vectorSize = matrixRows;
            matrixCols = 0;
            matrixRows = 0;
        } else if (vectorSize > 1)
            vectorSize = 1;
    }

    virtual void setElementType(TBasicType t, int s, int mc, int mr, const TType* userDef)
    {
        type = t;
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

    virtual TBasicType getBasicType() const { return type; }
    virtual const TSampler& getSampler() const { return sampler; }
    virtual TQualifier& getQualifier() { return qualifier; }
    virtual const TQualifier& getQualifier() const { return qualifier; }

    virtual int getVectorSize() const { return vectorSize; }
    virtual int getMatrixCols() const { return matrixCols; }
    virtual int getMatrixRows() const { return matrixRows; }

	virtual bool isMatrix() const { return matrixCols ? true : false; }
    virtual bool isArray() const  { return arraySizes != 0; }
    int getArraySize() const { return arraySizes->front(); }
    void setArraySizes(TArraySizes s) {
        // copy; we don't want distinct types sharing the same descriptor
        if (! arraySizes)
            arraySizes = NewPoolTArraySizes();
        *arraySizes = *s;
    }
    void changeArraySize(int s) { arraySizes->front() = s; }
    void setMaxArraySize (int s) { maxArraySize = s; }
    int getMaxArraySize () const { return maxArraySize; }
    void setArrayInformationType(TType* t) { arrayInformationType = t; }
    TType* getArrayInformationType() { return arrayInformationType; }
    virtual bool isVector() const { return vectorSize > 1; }
    const char* getBasicString() const {
        return TType::getBasicString(type);
    }
    static const char* getBasicString(TBasicType t) {
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
	    const int maxSize = 200;
        char buf[maxSize];
        char *p = &buf[0];
	    char *end = &buf[maxSize];

        if (qualifier.hasLayout()) {
            p += snprintf(p, end - p, "layout(");
            if (qualifier.hasLocation())
                p += snprintf(p, end - p, "location=%d ", qualifier.layoutSlotLocation);
            if (qualifier.layoutMatrix != ElmNone)
                p += snprintf(p, end - p, "%s ", TQualifier::getLayoutMatrixString(qualifier.layoutMatrix));
            if (qualifier.layoutPacking != ElpNone)
                p += snprintf(p, end - p, "%s ", TQualifier::getLayoutPackingString(qualifier.layoutPacking));
            p += snprintf(p, end - p, ") ");
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
            if (arraySizes->front() == 0)
                p += snprintf(p, end - p, "unsized array of ");
            else
                p += snprintf(p, end - p, "%d-element array of ", arraySizes->front());
        }
        if (qualifier.precision != EpqNone)
            p += snprintf(p, end - p, "%s ", getPrecisionQualifierString());
        if (matrixCols > 0)
            p += snprintf(p, end - p, "%dX%d matrix of ", matrixCols, matrixRows);
        else if (vectorSize > 1)
            p += snprintf(p, end - p, "%d-component vector of ", vectorSize);

        *p = 0;
        TString s(buf);
        s.append(getCompleteTypeString());

        return s;
    }

    TString getCompleteTypeString() const
    {
        if (type == EbtSampler)
            return sampler.getString();
        else
            return getBasicString();
    }

    const char* getStorageQualifierString() const { return ::getStorageQualifierString(qualifier.storage); }
    const char* getPrecisionQualifierString() const { return ::getPrecisionQualifierString(qualifier.precision); }
    TTypeList* getStruct() { return structure; }

    int getObjectSize() const
    {
        int totalSize;

        if (getBasicType() == EbtStruct || getBasicType() == EbtBlock)
            totalSize = getStructSize();
        else if (matrixCols)
            totalSize = matrixCols * matrixRows;
        else
            totalSize = vectorSize;

        if (isArray())
            totalSize *= Max(getArraySize(), getMaxArraySize());

        return totalSize;
    }

    TTypeList* getStruct() const { return structure; }
    TString& getMangledName()
    {
        if (!mangled) {
			mangled = NewPoolTString("");
            buildMangledName(*mangled);
            *mangled += ';' ;
        }

        return *mangled;
    }

    bool sameElementType(const TType& right) const
    {
        return       type == right.type       &&
                  sampler == right.sampler    &&
               vectorSize == right.vectorSize &&
               matrixCols == right.matrixCols &&
               matrixRows == right.matrixRows &&
                structure == right.structure;
    }

    bool operator==(const TType& right) const
    {
        return sameElementType(right) &&
               (arraySizes == 0 && right.arraySizes == 0 ||
                (arraySizes && right.arraySizes && *arraySizes == *right.arraySizes));
        // don't check the qualifier, it's not ever what's being sought after
    }

    bool operator!=(const TType& right) const
    {
        return !operator==(right);
    }

protected:
    void buildMangledName(TString&);
    int getStructSize() const;

	TBasicType type      : 8;
    int vectorSize       : 4;
    int matrixCols       : 4;
    int matrixRows       : 4;
    TSampler sampler;
    TQualifier qualifier;

    TArraySizes arraySizes;

    TTypeList* structure;      // 0 unless this is a struct
    mutable int structureSize;
    int maxArraySize;
    TType* arrayInformationType;
	TString *fieldName;         // for structure field names
    TString *mangled;
	TString *typeName;          // for structure field type name
};

#endif // _TYPES_INCLUDED_
