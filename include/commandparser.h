#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "scanner.h"
#include "calc.h"
#include "parser.h"

class CommandParser
{
    enum ECommand {
        CMD_HELP,
        CMD_QUIT,
        CMD_VAR,
        CMD_FUN,
        CMD_LOAD,
        CMD_SAVE,
        CMD_ERROR
    };

public:
    CommandParser(Scanner & scanner, Calc& calc);
    STATUS Excute();
private:
    void Help() const;
    void ListVar() const;
    void ListFunction() const;
    STATUS Load(const std::string & fileName);
    STATUS Save(const std::string & fileName);
    Scanner & scanner_;
    Calc& calc_;
    ECommand cmd_;
    std::string cmdName_;
};

#endif // COMMANDPARSER_H
