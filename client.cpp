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
			.function("value",&FloatBits::value)
			.function("asBinary",&FloatBits::asBinary);
}

#endif
