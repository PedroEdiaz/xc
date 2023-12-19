struct stack
{
	unsigned char i;
	unsigned char body[0xff];
};

void push( struct stack * s,  unsigned char val );
unsigned char pop( struct stack * s );
unsigned char peak( struct stack * s );

#ifdef IMPLEMENT

void push( struct stack * s, unsigned char val )
{
	s->body[(s->i)++]=val;
}

unsigned char pop( struct stack * s )
{
	return s->body[--(s->i)];
}

unsigned char peak( struct stack * s )
{
	return s->body[(s->i)-1];
}

#endif
