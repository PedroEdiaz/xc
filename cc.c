#include "cc.h"

int main( int argc, char * argv[] )
{

	char * data_file="stdin";
	unsigned int data_line=1, data_chr=0;

	char i=1, fd=0, *msg="No file";

	if( argc==1 )
		goto parse;

	while( i<argc )
	{
		data_line=1;
		data_chr=0;
		data_file=argv[i];

		++i;

		fd=open( data_file, O_RDONLY );

		if( fd < 0  )
			goto err;
	parse:
		msg=parse( fd, &data_line, &data_chr );

		if( msg )
			goto err;

		close( fd );

	}
	
	return 0;

err:
	write_err( msg, data_file, data_line, data_chr );
	return 1;
}
