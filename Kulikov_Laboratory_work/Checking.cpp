#include "Checking.h"


bool EnteringCheckingBool()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!СheckingValues(ch, cin, '0', '1'));
	if (ch == '1')
	{
		return true;
	}
	return false;
}

bool CheckingString(string S)
{
	int i = 0;
	while ( i != S.size()) {
		if (!(S[i] >= 'A' && S[i] <= 'z') && !(S[i] == ' ') && !(S[i]>='0' && S[i]<='9') )
		{
			cout<<"В имени должны быть только латинские буквы или цифры."<<endl;
			return false;
		}
		++i;
	}
	return true;
}