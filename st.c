#define ct_t unsigned long

struct stack
{
	struct stack *prev, *root;
	ct_t value;
};

void push( struct stack ** s,  ct_t val );

char isempty( struct stack * s );
ct_t pop( struct stack ** s );
ct_t peek( struct stack * s );

#ifdef IMPLEMENT
#include <stdlib.h>

void err( char *, char *, char );

char isempty( struct stack * s )
{
	return !s;
}

void push( struct stack ** s, ct_t val )
{
	struct stack * p=malloc(sizeof(struct stack));

	p->prev=*s;
	p->value=val;


	if( isempty( *s ) )
	{
		p->root=p;
		goto skip;
	}

	p->root=(*s)->root;
skip:
	*s=p;
	return;
}

ct_t pop( struct stack ** s )
{
	struct stack * p;
	ct_t res;

	res=(*s)->value;
	p=(*s)->prev;

	free(*s);
	*s=p;
	
	return res;
}

ct_t peek( struct stack * s )
{
	return s->value;
}

#endif
