#include "Num.h"

#include <limits>
#include <stdexcept>
#include <string>

int main()
{
    Num<int> number(10);
    number += 5;

    if ((number + 5).get() != 20 || (number * 2).get() != 30)
        return 1;

    Num<int> previous = number++;
    if (previous.get() != 15 || number.get() != 16)
        return 2;

    Num<int> old = number--;
    if (old.get() != 16 || number.get() != 15)
        return 3;

    Num<int> hex(-42);
    hex.setBase(16);
    if (hex.toString() != "-2a")
        return 4;

    Num<int> copy = hex;
    if (copy.getBase() != 16 || copy.toString() != "-2a")
        return 5;

    Num<long long> minimum(std::numeric_limits<long long>::min());
    if (minimum.toString() != std::to_string(std::numeric_limits<long long>::min()))
        return 6;

    Num<unsigned long long> maximum(std::numeric_limits<unsigned long long>::max());
    maximum.setBase(16);
    if (maximum.toString() != "ffffffffffffffff")
        return 7;

    Num<unsigned int> bits(0xF0U);
    if ((bits & 0x30U).get() != 0x30U || (bits | 0x0FU).get() != 0xFFU)
        return 8;

    if ((bits ^ 0xFFU).get() != 0x0FU || (bits >> 4U).get() != 0x0FU)
        return 9;

    Num<double> fraction(3.14159);
    fraction.setPrecision(3);
    if (fraction.toString() != "3.142" || !(fraction > 3.0))
        return 10;

    bool invalidBaseRejected = false;
    try
    {
        hex.setBase(1);
    }
    catch (const std::invalid_argument &)
    {
        invalidBaseRejected = true;
    }

    return invalidBaseRejected ? 0 : 11;
}
