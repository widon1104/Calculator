#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

class SymbolTable;

typedef double (*PtrFun)(double);

class FunctionTable
{
public:
    FunctionTable(SymbolTable &tb);
    ~FunctionTable();
    void Init(SymbolTable &tb);

    unsigned int GetSize() const
    {
        return size_;
    }

    PtrFun GetFunction(unsigned int id) const
    {
        return pFun_[id];
    }
private:
    PtrFun* pFun_;
    unsigned int size_;
};

#endif // FUNCTIONTABLE_H
