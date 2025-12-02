/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#pragma once

#include <cstdint>

void deprecatedOption(const char* oldArg, const char* newArg, const char* removeDate);

uint64_t getCurrentTime();
const char* formatNum(int num, char delimiter = '\'');
const char* isEnabled(bool enabled);

bool shiftArg(int argc, char* argv[], int& idx, const char*& value);
bool shiftArg(int argc, char* argv[], int& idx, uint32_t& value);
