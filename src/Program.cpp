#include "preCompiled.h"

Program::Program(const std::wstring& programPath)
	: path(programPath)
{
	if( std::filesystem::is_directory(path) || !std::filesystem::is_regular_file(path) || !path.has_extension() )
	{
		path = L"";
		return;
	}

	std::wstring ext = path.extension().native();
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	if( ext != L"exe" )
		path = L"";
}

// Checks to see if the program actually exists
// Returns: false on failure
bool Program::exists() const
{
	return std::filesystem::exists(path);
}

// Retrieves the Program version
// Returns: ProgramVersion on success
ProgramVersion Program::getVersion() const
{
	uint64_t ret = 0u;
	if( !exists() )
		return ret;

	DWORD dwLen, dwDummy;
	dwLen = GetFileVersionInfoSize(path.c_str(), &dwDummy);
	if( dwLen )
	{
		std::unique_ptr<BYTE> versionInfo(new BYTE[dwLen]);
		if( versionInfo )
		{
			if( GetFileVersionInfo(path.c_str(), NULL, dwLen, versionInfo.get()) )
			{
				UINT uLen;
				VS_FIXEDFILEINFO* ffi;
				if( VerQueryValue(versionInfo.get(), L"\\", reinterpret_cast<LPVOID*>(&ffi), &uLen) != 0 )
				{
					ret = (static_cast<uint64_t>(ffi->dwFileVersionMS) << 32) | (static_cast<uint64_t>(ffi->dwFileVersionLS));
				}
			}
		}
	}

	return ret;
}
