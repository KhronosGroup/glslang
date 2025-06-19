#include "workspace.hpp"
#include <vector>

Workspace::Workspace() : root_("/") {}

void Workspace::set_root(std::string const& root) { root_ = root; }
std::string const& Workspace::get_root() const { return root_; }
void Workspace::add_doc(Doc&& doc)
{
    docs_[doc.uri()] = std::move(doc);
}

Symbol* Workspace::find_symbol(std::string const& target)
{
    for (auto& [uri, doc]: docs_) {
        for (auto& [name, s]: doc.symbols()) {
            if (name == target) {
                return &s;
            }
        }
    }

    return nullptr;
}

Symbol* Workspace::find_symbol_by_use(std::string const& uri, const int line, const int col)
{
    auto& table = docs_[uri].symbols();
    for (auto& [name, sym] : table) {
        for (auto& use : sym.uses()) {
            auto loc = use->getLoc();
            if (loc.line == line) {
                auto offset = loc.column;
                if (col >= offset && col <= offset + sym.name().size()) {
                    return &sym;
                }
            }
        }
    }

    return nullptr;
}
