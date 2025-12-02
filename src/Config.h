/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#pragma once

#include <cstdint>

struct sConfig
{
    uint32_t border = 0;
    uint32_t padding = 1;
    bool pot = false;
    bool trim = false;
    bool multi = false;
    bool keepFloat = false;
    bool overlay = false;
    bool alowDupes = false;
    bool slowMethod = false;
    bool dropExt = false;
    uint32_t maxTextureSize = 2048u;

    void dump() const;
};
