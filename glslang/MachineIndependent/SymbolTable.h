//
//Copyright (C) 2002-2005  3Dlabs Inc. Ltd.
//Copyright (C) 2013 LunarG, Inc.
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

#ifndef _SYMBOL_TABLE_INCLUDED_
#define _SYMBOL_TABLE_INCLUDED_

//
// Symbol table for parsing.  Has these design characteristics:
//
// * Same symbol table can be used to compile many shaders, to preserve
//   effort of creating and loading with the large numbers of built-in
//   symbols.
//
// -->  This requires a copy mechanism, so initial pools used to create
//   the shared information can be popped.  So, care is taken with
//   copying pointers to point to new copies.  Done through "clone"
//   methods.
//
// * Name mangling will be used to give each function a unique name
//   so that symbol table lookups are never ambiguous.  This allows
//   a simpler symbol table structure.
//
// * Pushing and popping of scope, so symbol table will really be a stack
//   of symbol tables.  Searched from the top, with new inserts going into
//   the top.
//
// * Constants:  Compile time constant symbols will keep their values
//   in the symbol table.  The parser can substitute constants at parse
//   time, including doing constant folding and constant propagation.
//
// * No temporaries:  Temporaries made from operations (+, --, .xy, etc.)
//   are tracked in the intermediate representation, not the symbol table.
//

#include "../Include/Common.h"
#include "../Include/intermediate.h"
#include "../Include/InfoSink.h"

namespace glslang {

//
// Symbol base class.  (Can build functions or variables out of these...)
//
class TVariable;
class TFunction;
class TAnonMember;
class TSymbol {
public:
    POOL_ALLOCATOR_NEW_DELETE(GetThreadPoolAllocator())
    explicit TSymbol(const TString *n) :  name(n), writable(true) { }
	virtual TSymbol* clone() = 0;
    virtual ~TSymbol() { }

    const TString& getName() const { return *name; }
    void changeName(const TString* newName) { name = newName; }
    virtual const TString& getMangledName() const { return getName(); }
    virtual TFunction* getAsFunction() { return 0; }
    virtual const TFunction* getAsFunction() const { return 0; }
    virtual TVariable* getAsVariable() { return 0; }
    virtual const TVariable* getAsVariable() const { return 0; }
    virtual const TAnonMember* getAsAnonMember() const { return 0; }
    void setUniqueId(int id) { uniqueId = id; }
    int getUniqueId() const { return uniqueId; }
    virtual void dump(TInfoSink &infoSink) const = 0;

    bool isReadOnly() { return ! writable; }
    void makeReadOnly() { writable = false; }

protected:
	explicit TSymbol(const TSymbol&);
    TSymbol& operator=(const TSymbol&);

    const TString *name;
    unsigned int uniqueId;      // For cross-scope comparing during code generation

    //
    // N.B.: Non-const functions that will be generally used should assert an this,
    // to avoid overwriting shared symbol-table information.
    //
    bool writable;
};

//
// Variable class, meaning a symbol that's not a function.
//
// There could be a separate class heirarchy for Constant variables;
// Only one of int, bool, or float, (or none) is correct for
// any particular use, but it's easy to do this way, and doesn't
// seem worth having separate classes, and "getConst" can't simply return
// different values for different types polymorphically, so this is
// just simple and pragmatic.
//
class TVariable : public TSymbol {
public:
    TVariable(const TString *name, const TType& t, bool uT = false ) : TSymbol(name), userType(uT) { type.shallowCopy(t); }
	virtual TVariable* clone();
    virtual ~TVariable() { }

    virtual TVariable* getAsVariable() { return this; }
    virtual const TVariable* getAsVariable() const { return this; }
    TType& getWritableType() { assert(writable); return type; }
    const TType& getType() const { return type; }
    bool isUserType() const { return userType; }

    virtual void dump(TInfoSink &infoSink) const;

