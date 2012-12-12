//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
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

#ifndef _CONSTANT_UNION_INCLUDED_
#define _CONSTANT_UNION_INCLUDED_


class constUnion {
public:

    POOL_ALLOCATOR_NEW_DELETE(GlobalPoolAllocator)        
    void setIConst(int i) {iConst = i; type = EbtInt; }
    void setFConst(float f) {fConst = f; type = EbtFloat; }
    void setBConst(bool b) {bConst = b; type = EbtBool; }

    int getIConst() { return iConst; }
    float getFConst() { return fConst; }
    bool getBConst() { return bConst; }
    int getIConst() const { return iConst; }
    float getFConst() const { return fConst; }
    bool getBConst() const { return bConst; }

    bool operator==(const int i) const
    {
        if (i == iConst)
            return true;

        return false;
    }

    bool operator==(const float f) const
    {
        if (f == fConst)
            return true;

        return false;
    }

    bool operator==(const bool b) const
    {
        if (b == bConst)
            return true;

        return false;
    }

    bool operator==(const constUnion& constant) const
    {
        if (constant.type != type)
            return false;

        switch (type) {
        case EbtInt:
            if (constant.iConst == iConst)
                return true;

            break;
        case EbtFloat:
            if (constant.fConst == fConst)
                return true;

            break;
        case EbtBool:
            if (constant.bConst == bConst)
                return true;

            break;
        }

        return false;
    }

    bool operator!=(const int i) const
    {
        return !operator==(i);
    }

    bool operator!=(const float f) const
    {
        return !operator==(f);
    }

    bool operator!=(const bool b) const
    {
        return !operator==(b);
    }

    bool operator!=(const constUnion& constant) const
    {
        return !operator==(constant);
    }

    bool operator>(const constUnion& constant) const
    { 
        assert(type == constant.type);
        switch (type) {
        case EbtInt:
            if (iConst > constant.iConst)
                return true;

            return false;
        case EbtFloat:
            if (fConst > constant.fConst)
                return true;

            return false;
        default:
            assert(false && "Default missing");
            return false;
        }

        return false;
    }

    bool operator<(const constUnion& constant) const
    { 
        assert(type == constant.type);
        switch (type) {
        case EbtInt:
            if (iConst < constant.iConst)
                return true;

            return false;
        case EbtFloat:
            if (fConst < constant.fConst)
                return true;

            return false;
        default:
            assert(false && "Default missing");
            return false;
        }

        return false;
    }

    constUnion operator+(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtInt: returnValue.setIConst(iConst + constant.iConst); break;
        case EbtFloat: returnValue.setFConst(fConst + constant.fConst); break;
        default: assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator-(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtInt: returnValue.setIConst(iConst - constant.iConst); break;
        case EbtFloat: returnValue.setFConst(fConst - constant.fConst); break;
        default: assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator*(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtInt: returnValue.setIConst(iConst * constant.iConst); break;
        case EbtFloat: returnValue.setFConst(fConst * constant.fConst); break; 
        default: assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator%(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtInt: returnValue.setIConst(iConst % constant.iConst); break;
        default:     assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator>>(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtInt: returnValue.setIConst(iConst >> constant.iConst); break;
        default:     assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator<<(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtInt: returnValue.setIConst(iConst << constant.iConst); break;
        default:     assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator&(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtInt:  returnValue.setIConst(iConst & constant.iConst); break;
        default:     assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator|(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtInt:  returnValue.setIConst(iConst | constant.iConst); break;
        default:     assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator^(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtInt:  returnValue.setIConst(iConst ^ constant.iConst); break;
        default:     assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator&&(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtBool: returnValue.setBConst(bConst && constant.bConst); break;
        default:     assert(false && "Default missing");
        }

        return returnValue;
    }

    constUnion operator||(const constUnion& constant) const
    { 
        constUnion returnValue;
        assert(type == constant.type);
        switch (type) {
        case EbtBool: returnValue.setBConst(bConst || constant.bConst); break;
        default:     assert(false && "Default missing");
        }

        return returnValue;
    }

    TBasicType getType() { return type; }
private:

    union  {
        int iConst;  // used for ivec, scalar ints
        bool bConst; // used for bvec, scalar bools
        float fConst;   // used for vec, mat, scalar floats
    } ;

    TBasicType type;
};

#endif // _CONSTANT_UNION_INCLUDED_
