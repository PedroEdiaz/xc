#include "cc.h"

int optimize( struct stack * st, struct stack * ct )
{
	token_t t=pop(st);
	int c;

	switch( arity(t) )
	{
	case 2:
		if( peak(st) )
			goto err;

		pop(st);
		c=pop(ct);
	}

	if( peak(st)  )
		goto err;

	pop(st);
	push( ct, eval(t,pop(ct),c) );

	push( st, FG_NUM );
	return 1;

err:
	return 0;
}

char *  codegen( struct stack * st, struct stack * ct )
{
	while( st->i )
	{
		char t;
	
		if(  t=pop(st) )
		{
			write_n( 1, t );
			write( 1, "\n", 1  );
			goto cont;
		}

		write( 1, "\t", 1  );
		write_n( 1, pop(ct) );
		write( 1, "\n", 1  );

	cont:
	}

	return 0;
}