    const TConstUnionArray& getConstArray() const { return unionArray; }
    void setConstArray(const TConstUnionArray& constArray) { unionArray = constArray; }

protected:
    explicit TVariable(const TVariable&);
    TVariable& operator=(const TVariable&);

    TType type;
    bool userType;
    // we are assuming that Pool Allocator will free the memory allocated to unionArray
    // when this object is destroyed
    TConstUnionArray unionArray;
};

//
// The function sub-class of symbols and the parser will need to
// share this definition of a function parameter.
//
struct TParameter {
    TString *name;
    TType* type;
	void copyParam(const TParameter& param) 
    {
		if (param.name)
            name = NewPoolTString(param.name->c_str());
        else
            name = 0;
		type = param.type->clone();
	}
};

//
// The function sub-class of a symbol.
//
class TFunction : public TSymbol {
public:
    explicit TFunction(TOperator o) :
        TSymbol(0),
        op(o),
        defined(false) { }
    TFunction(const TString *name, const TType& retType, TOperator tOp = EOpNull) :
        TSymbol(name),
        mangledName(*name + '('),
        op(tOp),
        defined(false) { returnType.shallowCopy(retType); }    
	virtual TFunction* clone();
	virtual ~TFunction();

    virtual TFunction* getAsFunction() { return this; }
    virtual const TFunction* getAsFunction() const { return this; }

    void addParameter(TParameter& p)
    {
        assert(writable);
        parameters.push_back(p);
        p.type->appendMangledName(mangledName);
    }

    const TString& getMangledName() const { return mangledName; }
    const TType& getReturnType() const { return returnType; }
    void relateToOperator(TOperator o) { assert(writable); op = o; }
    TOperator getBuiltInOp() const { return op; }
    void setDefined() { assert(writable); defined = true; }
    bool isDefined() const { return defined; }

    int getParamCount() const { return static_cast<int>(parameters.size()); }
    TParameter& operator [](int i) { assert(writable); return parameters[i]; }
    const TParameter& operator [](int i) const { return parameters[i]; }

    virtual void dump(TInfoSink &infoSink) const;

protected:
    explicit TFunction(const TFunction&);
    TFunction& operator=(TFunction&);

    typedef TVector<TParameter> TParamList;
	TParamList parameters;
    TType returnType;
    TString mangledName;
    TOperator op;
    bool defined;
};

class TAnonMember : public TSymbol {
public:
    TAnonMember(const TString* n, unsigned int m, TSymbol& a) : TSymbol(n), anonContainer(a), memberNumber(m) { }
	virtual TAnonMember* clone();
    virtual ~TAnonMember() { }

    const TAnonMember* getAsAnonMember() const { return this; }
    TSymbol& getAnonContainer() const { return anonContainer; }
    unsigned int getMemberNumber() const { return memberNumber; }
    virtual void dump(TInfoSink &infoSink) const;

protected:
    explicit TAnonMember(TAnonMember&);
    TAnonMember& operator=(TAnonMember&);

    TSymbol& anonContainer;
    unsigned int memberNumber;
};

class TSymbolTableLevel {
public:
    POOL_ALLOCATOR_NEW_DELETE(GetThreadPoolAllocator())
    TSymbolTableLevel() : defaultPrecision(0), anonId(0) { }
	~TSymbolTableLevel();

