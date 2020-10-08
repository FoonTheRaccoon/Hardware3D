#include "RacException.h"
#include <sstream>
#include "dxerr.h"
#include <sstream>
#include <d3dcompiler.h>


RacException::RacException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* RacException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* RacException::GetType() const noexcept
{
	return "Rac Exception";
}

int RacException::GetLine() const noexcept
{
	return line;
}

const std::string& RacException::GetFile() const noexcept
{
	return file;
}

std::string RacException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}

// Graphics exception stuff
HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file),
	hr(hr)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}

const char* HrException::what() const noexcept
{
	std::ostringstream oss;
	const auto ErrorString = W2N(GetErrorString());
	const auto ErrorDescription = W2N(GetErrorDescription());
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << ErrorString << std::endl
		<< "[Description] " << ErrorDescription << std::endl;
	if (!info.empty())
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	}
	oss << GetOriginString();
	whatBuffer = oss.str();

	delete ErrorString, ErrorDescription;

	return whatBuffer.c_str();
}

const char* HrException::GetType() const noexcept
{
	return "Chili Graphics Exception";
}

HRESULT HrException::GetErrorCode() const noexcept
{
	return hr;
}

const WCHAR* HrException::GetErrorString() const noexcept
{
	return DXGetErrorStringW(hr);
}

WCHAR* HrException::GetErrorDescription() const noexcept
{
	WCHAR buf[512];
	DXGetErrorDescriptionW(hr, buf, sizeof(buf));
	return buf;
}

std::string HrException::GetErrorInfo() const noexcept
{
	return info;
}


const char* DeviceRemovedException::GetType() const noexcept
{
	return "Rac Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}
InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}


const char* InfoException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* InfoException::GetType() const noexcept
{
	return "Rac Graphics Info Exception";
}

std::string InfoException::GetErrorInfo() const noexcept
{
	return info;
}
