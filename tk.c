#include "cc.h"

enum 
{
	OP_ASG=SX_LAST,
	OP_TRN,
	OP_TRD,
	OP_LGO,
	OP_LGA,
	OP_BWO,
	OP_BWX,
	OP_BWA,
	OP_ONE,
	OP_OEQ,
	OP_OGE,
	OP_OLE,
	OP_OGR,
	OP_OLW,
	OP_BWR,
	OP_BWL,
	OP_ALS,
	OP_ALA,
	OP_ALP,
	OP_ALM,
	OP_ALD,
	OP_LGN,
	OP_BWN,
	OP_DEP,
	OP_INP,
	OP_DES,
	OP_INS, 
	OP_UNS,
	OP_UNA,
	OP_LAST
};

const token_t op_trn = OP_TRN;

char * sym[] =
{
	[SX_TPP]="\n#",
	[SX_OPC]="/*",
	[SX_CLC]="*/",
	[SX_SNC]="//",
	[SX_OPB]="{",
	[SX_CLB]="}",
	[SX_OPP]="(",
	[SX_CLP]=")",
	[SX_SMC]=";",
	[KW_RETURN]="return",
	[SX_LAST]=NULL,

	[OP_ASG]="=",
	[OP_TRN]="?",
	[OP_TRD]=":",
	[OP_LGO]="||",
	[OP_LGA]="&&",
	[OP_BWO]="|",
	[OP_BWX]="^",
	[OP_BWA]="&",
	[OP_ONE]="!=",
	[OP_OEQ]="==",
	[OP_OGE]=">=",
	[OP_OLE]="<=",
	[OP_OGR]=">",
	[OP_OLW]="<",
	[OP_BWR]=">>",
	[OP_BWL]="<<",
	[OP_ALS]="-",
	[OP_ALA]="+",
	[OP_ALP]="*",
	[OP_ALM]="%",
	[OP_ALD]="/",

	[OP_LGN]="!",
	[OP_BWN]="~",

	[OP_DES]="--",
	[OP_INS]="++",
	[OP_DEP]=NULL,
	[OP_INP]=NULL, 
	[OP_UNS]=NULL,
	[OP_UNA]=NULL,
};

token_t syntax( token_t last, token_t * tk )
{
	switch( *tk )
	{
	case SX_TPP:
		return FG_ERR;
	case SX_OPC:
	case SX_CLC:
	case SX_SNC:
		return last;

	case KW_RETURN:
		return (last==FG_ERR )? *tk: FG_EOF;
	case FG_NUM:
		return (last==FG_NUM)?FG_EOF:*tk;
	case SX_OPP:
		return (last==FG_NUM)?FG_EOF:*tk;
	case SX_CLP:
		return (last==FG_NUM)?FG_NUM:FG_EOF;
	case SX_OPB:
		return (last==FG_ERR)?FG_ERR:FG_EOF;
	case SX_CLB:
		return (last==FG_ERR)?FG_ERR:FG_EOF;

	case SX_SMC:
		switch( last )
		{
		case FG_ERR:
		case KW_RETURN:
			return FG_ERR;
		}

		return (last==FG_NUM)?FG_ERR:FG_EOF;

	case OP_TRD:
		*tk=SX_CLP;
		return OP_TRD;
		
	case OP_INS:
		if( last!=FG_NUM )
			return *tk=OP_INP;
	case OP_DES:
		if( last!=FG_NUM )
			return *tk=OP_DEP;
		return FG_NUM;
	case OP_ALA:
		if( last!=FG_NUM )
			return *tk=OP_UNA;
	case OP_ALS:
		if( last!=FG_NUM )
			return *tk=OP_UNS;
	}

	return (last==FG_NUM)?*tk:FG_EOF;
}

