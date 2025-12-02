/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#include "File.h"
#include "Log.h"

cFile::cFile()
{
}

cFile::~cFile()
{
    close();
}

bool cFile::open(const char* path, const char* mode)
{
    m_file = ::fopen(path, mode);
    if (m_file != nullptr)
    {
        (void)::fseek(m_file, 0, SEEK_END);
        m_size = static_cast<uint32_t>(::ftell(m_file));
        (void)::fseek(m_file, 0, SEEK_SET);

        return true;
    }

    cLog::Error("Can't open '{}'.", path);

    return false;
}

void cFile::close()
{
    if (m_file != nullptr)
    {
        (void)::fclose(m_file);
        m_file = nullptr;
    }
}

uint32_t cFile::seek(uint32_t offset, int whence) const
{
    return static_cast<uint32_t>(::fseek(m_file, offset, whence));
}

uint32_t cFile::read(void* ptr, uint32_t size) const
{
    if (m_file != nullptr)
    {
        return static_cast<uint32_t>(::fread(ptr, 1, size, m_file));
    }

    return 0u;
}

uint32_t cFile::write(const void* ptr, uint32_t size) const
{
    if (m_file != nullptr)
    {
        return static_cast<uint32_t>(::fwrite(ptr, 1, size, m_file));
    }

    return 0u;
}

uint32_t cFile::getOffset() const
{
    if (m_file != nullptr)
    {
        return static_cast<uint32_t>(::ftell(m_file));
    }

    return 0u;
}
