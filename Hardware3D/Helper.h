#pragma once

//Helper Functions
#include "FrameTimer.h"
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <string>
#include <mbstring.h>
#include <memory>

//Global timer to be used by everything (Unless local scope timer is need)
inline FrameTimer globalTimer;

//const char* to const wchar_t*conversion NEED TO DELETE OUTSIDE OF FUNCTION
inline const wchar_t* N2W(const char* orig)
{
	size_t newsize = strlen(orig) + 1;

	wchar_t* wcstring = new wchar_t[newsize];

	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

	return wcstring;
}

//const wchar_t* to const char* conversion NEED TO DELETE OUTSIDE OF FUNCTION
inline const char* W2N(const wchar_t* orig)
{
    size_t origsize = wcslen(orig) + 1;
    size_t convertedChars = 0;

    char strConcat[] = " (char *)";
    size_t strConcatsize = (strlen(strConcat) + 1) * 2;

    const size_t newsize = origsize * 2;

    char* nstring = new char[newsize + strConcatsize];

    wcstombs_s(&convertedChars, nstring, newsize, orig, _TRUNCATE);

    _mbscat_s((unsigned char*)nstring, newsize + strConcatsize, (unsigned char*)strConcat);

    return nstring;
}