#include <Parsers/ASTWindow.h>
namespace DB
{

ASTPtr ASTWindow::clone() const
{
    auto res = std::make_shared<ASTWindow>(*this);
    res->children.clear();
    if (partition) 
    {
        res->set(res->partition, partition->clone());
    }
    return res; 
}
void ASTWindow::formatImpl(const FormatSettings & settings, FormatState & state, FormatStateStacked frame) const
{
    frame.need_parens = false;
    if (partition) 
    {
        settings.ostr << "PARTITION BY ";
        partition->formatImpl(settings, state, frame);
    }
}
}
