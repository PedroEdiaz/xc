#include "cc.h"

enum
{
	SX_BLK=5,
	SX_OPB,
	SX_CLB,
	SX_OPP,
	SX_CLP,
	SX_SMC,
};

token_t sx_token( token_t * last, char c )
{
	if( c <= ' ' )
		return SX_BLK;

	switch( c )
	{
	case ';': return SX_SMC;
	case '{': return SX_OPB;
	case '}': return SX_CLB;
	case '(': return SX_OPP;
	case ')': return SX_CLP;
	}

	return token(last,  c );
}

#define FLAG( t, flag ) ( t<4 && t&flag )

int syntax( struct stack * op , token_t t, token_t *last )
{
	switch( t )
	{
	case SX_SMC:
		if( peak(op)==SX_OPP || *last>SX_SMC )
			return 1;

		*last=FG_ERR;
		return 0;
	case SX_CLP:
		*last=FG_NUM;
		return !(op->i && pop(op)==SX_OPP);
	case SX_CLB:
		*last=FG_ERR;
		return !(op->i && pop(op)==SX_OPB); 
	case SX_OPB:
	case SX_OPP:
		*last=FG_ERR;
		return 0;
	case SX_BLK:
		*last=*last? t: *last;
		return 0;
	}

	*last= FLAG(*last, FG_SFX)? FG_NUM: t;

	return 0;
}

void update_err( char c, unsigned int * line, unsigned int * chr )
{
	++(*chr);
	if( c == '\n' )
	{
		++*line;	
		*chr=0;
	}
}

char * parse( int fd, unsigned int * line, unsigned int * chr )
{
	char *msg = "Syntax error: '_'";
	char s, i, buff[0xff];

	char *c = msg+15;

	struct stack st={0}, ct= {0}, op={0};
	token_t t, last=FG_ERR;

	while( s=read( fd, buff, 0xff ) )
	{
		i=0;
		while( i<s )
		{
			update_err( *c=buff[i], line, chr );
			switch( t=sx_token(&last,*c) )
			{
			case FG_NUM:
#warning TODO: Parse constants
				push( &ct, *c-'0' );
		
			default:
				if( FLAG(last,FG_POP) )
					pop(&op);

				while( t && op.i && peak(&op)>t )
				{
					push( &st, pop(&op) );
					if( !optimize( &st, &ct ) )
						return "Unrechable";
				}

			case SX_OPB:
			case SX_OPP:
			case SX_BLK:
				if( syntax( &op, t, &last ) ) 
			case FG_ERR:
					return msg;

				if( t==SX_CLP || t==SX_CLB || t==SX_BLK )
					goto end;

				switch( t )
				{
				case SX_SMC:
					if( peak(&st) == t )
						goto end;

				case FG_NUM:
					push( &st, t );
					goto end;

				default:
				push( &op, t );
				}


			case FG_POP:
			end:
			}
			++i;
		}
	}

	*c='{'; 

	if( op.i )
		return msg;

	return codegen( &st, &ct );
}
