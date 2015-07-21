binc
=======

Fast and intuitive command line calculator in C++. (pronounced "bink")  
Offers bitwise operators and multiple (hex, oct, dec) input and display modes.  
Especially useful for practicing boolean algebra and bit manipulation.  

[**Online console**](http://johnsonzhong.me/projects/bincalc/tester.html)

### Get started
 1. clone anywhere `git clone https://github.com/LemonPi/binc.git`
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
> sin(pi); cos(pi)
0
-1
> ln 5
1.60944
> exit
```

#### Pipe mode
```
cmd> binc "1 + 2 * 3; @ / 2"
7
3.5

cmd> binc < math_file
> 0000 0000 0000 0000 0000 0000 0011 0110 (54)
> 0000 0000 0000 0000 0000 0000 0110 1100 (108)

cmd> cat math_file
2 + 52
@ * 2
```
The output terminates with a newline.

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
These functions take 1 argument and return 1 value `(f: R x R -> R)`
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
These functions take no argument and adjust the state of binc,
their effects lasting until another modifier in their group gets called.
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

// whether to have > prompt
prompt
noprompt

// list history
hist
history

// list functions and modifiers
funcs
unary
unaries
print_unaries

modifier
modifiers
print_modifiers

```

### Why binc?
 - no 3rd party dependencies 
 - input and output in binary, hex, and oct
 - bit display in verbose mode (no other calculator has this out of the box)
 - change display to hex and oct with a single command 
 - instantaneous load (take that Google and Python)
 - can feed pipes and files to

## Detailed Usage
#### Input
Input can be in decimal, binary, octal, or hexadecimal:
```
> x = 100
0000 0000 0000 0000 0000 0000 0110 0100 (100)
> x = b100
0000 0000 0000 0000 0000 0000 0000 0100 (4)
> x = 0100
0000 0000 0000 0000 0000 0000 0100 0000 (64)
> x = 0x100
0000 0000 0000 0000 0000 0001 0000 0000 (256)
```

#### Output
Similarly, output can be in dec, bin, oct, or hex:
```
> x = 100
0000 0000 0000 0000 0000 0000 0110 0100 (100)
> hex
> x
0000 0000 0000 0000 0000 0000 0110 0100 (64)
> oct
> x
0000 0000 0000 0000 0000 0000 0110 0100 (144)
> terse
> x
144
> verbose
> x
0000 0000 0000 0000 0000 0000 0110 0100 (144)
```

#### Character literals
Instead of treating the character as a variable, take the ASCII value of it
```
> a
error: a not found
> \a
0000 0000 0000 0000 0000 0000 0110 0001 (141)
```

#### History
```
... some commands
> hist
100
1
2
98
97
97
> @
0000 0000 0000 0000 0000 0000 0110 0001 (97)
> @@@
0000 0000 0000 0000 0000 0000 0110 0010 (98)
> @@@@
0000 0000 0000 0000 0000 0000 0000 0010 (2)
```
Note that querying for previous commands doesn't add to the history.


### Tips
- requires C++11 (makefile builds with g++ by default)
- exit by `exit`, `quit`, or `Ctrl + C `
- order of operation: parentheses --> binary ops --> * / --> + -

