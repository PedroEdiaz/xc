#include "cc.h"

int optimize( struct stack * st, struct stack * ct )
{
	token_t t=pop(st,1);
	ct_t b,c;

	switch( arity(t) )
	{
	case 3:
		if( peak(st) )
			goto err1;

		pop(st,1);
		c=pop(ct,sizeof(ct_t));
	case 2:
		if( peak(st) )
			goto err2;

		pop(st,1);
		b=pop(ct,sizeof(ct_t));
	}

	if( peak(st) )
		goto err3;

	b=eval(t,pop(ct,sizeof(ct_t)),b,c);
	push( ct, b, sizeof( ct_t) );

	return 1;

err3:
err2:
err1:
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
