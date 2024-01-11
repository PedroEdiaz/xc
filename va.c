#include "cc.h"

char str[32];

char * parse_va( char * c, int fd )
{
	int i=0;

	while( ( 'a' <= *c && *c <= 'z' ) || *c=='_' )
	{
		str[i]=*c;

		*c=read_chr(fd);
		++i;

		if( i == 32 )
		{
			err( "Long string" , 0x00, 0 );
			goto end;
		}
	}
end:
	str[i]=0x00;

	return str;
}
