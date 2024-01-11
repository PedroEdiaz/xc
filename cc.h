#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "st.c"

#define FLAG( t, flag ) ( t<FG_ERR && t&flag )
#define FG_NUM 0b000
#define FG_SFX 0b001 
#define FG_POP 0b010 
#define FG_ERR 0b100 

#define token_t unsigned char

void parse( int );

token_t token( token_t * last, char c );
token_t token_str( token_t * last, char * str );
ct_t eval( token_t, ct_t, ct_t, ct_t );
int arity( token_t );
int assoc( token_t );

int codegen( struct stack *, struct stack * );
void optimize( struct stack *, struct stack * );

unsigned int init_err( char * );
void err( char *, char, int );
void write_n( int fd, ct_t n );

char read_chr( int fd  );

ct_t parse_ct( char * c, int fd );
char * parse_va( char * c, int fd );
void parse_pp( char * c, int fd );

enum
{
	SX_BLK=5,
	SX_SPP,
	SX_OPB,
	SX_CLB,
	SX_OPP,
	SX_CLP,
	SX_SMC,
};
