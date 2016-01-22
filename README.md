# FloatingPointBitJS

This is a simple library to calculate single precision floating point (IEEE 754) numbers when setting
particular bits. It is written in C++ to be compiled to Javascript with [Emscripten](https://kripken.github.io/emscripten-site/index.html).
Building instructions are at the bottom of the file.

## Using the javascript files

#### The FloatBits class

The essence of the library is in the FloatBits class. Once you have an instance of this class (see below), you can use it in
the following way. Assuming the instance is called `myNumber`:

    myNumber.size()

Returns the number of bits in the number. Always 32.

    myNumber.get( bitNumber )

Returns true if the bit at `bitNumber` is set, false if not. The range of accepted values is [0,31], so the least significant
bit is 0 and the most significant bit is 31. If a bit greater than 31 is requested then it will *always* return false. If a negative
number is requested an exception is thrown.

    myNumber.set( bitNumber, value )
    
Set the bit at `bitNumber` to the boolean value `value`. The rules for the range of `bitnumber` are the same as for `get()`.

    myNumber.valueFrom( floatNumber )

Set the bits to be the same as for the number `floatNumber`. Note that single precision floating points cannot represent
every number exactly so the closest possible bit values are set.

    myNumber.bitValueFromInt( intNumber )

Set the bits to be the same as the number supplied. Note this isn't the same as casting to a float and then calling `valueFrom()`
since integers and floats have completely different bit representations.

    myNumber.value()

Returns the float value represented by the current bit settings.

    myNumber.asBinary()

Returns a string representing the binary values of the bits. The string is padded with leading zeros to be 32 characters in length.
There is no prefix.

    myNumber.asHex()

Returns a hex string of the bit values. The hex characters are lowercase, and it is padded with leading zeros to be 8 characters
in length. There is no prefix (e.g. "0x").

    myNumber.asDecimal()

Returns a string of the decimal representation of the bits. The number will be rounded, and not exact.

    myNumber.asInt()

Return the integer value if the bits were for an unsigned int. This is not the same as converting `value()` to an int, it is
the bitwise conversion. E.g. if the bits are set so that the float value is 1, this function will return 1065353216 (both have
bit values of 0x3f800000).

    myNumber.delete()

Free any resources taken by the instance. This should be called if you no longer need the object and you are creating many
instances.

#### Creating instances of the FloatBits class

Creating instances of the FloatBits class requires a little more code than you might expect. You first need to create an instance
of the module, then ask it for an instance of FloatBits. However, because the module loads some resources asynchronously you need
to make sure the module has been loaded properly before asking for an instance of FloatBits. For most browsers using the `window.onload`
event is sufficient, however for some reason Chrome fires that early before everything has necessarily been loaded. To get around
this you can attach a special `onRuntimeInitialized` function to the module instance to fire your code. For example:

    <script language="javascript" type="text/javascript" src="FloatingPoint.js"></script>
    <script>
        var moduleInstance=window.FloatingPoint();
        moduleInstance.onRuntimeInitialized=function() {
            myNumber=new moduleInstance.FloatBits;
            
            <... other code ...>
        };
    </script>

This works on all browsers so is preferred over the traditional `window.onload` approach.  Have a look at the Example.html file
and the Tests.html file to see real world examples. If you get a

    Uncaught TypeError: moduleInstance.FloatBits is not a function
    
error in the javascript console then you are trying to create an instance before the module has finished loading.

Note that any FloatBits instances you create are not automatically cleaned up. If you create many instances then you should call
the `delete()` method once finished.

## Building

To build it only requires [cmake](https://cmake.org) and [emscripten](https://kripken.github.io/emscripten-site/index.html),
although emscripten has several other dependencies. If you have those tools installed it should be enough to

    mkdir <source tree>/build
    cd <source tree>/build
    cmake .. -DEMSCRIPTEN_ROOT_PATH=<path to emscripten>
    make

The output will be in `<source tree>/build/www`. The only two files you need are the FloatingPoint.js and FloatingPoint.js.mem
files. The other two are just example and test files. For how to use them see above.