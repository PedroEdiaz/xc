#define ct_t unsigned long

struct stack
{
	unsigned char i;
	unsigned char body[0xff];
};

void push( struct stack * s,  ct_t val, char size );
ct_t pop( struct stack * s , char size );
ct_t peak( struct stack * s );

#ifdef IMPLEMENT

void push( struct stack * s, ct_t val, char size )
{
	while( size )
	{
		s->body[(s->i)++]=val;
		val>>=8;
		--size;
	}
}

ct_t pop( struct stack * s,  char size )
{
	ct_t res=0;
	while( size )
	{
		res<<=8;
		res+=s->body[--(s->i)];
		--size;
	}

	return res;
}

ct_t peak( struct stack * s )
{
	return s->body[(s->i)-1];
}

#endif
