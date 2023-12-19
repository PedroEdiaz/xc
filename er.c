#include <unistd.h>
#define ct_t unsigned long

void write_n( int fd, ct_t n )
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

unsigned int line, chr;
unsigned int i, s;
char buff[0xff];

unsigned int init_err( void )
{
	unsigned int r;
	line=1;
	chr=0;
	return line;
}

char read_chr( int fd )
{
	char c;

	if( !i || i==s )
	{
		i=0;
		s=read( fd, buff, 0xff );
	}

	if( !s )
		return 0xff;

	c=buff[i];
	++i;

	++chr;
	if( c == '\n' )
	{
		++line;	
		chr=0;
	}

	return c;
}

void write_err( char * s, char c, char * file )
{
	char d[2] = { ':', '\n' };

	write( 2, file, strlen(file) );
	write( 2, d, 1 );

	write_n( 2, line);
	write( 2, d, 1 );

	write_n( 2, chr);
	write( 2, d, 1 );

	write( 2, s, strlen(s) );
	write( 2, d, 1 );

	if( c )
		write( 2, &c, 1 );

	write( 2, d+1, 1 );
}
