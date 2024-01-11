#include "cc.h"

void trow( char * c, int fd, int b )
{
	unsigned int i=0;
	char buff[255];

	while( (*c=read_chr(fd))!='\n' )
	{
		buff[i]=*c;
		++i;
	}
	buff[i]=0x00;
	err( buff, 0x00, b );
	return;
}

void parse_pp( char * c, int fd )
{
	char * str;
	*c=read_chr(fd);

	switch( *c )
	{
	case '!':
		while( (*c=read_chr(fd))!='\n' )
			;
		return; 
	}

	str = parse_va( c, fd );

	if( !strcmp( str, "warning" ) )
		return trow( c, fd, 0 );	

	if( !strcmp( str, "error" ) )
		return trow( c, fd, 1 );	

	err( "No preprocessor directive", *c, 0 );
	return;
}