    bool insert(TSymbol& symbol)
    {
        //
        // returning true means symbol was added to the table with no semantic errors
        //
        tInsertResult result;
        const TString& name = symbol.getName();
        if (name == "") {
            // An empty name means an anonymous container, exposing its members to the external scope.
            // Give it a name and insert its members in the symbol table, pointing to the container.
            char buf[20];
            snprintf(buf, 20, "__anon__%d", anonId++);
            symbol.changeName(NewPoolTString(buf));

            bool isOkay = true;
            const TTypeList& types = *symbol.getAsVariable()->getType().getStruct();
            for (unsigned int m = 0; m < types.size(); ++m) {
                TAnonMember* member = new TAnonMember(&types[m].type->getFieldName(), m, symbol);
                result = level.insert(tLevelPair(member->getMangledName(), member));
                if (! result.second)
                    isOkay = false;
            }

            return isOkay;
        } else {
            // Check for redefinition errors:
            // - STL itself will tell us if there is a direct name collision at this level
            // - additionally, check for function/variable name collisions
            // - for ES, for overriding or hiding built-in function
            const TString& insertName = symbol.getMangledName();
            if (symbol.getAsFunction()) {
                // make sure there isn't a variable of this name
                if (level.find(name) != level.end())
                    return false;

                // insert, and whatever happens is okay
                level.insert(tLevelPair(insertName, &symbol));

                return true;
            } else {
                result = level.insert(tLevelPair(insertName, &symbol));

                return result.second;
            }
        }
    }

    TSymbol* find(const TString& name) const
    {
        tLevel::const_iterator it = level.find(name);
        if (it == level.end()) 
            return 0;
        else
            return (*it).second;
    }

    bool hasFunctionName(const TString& name) const
    {
        tLevel::const_iterator candidate = level.lower_bound(name);
        if (candidate != level.end()) {
            const TString& candidateName = (*candidate).first;
            TString::size_type parenAt = candidateName.find_first_of('(');
            if (parenAt != candidateName.npos && candidateName.compare(0, parenAt, name) == 0)

                return true;
        }

        return false;
    }

    // Use this to do a lazy 'push' of precision defaults the first time
    // a precision statement is seen in a new scope.  Leave it at 0 for
    // when no push was needed.  Thus, it is not the current defaults,
    // it is what to restore the defaults to when popping a level.
    void setPreviousDefaultPrecisions(const TPrecisionQualifier *p)
    {
        // can call multiple times at one scope, will only latch on first call,
        // as we're tracking the previous scope's values, not the current values
        if (defaultPrecision != 0)
            return;

        defaultPrecision = new TPrecisionQualifier[EbtNumTypes];
        for (int t = 0; t < EbtNumTypes; ++t)
            defaultPrecision[t] = p[t];
    }

    void getPreviousDefaultPrecisions(TPrecisionQualifier *p)
    {
        // can be called for table level pops that didn't set the
        // defaults
        if (defaultPrecision == 0 || p == 0)
            return;

        for (int t = 0; t < EbtNumTypes; ++t)
            p[t] = defaultPrecision[t];
    }

    void relateToOperator(const char* name, TOperator op);
    void dump(TInfoSink &infoSink) const;
	TSymbolTableLevel* clone();
    void readOnly();

protected:
    explicit TSymbolTableLevel(TSymbolTableLevel&);
    TSymbolTableLevel& operator=(TSymbolTableLevel&);

    typedef std::map<TString, TSymbol*, std::less<TString>, pool_allocator<std::pair<const TString, TSymbol*> > > tLevel;
    typedef const tLevel::value_type tLevelPair;
    typedef std::pair<tLevel::iterator, bool> tInsertResult;

    tLevel level;  // named mappings
    TPrecisionQualifier *defaultPrecision;
    int anonId;
};

class TSymbolTable {
public:
    TSymbolTable() : uniqueId(0), noBuiltInRedeclarations(false), adoptedLevels(0)
    {
        //
        // This symbol table cannot be used until push() is called.
        //
    }
    ~TSymbolTable()
    {
        // this can be called explicitly; safest to code it so it can be called multiple times

        // don't deallocate levels passed in from elsewhere
        while (table.size() > adoptedLevels)
            pop(0);
    }

    void adoptLevels(TSymbolTable& symTable)
    {
        for (unsigned int level = 0; level < symTable.table.size(); ++level) {
            table.push_back(symTable.table[level]);
            ++adoptedLevels;
        }
        uniqueId = symTable.uniqueId;
        noBuiltInRedeclarations = symTable.noBuiltInRedeclarations;
    }

