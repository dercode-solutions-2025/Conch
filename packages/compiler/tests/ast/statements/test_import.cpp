#include <catch2/catch_test_macros.hpp>

#include "ast/common_helpers.hpp"
#include "ast/expressions/primitive.hpp"
#include "ast/statements/helpers.hpp"

#include "ast/expressions/identifier.hpp"

#include "lexer/keywords.hpp"
#include "lexer/token.hpp"

namespace conch::tests {

namespace helpers {

auto test_import(std::string_view input, const ast::ImportStatement& expected) -> void {
    Parser p{input};
    auto [ast, errors] = p.consume();

    helpers::check_errors<ParserDiagnostic>(errors);
    REQUIRE(ast.size() == 1);

    const auto  actual{std::move(ast[0])};
    const auto& actual_decl = helpers::try_into<ast::ImportStatement>(*actual);
    REQUIRE(expected == actual_decl);
}

} // namespace helpers

TEST_CASE("Module imports") {
    helpers::test_import(
        "import std;",
        ast::ImportStatement{Token{keywords::IMPORT},
                             make_box<ast::IdentifierExpression>(Token{TokenType::IDENT, "std"}),
                             {}});

    helpers::test_import(
        "import std as stud;",
        ast::ImportStatement{Token{keywords::IMPORT},
                             make_box<ast::IdentifierExpression>(Token{TokenType::IDENT, "std"}),
                             make_box<ast::IdentifierExpression>(Token{TokenType::IDENT, "stud"})});
}

TEST_CASE("User imports") {
    helpers::test_import(
        R"(import "ast/node.conch" as node;)",
        ast::ImportStatement{
            Token{keywords::IMPORT},
            make_box<ast::StringExpression>(Token{TokenType::STRING, R"("ast/node.conch")"},
                                            std::string{"ast/node.conch"}),
            make_box<ast::IdentifierExpression>(Token{TokenType::IDENT, "node"})});
}

TEST_CASE("Incorrect module imports ") {
    helpers::test_fail("import 2;", ParserDiagnostic{ParserError::ILLEGAL_IMPORT_TYPE, 1, 8});
    helpers::test_fail("import as 2;", ParserDiagnostic{ParserError::ILLEGAL_IMPORT_TYPE, 1, 8});
    helpers::test_fail("import 2 as 3;", ParserDiagnostic{ParserError::ILLEGAL_IMPORT_TYPE, 1, 8});
    helpers::test_fail(
        "import std as 2;",
        ParserDiagnostic{
            "Expected token IDENT, found INT_10", ParserError::UNEXPECTED_TOKEN, 1, 15});
}

TEST_CASE("Incorrect user imports ") {
    helpers::test_fail(R"(import "";)", ParserDiagnostic{ParserError::EMPTY_USER_IMPORT, 1, 8});
    helpers::test_fail(R"(import "" as e;)",
                       ParserDiagnostic{ParserError::EMPTY_USER_IMPORT, 1, 8});
    helpers::test_fail(R"(import "ast/node.conch";)",
                       ParserDiagnostic{ParserError::USER_IMPORT_MISSING_ALIAS, 1, 1});
    helpers::test_fail(
        R"(import "ast/node.conch" as 2;)",
        ParserDiagnostic{
            "Expected token IDENT, found INT_10", ParserError::UNEXPECTED_TOKEN, 1, 28});
}

} // namespace conch::tests
