#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "serial.h"

class SymbolTable;

class Storage : public Serializable
{
public:
    Storage(SymbolTable &tbl);
    void Serialize(Serializer& out) const;
    void DeSerialize(DeSerializer& in);
    void Clear();
    bool IsInit(unsigned int id) const;
    void AddConstants(SymbolTable &tbl);
    double GetValue(unsigned int id) const;
    void SetValue(unsigned int id, double val);
    void AddValue(unsigned int id, double val);

private:
    std::vector<double> cells_;
    std::vector<bool> inits_;
};

#endif
