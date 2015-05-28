#ifndef NODE_H
#define NODE_H


class Node
{
public:
    Node();
    ~Node();
    void Calc();
};

class NodePtr
{
public:
    explicit NodePtr(Node *ptr = NULL) :
        ptr_(ptr) { }

    NodePtr(NodePtr& other) :
        ptr_(other.Release()) { }

    NodePtr& operator = (NodePtr& other)
    {
        Reset(other.Release());
        return *this;
    }

    ~NodePtr()
    {
        delete ptr_;
    }
    Node* operator->() const
    {
        return ptr_;
    }
    Node* Get() const
    {
        return ptr_;
    }
    Node& operator *() const
    {
        return *Get();
    }

    //拷贝构造时候释放所有权
    Node* Release()
    {
        Node *tmp = ptr_;
        ptr_ = NULL;
        return tmp;
    }

    void Reset(Node* ptr = NULL)
    {
        if (ptr_ != ptr)
        {
            delete ptr_;
        }
        ptr_ = ptr;
    }

private:
    Node *ptr_;
};

#endif // NODE_H
