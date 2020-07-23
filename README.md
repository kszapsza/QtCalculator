# QtCalculator
First steps in Qt framework with C++: an implementation of simple calculator app.

## Features
- [x] basic arithmetical operation: addition, subtraction, multiplication, division, 2nd power and square root,
- [x] additional results memory: MRC, M+, M- functions known from standard calculators,
- [x] alternative mode introducing additional math functions as seen on scientific mode in Windows calculator,
such as modulo, logarithms, exponential functions, factorial etc.

### Basic mode
Allows performing addition, subtraction, multiplication, division, square power and root calculation, changing sign,
percentage calculations and additional results memory (MRC, M+, M-).

![Calculator window screenshot – basic mode](https://github.com/kszapsza/QtCalculator/raw/master/calc_basic.png)

### Scientific mode
Allows performing all basic operations (apart from memory) and additionally: inserting 𝜋/e constants, generating random
real numbers between 0 and 1, modulo operation (for integers), factorial (for reals), natural logarithm, 2 and 10 base
logarithm, n-base logarithm, custom power function (xⁿ), exponential functions (e, 10 base), absolute value and
inverting numbers (1/x).

![Calculator window screenshot – scientific mode](https://github.com/kszapsza/QtCalculator/raw/master/calc_sci.png)

## To be done
- [ ] trigonometric functions, deg/rad/grad modes, dec/bin/oct/hex conversions.