#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include "serial.h"

class SymbolTable : public Serializable
{
public:
    enum {IDNOTFOUND = -1};
    SymbolTable(void) : curId_(0) {}
    void Serialize(Serializer& out) const;
    void DeSerialize(DeSerializer& in);
    unsigned int Add(const std::string &str);
    unsigned int Find(const std::string &str) const;
    void Clear();
    std::string GetSymbolName(unsigned int id) const;
    unsigned int GetCurId() const
    {
        return curId_;
    }
private:
    std::map<const std::string, unsigned int> dictionary_;
    unsigned int curId_;
};

#endif
