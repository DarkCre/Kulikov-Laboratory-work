#include "Checking.h"


bool EnteringCheckingBool()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!�heckingValues(ch, cin, '0', '1'));
	if (ch == '1')
	{
		return true;
	}
	return false;
}