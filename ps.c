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
		if( isempty(*op) || *(token_t*)pop(op,1)!=SX_OPP )
			err( err_msg_ps[1], "'(' or '?'", 1 );
		return;
	case SX_CLB:
		if( isempty(*op) || *(token_t*)pop(op,1)!=SX_OPB )
			err( err_msg_ps[1], "{", 1 );
		return;
	}
}

struct stack *dicts=NULL;
struct dict
{
	char * key;
	lp_t value;
};

void parse( int fd )
{
	struct stack *st=NULL, *ct=NULL, 
		*op=NULL;

	lp_t lp;
	token_t tk;
	char * s;

	bool_t rechable=0;

	next:
	while( s=tokenize(fd) )
	{
		tk=token(s,1);
	token:
		switch( tk )
		{
		case SX_CLC:
			err( err_msg_ps[1], "/*", 1 );
		case FG_ERR:
		case FG_VAR:
			err( err_msg_ps[0], s, 1 );
		case FG_EOF:
			goto end;

		case SX_TPP:
			parse_pp( fd );
			goto next;

		case SX_OPC:
			while( (s=tokenize(fd)) && tk!=SX_CLC )
				tk=token(s,0);

			if( !s )
				err( err_msg_ps[1], "*/", 1 );

			goto next;

		case SX_SNC:
			while( (s=tokenize(fd)) && *s!='\n' )
				;
			goto next;

		case FG_LBL:
			{
				ct_t plp;
				plp=label(s);
				push( &ct, &plp, sizeof(ct_t) );
			}

			tk=FG_NUM;
			push( &st, &tk, 1 );
			goto next;

		case KW_LABEL:
		{
			struct dict l;

			rechable=1;

			l.value=lp;
			l.key=malloc(strlen(s));
			strcpy(l.key,s);
			push( &dicts, &l, sizeof(struct dict) );

			while( (tk=token(tokenize(fd),0)) == FG_BLK )
				;

			if( tk!=op_trn+1 )
			{
				free(l.key);
				pop( &dicts, sizeof(struct dict ) );
				err( "Unrechable", "Label", 1 );
			}

			goto next;
		}

		case FG_NUM:
			{
				ct_t val;
				val=parse_ct(s);
				push( &ct, &val, sizeof(ct_t) );
			}
			push( &st, &tk, 1 );
			goto next;

		default:
			while( !isempty(op) && 
				( peek(op)>tk || ( peek(op)==tk && !assoc(tk) ) ) )
			{
				push( &st, pop(&op,1), 1 );
				optimize( &st, &ct );
			}

			if( tk==op_trn )
			{
				push( &op, &tk, 1 );
				tk=SX_OPP;
			}

		case SX_OPB:
		case SX_OPP:
			safe( &op, tk );

			switch( tk )
			{
			case SX_SMC:
				if( isempty(st) )
					goto next;

				if( peek(st)==FG_NUM )
				{
					pop(&st,1);
					pop(&ct,sizeof(ct_t));
				}

				/* Invert ct stack */
				if( rechable )
				{
					struct stack * tmp = NULL;

					if( unreach(peek(st)) )
						rechable=0;

					while( !isempty(st) )
						push( &tmp, pop(&st,1), 1 );

					lp=codegen( &tmp, &ct );
					goto next;
				}

				/* Unrechable code */
				while( !isempty(st) )
					if( *(token_t*)pop(&st,1)==FG_NUM )
						pop( &ct, sizeof(ct_t) );

			case SX_CLP:
			case SX_CLB:
				goto next;
			}

			push( &op, &tk, 1 );

		case FG_BLK:
		}
	}
end:

	if( !isempty(op) )
		err( err_msg_ps[1], "}", 1 );

	while( !isempty(dicts) )
	{
		struct dict * d;
		d=(struct dict * )pop(&dicts,sizeof(struct dict) );
		write_n( 1, label(d->key) );
		write( 1, "=", 1 );
		write_n( 1, d->value );
		write( 1, "\n", 1 );
		free( d->key );
	}
}
