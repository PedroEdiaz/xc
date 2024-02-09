#define N 7

#warning This should be a function
main:
{
	;
	goto next; 

	/* Unrechable code */
	return 1?(30+40)*50:0;
	goto idk; 
next:
	return N;

	// Unrechable code
	return;
} 
