#include "cc.h"

char * err_msg_ps[2] = {"Syntax error", "Missing char"};

void safe( struct stack * op , token_t t )
{
	switch( t )
	{
	case SX_SMC:
		if( !isempty(op) && peek(op)==SX_OPP )
			err( err_msg_ps[1], "')' or ':'", 1 );
		return;
	case SX_CLP:
		if( isempty(op) || pop(op,1)!=SX_OPP )
			err( err_msg_ps[1], "'?' or '('", 1 );
		return;
	case SX_CLB:
		if( isempty(op) || pop(op,1)!=SX_OPB )
			err( err_msg_ps[1], "{", 1 );
		return;
	}
}

void parse( int fd )
{
	struct stack st={0,0}, ct= {0,0}, op={0,0};

	token_t tk;
	char * s;

 	next:
	while( s=tokenize(fd) )
	{
		switch( tk=token(s) )
		{
		case FG_ERR:
			err( err_msg_ps[0], s, 1 );
		case FG_EOF:
			goto end;

		case FG_TPP:
			parse_pp( fd );
			goto next;
		case FG_NUM:
			push( &ct, parse_ct(s), sizeof(ct_t) );
			push( &st, tk, 1 );
			goto next;

		default:
			while( !isempty(&op) && 
				( peek(&op)>tk || ( peek(&op)==tk && !assoc(tk) ) ) )
			{
				push( &st, pop(&op,1), 1 );
				optimize( &st, &ct );
			}

			if( tk==op_trn )
			{
				push( &op, tk, 1 );
				tk=SX_OPP;
			}

		case SX_OPB:
		case SX_OPP:
			safe( &op, tk );

			switch( tk )
			{
			case SX_SMC:
				if( !isempty(&st) &&  peek( &st )==FG_NUM )
				{
					pop( &st, 1 );
					pop( &ct, sizeof(ct_t) );
				}
				codegen( &st, &ct );
			case SX_CLP:
			case SX_CLB:
				goto next;
			}

			push( &op, tk, 1 );

		case FG_BLK:
		}
	}
end:

	if( !isempty(&op) )
		err( err_msg_ps[1], "}", 1 );
}
