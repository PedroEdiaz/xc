#include <unistd.h>
#include <fcntl.h>
#include "st.c"

#define u8 unsigned char


#define FG_NUM 0b000
#define FG_SFX 0b001 
#define FG_POP 0b010 
#define FG_ERR 0b100 
char parse( int, unsigned int *, unsigned int * );

#define token_t unsigned char
token_t token( token_t * last, char c );
int arity( token_t );
int eval( token_t, int, int );

char codegen( struct stack *, struct stack * );
int optimize( struct stack *, struct stack * );

void write_err( char *, char, char *,  unsigned int, unsigned int  );
void write_n( int fd, int n );

u8 read_chr( u8 * i, u8 s, char * buff,
	char * c, int fd, unsigned int * line, unsigned int * chr );

u8 parse_cnt( int * res, u8 * i, u8 s, char * buff,
	char * c, int fd, unsigned int * line, unsigned int * chr );


