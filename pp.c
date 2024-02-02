#include "cc.h"

void trow( int fd, int b )
{
	unsigned int i=0;
	char buff[255];

	while( (buff[i]=read_chr(fd))!='\n' )
		++i;

	buff[i]=0x00;
	return err( "Preprocesor", buff, b );
}

void parse_pp( int fd )
{
	char *str, c;

	str = tokenize( fd );

	if( !strcmp( str, "warning" ) )
		return trow( fd, 0 );	

	if( !strcmp( str, "error" ) )
		return trow( fd, 1 );	

	while( read_chr(fd)!='\n' )
		;

	err( "No preprocessor directive", str, 0 );
	return;
}
