#include "cc.h"

void optimize( struct stack ** st, struct stack ** ct )
{
	token_t t=pop(st);
	ct_t b,c;

	switch( arity(t) )
	{
	case 0:
		push(st,t);
		return;

	case 3:
		if( peek(*st) != FG_NUM )
			goto err1;

		pop(st);
		c=pop(ct);
	case 2:
		if( peek(*st) != FG_NUM )
			goto err2;

		pop(st);
		b=pop(ct);
	}

	if( peek(*st) != FG_NUM )
		goto err3;

	b=eval(t,pop(ct),b,c);
	push( ct, b );

	return;

err3:
err2:
err1:
	err( "Unrechable: Optimize", 0x00, 1 );
}
