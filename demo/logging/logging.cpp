#include "logging.h"

#include <stdio.h>
#include <stdarg.h>

CExactime                DataLogging::s_timer;
set<DataLogging::ABLogWriter*>        DataLogging::s_curWriter;
map<string,DataLogging::ABLogWriter*> DataLogging::s_writers;

bool DataLogging::Logging(const string &strLine)
{
	bool bRet = false;
	s_timer.Freeze();
	for (set<ABLogWriter*>::iterator it = s_curWriter.begin(); it != s_curWriter.end(); it++)
	{
		if (*it != NULL)
		{
			if((*it)->Write(s_timer.GetShowStr() + "\t" + strLine + "\n"))
			{
				if (!bRet)
				{
					bRet = true;
				}
			}
		}
	}
	return bRet;
}
bool DataLogging::Logging(const char *fmt, ...)
{
	if (fmt == NULL)
	{
		return false;
	}
	va_list args;
	char buf[1024];
	int len = 0;
	va_start(args,fmt);
	len = vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	if (len < 1)
	{
		return false;
	}
	return Logging(string(buf));
}
bool DataLogging::UseCall(WriteCallBack wrCall)
{
	char idx[32];
	sprintf(idx,"%lX",(unsigned long)wrCall);
	if (wrCall != NULL)
	{
		if (s_writers.count(idx) < 1)
		{
			//ABLogWriter * p = (ABLogWriter *)(new DataLogging::CCallLogWriter(wrCall));
			s_writers[string(idx)] = new CCallLogWriter(wrCall);
		}
		s_curWriter.insert(s_writers[string(idx)]);
	}
	else
	{
		return false;
	}
	return true;
}
bool DataLogging::DumpCall(WriteCallBack wrCall)
{
	char idx[32];
	sprintf(idx,"%lX",(unsigned long)wrCall);
	if (s_writers.count(string(idx)) > 0 && s_curWriter.count(s_writers[string(idx)]) > 0)
	{
		s_curWriter.erase(s_writers[string(idx)]);
	}
	else
	{
		return false;
	}
}


bool DataLogging::UseFile(const string &strFileName)
{
	if (!strFileName.empty())
	{
		if (s_writers.count(strFileName) < 1)
		{
			//ABLogWriter * p = new DataLogging::CFileLogWriter(strFileName);
			s_writers[strFileName] = new CFileLogWriter(strFileName);
		}
		s_curWriter.insert(s_writers[strFileName]);
	}
	else
	{
		return false;
	}
	return true;
}
bool DataLogging::DumpFile(const string &strFileName)
{
	if (s_writers.count(strFileName) > 0 
		&& s_curWriter.count(s_writers[strFileName]) > 0)
	{
		s_curWriter.erase(s_writers[strFileName]);
	}
	else
	{
		return false;
	}
}
bool DataLogging::Clear()
{
	s_curWriter.clear();
	for (map<string,ABLogWriter*>::iterator it = s_writers.begin(); it != s_writers.end(); it++)
	{
		delete it->second;
	}
	s_writers.clear();
	return true;
}

/////////////////file writer
DataLogging::CFileLogWriter::CFileLogWriter(const string &strFile)
{
	m_strFileName = strFile;
	m_bOpen = false;
	if (m_strFileName.empty())
	{
		m_strFileName = "new.log";
	}
}
DataLogging::CFileLogWriter::~CFileLogWriter()
{
	m_of.close();
}
bool DataLogging::CFileLogWriter::Write(const string &wrStr)
{
	if (!m_bOpen)
	{
		m_of.open(m_strFileName.data(),ios::app);
		if (!m_of)
		{
			return false;
		}
		m_bOpen = true;
	}
	m_of << wrStr;
	return true;
}

///////call writer
DataLogging::CCallLogWriter::CCallLogWriter(WriteCallBack wrCall)
{
	if (wrCall != NULL)
	{
		m_pCall = wrCall;
	}
	else
	{
		m_pCall = NULL;
	}
}
bool DataLogging::CCallLogWriter::Write(const string &wrStr)
{
	if (m_pCall == NULL)
	{
		return false;
	}
	return m_pCall(wrStr);
}

