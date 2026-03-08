#pragma once

#include "ast/expressions/infix.hpp"
#include "ast/node.hpp"

namespace conch::ast {

class BinaryExpression : public InfixExpression<BinaryExpression> {
  public:
    static constexpr auto KIND = NodeKind::BINARY_EXPRESSION;

  public:
    using InfixExpression::InfixExpression;
    MAKE_AST_COPY_MOVE(BinaryExpression)

    using InfixExpression::parse;
};

} // namespace conch::ast
