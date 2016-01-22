/** @file
 *
 * Source file for the FloatBits class.
 *
 * @author Mark Grimes
 * @copyright MIT licence, see http://opensource.org/licenses/MIT
 * @date 19/Jan/2016
 */
#include "FloatBits.h"
#include <sstream>
#include <iomanip>

bool FloatBits::get( size_t bit ) const
{
	if( bit>=size() ) return false;
	return bits_[bit];
}

void FloatBits::set( size_t bit, bool value )
{
	if( bit<size() ) bits_[bit]=value;
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

void FloatBits::bitValueFromInt( unsigned int value )
{
	const unsigned char* asBits=reinterpret_cast<unsigned char*>(&value);
	for( size_t byteIndex=0; byteIndex<sizeof(unsigned int); ++byteIndex )
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
	return bits_.to_string();
}

std::string FloatBits::asHex()
{
	std::stringstream output;
	output << std::hex << std::setw(8) << std::setfill('0') << bits_.to_ulong();
	return output.str();
}

std::string FloatBits::asDecimal()
{
	std::stringstream output;
	output << std::dec << value();
	return output.str();
}

unsigned long FloatBits::asInt()
{
	return bits_.to_ulong();
}
