#ifndef __GLSLD_SYMBOL_HPP__
#define __GLSLD_SYMBOL_HPP__
#include "../glslang/Include/intermediate.h"
#include <vector>
class Symbol {
    enum class SymbolType { VARIABLE, FUNCTION, TYPE, UNKOWN };

    struct Loc {
        std::string filename;
        int line = 0;
        int col = 0;

        struct Loc& operator=(const glslang::TSourceLoc& loc)
        {
            filename = loc.getFilename();
            line = loc.line - 1;
            col = loc.column - 1;
            return *this;
        }
    };

    struct __SymbolStatus {
        std::string name;
        std::string mangled_name;
        SymbolType type = Symbol::SymbolType::UNKOWN;
        std::vector<Symbol> uses;
        int ref = 1;
        struct Loc loc;
    };

    __SymbolStatus* status_;

    void release_();

public:
    //TODO: copy and delete
    Symbol();
    Symbol(const glslang::TIntermSymbol* interm);
    Symbol(const Symbol& rhs);
    Symbol& operator=(const Symbol& rhs);
	Symbol& operator=(Symbol&&);
	Symbol(Symbol&&);
    virtual ~Symbol();

    std::string const& name() const { return status_->name; }
    std::vector<Symbol>& uses() { return status_->uses; }
    void add_uses(const glslang::TIntermSymbol* sym);
    Loc loc() const { return status_->loc; }
};

#endif
