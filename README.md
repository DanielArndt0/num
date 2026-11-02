# Num

A lightweight, header-only numeric wrapper for C++11 and later.

Num provides arithmetic, comparison, increment and decrement operations, along with bitwise operators for integral types and configurable string conversion.

## Requirements

- C++11 or later
- CMake 3.16 or later for CMake integration

## Usage

```cpp
#include "Num.h"

#include <string>

int main()
{
    Num<int> number(10);
    number += 5;

    Num<int> hex = number;
    hex.setBase(16);
    std::string text = hex.toString();

    return number.get() == 15 && text == "f" ? 0 : 1;
}
```

For more examples and API details, see [Usage Documentation](docs/usage.md).

## Manual Integration

Download [Num.h](https://github.com/DanielArndt0/Num/blob/main/include/Num.h) and add it to your project's include directory.

Include the header with `#include "Num.h"`. No separate compilation or external libraries are required.

## CMake Integration

You can download Num from GitHub automatically using CMake's `FetchContent`:

```cmake
include(FetchContent)

FetchContent_Declare(
    Num
    GIT_REPOSITORY https://github.com/DanielArndt0/Num.git
    GIT_TAG v1.0.0
)

FetchContent_MakeAvailable(Num)

target_link_libraries(my_target PRIVATE Num::Num)
```

If you already have the Num source directory locally, you can add it instead:

```cmake
add_subdirectory(path/to/Num)
target_link_libraries(my_target PRIVATE Num::Num)
```

Replace `my_target` with your application's CMake target. Num is header-only and does not require a separately compiled binary.

## Compatibility

Num requires C++11 or later. It supports standard arithmetic types other than `bool`. Bitwise and shift operators are available for integral types only.

`toString()` returns `std::string`. For integral types it supports bases 2 through 36, and for floating-point types it uses fixed decimal precision. String conversion uses only the C++ standard library.

## Disclaimer

Num is a lightweight C++ library developed for educational purposes and experimentation with numeric types, operators, and templates.

It is not intended to replace built-in arithmetic types or standard C++ utilities.
