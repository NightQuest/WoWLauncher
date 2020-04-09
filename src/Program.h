#pragma once

class ProgramVersion
{
public:
	ProgramVersion(uint64_t _version)
		: version(_version)
	{
	}

	std::wstring getString() const
	{
		std::wstringstream ss;
		ss << version_major
			<< L"."
			<< version_minor
			<< L"."
			<< version_patch
			<< L"."
			<< version_hotfix;
		return ss.str();
	}

	union
	{
#pragma pack(push, 1)
		struct
		{
			uint16_t version_major;
			uint16_t version_minor;
			uint16_t version_patch;
			uint16_t version_hotfix;
		};
#pragma pack(pop)
		uint64_t version;
	};
};

class Program
{
public:
	Program() = delete;
	Program(const std::wstring& programPath);

	operator bool() const { return exists(); }

	bool exists() const;
	ProgramVersion getVersion() const;

protected:
	std::filesystem::path path;
};
