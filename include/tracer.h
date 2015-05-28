#ifndef TRACER_H
#define TRACER_H

#ifndef NDEBUG

#include <iostream>
#include <cstdlib>
#include <map>

void* operator new(size_t size) throw(std::bad_alloc);
void* operator new(size_t size, const char *file, long line);
void* operator new[](size_t size, const char *file, long line);

void operator delete(void* p) throw();
void operator delete(void* p, const char*, long);
void operator delete[](void* p) throw();

class Tracer
{
private:
    class Entry
    {
    public:
        Entry(const char *file = 0, long line = 0) :
            file_(file), line_(line) {}
        const char* File() const { return file_; }
        long Line() const { return line_; }
    private:
        const char *file_;
        long line_;
    };
    class Lock
    {
    public:
        Lock(Tracer& tracer) : tracer_(tracer)
        {
            tracer_.lock();
        }
        ~Lock()
        {
            tracer_.unlock();
        }
    private:
        Tracer& tracer_;
    };

    friend class Lock;
public:
    Tracer();
    ~Tracer();

    static bool ready;

    void Add(void *p, const char *file, long line);
    void Remove(void *p);
    void Dump();

private:
    std::map<void*, Entry> mapEntry_;
    //防止new的递归调用
    int lockCount_;
    void lock()
    {
        lockCount_++;
    }
    void unlock()
    {
        lockCount_--;
    }
};

extern  Tracer NewTrace;

#endif

#endif // TRACER_H
