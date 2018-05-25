#pragma once
#include <string>
#include <map>

#define GetTGMTConfig TGMTConfig::GetInstance
#ifdef UNICODE
#define TGMT_STRING std::wstring
#define TGMTSTR LPCWSTR
#else
#define TGMT_STRING std::string
#define TGMTSTR LPCSTR
#endif

class TGMTConfig
{
	static TGMTConfig* instance;

	class INIReader
	{
	private:
		int m_lastReadSuccess;
		std::map<std::string, std::string> _values;
		static std::string MakeKey(std::string section, std::string name);
		static int ValueHandler(void* user, char* section, char* name, char* value);

	public:
		INIReader();

		bool LoadSetting(std::string settingFile);

		std::string ReadValueString(std::string section, std::string name, std::string default_value);
		long ReadValueInt(std::string section, std::string name, long default_value);
		double ReadValueDouble(std::string section, std::string name, double default_value);
		//valid true values are "true", "yes", "on", "1",
		// and valid false values are "false", "no", "off", "0" (not case sensitive).
		bool ReadValueBool(std::string section, std::string name, bool default_value);
		bool LastReadSuccess();
	}m_reader;


	std::string m_iniFile;
	std::string TGMTConfig::ReadSetting(std::string iniFile, std::string section, std::string key);

	bool m_lastReadSuccess;
public:
	static TGMTConfig* GetInstance()
	{
		if (!instance)
			instance = new TGMTConfig();
		return instance;
	}

	TGMTConfig();
	~TGMTConfig();

	bool LoadSettingFromFile(std::string settingFile = "config.ini");

#if (defined(WIN32) || defined(WIN64)) && defined( UNICODE)
	std::wstring ReadValueWString(std::string section, std::string key, std::wstring defaultValue = L"");
#endif
	std::string ReadValueString(std::string section, std::string key, std::string defaultValue = "");
	int ReadValueInt(std::string section, std::string key, int defaultValue = 0);
	bool ReadValueBool(std::string section, std::string key, bool defaultValue = false);
	double ReadValueDouble(std::string section, std::string key, double defaultValue = 0.f);

	bool LastReadSuccess();

#if defined(WIN32) || defined(WIN64)
	void WriteConfigString(std::string section, std::string key, std::string value);
#ifdef UNICODE
	void WriteConfigWString(std::string section, std::string key, std::wstring value);
#endif
	void WriteConfigInt(std::string section, std::string key, int value);
	void WriteConfigDouble(std::string section, std::string key, double value);
	void WriteConfigBool(std::string section, std::string key, bool value);
#endif



};
