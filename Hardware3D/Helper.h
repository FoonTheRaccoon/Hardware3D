#pragma once

//Helper Functions
#include <stdlib.h>
#include <cstring>
#include <memory>

//Little char to wchar_t conversion NEED TO DELETE OUTSIDE OF FUNCTION
inline const wchar_t* N2W(const char* orig)
{
	size_t newsize = strlen(orig) + 1;

	wchar_t* wcstring = new wchar_t[newsize];

	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

	return wcstring;
}