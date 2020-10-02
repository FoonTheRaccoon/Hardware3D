#pragma once

//Helper Functions
#include <stdlib.h>
#include <cstring>

//Little ASCII to wchar conversion
inline const wchar_t* U2W(const char* orig)
{
	size_t newsize = strlen(orig) + 1;

	wchar_t* wcstring = new wchar_t[newsize];

	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

	return wcstring;
}