#include "doc.hpp"

Doc::Doc(std::string const& uri, const int version, std::string const& text) : uri_(uri), version_(version), text_(text)
{
    infer_language_();
}

Doc::Doc(const Doc& rhs) : uri_(rhs.uri_), version_(rhs.version_), text_(rhs.text_), language_(rhs.language_) {}

Doc::Doc(Doc&& rhs)
    : uri_(std::move(rhs.uri_)), version_(std::move(rhs.version_)), text_(std::move(rhs.text_)),
      language_(rhs.language_)
{
}

Doc& Doc::operator=(const Doc& rhs)
{
    version_ = rhs.version_;
    uri_ = rhs.uri_;
    text_ = rhs.text_;
    language_ = rhs.language_;
    return *this;
}

Doc& Doc::operator=(Doc&& rhs)
{
    version_ = std::move(rhs.version_);
    uri_ = std::move(rhs.uri_);
    text_ = std::move(rhs.text_);
    language_ = rhs.language_;
    return *this;
}

void Doc::infer_language_()
{
    // support compute stage only now
    language_ = EShLangCompute;
}
