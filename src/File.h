/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#pragma once

#include <cstdint>
#include <cstdio>

class cFile final
{
public:
    cFile();
    ~cFile();

    bool open(const char* path, const char* mode = "rb");
    void close();

    uint32_t getOffset() const;

    uint32_t seek(uint32_t offset, int whence) const;
    uint32_t read(void* ptr, uint32_t size) const;
    uint32_t write(const void* ptr, uint32_t size) const;

    long getSize() const
    {
        return m_size;
    }

    void* getHandle() const
    {
        return m_file;
    }

protected:
    FILE* m_file = nullptr;
    uint32_t m_size = 0u;
};
