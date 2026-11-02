#ifndef NUM_H
#define NUM_H

#include <algorithm>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

template <typename T>
class Num
{
    static_assert(std::is_arithmetic<T>::value && !std::is_same<T, bool>::value,
                  "Num requires a numeric type other than bool");
    static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value,
                  "Num requires an unqualified numeric type");

private:
    T number_ = T();
    unsigned char base_ = 10;
    unsigned char precision_ = 2;

    template <typename U>
    static bool isNegative(U value, std::true_type)
    {
        return value < 0;
    }

    template <typename U>
    static bool isNegative(U, std::false_type)
    {
        return false;
    }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, std::string>::type format() const
    {
        typedef typename std::make_unsigned<U>::type Unsigned;
        const bool negative = isNegative(number_, typename std::is_signed<U>::type());
        Unsigned magnitude = static_cast<Unsigned>(number_);

        if (negative)
            magnitude = static_cast<Unsigned>(Unsigned(0) - magnitude);

        const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
        std::string result;

        do
        {
            const unsigned digit = static_cast<unsigned>(magnitude % base_);
            result.push_back(digits[digit]);
            magnitude = static_cast<Unsigned>(magnitude / base_);
        } while (magnitude != 0);

        if (negative)
            result.push_back('-');

        std::reverse(result.begin(), result.end());
        return result;
    }

    template <typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, std::string>::type format() const
    {
        std::ostringstream stream;
        stream.imbue(std::locale::classic());
        stream << std::fixed << std::setprecision(precision_) << number_;
        return stream.str();
    }

public:
    Num() = default;
    Num(T number) : number_(number) {}
    Num(const Num &) = default;
    Num(Num &&) = default;
    Num &operator=(const Num &) = default;
    Num &operator=(Num &&) = default;

    Num &operator=(T other)
    {
        number_ = other;
        return *this;
    }

    Num &operator+=(const Num &other)
    {
        number_ += other.number_;
        return *this;
    }
    Num &operator+=(T other)
    {
        number_ += other;
        return *this;
    }
    Num &operator-=(const Num &other)
    {
        number_ -= other.number_;
        return *this;
    }
    Num &operator-=(T other)
    {
        number_ -= other;
        return *this;
    }
    Num &operator*=(const Num &other)
    {
        number_ *= other.number_;
        return *this;
    }
    Num &operator*=(T other)
    {
        number_ *= other;
        return *this;
    }
    Num &operator/=(const Num &other)
    {
        number_ /= other.number_;
        return *this;
    }
    Num &operator/=(T other)
    {
        number_ /= other;
        return *this;
    }

    Num operator+(const Num &other) const { return Num(number_ + other.number_); }
    Num operator+(T other) const { return Num(number_ + other); }
    Num operator-(const Num &other) const { return Num(number_ - other.number_); }
    Num operator-(T other) const { return Num(number_ - other); }
    Num operator*(const Num &other) const { return Num(number_ * other.number_); }
    Num operator*(T other) const { return Num(number_ * other); }
    Num operator/(const Num &other) const { return Num(number_ / other.number_); }
    Num operator/(T other) const { return Num(number_ / other); }

    bool operator==(const Num &other) const { return number_ == other.number_; }
    bool operator==(T other) const { return number_ == other; }
    bool operator!=(const Num &other) const { return number_ != other.number_; }
    bool operator!=(T other) const { return number_ != other; }
    bool operator<(const Num &other) const { return number_ < other.number_; }
    bool operator<(T other) const { return number_ < other; }
    bool operator>(const Num &other) const { return number_ > other.number_; }
    bool operator>(T other) const { return number_ > other; }
    bool operator<=(const Num &other) const { return number_ <= other.number_; }
    bool operator<=(T other) const { return number_ <= other; }
    bool operator>=(const Num &other) const { return number_ >= other.number_; }
    bool operator>=(T other) const { return number_ >= other; }

    Num &operator++()
    {
        ++number_;
        return *this;
    }
    Num operator++(int)
    {
        Num previous(*this);
        ++number_;
        return previous;
    }
    Num &operator--()
    {
        --number_;
        return *this;
    }
    Num operator--(int)
    {
        Num previous(*this);
        --number_;
        return previous;
    }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator&(const Num &other) const { return Num(number_ & other.number_); }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator&(T other) const { return Num(number_ & other); }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator|(const Num &other) const { return Num(number_ | other.number_); }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator|(T other) const { return Num(number_ | other); }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator^(const Num &other) const { return Num(number_ ^ other.number_); }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator^(T other) const { return Num(number_ ^ other); }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator>>(const Num &other) const { return Num(number_ >> other.number_); }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator>>(T other) const { return Num(number_ >> other); }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator<<(const Num &other) const { return Num(number_ << other.number_); }

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value, Num>::type
    operator<<(T other) const { return Num(number_ << other); }

    operator T() const { return number_; }
    T get() const { return number_; }

    Num &setBase(unsigned char base)
    {
        if (base < 2 || base > 36)
            throw std::invalid_argument("Num base must be between 2 and 36");

        base_ = base;
        return *this;
    }

    Num &setPrecision(unsigned char precision)
    {
        precision_ = precision;
        return *this;
    }

    unsigned char getBase() const { return base_; }
    unsigned char getPrecision() const { return precision_; }
    std::string toString() const { return format(); }
};

#endif
