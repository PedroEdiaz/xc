#include "cc.h"

token_t sx_token( token_t * last, char c )
{
	if( c <= ' ' )
		return SX_BLK;

	switch( c )
	{
	case '#': return SX_SPP;
	case ';': return SX_SMC;
	case '{': return SX_OPB;
	case '}': return SX_CLB;
	case '(': return SX_OPP;
	case ')': return SX_CLP;
	}

	return token(last,  c );
}

char * err_msg_ps[2] = {"Syntax error", "Missing char"};

int syntax( struct stack * op , token_t t, token_t last )
{
	switch( t )
	{
	case SX_SMC:
		if( !isempty(op) && peek(op)==SX_OPP )
			err( "Missing char ')' or ':'", 0x00, 1 );

		if( last>SX_SMC )
			err( err_msg_ps[0], ';', 1 );

		return FG_ERR;
	case SX_CLP:
		if( isempty(op) || pop(op,1)!=SX_OPP )
			err( err_msg_ps[1], (last==t)?'?':'(', 1 );

		return (last==t)?FG_ERR:FG_NUM;
	case SX_CLB:
		if( isempty(op) || pop(op,1)!=SX_OPB )
			err( err_msg_ps[1], '{', 1 );

		return FG_ERR;
	case SX_OPB:
	case SX_OPP:
		return FG_ERR;
	case SX_BLK:
		return last? t: last;
	}

	
	return FLAG(last, FG_SFX)? FG_NUM: t;
}

void parse( int fd )
{
	struct stack st={0,0}, ct= {0,0}, op={0,0};
	token_t t, last=FG_ERR;
	unsigned char c;

	while( (c=read_chr(fd))!=0xff )
	{
	next_token:
		switch( t=sx_token(&last,c) )
		{
		case FG_ERR:
			err( err_msg_ps[0], c, 1 );

		case SX_SPP:
			parse_pp( &c, fd );

			if( c == 0xff )
				goto end;

			goto next_token;

		case FG_NUM:
			push( &ct, parse_ct( &c, fd ), sizeof(ct_t) );

			push( &st, t, 1 );
			last=t;

			if( c == 0xff )
				goto end;

			goto next_token;

		default:
			if( last==SX_CLP )
				t=SX_CLP;


			if( FLAG(last,FG_POP) )
				pop(&op,1);

			while( t && !isempty(&op) && ( peek(&op)>t || ( peek(&op)==t && !assoc(t) ) ) )
			{
				push( &st, pop(&op,1), 1 );
				optimize( &st, &ct );
			}

			if( last==SX_OPP )
			{
				push( &op, t, 1 );
				last=t;
				t=SX_OPP;
			}

		case SX_OPB:
		case SX_OPP:
		case SX_BLK:
			last=syntax( &op, t, last );

			if( t==SX_CLP || t==SX_CLB || t==SX_BLK )
				goto end;


			if( t == SX_SMC )
			{
				codegen( &st, &ct );
				goto end;
			}

			push( &op, t, 1 );

			case FG_POP:
		end:
		}
	}

	c='{'; 

	if( !isempty(&op) )
		err( err_msg_ps[1], '}', 1 );

}
