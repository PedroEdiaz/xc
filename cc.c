#include "cc.h"

int main( int argc, char * argv[] )
{

	char * data_file="stdin";
	unsigned int data_line=1, data_chr=0;

	char i=1, fd=0;

	if( argc==1 )
		goto parse;

	next_file:
	while( i<argc )
	{
		data_line=1;
		data_chr=0;
		data_file=argv[i];
		++i;

		fd=open( data_file, O_RDONLY );

	parse:
		init_err(data_file);

		if( fd < 0  )
		{
			err( "No file", 0x00, 0 );
			goto next_file;
		}

		parse(fd);
		close(fd);
	}
	
	return 0;
}
