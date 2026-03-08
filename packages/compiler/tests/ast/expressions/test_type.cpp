#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include "ast/helpers.hpp"

#include "ast/expressions/function.hpp"
#include "ast/expressions/identifier.hpp"
#include "ast/expressions/type.hpp"
#include "ast/statements/declaration.hpp"

#include "lexer/keywords.hpp"

namespace conch::tests {

namespace helpers {

auto test_type_expr(std::string_view type_str, ast::TypeExpression&& expected) -> void {
    const auto input = fmt::format("var a: {};", type_str);
    helpers::test_stmt(
        input,
        ast::DeclStatement{Token{keywords::VAR},
                           make_box<ast::IdentifierExpression>(Token{TokenType::IDENT, "a"}),
                           make_box<ast::TypeExpression>(std::move(expected)),
                           nullopt,
                           ast::DeclModifiers::VARIABLE});
}

} // namespace helpers

const Token colon{TokenType::COLON, ":"};

TEST_CASE("Shallow type") {
    helpers::test_type_expr(
        "int",
        ast::TypeExpression{
            colon,
            ast::ExplicitType{
                {}, make_box<ast::IdentifierExpression>(Token{TokenType::INT_TYPE, "int"})}});
}

} // namespace conch::tests
