#ifndef __GLSLD_WORKSPACE_HPP__
#define __GLSLD_WORKSPACE_HPP__
#include "../glslang/MachineIndependent/localintermediate.h"
#include "doc.hpp"
#include "symbol.hpp"
#include <map>
class Workspace {
    std::string root_;
    std::map<std::string, Doc> docs_;
    std::map<std::string, std::map<std::string, Symbol>> symbols_;

    int parse_doc_(const Doc& doc);

public:
    Workspace();
    void add_doc(Doc&& doc);
    std::string const& get_root() const;
    void set_root(std::string const& root);
	Symbol* find_symbol(std::string const& name);
	Symbol* find_symbol_by_use(std::string const& uri, const int line, const int col);
};
#endif
