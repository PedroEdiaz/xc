#include "cc.h"

ct_t parse_ct( char * c, int fd )
{
	char base=10;
	ct_t res=0;

	if( *c=='0' )
	{
		*c=read_chr(fd);

		switch( *c )
		{
		case 'b':
			base=2;
			*c=read_chr(fd);
			goto end;
		case 'x':
			base=16;
			*c=read_chr(fd);
			goto hex;
		}
		base=8;
	end:
	}

	while( '0'<=*c &&  *c<='0'+base-1 )
	{
		res *= base;
		res += *c-'0';
		*c=read_chr(fd);
	}

	return  res;

hex:
	while( ('0'<=*c&&*c<='9') || ('a'<=*c&&*c<='f') )
	{
		res *= base;
		res += ('a'<=*c&&*c<='f')?*c-'a'+10:*c-'0';
		*c=read_chr(fd);
	}
	return  res;
}
