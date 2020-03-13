#pragma once

class Registry
{
public:
	Registry();
	~Registry();


	bool Open(HKEY key, const std::wstring& path, REGSAM samDesired);
	bool Close();
	bool Create(HKEY key, const std::wstring& path, REGSAM samDesired, bool openExisting = false);
	DWORD getDWORD(const std::wstring& keyName);
	std::wstring getString(const std::wstring& keyName);
	std::wstring getMultiString(const std::wstring& keyName);

	bool setDWORD(const std::wstring& keyName, DWORD value);
	bool setString(const std::wstring& keyName, std::wstring& value);
	bool setMultiString(const std::wstring& keyName, std::wstring& value);

	std::wstring getLastError();

private:
	HKEY hKey;
	LSTATUS lastError;

	bool hasReturnedError(LSTATUS ret);
};
