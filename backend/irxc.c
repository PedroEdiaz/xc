#include "../cc.h"

int codegen( struct stack ** st, struct stack ** ct )
{
	while( !isempty(*st) )
	{
		token_t * t;
		t=pop(st,1);

		if(  *t!=FG_NUM )
		{
			write_n( 1, *t );
			goto cont;
		}

		write( 1, "\t", 1  );
		write_n( 1, *(ct_t*)pop(ct,sizeof(ct_t)) );
	cont:
		write( 1, "\n", 1  );
	}

	return 0;
}
