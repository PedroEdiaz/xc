#define token_t unsigned char

struct stack
{
	struct stack *prev;
	void * value;
};

void push( struct stack ** s, void * val, char size );

char isempty( struct stack * s );
void * pop( struct stack ** s, char size );
token_t peek( struct stack * s );

#ifdef IMPLEMENT
#include <stdlib.h>
#include <string.h>

char isempty( struct stack * s )
{
	return !s;
}

void push( struct stack ** s, void * val, char size )
{
	struct stack * p=malloc(sizeof(struct stack));

	p->prev=*s;
	p->value=malloc(size);
	memcpy( p->value, val, size );

	*s=p;
	return;
}

void * pop( struct stack ** s, char size )
{
	struct stack * p;
	void * res;

	res=malloc(size);
	memcpy( res, (*s)->value, size );

	p=(*s)->prev;

	free((*s)->value);
	free(*s);
	*s=p;
	
	return res;
}

token_t peek( struct stack * s )
{
	token_t res;
	memcpy( &res, s->value, 1 );
	return res;
}

#endif
