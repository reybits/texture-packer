/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#pragma once

#include "Atlas/AtlasSize.h"

#include <string>

class AtlasPacker;
class cFile;
class cTrim;
struct sConfig;

class cImageList final
{
public:
    cImageList(const sConfig& config, uint32_t reserve);
    ~cImageList();

    enum class Result
    {
        OK,
        NotAnImage,
        CannotOpen,
        TooBig,
    };
    Result loadImage(const std::string& path, uint32_t trimCount);

    bool doPacking(const char* desiredAtlasName, const char* outputResName,
                   const char* resPathPrefix, sSize& atlasSize);

    const ImageList& getList() const
    {
        return m_images;
    }

private:
    bool prepareSize(AtlasPacker* packer, const sSize& atlasSize);
    bool prepareAtlas(AtlasPacker* packer, sSize& atlasSize);
    void writeHeader(cFile& file);
    void writeFooter(cFile& file);

private:
    const sConfig& m_config;
    cAtlasSize m_size;
    cTrim* m_trim;

private:
    ImageList m_images;
};
