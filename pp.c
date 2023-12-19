#include "cc.h"

int parse_pp( char * c, int fd )
{
	*c=read_chr(fd);
	switch( *c )
	{
	case '!':
		while( (*c=read_chr(fd))!='\n' )
			;
	}
	return 1;
}
