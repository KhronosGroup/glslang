#include "workspace.hpp"
#include "glsld/doc.hpp"
#include <vector>

Workspace::Workspace() : root_("/") {}

void Workspace::set_root(std::string const& root) { root_ = root; }
std::string const& Workspace::get_root() const { return root_; }
void Workspace::add_doc(Doc&& doc) { docs_[doc.uri()] = std::move(doc); }

std::vector<Doc::LookupResult> Workspace::lookup_nodes_at(std::string const& uri, const int line, const int col)
{
    if (docs_.count(uri)) {
        return docs_[uri].lookup_nodes_at(line, col);
    }
    return {};
}

glslang::TSourceLoc Workspace::locate_symbol_def(std::string const& uri, const int line, const int col)
{
    if (docs_.count(uri) <= 0)
        return {.name = nullptr, .column = 0, .line = 0};

    auto nodes = lookup_nodes_at(uri, line, col);

    for (auto& node : nodes) {
        if (node.kind == Doc::LookupResult::Kind::SYMBOL) {
            return docs_[uri].locate_symbol_def(node.sym);
        } else if (node.kind == Doc::LookupResult::Kind::FIELD) {
            return node.field.loc;
        }
    }

    return {.name = nullptr, .column = 0, .line = 0};
}

