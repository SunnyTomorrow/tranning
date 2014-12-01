#include "logging.h"

#include <iostream>
#include <cstdio>
using namespace std;

bool func1(const string &str)
{
	cout << "cout\t" << str;
}
bool func2(const string &str)
{
	printf("printf\t%s",str.data());
}
int main()
{
	int age1 = 28,age2 = 82;
	DataLogging::UseCall(func1);
	DataLogging::UseFile("test.log");
	DataLogging::Logging("oh my god!");
	DataLogging::Logging("she is %d year old, her hasbund is %d year old!"
	, age1, age2);
	DataLogging::UseCall(func2);
	DataLogging::Logging("hello test1!");
	DataLogging::DumpCall(func1);
	DataLogging::UseCall(func2);
	DataLogging::Logging("hello test2!");
	DataLogging::DumpFile("test.log");
	DataLogging::Logging("hello test3!");
	DataLogging::Clear();
	DataLogging::Logging("hello test4!");
	getchar();
	return 0;
}
