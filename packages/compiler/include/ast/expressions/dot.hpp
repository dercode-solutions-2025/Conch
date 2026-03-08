#pragma once

#include "ast/expressions/infix.hpp"
#include "ast/node.hpp"

namespace conch::ast {

class DotExpression : public InfixExpression<DotExpression> {
  public:
    static constexpr auto KIND = NodeKind::DOT_EXPRESSION;

  public:
    using InfixExpression::InfixExpression;
    MAKE_AST_COPY_MOVE(DotExpression)

    using InfixExpression::parse;
};

} // namespace conch::ast
