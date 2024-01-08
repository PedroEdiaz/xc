#include "../cc.h"

int codegen( struct stack * st, struct stack * ct )
{
	while( !isempty(st) )
	{
		char t;

		if(  t=unqueue(st,1) )
		{
			write_n( 1, t );
			goto cont;
		}

		write( 1, "\t", 1  );
		write_n( 1, unqueue(ct,8) );
	cont:
		write( 1, "\n", 1  );
	}

	return 0;
}
