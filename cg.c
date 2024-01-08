#include "cc.h"

void optimize( struct stack * st, struct stack * ct )
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

	return;

err3:
err2:
err1:
	err( "Unrechable", 0x00, 1 );
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

#warning	This may not work, but works for me.
		write( 1, "\t", 1  );
		write_n( 1, *(ct_t*)&(ct->body[k]) );
		write( 1, "\n", 1  );

		k+=8;

	cont:
	}

	st->i=ct->i=0;
	return 0;
}
