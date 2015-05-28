#include <cstdio>
#include <assert.h>
#include <iostream>
#include <sstream>
#include "parser.h"
#include "scanner.h"
#include "node.h"
#include "calc.h"
#include "exception.h"
#include "debug_new.h"

Parser::Parser(Scanner & scanner, Calc& calc) :
    scanner_(scanner), calc_(calc), status_(STATUS_OK)
{
}

STATUS Parser::Parse()
{
    tree_ = Expr();
    if (!scanner_.IsDone()) {
        status_ = STATUS_ERROR;
    }
    return status_;
}

std::tr1::shared_ptr<Node> Parser::Expr()
{
    std::tr1::shared_ptr <Node> node = Term();
    EToken token = scanner_.Token();
    std::tr1::shared_ptr <MultipleNode> multiple_node;
//    if (token == TOKEN_PLUS) {
//        scanner_.Accept();
//        Node* nodeRight = Expr();
//        node = new AddNode(node, nodeRight);
//    } else if (token == TOKEN_MINUS) {
//        scanner_.Accept();
//        Node* nodeRight = Expr();
//        node = new SubNode(node, nodeRight);
//    }
    if (token == TOKEN_PLUS || token == TOKEN_MINUS) {

//      Expr := Term { ('+' | '-') Term}

        multiple_node = std::tr1::shared_ptr<MultipleNode>(new SumNode(node));
        do {
            scanner_.Accept();
            std::tr1::shared_ptr<Node> nextNode = Term();
            multiple_node->AppendChild(nextNode,
                                       token == TOKEN_PLUS);
            //更新扫描状态
            token = scanner_.Token();
        } while(token == TOKEN_PLUS || token == TOKEN_MINUS);
        node = multiple_node;

    } else if (token == TOKEN_ASSIGN) {

        // BNF表示法
        // Expr := Term = Expr
        scanner_.Accept();
        std::tr1::shared_ptr<Node> nodeRight = Expr();
        if (node->IsLValue()) {
            node = std::tr1::shared_ptr<Node>(new AssignNode(node, nodeRight));
        } else {
            status_ = STATUS_ERROR;
            //std::cout << "The left hand side of an assignment must be a variable" << std::endl;
            //Todo 抛出异常
            throw SyntaxError("The left hand side of an assignment must be a variable");
        }
    }
    return node;
}

//项
std::tr1::shared_ptr<Node> Parser::Term()
{
    std::tr1::shared_ptr<Node> node = Factor();

    std::tr1::shared_ptr<MultipleNode> multiple_node;

    EToken token = scanner_.Token();

//    if (token == TOKEN_MULTIPLY) {
//        scanner_.Accept();
//        Node* nodeRight = Term();
//        node = new MultiplyNode(node, nodeRight);
//    } else if (token == TOKEN_DIVIDE) {
//        scanner_.Accept();
//        Node* nodeRight = Term();
//        node = new DivideNode(node, nodeRight);
//    }

    if (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE) {

//      Expr := Factor { ('*' | '/') Factor }

        multiple_node = std::tr1::shared_ptr<MultipleNode>(new ProductNode(node));
        do {
            scanner_.Accept();
            std::tr1::shared_ptr<Node> nextNode = Factor();
            multiple_node->AppendChild(nextNode,
                                       token == TOKEN_MULTIPLY);
            //更新扫描状态
            token = scanner_.Token();
        } while(token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE);
        node = multiple_node;
    }
    return node;
}

std::tr1::shared_ptr<Node> Parser::Factor()
{
    std::tr1::shared_ptr<Node> node;
    EToken token = scanner_.Token();
    if (token == TOKEN_LPARENTHESIS) {
        scanner_.Accept();
        node = Expr();
        if (scanner_.Token() ==
                TOKEN_RPARENTHESIS) {
            scanner_.Accept();
        } else {
            status_ = STATUS_ERROR;
            //Todo: 抛出异常
            //std::cout << "missing parenthesis" << std::endl;
            throw SyntaxError("missing parenthesis");
            //node = NULL;
        }
    } else if (token == TOKEN_NUMBER) {
        node = std::tr1::shared_ptr<Node>(new NumberNode(scanner_.Number()));
        scanner_.Accept();
    } else if (token == TOKEN_INDENTIFIER) {
        std::string symbol = scanner_.GetSymbol();
        unsigned int id = calc_.FindSymbol(symbol);
        scanner_.Accept();

        if (scanner_.Token() == TOKEN_LPARENTHESIS) {
            //is Fun()
            scanner_.Accept(); //accept '('
            node = Expr();
            if (scanner_.Token() == TOKEN_RPARENTHESIS) {
                scanner_.Accept();
                if (id != SymbolTable::IDNOTFOUND &&
                        calc_.IsFunction(id)) {
                    node = std::tr1::shared_ptr<Node>(new FunctionNode(node, calc_.GetFunction(id)));
                } else {
                    status_ = STATUS_ERROR;
//                    std::cout << "unKnown function " << "\"" << symbol << "\"" << std::endl;
//                    char buf[256] = {0};
//                    snprintf(buf, sizeof(buf), "UnKnown function \"%s\"", symbol.c_str());
                    std::ostringstream oss;
                    oss << "Unknown function\"" << symbol << "\"";
                    throw SyntaxError(oss.str());
                }
            } else {
                //std::cout << "Missing parenthesis in a function call" << std::endl;
                status_ = STATUS_ERROR;
                throw SyntaxError("Missing parenthesis in a function call");
            }

        } else {
            if (id == SymbolTable::IDNOTFOUND) {
                id = calc_.AddSymbol(symbol);
            }
            node = std::tr1::shared_ptr<Node>(new VariableNode(id, calc_.GetStorage()));
        }

    } else if (token == TOKEN_MINUS) {
        scanner_.Accept();
        node = std::tr1::shared_ptr<Node>(new UMinusNode(Factor()));
    } else {
        //Todo: 抛出异
        //std::cout << "Not a valid expression" << std::endl;
        status_ = STATUS_ERROR;
        throw SyntaxError("Not a valid expression");
    }
    return node;
}

double Parser::Calculate() const
{
    assert(tree_.get() != NULL);
    return tree_->Calc();
}
