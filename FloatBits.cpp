#include "FloatBits.h"

bool FloatBits::get( size_t bit ) const
{
	return bits_[bit];
}

void FloatBits::set( size_t bit, bool value )
{
	bits_[bit]=value;
}

void FloatBits::valueFrom( float value )
{
	const unsigned char* asBits=reinterpret_cast<unsigned char*>(&value);
	for( size_t byteIndex=0; byteIndex<sizeof(float); ++byteIndex )
	{
		for( size_t bitIndex=0; bitIndex<8; ++bitIndex )
		{
			size_t bit=byteIndex*8+bitIndex;
			bits_[bit]=(0x1<<bitIndex)&asBits[byteIndex];
		}
	}
}

float FloatBits::value()
{
	float returnValue=0;
	unsigned char* value=reinterpret_cast<unsigned char*>(&returnValue);
	for( size_t byteIndex=0; byteIndex<sizeof(float); ++byteIndex )
	{
		for( size_t bitIndex=0; bitIndex<8; ++bitIndex )
		{
			size_t bit=byteIndex*8+bitIndex;
			if( bits_[bit] )
			{
				value[byteIndex]=value[byteIndex]|(0x1<<bitIndex);
			}
		}
	}
	return returnValue;
}

std::string FloatBits::asBinary()
{
#ifdef __EMSCRIPTEN__
	// Emscripten seems to have trouble setting any string
	return std::string();
#else
	std::string result(size(),'0'); // fill completely with 0s to start
	// Then go through and change any set bits to "1"
	for( size_t index=0; index<size(); ++index )
	{
		if( get(index) ) result[size()-index-1]='1';
	}
	return result;
#endif
}
