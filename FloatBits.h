#ifndef INCLUDEGUARD_FloatBits_h
#define INCLUDEGUARD_FloatBits_h

#include <bitset>
#include <string>

/** @brief Class that can manipulate individual bits of a single precision floating point number.
 *
 * Implemented as a very thin wrapper around std::bitset.
 *
 * @author Mark Grimes
 * @copyright MIT licence, see http://opensource.org/licenses/MIT
 * @date 19/Jan/2016
 */
class FloatBits
{
public:
	/// @brief Returns the number of bits in the floating point number, i.e. always 32.
	constexpr size_t size() const { return bits_.size(); }

	/** @brief True if the bit number requested is set, false otherwise
	 *
	 * The range of accepted values is [0,31], so the least significant bit is 0
	 * and the most significant bit is 31. If a bit outside this range is requested
	 * then it will *always* return false. */
	bool get( size_t bit ) const;

	/** @brief Set the bit number specified to the given value
	 *
	 * The range of bit numbers is [0,31]. If a number outside this range is supplied
	 * no action is taken. */
	void set( size_t bit, bool value );

	/** @brief Set the bits to be the same as float supplied */
	void valueFrom( float value );

	/** @brief Set the bits to be the same as the integer supplied */
	void bitValueFromInt( unsigned int value );

	/** @brief Return the numerical value of the current bit arrangement */
	float value();

	/** @brief Return a string representing the binary values of the bits
	 *
	 * The string is padded with leading zeros to be 32 characters in length.
	 * There is no prefix. */
	std::string asBinary();

	/** @brief Return a hex string of the bit values
	 *
	 * The hex characters are lowercase, and it is padded with leading zeros
	 * to be 8 characters in length. There is no prefix (e.g. "0x").*/
	std::string asHex();

	/** @brief Return a string of the decimal representation of the bits
	 *
	 * Note that the number will be rounded, and not be exact.*/
	std::string asDecimal();

	/** @brief Return the integer value if the bits were for an unsigned int
	 *
	 * Note this is not the same as converting value() to an int, it is the bitwise
	 * conversion. E.g. if the bits are set so that the float value is 1, this function
	 * will return 1065353216 (both have bit values of 0x3f800000).*/
	unsigned long asInt();
protected:
	std::bitset<sizeof(float)*8> bits_;
};

#endif
