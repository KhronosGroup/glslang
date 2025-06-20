#include "workspace.hpp"
#include <vector>

Workspace::Workspace() : root_("/") {}

void Workspace::set_root(std::string const& root) { root_ = root; }
std::string const& Workspace::get_root() const { return root_; }
void Workspace::add_doc(Doc&& doc) { docs_[doc.uri()] = std::move(doc); }

std::vector<glslang::TIntermSymbol*> Workspace::locate_symbol_at(std::string const& uri, const int line, const int col)
{
    if (docs_.count(uri)) {
        return docs_[uri].locate_symbols_at(line, col);
    }
    return {};
}

glslang::TIntermSymbol* Workspace::locate_symbol_def(std::string const& uri, const int line, const int col)
{
    if (docs_.count(uri) <= 0)
        return nullptr;

    auto uses = locate_symbol_at(uri, line, col);

    for (auto& use : uses) {
        auto def = docs_[uri].locate_symbol_def(use);
        if (def)
            return def;
    }

    return nullptr;
}

