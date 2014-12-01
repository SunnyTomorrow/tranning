#include "exactime.h"
#include <stdio.h>
#include <time.h>

CExactime::CExactime()
{
	m_frzTime.gettimeofday();
}
CExactime::CExactime(const CExactime &et)
{
	m_frzTime = et.m_frzTime;
}
bool CExactime::Freeze()
{
	m_frzTime.gettimeofday();
}
string CExactime::GetDateStr()
{
	char str[20];
	time_t dt = m_frzTime[0];
	strftime(str,20,"%Y-%m-%d",localtime(&dt));
	return string(str);
}
string CExactime::GetTimeStr()
{
        char str[20];
	time_t dt = m_frzTime[0];
        strftime(str,20,"%H:%M:%S",localtime(&dt));
        return string(str);
}
string CExactime::GetUSecStr()
{
        char str[20];
	time_t us = m_frzTime[1];
        sprintf(str,"%06lu",us);
        return string(str);
}
string CExactime::GetShowStr()
{
	return (GetDateStr() + " " + GetTimeStr() + " " + GetUSecStr());
}