token_t token( char * s ) 
{
	static token_t last=FG_ERR;
	unsigned char i=SX_START;

	if( *s<=' ' & !*(s+1) )
		return FG_BLK;

	if( '0' <= *s && *s<='9' )
	{
		i=FG_NUM;
		goto end;
	}

	if( *s=='\'' )
		return FG_NUM;

	while( i < OP_LAST )
	{
		if( !sym[i] )
			goto next;

		if( !strcmp( s, sym[i] ) )
			goto end;
	next:
		++i;
	}

	return FG_ERR;

end:
	last = syntax(last, &i );

	if( last == FG_EOF )
		return FG_ERR;

	return i;
}

ct_t eval( token_t op, ct_t a, ct_t b, ct_t c )
{
	switch( op )
	{
	case OP_TRN: return a?b:c;
	case OP_DES: return a--;
	case OP_INS: return a++;
	case OP_ALD: return a/b;
	case OP_ALM: return a%b;
	case OP_ALP: return a*b;
	case OP_ALA: return a+b;
	case OP_ALS: return a-b;
	case OP_BWL: return a>>b;
	case OP_BWR: return a<<b;
	case OP_OLW: return a<b;
	case OP_OGR: return a>b;
	case OP_OLE: return a<=b;
	case OP_OGE: return a>=b;
	case OP_OEQ: return a==b;
	case OP_ONE: return a!=a;
	case OP_BWA: return a&b;
	case OP_BWO: return a|b;
	case OP_BWX: return a^b;
	case OP_LGA: return a&&b;
	case OP_LGO: return a||b;

	case OP_UNA: return +a;
	case OP_UNS: return -a;
	case OP_INP: return ++a;
	case OP_DEP: return --a;
	case OP_BWN: return ~a;
	case OP_LGN: return !a;
	}

	err( "Unreachable", "Eval", 1 );
	return 1;
}

int assoc( token_t t )
{
	return t==OP_ASG || t==OP_TRN;
}

int arity( token_t t )
{
	switch( t )
	{
	case OP_TRN: 
		return 3;
	case OP_DES: 
	case OP_INS: 
	case OP_UNA: 
	case OP_UNS:
	case OP_INP:
	case OP_DEP: 
	case OP_BWN:
	case OP_LGN: 
		return 1;
	case KW_RETURN:
		return 0;
	}
	return 2;
}

char is_alfnum( char c )
{
	return  c=='_' | 
		( 'a' <= c & c <= 'z' ) |
		( 'A' <= c & c <= 'Z' ) |
		( '0' <= c & c <= '9' ) ; 
}

char is_delim( char c )
{
	return c=='\'' | c=='"' ;
}

char may_twice_equal( char c )
{
	return c=='<' | c=='>' ;
}

char may_twice( char c )
{
	return may_twice_equal(c) |
		c=='+' | c=='-' | 
		c=='&' | c=='|' ; 

}

char may_equal( char c )
{
	return may_twice(c) | 
		c=='!' | c=='=' |
		c=='*' | c=='/' | 
		c=='%' | c=='^' ;
}

char * tokenize( fd_t fd )
{
	static char c=0,s=0, *p=NULL;
	unsigned char i=0;

	char cond;

	if( c )
		goto cont;

next:
	if( !(c=read_chr(fd)) )
		return FG_EOF;

cont:
	if( !p & c=='#' )
	{
		c=0;
		return  "\n#";
	}

	if( i==s-1 | !p )
		p=realloc(p,++s);

	cond = !i;
	cond |= is_alfnum(*p) & is_alfnum(c);

	switch( i * !cond )
	{
	case 2:
		cond |= may_twice_equal(*p) & c=='=';
		goto end;
	case 1:
		cond |= *p=='\n' & c=='#';
		cond |= *p=='/' & c=='/';
		cond |= *p=='/' & c=='*';
		cond |= *p=='*' & c=='/';
		cond |= may_twice(c) & *p==c;
		cond |= may_equal(*p) & c=='=';
	end:
	}

	cond |= is_delim(*p) & (*p!=c | (p[i-1]=='\\' & p[i-2]!='\\')) ;

	if( cond )
	{
		p[i++]=c;
		goto next;
	}

	if( is_delim(*p) & *p==c )
	{
		p[i++]=c;
		c=0;
		p[i]=0x00;
		return p;
	}

	p[i]=0x00;
	return p;
}
