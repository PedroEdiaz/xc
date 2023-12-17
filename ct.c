#include <unistd.h>
#define u8 unsigned char

u8 parse_cnt( u8 * res, u8 * i, u8 s, char * buff,
	char * c, int fd, unsigned int * line, unsigned int * chr )
{
	char base=10;
	*res=0;

	if( *c=='0' )
	{
		if( !read_chr( i, s, buff, c, fd, line, chr ) )
			return 0;

		switch( *c )
		{
		case 'b':
			base=2;
			if( !read_chr( i, s, buff, c, fd, line, chr ) )
				return 0;
			goto end;
		case 'x':
			base=16;
			if( !read_chr( i, s, buff, c, fd, line, chr ) )
				return 0;
			goto hex;
		}
		base=8;
	end:
	}

	while( '0'<=*c &&  *c<='0'+base-1 )
	{
		*res *= base;
		*res += *c-'0';

		if( !read_chr( i, s, buff, c, fd, line, chr ) )
			return 0;
	}

	return  s;

hex:
	while( ('0'<=*c&&*c<='9') || ('a'<=*c&&*c<='f') )
	{
		*res *= base;
		*res += ('a'<=*c&&*c<='f')?*c-'a'+10:*c-'0';

		if( !read_chr( i, s, buff, c, fd, line, chr ) )
			return 0;
	}
	return  s;
}
