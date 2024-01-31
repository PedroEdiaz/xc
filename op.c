#include "cc.h"

void optimize( struct stack * st, struct stack * ct )
{
	token_t t=pop(st,1);
	ct_t b,c;

	switch( arity(t) )
	{
	case 0:
		push(st,t,1);
		return;

	case 3:
		if( peek(st) != FG_NUM )
			goto err1;

		pop(st,1);
		c=pop(ct,sizeof(ct_t));
	case 2:
		if( peek(st) != FG_NUM )
			goto err2;

		pop(st,1);
		b=pop(ct,sizeof(ct_t));
	}

	if( peek(st) != FG_NUM )
		goto err3;

	b=eval(t,pop(ct,sizeof(ct_t)),b,c);
	push( ct, b, sizeof( ct_t) );

	return;

err3:
err2:
err1:
	err( "Unrechable: Optimize", 0x00, 1 );
}
