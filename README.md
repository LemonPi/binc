bincalc
=======

Stream based calculator with variables and bitwise operator support.
Useful for practicing binary manipulation.

Tips:
- build by typing "make" in the same directory
- requires a compiler supporting C++11 (makefile builds with g++ by default)
- put \ in front of letters to use literal character (e.g. \b = 98)
- Ctrl + C to exit, or another kill key
- adjustable values near top of source file (rep_type and bit_num)
- 0xnum is hex and 0num is oct
- order of operation: parentheses --> binary ops --> * / --> + -

Major components inspired by Bjarne Stroustrup's desktop calculator (The C++ Programming Language 4th Edition, Chapter 10)

