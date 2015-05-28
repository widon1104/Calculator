#include "symboltable.h"
#include "exception.h"

void SymbolTable::Serialize(Serializer &out) const
{
    unsigned int size = dictionary_.size();
    out << size;
    std::map<const std::string, unsigned int>::const_iterator it;
    for (it = dictionary_.begin(); it != dictionary_.end(); it++) {
        out << it->first << it->second;
    }
    out << curId_;
}

void SymbolTable::DeSerialize(DeSerializer &in)
{
    dictionary_.clear();
    unsigned int size = 0;
    in >> size;
    std::string str;
    unsigned int id = 0;
    for (unsigned int i = 0; i < size; i++) {
        in >> str >> id;
        dictionary_[str] = id;
    }
    in >> curId_;
}

unsigned int SymbolTable::Add(const std::string &str)
{
    dictionary_.insert(std::make_pair(str, curId_));
    return curId_++;
}

unsigned int SymbolTable::Find(const std::string &str) const
{
    std::map<const std::string, unsigned int>::const_iterator it;
    it = dictionary_.find(str);
    if (it != dictionary_.end()) {
        return it->second;
    }
    return IDNOTFOUND;
}

void SymbolTable::Clear()
{
    dictionary_.clear();
    curId_ = 0;
}

//函数对象的用法, 仿函数
//让一个类对象使用起来像一个函数
//STL六大组件之一
class IsEqualId
{
public:
    IsEqualId(const unsigned int id) : id_(id) {}

    bool operator ()(const std::pair<const std::string, unsigned int> & it)
    {
        return it.second == id_;
    }
private:
    unsigned int id_;
};

std::string SymbolTable::GetSymbolName(unsigned int id) const
{
    std::map<const std::string, unsigned>::const_iterator it;
    it = std::find_if(dictionary_.begin(), dictionary_.end(), IsEqualId(id));
    if (it == dictionary_.end()) {
        throw Exception("Internel error: missing entry in symbol table");
    }
    return it->first;
}
