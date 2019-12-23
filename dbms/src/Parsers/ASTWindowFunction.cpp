#include <Common/typeid_cast.h>
#include <Parsers/ASTLiteral.h>
#include <Parsers/ASTWindowFunction.h>
#include <Parsers/ASTWithAlias.h>
#include <Parsers/ASTSubquery.h>
#include <IO/WriteHelpers.h>
#include <IO/WriteBufferFromString.h>
namespace DB
{

void ASTWindowFunction::appendColumnNameImpl(WriteBuffer & ostr) const
{
    source_function->appendColumnName(ostr);
    writeString(" OVER ", ostr);
    writeChar('(', ostr);
    window->appendColumnName(ostr);
    writeChar(')', ostr);
}
ASTPtr ASTWindowFunction::clone() const
{
    auto res = std::make_shared<ASTWindowFunction>(*this);
    res->set(res->source_function, source_function->clone());
    res->set(res->window, window->clone());
    return res;
}
void ASTWindowFunction::formatImplWithoutAlias(const FormatSettings & settings, FormatState & state, FormatStateStacked frame) const
{
    FormatStateStacked nested_dont_need_parens = frame;
    nested_dont_need_parens.need_parens = false;
    source_function->formatImpl(settings, state, nested_dont_need_parens);
    settings.ostr << " OVER (";
    window->formatImpl(settings, state, nested_dont_need_parens);
    settings.ostr << ")";
}
}
