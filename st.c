#define ct_t unsigned long
#define isempty( s ) (((s)->i)==((s)->j))
#define isfull( s, size ) (((s)->i)+size==((s)->j))
#define queue( s, size ) push( s, size )

struct stack
{
	unsigned char i,j;
	unsigned char body[0xff];
};
ct_t unqueue( struct stack * s , char size );
void push( struct stack * s,  ct_t val, char size );

ct_t pop( struct stack * s , char size );
ct_t peek( struct stack * s );

#ifdef IMPLEMENT

void err( char *, char, char );
char * err_msg_st[2] = {"Unreachable: Empty stack", "No space in stack"};

void push( struct stack * s, ct_t val, char size )
{
	if( isfull(s,size) )
		err( err_msg_st[1] , 0x00, 1 );

	while( size )
	{
		s->body[(s->i)++]=val;
		val>>=8;
		--size;
	}
}

ct_t unqueue( struct stack * s, char size )
{
	char aux;
	ct_t res=0;

	if( isempty(s) )
		err( err_msg_st[1] , 0x00, 1 );

	aux=(s->j+=size);

	while( size )
	{
		res<<=8;
		res+=s->body[--(s->j)];
		--size;
	}

	s->j=aux;

	return res;
}

ct_t pop( struct stack * s,  char size )
{
	ct_t res=0;

	if( isempty( s ) )
		err( err_msg_st[0] , 0x00, 1 );

	while( size )
	{
		res<<=8;
		res+=s->body[--(s->i)];
		--size;
	}

	return res;
}

ct_t peek( struct stack * s )
{
	if( isempty( s ) )
		err( err_msg_st[0] , 0x00, 0 );

	return s->body[(s->i)-1];
}

#endif
