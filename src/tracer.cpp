#include "tracer.h"

#ifndef NDEBUG

Tracer NewTrace;

bool Tracer::ready = false;

Tracer::Tracer() : lockCount_(0)
{
    ready = true;
}

Tracer::~Tracer()
{
    ready = false;
    Dump();
}

void* operator new(size_t size) throw(std::bad_alloc)
{
    void *p = malloc(size);
    if (Tracer::ready) {
        NewTrace.Add(p, "?", 0);
    }
    return p;
}

void* operator new(size_t size, const char *file, long line)
{
    void *p = malloc(size);
    if (Tracer::ready) {
        NewTrace.Add(p, file, line);
    }
    return p;
}

void* operator new[](size_t size, const char *file, long line)
{
    void *p = malloc(size);
    if (Tracer::ready) {
        NewTrace.Add(p, file, line);
    }
    return p;
}

void operator delete(void* p, const char*, long)
{
    if (Tracer::ready) {
        NewTrace.Remove(p);
    }
    free(p);
}

void operator delete(void* p) throw()
{
    if (Tracer::ready) {
        NewTrace.Remove(p);
    }
    free(p);
}

void operator delete[](void* p) throw()
{
    if (Tracer::ready) {
        NewTrace.Remove(p);
    }
    free(p);
}

void Tracer::Add(void *p, const char *file, long line)
{
    if (lockCount_ > 0)
        return;
    Tracer::Lock lock(*this);
    mapEntry_[p] = Entry(file, line);
}

void Tracer::Remove(void *p)
{
    if (lockCount_ > 0)
        return;
    Tracer::Lock lock(*this);
    std::map<void *, Entry>::iterator it;
    it = mapEntry_.find(p);
    if (it != mapEntry_.end()) {
        mapEntry_.erase(it);
    }
}

void Tracer::Dump()
{
    if (mapEntry_.size() > 0) {
        std::cout << "*** Memory leak *** " << std::endl;
        std::map<void *, Entry>::iterator it;
        for (it = mapEntry_.begin(); it != mapEntry_.end(); it++) {
            const char *file = it->second.File();
            long line = it->second.Line();
            std::cout << "0x" << std::hex << it->first << ":"
                      << "file: " << file << " line: "
                      << std::dec << line << std::endl;
        }
        std::cout << std::endl;
    }
}

#endif
