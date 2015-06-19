bincalc
=======

Very fast and simple stream based calculator with variables and bitwise operator support.
Especially useful for practicing boolean algebra and bit manipulation.


Operators:
 - * / + - % basic arithmetic
 - >> << bit shifts
 - & | ^ ~ binary logic (^ is XOR, ~ is NOT)
 - ** ! exponent and factorial 

Todo:
 - function support (common trig functions)
 - symbolic math
 - keep track of value history

Tips:
- build by typing "make" in the same directory
- requires a compiler supporting C++11 (makefile builds with g++ by default)
- put \ in front of letters to use literal character (e.g. \b = 98)
- Ctrl + C to exit, or another kill key
- adjustable values near top of source file (rep_type and bit_num)
- 0xnum is hex, 0num is oct, bnum is binary
- order of operation: parentheses --> binary ops --> * / --> + -

Major components inspired by Bjarne Stroustrup's desktop calculator (The C++ Programming Language 4th Edition, Chapter 10)

