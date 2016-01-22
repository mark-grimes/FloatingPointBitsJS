/** @file
 *
 * Embind code for all C++ code required by the client.
 *
 * @author Mark Grimes
 * @copyright MIT licence, see http://opensource.org/licenses/MIT
 * @date 20/Jan/2016
 */
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#include "FloatBits.h"

EMSCRIPTEN_BINDINGS(my_module)
{
	emscripten::class_<FloatBits>("FloatBits")
			.constructor<>()
			.function("size",&FloatBits::size)
			.function("get",&FloatBits::get)
			.function("set",&FloatBits::set)
			.function("valueFrom",&FloatBits::valueFrom)
			.function("bitValueFromInt",&FloatBits::bitValueFromInt)
			.function("value",&FloatBits::value)
			.function("asBinary",&FloatBits::asBinary)
			.function("asHex",&FloatBits::asHex)
			.function("asDecimal",&FloatBits::asDecimal)
			.function("asInt",&FloatBits::asInt);
}

#endif
