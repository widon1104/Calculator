#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cassert>
#include <tr1/memory>
#include "functiontable.h"

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}
private:
    Noncopyable(const Noncopyable &);
    const Noncopyable & operator=(const Noncopyable&);
};

//基类Node继承于Noncopyable, 防止拷贝构造
class Node : private Noncopyable
{
public:
    virtual double Calc() const = 0;
    virtual ~Node() {}
    virtual bool IsLValue() const
    {
        return false;
    }
    virtual void Assign(double x)
    {
        assert(!"Assign called incorrectlly.");
    }
};

class NumberNode : public Node
{
public:
    NumberNode(double number) : number_(number) {}
    double Calc() const;
private:
    const double number_;
};

class BinaryNode : public Node
{
public:
    BinaryNode(std::tr1::shared_ptr<Node>& left, std::tr1::shared_ptr<Node>& right) :
        left_(left), right_(right) {}
    ~BinaryNode();
protected:
    //Node * const left_;
    //Node * const right_;
    std::tr1::shared_ptr<Node> left_;
    std::tr1::shared_ptr<Node> right_;
};

class UnaryNode : public Node
{
public:
    UnaryNode(std::tr1::shared_ptr<Node>& child) : child_(child) {}
    ~UnaryNode();
protected:
    //std::tr1::shared_ptr<Node> const child_;
    std::tr1::shared_ptr<Node> const child_;
};

class FunctionNode : public UnaryNode
{
public:
    FunctionNode(std::tr1::shared_ptr<Node>& child, PtrFun pFun) :
        UnaryNode(child), pFun_(pFun) {}
    double Calc() const;
private:
    PtrFun pFun_;
};

//class AddNode : public BinaryNode
//{
//public:
//    AddNode(Node *left, Node *right) :
//        BinaryNode(left, right) {}
//    double Calc() const;
//};

//class SubNode : public BinaryNode
//{
//public:
//    SubNode(Node *left, Node *right) :
//        BinaryNode(left, right) {}
//    double Calc() const;
//};

//class MultiplyNode : public BinaryNode
//{
//public:
//    MultiplyNode(Node *left, Node *right) :
//        BinaryNode(left, right) {}
//    double Calc() const;
//};

//class DivideNode : public BinaryNode
//{
//public:
//    DivideNode(Node *left, Node *right) :
//        BinaryNode(left, right) {}
//    double Calc() const;
//};

class UMinusNode : public UnaryNode
{
public:
    UMinusNode(std::tr1::shared_ptr<Node> child) :
        UnaryNode(child) {};
    double Calc() const;
};

class MultipleNode : public Node
{
public:
    MultipleNode(std::tr1::shared_ptr<Node>& node)
    {
        AppendChild(node, true);
    }
    void AppendChild(std::tr1::shared_ptr<Node>& node, bool positive)
    {
        childs_.push_back(node);
        positives_.push_back(positive);
    }
    ~MultipleNode();
protected:
    std::vector<std::tr1::shared_ptr<Node> > childs_;
    std::vector<bool> positives_;
};

class SumNode : public MultipleNode
{
public:
    SumNode(std::tr1::shared_ptr<Node>& node) :
        MultipleNode(node) {}
    double Calc() const;
};

class ProductNode : public MultipleNode
{
public:
    ProductNode(std::tr1::shared_ptr<Node>& node) :
        MultipleNode(node) {}
    double Calc() const;
};

class Storage;
class VariableNode : public Node
{
public:
    VariableNode(unsigned int id, Storage& storage) :
        id_(id), storage_(storage){ }
    double Calc() const;
    bool IsLValue() const;
    void Assign(double val);
private:
    const unsigned int id_;
    Storage & storage_;
};

class AssignNode : public BinaryNode
{
public:
    AssignNode(std::tr1::shared_ptr<Node>& left, std::tr1::shared_ptr<Node>& right) :
        BinaryNode(left, right)
    {
        assert(left->IsLValue());
    }
    double Calc() const;
};

#endif // NODE_H
