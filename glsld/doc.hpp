#ifndef __GLSLD_DOC_HPP__
#define __GLSLD_DOC_HPP__
#include "../glslang/Public/ShaderLang.h"
#include <string>

class Doc {
    std::string uri_;
    int version_;
	std::string text_;
    EShLanguage language_;

    void infer_language_();

public:
    Doc() = default;
    Doc(std::string const& uri, const int version, std::string const& text);
    Doc(const Doc& rhs);
    Doc(Doc&& rhs);
    Doc& operator=(const Doc& doc);
    Doc& operator=(Doc&& doc);

    int version() const { return version_; }
    std::string const& text() const { return text_; }
    std::string const& uri() const { return uri_; }
    EShLanguage language() const { return language_; }
    void set_version(const int version) { version_ = version; }
    void set_text(std::string const& text) { text_ = text; }
    void set_uri(std::string const& uri) { uri_ = uri; }
};
#endif
