#include "cc.h"

char * err_msg_ps[2] = {"Syntax error", "Missing char"};

void safe( struct stack ** op , token_t t )
{
	switch( t )
	{
	case SX_SMC:
		if( !isempty(*op) && peek(*op)==SX_OPP )
			err( err_msg_ps[1], "')' or ':'", 1 );
		return;
	case SX_CLP:
		if( isempty(*op) || pop(op)!=SX_OPP )
			err( err_msg_ps[1], "'?' or '('", 1 );
		return;
	case SX_CLB:
		if( isempty(*op) || pop(op)!=SX_OPB )
			err( err_msg_ps[1], "{", 1 );
		return;
	}
}

void parse( int fd )
{
	struct stack *st=NULL, *ct=NULL, *op=NULL;

	token_t tk;
	char * s;

 	next:
	while( s=tokenize(fd) )
	{
		switch( tk=token(s) )
		{
		case SX_CLC:
			err( err_msg_ps[1], "/*", 1 );
		case FG_ERR:
			err( err_msg_ps[0], s, 1 );
		case FG_EOF:
			goto end;

		case SX_TPP:
			parse_pp( fd );
			goto next;

		case SX_OPC:
			while( (s=tokenize(fd)) && tk!=SX_CLC )
				tk=token(s);

			if( !s )
				err( err_msg_ps[1], "*/", 1 );

			goto next;

		case SX_SNC:
			while( read_chr(fd) !='\n' )
				;
			goto next;

		case FG_NUM:
			push( &ct, parse_ct(s) );
			push( &st, tk );
			goto next;

		default:
			while( !isempty(op) && 
				( peek(op)>tk || ( peek(op)==tk && !assoc(tk) ) ) )
			{
				push( &st, pop(&op) );
				optimize( &st, &ct );
			}

			if( tk==op_trn )
			{
				push( &op, tk );
				tk=SX_OPP;
			}

		case SX_OPB:
		case SX_OPP:
			safe( &op, tk );

			switch( tk )
			{
			case SX_SMC:
				if( !isempty(st) &&  peek(st)==FG_NUM )
				{
					pop(&st);
					pop(&ct);
				}
				{
					struct stack * tmp = NULL;
					while( !isempty(st) )
						push( &tmp, pop(&st) );
					codegen( &tmp, &ct );
				}
			case SX_CLP:
			case SX_CLB:
				goto next;
			}

			push( &op, tk );

		case FG_BLK:
		}
	}
end:

	if( !isempty(op) )
		err( err_msg_ps[1], "}", 1 );
}
