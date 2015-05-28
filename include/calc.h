#ifndef CALC_H
#define CALC_H

#include <iostream>
#include "symboltable.h"
#include "storage.h"
#include "functiontable.h"

class Parser;
class FunctionTable;

class Calc
{
    friend class Parser;
public:
    Calc() : funTable_(symbol_), storage_(symbol_) {}
    void ListFunction() const;
    void ListVar() const;
    void Serialize(Serializer& out) const;
    void DeSerialize(DeSerializer& in);
private:
    bool GetVariableValue(unsigned int id, double &val) const;
    Storage& GetStorage()
    {
        return storage_;
    }
    PtrFun GetFunction(unsigned int id) const
    {
        return funTable_.GetFunction(id);
    }
    bool IsFunction(unsigned int id) const
    {
        return id < funTable_.GetSize();
    }
    unsigned int AddSymbol(const std::string &str);
    unsigned int FindSymbol(const std::string &str) const;
    SymbolTable symbol_;
    FunctionTable funTable_;
    Storage storage_;
};

#endif // CALC_H
