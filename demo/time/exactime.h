#ifndef _EXACTIME_H_
#define _EXACTIME_H_

#include "timevalue.h"

#include <string>
using namespace std;

class CExactime
{
public:
	CExactime();
	CExactime(const CExactime &et);

	bool Freeze();
	string GetDateStr();
	string GetTimeStr();
	string GetUSecStr();
	string GetShowStr();
private:
	Timevalue m_frzTime;
};

#endif//_EXACTIME_H_
