#include "exactime.h"

#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
	CExactime now;
	now.Freeze();
	cout << now.GetShowStr() << endl;
	getchar();
	return 0;
}
