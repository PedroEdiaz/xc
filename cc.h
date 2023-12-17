#include <unistd.h>
#include <fcntl.h>
#include "st.h"
#define u8 unsigned char

void write_err( char *, char, char *,  unsigned int, unsigned int  );
void write_n( int fd, int n );

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
