#include <unistd.h>

void write_n( int fd, int n )
{
	unsigned char buff[0xff], i=0xff-1;

	buff[i]='\0';

	goto start;

	while( n )
	{
	start:	
		--i;
		buff[i]='0'+n%10;
		n/=10;
	}

	write( fd, buff+i, 0xff-i );
}

int strlen( char * s )
{
	char * p;

	p=s;
	while( *p )
		++p;

	return p-s;
}

void write_err( char * s, char * file, unsigned int line, unsigned int chr )
{
	char d[2] = { ':', '\n' };

	write( 2, file, strlen(file) );
	write( 2, d, 1 );

	write_n( 2, line);
	write( 2, d, 1 );

	write_n( 2, chr);
	write( 2, d, 1 );

	write( 2, s, strlen(s) );
	write( 2, d+1, 1 );
}
