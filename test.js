const assert=require('assert');
var tools=require('./build/www/FloatingPoint');

var blah=new tools.FloatBits;
blah.valueFrom(78);
assert.strictEqual( blah.value(), 78 );
blah.set(31,true);
assert.strictEqual( blah.value(), -78 );
blah.set(25,false);
assert.strictEqual( blah.value(), -4.875 );

// If control got this far then everything must have passed
console.log( "** All javascript tests passed" );
