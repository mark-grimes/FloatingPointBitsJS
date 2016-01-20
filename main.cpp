#include <cstdio>
#include <array>

#include "FloatBits.h"

int main( int argc, char* argv[] )
{
	printf( "** Starting c++ test\n" );
	FloatBits blah;
	blah.valueFrom(78);
	printf( "%f from\n", blah.value() );
	blah.set(31,true);
	printf( "%f from\n", blah.value() );
	blah.set(25,false);
	printf( "%f from\n", blah.value() );
	return 0;
}

