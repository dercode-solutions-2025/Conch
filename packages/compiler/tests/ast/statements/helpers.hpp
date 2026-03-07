#pragma once

#include <string_view>

#include "ast/statements/decl.hpp"
#include "ast/statements/import.hpp"

namespace conch::tests::helpers {

auto test_decl(std::string_view input, const ast::DeclStatement& expected) -> void;
auto test_import(std::string_view input, const ast::ImportStatement& expected) -> void;

} // namespace conch::tests::helpers
