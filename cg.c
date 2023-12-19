#include "cc.h"

int optimize( struct stack * st, struct stack * ct )
{
	token_t t=pop(st,1);
	int c;

	switch( arity(t) )
	{
	case 2:
		if( peak(st) )
			goto err;

		pop(st,1);
		c=pop(ct,sizeof(ct_t));
	}

	if( peak(st) )
		goto err;

	c=eval(t,pop(ct,sizeof(ct_t)),c);
	push( ct, c, sizeof(ct_t) );

	return 1;

err:
	return 0;
}

int codegen( struct stack * st, struct stack * ct )
{
	char j=0, k=0;

	while( j<st->i )
	{
		char t;
	
		t=st->body[j];
		j++;

		if(  t )
		{
			write_n( 1, t );
			write( 1, "\n", 1  );
			goto cont;
		}


		write( 1, "\t", 1  );
#warning This may not work, but works for me.
		write_n( 1, *(ct_t*)&(ct->body[k]) );
		k+=8;
		write( 1, "\n", 1  );

	cont:
	}

	return 0;
}