    //
    // While level adopting is generic, the methods below enact a the following
    // convention for levels:
    //   0: common built-ins shared across all stages, all compiles, only one copy for all symbol tables
    //   1: per-stage built-ins, shared across all compiles, but a different copy per stage
    //   2: built-ins specific to a compile, like resources that are context-dependent, or redeclared built-ins
    //   3: user-shader globals
    //
protected:
    bool isSharedLevel(int level)  { return level <= 1; }    // exclude all per-compile levels
    bool isBuiltInLevel(int level) { return level <= 2; }    // exclude user globals
    bool isGlobalLevel(int level)  { return level <= 3; }    // include user globals
public:
    bool isEmpty() { return table.size() == 0; }
    bool atBuiltInLevel() { return isBuiltInLevel(currentLevel()); }
    bool atGlobalLevel()  { return isGlobalLevel(currentLevel()); }

    void setNoBuiltInRedeclarations() { noBuiltInRedeclarations = true; }
    
    void push()
    {
        table.push_back(new TSymbolTableLevel);
    }

    void pop(TPrecisionQualifier *p)
    {
        table[currentLevel()]->getPreviousDefaultPrecisions(p);
        delete table.back();
        table.pop_back();
    }

    bool insert(TSymbol& symbol)
    {
        symbol.setUniqueId(++uniqueId);

        if (symbol.getAsVariable()) {
            // make sure there isn't a function of this name
            if (table[currentLevel()]->hasFunctionName(symbol.getName()))
                return false;
            if (atGlobalLevel() && currentLevel() > 0 && noBuiltInRedeclarations) {
                if (table[0]->hasFunctionName(symbol.getName()))
                    return false;
                if (currentLevel() > 1 && table[1]->hasFunctionName(symbol.getName()))
                    return false;
            }
        }

        return table[currentLevel()]->insert(symbol);
    }

    //
    // To copy a variable from a shared level up to the current level, so it can be 
    // modified without impacting other users of the shared table.
    //
    TVariable* copyUp(TVariable* shared)
    {        
        TVariable* variable = shared->clone();
        variable->setUniqueId(shared->getUniqueId());
        table[currentLevel()]->insert(*variable);

        return variable;
    }

    TSymbol* find(const TString& name, bool* builtIn = 0, bool *currentScope = 0)
    {
        int level = currentLevel();
        TSymbol* symbol;
        do {
            symbol = table[level]->find(name);
            --level;
        } while (symbol == 0 && level >= 0);
        level++;
        if (builtIn)
            *builtIn = isBuiltInLevel(level);
        if (currentScope)
            *currentScope = isGlobalLevel(currentLevel()) || level == currentLevel();  // consider shared levels as "current scope" WRT user globals

        return symbol;
    }

    void relateToOperator(const char* name, TOperator op)
    {
        for (unsigned int level = 0; level < table.size(); ++level)
            table[level]->relateToOperator(name, op);
    }

    int getMaxSymbolId() { return uniqueId; }
    void dump(TInfoSink &infoSink) const;
	void copyTable(const TSymbolTable& copyOf);

    void setPreviousDefaultPrecisions(TPrecisionQualifier *p) { table[currentLevel()]->setPreviousDefaultPrecisions(p); }

    void readOnly()
    {
        for (unsigned int level = 0; level < table.size(); ++level)
            table[level]->readOnly();
    }

protected:
    TSymbolTable(TSymbolTable&);
    TSymbolTable& operator=(TSymbolTableLevel&);

    int currentLevel() const { return static_cast<int>(table.size()) - 1; }

    std::vector<TSymbolTableLevel*> table;
    int uniqueId;     // for unique identification in code generation
    bool noBuiltInRedeclarations;
    unsigned int adoptedLevels;
};

} // end namespace glslang

#endif // _SYMBOL_TABLE_INCLUDED_
