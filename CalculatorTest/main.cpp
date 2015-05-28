#include <iostream>
#include <memory>
#include <vector>
#include <tr1/memory>
#include "node.h"
#include "debug_new.h"

using namespace std;

int main()
{
    //cout << "Hello World!" << endl;
    //int *p = new int;
    //delete p;

    //int *p2 = new int[5];
    //delete[] p2;

    NodePtr np(new Node);
    np->Calc();
    NodePtr np2(np);
    NodePtr np3;
    np3 = np2;

    /*
    std::auto_ptr<Node> node(new Node);
    vector<std::auto_ptr<Node> > v;
    v.push_back(node);
    */

    std::tr1::shared_ptr <Node> node2(new Node);
    vector<std::tr1::shared_ptr <Node> > v;
    v.push_back(node2);
    return 0;
}
