#ifndef __GLSLD_SYMBOL_HPP__
#define __GLSLD_SYMBOL_HPP__
#include "../glslang/Include/intermediate.h"
#include <vector>
class Symbol {
    enum class SymbolType { VARIABLE, FUNCTION, TYPE, UNKOWN };

    struct __SymbolStatus {
        std::string name;
        std::string mangled_name;
        SymbolType type = Symbol::SymbolType::UNKOWN;
        std::vector<glslang::TIntermSymbol*> uses;
        glslang::TIntermSymbol* def;
        int ref = 1;
    };

    __SymbolStatus* status_;

    void release_();

public:
    //TODO: copy and delete
    Symbol();
    Symbol(glslang::TIntermSymbol* interm);
    Symbol(const Symbol& rhs);
    Symbol& operator=(const Symbol& rhs);
    Symbol& operator=(Symbol&&);
    Symbol(Symbol&&);
    virtual ~Symbol();

    std::string const& name() const { return status_->name; }
    std::vector<glslang::TIntermSymbol*>& uses() { return status_->uses; }
    void add_uses(glslang::TIntermSymbol* sym);
    glslang::TIntermSymbol* def() { return status_->def; }
    glslang::TSourceLoc loc() const { return status_->def->getLoc(); }
};

#endif
