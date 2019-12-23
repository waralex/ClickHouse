#pragma once

#include <Parsers/ASTWithAlias.h>
#include <Parsers/ASTWindow.h>
#include <Parsers/ASTExpressionList.h>
#include "Parsers/ASTFunction.h"


namespace DB
{

/** AST for function application or operator.
  */
class ASTWindowFunction : public ASTWithAlias
{
public:
    ASTFunction * source_function;
    /// parameters - for parametric aggregate function. Example: quantile(0.9)(x) - what in first parens are 'parameters'.
    ASTWindow * window;

public:
    /** Get text identifying the AST node. */
    String getID(char) const override {return "Window function";};

    ASTPtr clone() const override;

protected:
    void formatImplWithoutAlias(const FormatSettings & settings, FormatState & state, FormatStateStacked frame) const override;
    void appendColumnNameImpl(WriteBuffer & ostr) const override;
};



}
