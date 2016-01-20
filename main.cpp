#include <iostream>
#include <iomanip>
#include <bitset>

#include "FloatBits.h"

int main( int argc, char* argv[] )
{
	std::cout << "** Starting c++ test" << "\n";
	FloatBits blah;
	blah.valueFrom(78);
	std::cout << blah.value() << "\n";
	blah.set(31,true);
	std::cout << blah.value() << "\n";
	blah.set(25,false);
	std::cout << blah.value() << "\n";
	blah.valueFrom(-80);
	std::bitset<sizeof(int)*8> intBitset(blah.asInt());
	std::cout << "Bitset " << intBitset << "\n";
	std::cout << "As binary " << blah.asBinary() << "\n";
	std::cout << std::hex << blah.asInt() << " " << std::dec << blah.asInt() << "\n";
	return 0;
}

