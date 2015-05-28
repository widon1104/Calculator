#include "calc.h"

unsigned int Calc::FindSymbol(const std::string &str) const
{
    return symbol_.Find(str);
}

void Calc::ListFunction() const
{
    for (int i = 0; i < funTable_.GetSize(); i++) {
        std::cout << symbol_.GetSymbolName(i) << std::endl;
    }
}

bool Calc::GetVariableValue(unsigned int id, double &val) const
{
    if (storage_.IsInit(id)) {
        val = storage_.GetValue(id);
        return true;
    }
    return false;
}

void Calc::Serialize(Serializer &out) const
{
    symbol_.Serialize(out);
    storage_.Serialize(out);
}

void Calc::DeSerialize(DeSerializer &in)
{
    symbol_.DeSerialize(in);
    storage_.DeSerialize(in);
}

void Calc::ListVar() const
{
    for (int i = funTable_.GetSize(); i < symbol_.GetCurId(); i++) {
        std::string name = symbol_.GetSymbolName(i);
        double val = 0;
        if (GetVariableValue(i, val)) {
            std::cout << name << " = " << val << std::endl;
        } else {
            std::cout << name << " = ?" << std::endl;
        }
    }
}

unsigned int Calc::AddSymbol(const std::string &str)
{
    return symbol_.Add(str);
}
