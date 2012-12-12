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

//
// Symbol table for parsing.  Most functionaliy and main ideas 
// are documented in the header file.
//

#include "SymbolTable.h"

//
// TType helper function needs a place to live.
//

//
// Recursively generate mangled names.
//
void TType::buildMangledName(TString& mangledName)
{
    if (isMatrix())
        mangledName += 'm';
    else if (isVector())
        mangledName += 'v';

    switch (type) {
    case EbtFloat:              mangledName += 'f';      break;
    case EbtInt:                mangledName += 'i';      break;
    case EbtBool:               mangledName += 'b';      break;
    case EbtSampler1D:          mangledName += "s1";     break;
    case EbtSampler2D:          mangledName += "s2";     break;
    case EbtSampler3D:          mangledName += "s3";     break;
    case EbtSamplerCube:        mangledName += "sC";     break;
    case EbtSampler1DShadow:    mangledName += "sS1";    break;
    case EbtSampler2DShadow:    mangledName += "sS2";    break;
    case EbtSamplerRect:        mangledName += "sR2";    break;  // ARB_texture_rectangle
    case EbtSamplerRectShadow:  mangledName += "sSR2";   break;  // ARB_texture_rectangle
    case EbtStruct:
        mangledName += "struct-";
        if (typeName)
        	mangledName += *typeName;
        {// support MSVC++6.0
            for (unsigned int i = 0; i < structure->size(); ++i) {
                mangledName += '-';
                (*structure)[i].type->buildMangledName(mangledName);
            }
        }
    default: 
        break;
    }

    mangledName += static_cast<char>('0' + getNominalSize());
    if (isArray()) {
        char buf[10];
        sprintf(buf, "%d", arraySize);
        mangledName += '[';
        mangledName += buf;
        mangledName += ']';
    }
}

int TType::getStructSize() const
{ 
    if (!getStruct()) {
        assert(false && "Not a struct");
        return 0;
    }

    if (structureSize == 0)
        for (TTypeList::iterator tl = getStruct()->begin(); tl != getStruct()->end(); tl++)
            structureSize += ((*tl).type)->getObjectSize();
        
    return structureSize;
}

//
// Dump functions.
//

void TVariable::dump(TInfoSink& infoSink) const 
{
    infoSink.debug << getName().c_str() << ": " << type.getQualifierString() << " " << type.getBasicString();
    if (type.isArray()) {
        infoSink.debug << "[0]";
    }
    infoSink.debug << "\n";
}

void TFunction::dump(TInfoSink &infoSink) const
{
    infoSink.debug << getName().c_str() << ": " <<  returnType.getBasicString() << " " << getMangledName().c_str() << "\n";
}

void TSymbolTableLevel::dump(TInfoSink &infoSink) const 
{
    tLevel::const_iterator it;
    for (it = level.begin(); it != level.end(); ++it)
        (*it).second->dump(infoSink);
}

void TSymbolTable::dump(TInfoSink &infoSink) const
{
    for (int level = currentLevel(); level >= 0; --level) {
        infoSink.debug << "LEVEL " << level << "\n";
        table[level]->dump(infoSink);
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
	for (tLevel::iterator it = level.begin(); it != level.end(); ++it)
		delete (*it).second;
}

//
// Change all function entries in the table with the non-mangled name
// to be related to the provided built-in operation.  This is a low
// performance operation, and only intended for symbol tables that
// live across a large number of compiles.
//
void TSymbolTableLevel::relateToOperator(const char* name, TOperator op) 
{
    tLevel::iterator it;
    for (it = level.begin(); it != level.end(); ++it) {
        if ((*it).second->isFunction()) {
            TFunction* function = static_cast<TFunction*>((*it).second);
            if (function->getName() == name)
                function->relateToOperator(op);
        }
    }
}    


TSymbol::TSymbol(const TSymbol& copyOf)
{
	name = NewPoolTString(copyOf.name->c_str());
	uniqueId = copyOf.uniqueId;
}

TVariable::TVariable(const TVariable& copyOf, TStructureMap& remapper) : TSymbol(copyOf)
{	
	type.copyType(copyOf.type, remapper);
	userType = copyOf.userType;
	// for builtIn symbol table level, unionArray and arrayInformation pointers should be NULL
	assert(copyOf.arrayInformationType == 0); 
	arrayInformationType = 0;

	if (copyOf.unionArray) {		
		assert(!copyOf.type.getStruct()); 
		assert(copyOf.type.getObjectSize() == 1);
		unionArray = new constUnion[1];
        unionArray[0] = copyOf.unionArray[0];
	} else
		unionArray = 0;
}

TVariable* TVariable::clone(TStructureMap& remapper) 
{
	TVariable *variable = new TVariable(*this, remapper);

	return variable;
}

TFunction::TFunction(const TFunction& copyOf, TStructureMap& remapper) : TSymbol(copyOf)
{	
	for (unsigned int i = 0; i < copyOf.parameters.size(); ++i) {
		TParameter param;
		parameters.push_back(param);
		parameters.back().copyParam(copyOf.parameters[i], remapper);
	}

	returnType.copyType(copyOf.returnType, remapper);
	mangledName = copyOf.mangledName;
	op = copyOf.op;
	defined = copyOf.defined;
}

TFunction* TFunction::clone(TStructureMap& remapper) 
{
	TFunction *function = new TFunction(*this, remapper);

	return function;
}

TSymbolTableLevel* TSymbolTableLevel::clone(TStructureMap& remapper)
{
	TSymbolTableLevel *symTableLevel = new TSymbolTableLevel();
	tLevel::iterator iter;
	for (iter = level.begin(); iter != level.end(); ++iter) {
		symTableLevel->insert(*iter->second->clone(remapper));
	}

	return symTableLevel;
}

void TSymbolTable::copyTable(const TSymbolTable& copyOf)
{
	TStructureMap remapper;
	uniqueId = copyOf.uniqueId;
	for (unsigned int i = 0; i < copyOf.table.size(); ++i) {
		table.push_back(copyOf.table[i]->clone(remapper));
	}
}
