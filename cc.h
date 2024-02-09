#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "st.c"

#define token_t unsigned char
#define bool_t unsigned char
#define fd_t unsigned char
#define lp_t unsigned int
#define ct_t unsigned long

extern const token_t op_trn;

void parse( int );

token_t token( char *, bool_t );
ct_t eval( token_t, ct_t, ct_t, ct_t );
char * tokenize( fd_t );
int arity( token_t );
bool_t assoc( token_t );
bool_t unreach( token_t );

lp_t codegen( struct stack **, struct stack ** );
void optimize( struct stack **, struct stack ** );

unsigned int init_err( char * );
void err( char *, char *, bool_t );
void write_n( fd_t, ct_t );


char read_chr( fd_t  );

ct_t parse_ct( char * );
void parse_pp( fd_t );
lp_t label( char * );
char * definition( char * );

enum
{
	FG_EOF,
	FG_ERR,
	FG_BLK,
	FG_NUM,
	FG_VAR,
	FG_LBL,

	SX_START,

	SX_TPP,
	SX_OPC,
	SX_CLC,
	SX_SNC,

	SX_OPB,
	SX_CLB,
	SX_OPP,
	SX_CLP,
	SX_SMC,

	KW_RETURN,
	KW_LABEL,
	KW_GOTO,

	SX_LAST
};
