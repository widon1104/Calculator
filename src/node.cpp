#include <cmath>
#include <iostream>
#include "storage.h"
#include "node.h"
#include "exception.h"
#include "debug_new.h"

double NumberNode::Calc() const
{
    return number_;
}

//double AddNode::Calc() const
//{
//    return left_->Calc() + right_->Calc();
//}
//double SubNode::Calc() const
//{
//    return left_->Calc() - right_->Calc();
//}

//double MultiplyNode::Calc() const
//{
//    return left_->Calc() * right_->Calc();
//}

//double DivideNode::Calc() const
//{
//    double divisor = right_->Calc();
//    if (divisor != 0) {
//        return  left_->Calc() / divisor;
//    } else {
//        std::cout << "Error: Divisor by zero" << std::endl;
//        return HUGE_VAL;
//    }

//}


BinaryNode::~BinaryNode()
{
    //delete left_;
    //delete right_;
}

UnaryNode::~UnaryNode()
{
    //delete child_;
}

double UMinusNode::Calc() const
{
    return -child_->Calc();
}

double FunctionNode::Calc() const
{
    return (*pFun_)(child_->Calc());
}

MultipleNode::~MultipleNode()
{
    /*
    std::cout << "~MultipleNode" << std::endl;
    std::vector<Node *>::const_iterator it;
    for (it = childs_.begin(); it != childs_.end(); it++) {
        delete *it;
    }
    */
}

double SumNode::Calc() const
{
    double result = 0.0;
    std::vector<std::tr1::shared_ptr<Node> >::const_iterator child_it = childs_.begin();
    std::vector<bool>::const_iterator positive_it = positives_.begin();
    for (; child_it != childs_.end();  child_it++, positive_it++) {
        assert(positive_it != positives_.end());
        double val = (*child_it)->Calc();
        if (*positive_it)
            result += val;
        else
            result -= val;
    }
    assert(positive_it == positives_.end());
    return result;
}

double ProductNode::Calc() const
{
    double result = 1;
    std::vector<std::tr1::shared_ptr<Node> >::const_iterator child_it = childs_.begin();
    std::vector<bool>::const_iterator positive_it = positives_.begin();
    for (; child_it != childs_.end();  child_it++, positive_it++) {
        assert(positive_it != positives_.end());
        double val = (*child_it)->Calc();
        if (*positive_it)
            result *= val;
        else if (val != 0.0)
            result /= val;
        else {
            throw Exception("Division by zero");
        }
    }
    assert(positive_it == positives_.end());
    return result;
}

double VariableNode::Calc() const
{
    double x = 0.0;
    if (storage_.IsInit(id_)) {
        x = storage_.GetValue(id_);
    } else {
        throw SyntaxError("Use of uninitalized variable.");
    }
    return x;
}

bool VariableNode::IsLValue() const
{
    return true;
}

void VariableNode::Assign(double val)
{
    storage_.SetValue(id_, val);
}

double AssignNode::Calc() const
{
    double x = 0.0;
    x = right_->Calc();
    left_->Assign(x);
    return x;
}
