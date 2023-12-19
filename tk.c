#include "cc.h"

enum 
{
	OP_ASG=11,
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
};

int eval( token_t op, int a, int b )
{
	switch( op )
	{
	case OP_DES: return a--;
	case OP_INS: return a++;
	case OP_UNA: return +a;
	case OP_UNS: return -a;
	case OP_INP: return ++a;
	case OP_DEP: return --a;
	case OP_BWN: return ~a;
	case OP_LGN: return !a;
	case OP_ALD: return a/b;
	case OP_ALM: return a%b;
	case OP_ALP: return a*b;
	case OP_ALA: return a+b;
	case OP_ALS: return a-b;
	case OP_BWL: return a<<b;
	case OP_BWR: return a>>b;
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
	}
	return *(char*)0=0;
}

int arity( token_t t )
{
	switch( t )
	{
	case OP_DES: 
	case OP_INS: 
	case OP_UNA: 
	case OP_UNS:
	case OP_INP:
	case OP_DEP: 
	case OP_BWN:
	case OP_LGN: 
		return 1;
	}
	return 2;
}

token_t token( token_t * last, char c )
{
	if( '0' <= c && c <= '9' )
		return (*last)?FG_NUM:FG_ERR;

	switch( c )
	{
	case '/': return ( !*last )?OP_ALD:FG_ERR;
	case '%': return ( !*last )?OP_ALM:FG_ERR;
	case '*': return ( !*last )?OP_ALP:FG_ERR;
	case '^': return ( !*last )?OP_BWX:FG_ERR;
	case '!': return ( *last )?OP_LGN:FG_ERR;
	case '~': 
		switch( *last )
		{
		case FG_NUM: return FG_ERR;
		case OP_BWN: *last=FG_POP; return FG_POP;
		}
		return OP_BWN;
 	case '>':
		switch( *last )
		{
		case FG_NUM: return OP_OLW;
		case OP_OLW: *last=FG_POP; return OP_BWL;
		}
		return FG_ERR;
	case '<':
		switch( *last )
		{
		case FG_NUM: return OP_OGR;
		case OP_OGR: *last=FG_POP; return OP_BWR;
		}
		return FG_ERR;
	case '&':
		switch( *last )
		{
		case FG_NUM: return OP_BWA;
		case OP_BWA: *last=FG_POP; return OP_LGA;
		}
		return FG_ERR;
	case '|':
		switch( *last )
		{
		case FG_NUM: return OP_BWO;
		case OP_BWO: *last=FG_POP; return OP_LGO;
		}
		return FG_ERR;
	case '=': 
		switch( *last )
		{
		case FG_NUM: return OP_ASG;
		case OP_ASG: *last=FG_POP; return OP_OEQ;
		case OP_LGN: *last=FG_POP; return OP_ONE; 
		case OP_OGR: *last=FG_POP; return OP_OGE;
		case OP_OLW: *last=FG_POP; return OP_OLE;
		}
		return FG_ERR;
	case '+':
		switch( *last )
		{
		case FG_NUM: return OP_ALA;
		case OP_UNA: *last=FG_POP; return OP_INP;
		case OP_ALA: *last=FG_POP|FG_SFX; return OP_INS;
		}
		return OP_UNA;
	case '-': 
		switch( *last )
		{
		case FG_NUM: return OP_ALS;
		case OP_UNS: *last=FG_POP; return OP_DEP;
		case OP_ALS: *last=FG_POP|FG_SFX; return OP_DES;
		}
		return OP_UNS;
	}

	return FG_ERR;
}
