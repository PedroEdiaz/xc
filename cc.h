#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "st.c"

#define token_t unsigned char
#define fd_t unsigned char

extern const token_t op_trn;

void parse( int );

token_t token( char * s );
ct_t eval( token_t, ct_t, ct_t, ct_t );
char * tokenize( fd_t fd );
int arity( token_t );
int assoc( token_t );

int codegen( struct stack *, struct stack * );
void optimize( struct stack *, struct stack * );

unsigned int init_err( char * );
void err( char *, char *, int );
void write_n( fd_t, ct_t );


char read_chr( fd_t  );

ct_t parse_ct( char * );

enum
{
	FG_EOF,
	FG_ERR,
	FG_BLK,
	FG_NUM,

	SX_START,

	FG_TPP,

	SX_OPB,
	SX_CLB,
	SX_OPP,
	SX_CLP,
	SX_SMC,
	KW_RETURN,

	SX_LAST
};
