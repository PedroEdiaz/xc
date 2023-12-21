#include <unistd.h>
#include <fcntl.h>
#include "st.c"

#define FG_NUM 0b000
#define FG_SFX 0b001 
#define FG_POP 0b010 
#define FG_ERR 0b100 

char parse( int );

#define token_t unsigned char
token_t token( token_t * last, char c );
ct_t eval( token_t, ct_t, ct_t, ct_t );
int arity( token_t );
int assoc( token_t );

int codegen( struct stack *, struct stack * );
int optimize( struct stack *, struct stack * );

unsigned int init_err( void );
void write_err( char *, char, char *  );
void write_n( int fd, int n );

char read_chr( int fd  );

ct_t parse_ct( char * c, int fd );
int parse_pp( char * c, int fd );

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
