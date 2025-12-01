/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#pragma once

#include <cstdint>
#include <vector>

class cImage;

using ImageList = std::vector<cImage*>;

struct sSize
{
    uint32_t width = 0u;
    uint32_t height = 0u;
};

struct sOffset
{
    uint32_t x = 0u;
    uint32_t y = 0u;
};

struct sHotspot
{
    float x = 0.0f;
    float y = 0.0f;
};

struct sRect
{
    uint32_t width() const
    {
        return right - left;
    }

    uint32_t height() const
    {
        return bottom - top;
    }

    uint32_t left;
    uint32_t top;
    uint32_t right;
    uint32_t bottom;
};
