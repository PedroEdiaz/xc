#include <unistd.h>
#define u8 unsigned char

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

void write_err( char * s, char c, char * file, unsigned int line, unsigned int chr )
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

u8 read_chr( u8 * i, u8 s, char * buff,
	char * c, int fd, unsigned int * line, unsigned int * chr )
{
	if( ! *i )
		s=read( fd, buff, 0xff );

	if( *i==s )
	{
		*i=0;
		return s;
	}

	*c=buff[*i];
	++*i;

	++(*chr);
	if( *c == '\n' )
	{
		++*line;	
		*chr=0;
	}

	return  s;
}
