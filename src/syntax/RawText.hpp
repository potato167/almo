#pragma once

#include"../interfaces/ast.hpp"
#include"../interfaces/parser.hpp"
#include"../interfaces/syntax.hpp"

#include <limits>

namespace almo {

struct RawText : public ASTNode {

    std::string content;
    RawText(std::string _content) : content(_content) {
        set_uuid();
    }

    std::string to_html() const override {
        return content;
    }

    std::map<std::string, std::string> get_properties() const override {
        return {
            {"content", content}
        };
    }
    std::string get_classname() const override {
        return "RawText";
    }
};

struct RawText_syntax : InlineSyntax {
    // All string matches Rawtext syntax
    // but matches infinity position
    // because Rawtext syntax is weakest.
    // If the string matches other Inline syntax
    // RawText does not match it.
    int operator()(const std::string &str) const override {
        return std::numeric_limits<int>::max();
    }
    void operator()(const std::string &str, ASTNode &ast) const override {
        RawText node(str);
        ast.add_child(std::make_shared<RawText>(node));
    }
};

} // namespace almo