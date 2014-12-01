#ifndef _LOGGING_H_
#define _LOGGING_H_

#include "exactime.h"

#include <set>
#include <map>
#include <string>
#include <fstream>

using namespace std;

typedef bool (*WriteCallBack)(const string &);

class DataLogging
{
public:
	static bool Logging(const char * fmt, ...);
	static bool Logging(const string &trcLine);

	static bool UseCall(WriteCallBack wrCall);
	static bool DumpCall(WriteCallBack wrCall);
	static bool UseFile(const string &strFileName);
	static bool DumpFile(const string &strFileName);
	static bool Clear();
private:
	class ABLogWriter;
	static set<ABLogWriter*>        s_curWriter;
	static map<string,ABLogWriter*> s_writers;
	static CExactime                s_timer;
	//writer interface define
	class ABLogWriter
	{
	public:
		virtual ~ABLogWriter() {}
		virtual bool Write(const string &wrStr) = 0;
	//		virtual bool operator == (const ABLogWriter & writer) = 0;
	};
	///file writer define
	class CFileLogWriter: public ABLogWriter
	{
	public:
		CFileLogWriter(const string &strFile);
		~CFileLogWriter();
		bool Write(const string &wrStr);
	//	virtual bool operator == (const CFileLogWriter &writer);
	private:
		ofstream m_of;
		string m_strFileName;
		bool m_bOpen;
	};
	//// call writer define
	class CCallLogWriter: public ABLogWriter
	{
	public:
		CCallLogWriter(WriteCallBack wrCall);
		~CCallLogWriter(){}
		bool Write(const string &wrStr);
	//	virtual bool operator == (const CCallLogWriter &writer);
	private:
		WriteCallBack m_pCall;
	};
};
#endif//_LOGGING_H_
