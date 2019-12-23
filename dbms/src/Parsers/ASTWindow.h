#pragma once

#include <Parsers/ASTExpressionList.h>
#include <unordered_map>
namespace DB
{

class ASTWindow : public IAST
{
public:
    ASTExpressionList * partition;

    String getID(char) const override { return "Window"; }

    ASTPtr clone() const override;

    void formatImpl(const FormatSettings & settings, FormatState & state, FormatStateStacked frame) const override;

};
}
