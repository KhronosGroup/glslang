#ifndef __GLSLD_WORKSPACE_HPP__
#define __GLSLD_WORKSPACE_HPP__
#include "doc.hpp"
#include <map>
#include <vector>
class Workspace {
    std::string root_;
    std::map<std::string, Doc> docs_;

public:
    Workspace();
    Workspace(const Workspace&) = delete;
    Workspace(Workspace&&) = delete;
    Workspace& operator=(const Workspace&) = delete;
    Workspace& operator=(Workspace&&) = delete;

    void add_doc(Doc&& doc);
    std::string const& get_root() const;
    void set_root(std::string const& root);
	glslang::TIntermSymbol* locate_symbol_def(std::string const& uri, const int line, const int col);
    std::vector<glslang::TIntermSymbol*> locate_symbol_at(std::string const& uri, const int line, const int col);
};
#endif
