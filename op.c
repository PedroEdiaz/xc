#include "cc.h"

void optimize( struct stack ** st, struct stack ** ct )
{
	token_t * t;
	ct_t b,c;

	t=pop(st,1);
	switch( arity(*t) )
	{
	case 0:
		push(st,t,1);
		return;

	case 3:
		if( peek(*st) != FG_NUM )
			goto err1;

		pop(st,1);
		c=*(ct_t*)pop(ct,sizeof(ct_t));
	case 2:
		if( peek(*st) != FG_NUM )
			goto err2;

		pop(st,1);
		b=*(ct_t*)pop(ct,sizeof(ct_t));
	}

	if( peek(*st) != FG_NUM )
		goto err3;

	b=eval(*t,*(ct_t*)pop(ct,sizeof(ct_t)),b,c);
	push( ct, &b, sizeof(ct_t) );

	return;

err3:
err2:
err1:
	err( "Unrechable: Optimize", 0x00, 1 );
}
