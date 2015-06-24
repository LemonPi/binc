binc
=======

Fast and intuitive command line calculator.  
Offers bitwise operators and multiple (hex, oct, dec) input and display modes.  
Especially useful for practicing boolean algebra and bit manipulation.  

### Get started
 1. clone anywhere `git clone https://github.com/LemonPi/bincalc.git`
 2. open command line in directory
 3. `make` (for windows users, a Cygwin binary exists under bin/)
 4. (recommended) either put `binc` or a symlink of it in your system path

### Usage
You can use binc in shell mode or pipe mode.

#### Shell mode
```
cmd> binc
> my_var = 19
0000 0000 0000 0000 0000 0000 0001 0011 (19)
> my_var << 1
0000 0000 0000 0000 0000 0000 0010 0110 (38)
> \a
0000 0000 0000 0000 0000 0000 0110 0001 (97)
> @+3
0000 0000 0000 0000 0000 0000 0110 0100 (100)
> hex
> @
0000 0000 0000 0000 0000 0000 0110 0100 (64)
> terse
> @
64
> hist
19
97
100
> sin(pi)
0
> ln 5
1.60944
> exit
```

#### Pipe mode
```
cmd> binc 2+4
6
```

### Operators
 - `* / + - %` basic arithmetic
 - `>> <<` bit shifts
 - `& | ^ ~` binary logic (^ is XOR, ~ is NOT)
 - `** !` exponent and factorial 
 - `@` retrieves last value, `@@` retrieves value 2 values up (not including previous `@`s)

### Functions
There are functions that take a single value and return a value (standard math functions)
and functions that modify binc's state. The code in `core/lookup.cpp` is more up to date
than this readme.

#### Math functions
```
abs
ceil
floor
trunc
round

cos
sin
tan
acos
asin
atan
cosh
sinh
tanh
acosh
asinh
atanh

ln     // base e
log
lg     // base 2
exp
exp2

sqrt
cbrt
```


#### Modifiers
```
exit
quit   // same as exit

// change output mode (input is dependent on prefix: 0x = hex, b = binary, 0 = oct, else = dec)
hex
oct
dec

// whether to print bits
terse
verbose

// list history
hist
history
```


Todo:
 - ~~function support (common trig functions)~~
 - symbolic math
 - ~~keep track of value history~~

Tips:
- requires a compiler supporting C++11 (makefile builds with g++ by default)
- put \ in front of letters to use literal character (e.g. \b = 98)
- Ctrl + C can also exit
- 0xnum is hex, 0num is oct, bnum is binary
- order of operation: parentheses --> binary ops --> * / --> + -

