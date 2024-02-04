#include "cc.h"

struct define
{
	char *key, *value;
};

char * pp = "Preprocesor";

char * trow( fd_t fd )
{
	unsigned int i=0;
	static char buff[255];

	while( (buff[i]=read_chr(fd))!='\n' )
		++i;

	buff[i]=0x00;
	return buff;
}

struct stack * defines=NULL;

void parse_pp( fd_t fd )
{
	char *str, c;
	

	str = tokenize( fd );

	if( !strcmp( str, "warning" ) )
		return err( pp, trow(fd), 0 );

	if( !strcmp( str, "error" ) )
		return err( pp, trow(fd), 1 );

	if( !strcmp( str, "define" ) )
	{
		struct define d;

		while( (str=tokenize(fd)) )
		{
			if( token(str) != FG_BLK )
				goto end;
		}
	end:

		d.key=malloc( strlen(str) );
		strcpy( d.key, str );

		str=trow(fd);
		d.value=malloc( strlen(str) );
		strcpy( d.value, str );


		push( &defines, &d, sizeof(struct define) );
		return;	
	}

	while( read_chr(fd)!='\n' )
		;

	err( "No preprocessor directive", str, 0 );
	return;
}

char * definition( char * str )
{
	struct stack * s;
	struct define * d;

	s=defines;
	while( s )
	{
		d=s->value;
		if ( !strcmp( str, d->key ) )
			return d->value;
		s=s->prev;
	}
	return str;
}
