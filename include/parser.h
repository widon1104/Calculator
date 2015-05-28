#ifndef PARSER_H
#define PARSER_H

#include <tr1/memory>

class Scanner;
class Node;
class Calc;

enum STATUS
{
    STATUS_OK,
    STATUS_ERROR,
    STATUS_QUIT,
};

//Parse和Scanner是关联关系
class Parser
{
public:
    Parser(Scanner & scanner, Calc& calc);
    STATUS Parse();
    std::tr1::shared_ptr<Node> Expr();
    std::tr1::shared_ptr<Node> Term();
    std::tr1::shared_ptr<Node> Factor();
    double Calculate() const;
private:
    Scanner & scanner_;
    Calc& calc_;
    std::tr1::shared_ptr<Node> tree_;
    STATUS status_;
};

#endif // PARSER_H
