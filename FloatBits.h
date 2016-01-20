#ifndef INCLUDEGUARD_FloatBits_h
#define INCLUDEGUARD_FloatBits_h

#include <bitset>
#include <string>

class FloatBits //: public BitArray<sizeof(float)*8>
{
public:
	constexpr size_t size() const { return bits_.size(); }
	bool get( size_t bit ) const;
	void set( size_t bit, bool value );
	void valueFrom( float value );
	void bitValueFromInt( unsigned int value );
	float value();
	std::string asBinary();
	unsigned long asInt();
protected:
	std::bitset<sizeof(float)*8> bits_;
};

#endif
