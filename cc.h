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
int arity( token_t );
int eval( token_t, int, int );

char codegen( struct stack *, struct stack * );
int optimize( struct stack *, struct stack * );

unsigned int init_err( void );
void write_err( char *, char, char *  );
void write_n( int fd, int n );

char read_chr( int fd  );

int parse_ct( char * c, int fd );
int parse_pp( char * c, int fd );
