#pragma once

#include "ast/expressions/prefix.hpp"
#include "ast/node.hpp"

namespace conch::ast {

class UnaryExpression : public PrefixExpression<UnaryExpression> {
  public:
    static constexpr auto KIND = NodeKind::UNARY_EXPRESSION;

  public:
    using PrefixExpression::PrefixExpression;
    MAKE_AST_COPY_MOVE(UnaryExpression)

    using PrefixExpression::parse;
};

class ReferenceExpression : public PrefixExpression<ReferenceExpression> {
  public:
    static constexpr auto KIND = NodeKind::REFERENCE_EXPRESSION;

  public:
    using PrefixExpression::PrefixExpression;
    MAKE_AST_COPY_MOVE(ReferenceExpression)

    using PrefixExpression::parse;
};

class DereferenceExpression : public PrefixExpression<DereferenceExpression> {
  public:
    static constexpr auto KIND = NodeKind::DEREFERENCE_EXPRESSION;

  public:
    using PrefixExpression::PrefixExpression;
    MAKE_AST_COPY_MOVE(DereferenceExpression)

    using PrefixExpression::parse;
};

} // namespace conch::ast
