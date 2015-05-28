#ifndef SCANNER_H
#define SCANNER_H

#include <string>

enum EToken
{
    TOKEN_END,
    TOKEN_COMMAND,
    TOKEN_ERROR,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPARENTHESIS,
    TOKEN_RPARENTHESIS,
    TOKEN_INDENTIFIER,
    TOKEN_ASSIGN,
};

class Scanner
{
public:
    explicit Scanner(std::istream& in);
    ~Scanner();
    void Accept();
    void AcceptCommand();
    bool IsEmpty() const;
    bool IsDone() const;
    bool IsCommand() const;
    double Number() const;
    EToken Token() const;
    std::string GetSymbol() const;
private:
    void ReadChar();
    void SkipWhite();
    std::istream& in_;
    EToken token_;
    double number_;
    std::string symbol_;
    bool isEmtpy_;
    int look_;
};

#endif // SCANNER_H
