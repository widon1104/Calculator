#include <cassert>
#include <string>
#include <iostream>
#include "exception.h"
#include "commandparser.h"

CommandParser::CommandParser(Scanner &scanner, Calc &calc) :
    scanner_(scanner), calc_(calc)
{
    assert(scanner_.IsCommand());
    scanner_.Accept();
    cmdName_ = scanner_.GetSymbol();
    switch (cmdName_[0]) {
    case 'h':
        cmd_ = CMD_HELP;
        break;
    case 'q':
        cmd_ = CMD_QUIT;
        break;
    case 'v':
        cmd_ = CMD_VAR;
        break;
    case 'f':
        cmd_ = CMD_FUN;
        break;
    case 'l':
        cmd_ = CMD_LOAD;
        break;
    case 's':
        cmd_ = CMD_SAVE;
        break;
    default:
        cmd_ = CMD_ERROR;
        break;
    }
}

STATUS CommandParser::Excute()
{
    STATUS status = STATUS_OK;
    scanner_.AcceptCommand();
    std::string fileName;
    switch (cmd_) {
    case CMD_HELP:
        Help();
        break;
    case CMD_QUIT:
        std::cout << "Good Bye!" << std::endl;
        status = STATUS_QUIT;
        break;
    case CMD_VAR:
        ListVar();
        break;
    case CMD_FUN:
        ListFunction();
        break;
    case CMD_LOAD:
        fileName = scanner_.GetSymbol();
        status = Load(fileName);
        break;
    case CMD_SAVE:
        fileName = scanner_.GetSymbol();
        status = Save(fileName);
        break;
    default:
        std::cout << "Unknown command \"" << cmdName_ << std::endl;
        break;
    }

    std::string filename = scanner_.GetSymbol();
    return status;
}

void CommandParser::Help() const
{
    std::cout << "Recognized commands" << std::endl;
    std::cout << "!help" << std::endl;
    std::cout << "!quit" << std::endl;
    std::cout << "!v" << std::endl;
    std::cout << "!f" << std::endl;
    std::cout << "!load filename" << std::endl;
    std::cout << "!save filename" << std::endl;
}

void CommandParser::ListVar() const
{
    std::cout << "variable list:" << std::endl;
    calc_.ListVar();
}

void CommandParser::ListFunction() const
{
    std::cout << "function list:" << std::endl;
    calc_.ListFunction();
}

const int Version = 99;
STATUS CommandParser::Load(const std::string &fileName)
{
    std::cout << "load \"" << fileName << "\"." << std::endl;
    try {
        DeSerializer in(fileName);
        int ver = 0;
        in >> ver;
        if (ver != Version) {
            throw Exception("Miss match version.");
        }
        calc_.DeSerialize(in);
    }
    catch (FileStreamError& e) {
        std::cout << "Error Load: " << e.what() << std::endl;
    }
    catch (Exception& e) {
        std::cout << "Error Load: " << e.what() << std::endl;
    }

    return STATUS_OK;
}

STATUS CommandParser::Save(const std::string &fileName)
{
    std::cout << "Save \"" << fileName << "\"." << std::endl;
    try {
        Serializer out(fileName);
        out << Version;
        calc_.Serialize(out);
    }
    catch (FileStreamError& e) {
        std::cout << "Error Save: " << e.what() << std::endl;
    }
    return STATUS_OK;
}
