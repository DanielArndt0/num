# Num Usage

`Num<T>` wraps a single numeric value with arithmetic, comparison, bitwise, and formatting operations. It requires C++11 or later and has no dependencies beyond the standard library.

## Basic Operations

```cpp
#include "Num.h"

Num<int> first(10);
Num<int> second(3);

Num<int> sum = first + second;
Num<int> product = first * 2;
bool greater = first > second;
```

Results:

```text
sum.get() = 13
product.get() = 20
greater = true
```

The operators `+`, `-`, `*`, `/`, `+=`, `-=`, `*=`, `/=`, `==`, `!=`, `<`, `>`, `<=`, and `>=` support values of the same `Num<T>` specialization or the underlying type `T`.

`get()` returns the stored value. An implicit conversion to `T` is also available.

## Increment and Decrement

```cpp
Num<int> number(5);

Num<int> before = number++;
Num<int> after = ++number;
```

Results:

```text
before.get() = 5
after.get() = 7
number.get() = 7
```

Prefix operators return a reference to the updated object. Postfix operators return a copy of the previous value.

## Bitwise Operations

Bitwise and shift operators are supported only for integral types.

```cpp
Num<unsigned int> flags(0xF0U);

Num<unsigned int> masked = flags & 0x30U;
Num<unsigned int> shifted = flags >> 4U;
Num<unsigned int> flipped = flags ^ 0xFFU;
```

Results:

```text
masked.get() = 48
shifted.get() = 15
flipped.get() = 15
```

Available bitwise operators are `&`, `|`, `^`, `<<`, and `>>`. As with built-in C++ operations, invalid shift counts and signed overflow must be avoided.

## Integer to String

```cpp
Num<int> number(-42);

std::string decimal = number.toString();
number.setBase(16);
std::string hexadecimal = number.toString();
number.setBase(2);
std::string binary = number.toString();
```

Results:

```text
decimal = "-42"
hexadecimal = "-2a"
binary = "-101010"
```

`setBase()` accepts bases from 2 through 36 and throws `std::invalid_argument` for invalid values. The default base is 10. The sign is kept separate from the digits. `getBase()` returns the configured base.

## Floating-Point to String

```cpp
Num<double> pi(3.14159);

std::string defaultText = pi.toString();
pi.setPrecision(4);
std::string preciseText = pi.toString();
```

Results:

```text
defaultText = "3.14"
preciseText = "3.1416"
```

`toString()` returns `std::string` instead of a pointer to an internal character buffer. Floating-point formatting uses fixed decimal notation and the classic C locale, with a default precision of 2 decimal places. For floating-point values, `setBase()` has no effect on the formatted string.

## Copy and Move

```cpp
Num<int> first(31);
first.setBase(16);

Num<int> second = first;
```

Results:

```text
second.get() = 31
second.getBase() = 16
second.toString() = "1f"
```

Copying or moving a Num preserves its stored value, base, and precision settings.

## Limitations

- `Num<T>` requires an arithmetic, non-`bool` type. Qualified types such as `const int` are not supported as template arguments.
- Arithmetic follows the C++ rules for the underlying type, including overflow behavior and integer division by zero.
- Bitwise and shift operations are unavailable for floating-point types.
- String conversion requires the standard C++ string and stream facilities; it may be unsuitable for highly memory-constrained environments.
- The library is intended for study and does not replace built-in numeric types.
