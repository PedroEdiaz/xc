#include "../cc.h"

lp_t codegen( struct stack ** st, struct stack ** ct )
{
	static lp_t lp=0;

	write_n( 1, lp );
	write( 1, ":\n", 2  );

	while( !isempty(*st) )
	{
		token_t * t;
		t=pop(st,1);

		write( 1, "\t", 1  );
		if(  *t!=FG_NUM )
		{
			write_n( 1, *t );
			goto cont;
		}

		write( 1, "\t", 1  );
		write_n( 1, *(ct_t*)pop(ct,sizeof(ct_t)) );
	cont:
		write( 1, "\n", 1  );
		++lp;
	}

	return lp;
}
