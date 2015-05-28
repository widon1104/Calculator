#include <iostream>
#include "node.h"

Node::Node()
{
    std::cout << "Node ..." << std::endl;
}

Node::~Node()
{
    std::cout << "~Node ..." << std::endl;
}

void Node::Calc()
{
    std::cout << "Calc ..." << std::endl;
}

