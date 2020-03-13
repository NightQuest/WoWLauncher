#include "preCompiled.h"

Registry::Registry()
	: hKey(nullptr), lastError(0)
{
}

Registry::~Registry()
{
	if( hKey )
		Close();
}

// Opens an existing key for use.
// Returns: true on success
bool Registry::Open(HKEY key, const std::wstring& path, REGSAM samDesired)
{
	if( hKey )
		Close();

	return !hasReturnedError(::RegOpenKeyEx(key, path.c_str(), 0, samDesired, &hKey));
}

// Closes the currently open key, if it exists
// Returns: true on success
bool Registry::Close()
{
	LSTATUS ret = ::RegCloseKey(hKey);
	hKey = nullptr;

	return !hasReturnedError(ret);
}

// Creates a key, can optionally open an existing key
// Returns: true on success
bool Registry::Create(HKEY key, const std::wstring& path, REGSAM samDesired, bool openExisting)
{
	if( hKey )
		Close();

	DWORD dwDisposition = 0; // either REG_CREATED_NEW_KEY or REG_OPENED_EXISTING_KEY
	bool ret = !hasReturnedError(::RegCreateKeyEx(key, path.c_str(), 0, nullptr, 0, samDesired, nullptr, &hKey, &dwDisposition));

	if( ret )
	{
		if( !openExisting && dwDisposition == REG_OPENED_EXISTING_KEY )
		{
			Close();
			return false;
		}

		return true;
	}

	return false;
}

// Returns: a DWORD from the specified key
DWORD Registry::getDWORD(const std::wstring& keyName)
{
	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(DWORD);
	DWORD dwRet = 0;

	if( !hasReturnedError(::RegQueryValueEx(hKey, keyName.c_str(), NULL, &dwType, reinterpret_cast<LPBYTE>(&dwRet), &dwSize)) )
		return dwRet;

	return 0;
}

// Returns: a string from the specified key
std::wstring Registry::getString(const std::wstring& keyName)
{
	DWORD dwType = REG_SZ;
	DWORD dwSize = 0;
	std::wstring ret;

	if( !hasReturnedError(::RegQueryValueEx(hKey, keyName.c_str(), NULL, &dwType, 0, &dwSize)) ) // First, get the size
	{
		ret.reserve(dwSize);
		hasReturnedError(::RegQueryValueEx(hKey, keyName.c_str(), NULL, &dwType, reinterpret_cast<LPBYTE>(&ret[0]), &dwSize)); // Now get the value
	}

	return ret;
}

// Returns: a multiline string from the specified key
std::wstring Registry::getMultiString(const std::wstring& keyName)
{
	DWORD dwType = REG_MULTI_SZ;
	DWORD dwSize = 0;
	std::wstring ret;

	if( !hasReturnedError(::RegQueryValueEx(hKey, keyName.c_str(), NULL, &dwType, 0, &dwSize)) ) // First, get the size
	{
		ret.reserve(dwSize);
		hasReturnedError(::RegQueryValueEx(hKey, keyName.c_str(), NULL, &dwType, reinterpret_cast<LPBYTE>(&ret[0]), &dwSize)); // Now get the value
	}

	return ret;
}

// Sets a DWORD in the registry
// Returns: true on success
bool Registry::setDWORD(const std::wstring& keyName, DWORD value)
{
	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(DWORD);

	return !hasReturnedError(::RegSetValueEx(hKey, keyName.c_str(), 0, dwType, reinterpret_cast<LPBYTE>(&value), dwSize));
}

// Sets a string in the registry
// Returns: true on success
bool Registry::setString(const std::wstring& keyName, std::wstring& value)
{
	DWORD dwType = REG_SZ;
	DWORD dwSize = (value.length()+1) * sizeof(wchar_t);

	return !hasReturnedError(::RegSetValueEx(hKey, keyName.c_str(), 0, dwType, reinterpret_cast<LPBYTE>(&value[0]), dwSize));
}

// Sets a multiline string in the registry
// Returns: true on success
bool Registry::setMultiString(const std::wstring& keyName, std::wstring& value)
{
	DWORD dwType = REG_MULTI_SZ;
	DWORD dwSize = (value.length() + 1) * sizeof(wchar_t);

	return !hasReturnedError(::RegSetValueEx(hKey, keyName.c_str(), 0, dwType, reinterpret_cast<LPBYTE>(&value[0]), dwSize));
}

// Retrieves a formatted message for the last error
std::wstring Registry::getLastError()
{
	std::wstring ret;
	wchar_t* ptr = nullptr;
	if( ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, lastError, 0, reinterpret_cast<wchar_t*>(&ptr), 1, nullptr) > 0 )
	{
		ret = ptr;
		::LocalFree(ptr);
	}

	lastError = 0;

	return ret;
}

// Returns: true on an error, and sets the 'lastError' accordingly.
bool Registry::hasReturnedError(LSTATUS ret)
{
	if( ret != ERROR_SUCCESS )
	{
		lastError = ret;
		return true;
	}

	return false;
}
