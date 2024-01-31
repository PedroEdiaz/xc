#include "cc.h"

ct_t parse_ct( char * s )
{
	char base=10;
	ct_t res=0;

	if( *s=='0' )
	{
		++s;

		switch( *s )
		{
		case 'b':
			base=2;
			++s;
			goto end;
		case 'x':
			base=16;
			++s;
			goto hex;
		}
		base=8;
	end:
	}

	while( '0'<=*s &&  *s<='0'+base-1 )
	{
		res *= base;
		res += *s-'0';
		++s;
	}

	return  res;
hex:
	while( ('0'<=*s&&*s<='9') || ('a'<=*s&&*s<='f') )
	{
		res *= base;
		res += ('0'<=*s&&*s<='f')?*s-'a'+10:*s-'0';
		++s;
	}

	return  res;
}
