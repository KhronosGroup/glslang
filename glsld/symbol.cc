#include "symbol.hpp"

Symbol::Symbol()
{
    status_ = new __SymbolStatus;
    status_->ref = 1;
}

Symbol::Symbol(glslang::TIntermSymbol* sym)
{
    status_ = new __SymbolStatus;
    status_->name = sym->getName().c_str();
    status_->mangled_name = sym->getMangledName().c_str();
    status_->type = SymbolType::VARIABLE;

	status_->def = sym;
    status_->ref = 1;
}

Symbol::Symbol(const Symbol& rhs)
{
    release_();
    status_ = rhs.status_;
    status_->ref += 1;
}

Symbol::Symbol(Symbol&& rhs)
{
    release_();
    status_ = rhs.status_;
    rhs.status_ = nullptr;
}

void Symbol::add_uses(glslang::TIntermSymbol* sym) { 
	status_->uses.push_back(sym); 
}

Symbol& Symbol::operator=(const Symbol& rhs)
{
    release_();
    status_ = rhs.status_;
    status_->ref += 1;
    return *this;
}

Symbol& Symbol::operator=(Symbol&& rhs)
{
    release_();
    status_ = rhs.status_;
    rhs.status_ = nullptr;
    return *this;
}

Symbol::~Symbol() { release_(); }

void Symbol::release_()
{
    if (status_) {
        if (status_->ref == 1) {
            delete status_;
            status_ = nullptr;
        } else {
            status_->ref -= 1;
        }
    }
}
