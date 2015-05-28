#include <cmath>
#include <cassert>
#include <iostream>
#include "functiontable.h"
#include "symboltable.h"
#include "debug_new.h"

struct FunctionEntry {
    PtrFun pFun_;
    const char* funName_;
};

FunctionEntry Entrys[] =
{
    log, "log",
    log10, "log10",
    exp, "exp",
    sqrt, "sqrt",
    sin, "sin",
    cos, "cos",
    tan, "tan",
    sinh, "sinh",
    cosh, "cosh",
    tanh, "tanh",
    asin, "asin",
    acos, "acos",
    atan, "atan"
};

FunctionTable::FunctionTable(SymbolTable &tb) :
    size_(sizeof(Entrys)/sizeof(Entrys[0]))
{
    Init(tb);
}

void FunctionTable::Init(SymbolTable &tb)
{
    std::cout << "Function list: " << std::endl;
    pFun_ = new PtrFun[size_];
    for (unsigned int i = 0; i < size_; i++) {
        pFun_[i] = Entrys[i].pFun_;
        unsigned int j = tb.Add(Entrys[i].funName_);
        assert(i == j);
        std::cout << Entrys[i].funName_ << std::endl;
    }
}

FunctionTable::~FunctionTable()
{
    delete[] pFun_;
}

