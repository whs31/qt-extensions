// 26.09.2023 by whs31

#pragma once

#include <cmath>
#include <limits>
#include "QtExCore/Global"

namespace QtEx
{
  template<class T = decimal> constexpr inline T pi = enable_if_decimal<T>(3.141592653589793238462643383279502884L);
  template<class T = decimal> constexpr inline T euler = enable_if_decimal<T>(2.71828182845904523536028747135266249L);
  template<class T = decimal> constexpr inline T sqrt2 = enable_if_decimal<T>(1.41421356237309504880168872420969807L);
  template<class T = decimal> constexpr inline T sqrt3 = enable_if_decimal<T>(1.73205080756887729352744634150587236L);
  template<class T = decimal> constexpr inline T sqrt5 = enable_if_decimal<T>(2.23606797749978969640917366873127623L);
  template<class T = decimal> constexpr inline T phi = enable_if_decimal<T>(1.61803398874989484820458683436563811L);

  [[maybe_unused]] constexpr inline decimal π = pi<>;
  [[maybe_unused]] constexpr inline decimal e = euler<>;
  [[maybe_unused]] constexpr inline decimal φ = phi<>;

  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T log(T base, T exponent) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T log10(T exponent) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T log2(T exponent) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T ln(T exponent) noexcept;

  template<typename T> constexpr inline bool compare(T a, T b) noexcept;
  template<> constexpr inline bool compare<float>(float a, float b) noexcept;
  template<> constexpr inline bool compare<double>(double a, double b) noexcept;

  template<typename T> constexpr inline bool is_null(T a) noexcept;

  constexpr inline int ceil(float x) noexcept;
  constexpr inline int ceil(double x) noexcept;
  constexpr inline int floor(float x) noexcept;
  constexpr inline int floor(double x) noexcept;

  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T abs(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T sin(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T cos(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T tg(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T tan(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T arcsin(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T arccos(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T arctg(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T arctan(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T sqrt(T x) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T power(T base, T exponent) noexcept;

  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T deg2rad(T degrees) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T rad2deg(T radians) noexcept;

  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T sqrtSquaresSum(T a, T b) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T hypotenuse(T a, T b) noexcept;
  template<class T = decimal, enable_if_decimal_logic<T> = true> constexpr inline T sqrtSquaresDif(T a, T b) noexcept;

  template<class T = decimal> constexpr inline T min(T a, T b) noexcept;
  template<class T = decimal> constexpr inline T max(T a, T b) noexcept;
  template<class T = decimal> constexpr inline T clamp(T x, T lower, T upper) noexcept;
  template<class T = decimal, class U = decimal> constexpr inline T lerp(T start, T end, U t) noexcept;
  template<class T = decimal> constexpr inline T lerp(T start, T end, T t) noexcept;
  template<class T = decimal> constexpr inline bool inRange(T x, T start, T end) noexcept;

  template<class T = decimal, enable_if_decimal_logic<T> = true> inline T random() noexcept;
  template<> inline float random<float>() noexcept;
  template<> inline double random<double>() noexcept;
  template<class T = decimal> inline T randomInRange(T from, T to) noexcept;
  template<> inline int randomInRange<int>(int from, int to) noexcept;

  template<class T = decimal> constexpr inline T roundUpToPowerOf2(T x) noexcept;
} // QtEx

namespace QtEx
{
  template<class T, enable_if_decimal_logic<T>> constexpr inline T log(T base, T exponent) noexcept { return static_cast<T>(std::log(exponent) / std::log(base)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T log10(T exponent) noexcept { return log<T>(10, exponent); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T log2(T exponent) noexcept { return log<T>(2, exponent); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T ln(T exponent) noexcept { return log<T>(euler<T>, exponent); }

  template<typename T> constexpr inline bool compare(T a, T b) noexcept { return a == b; }
  template<> constexpr inline bool compare<float>(float a, float b) noexcept { return (std::abs(a - b) * 100000.f <= std::min(std::abs(a), std::abs(b))); }
  template<> constexpr inline bool compare<double>(double a, double b) noexcept { return (std::abs(a - b) * 1000000000000. <= std::min(std::abs(a), std::abs(b))); }

  template<typename T> constexpr inline bool is_null(T a) noexcept { return compare<T>(0, a); }

  constexpr inline int ceil(float x) noexcept { return static_cast<int>(std::ceil(x)); }
  constexpr inline int ceil(double x) noexcept { return static_cast<int>(std::ceil(x)); }
  constexpr inline int floor(float x) noexcept { return static_cast<int>(std::floor(x)); }
  constexpr inline int floor(double x) noexcept { return static_cast<int>(std::floor(x)); }

  template<class T, enable_if_decimal_logic<T>> constexpr inline T abs(T x) noexcept { return static_cast<T>(std::abs(x)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T sin(T x) noexcept { return static_cast<T>(std::sin(x)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T cos(T x) noexcept { return static_cast<T>(std::cos(x)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T tg(T x) noexcept { return tan<T>(x); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T tan(T x) noexcept { return static_cast<T>(std::tan(x)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T arcsin(T x) noexcept { return static_cast<T>(std::asin(x)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T arccos(T x) noexcept { return static_cast<T>(std::acos(x)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T arctg(T x) noexcept { return arctan<T>(x); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T arctan(T x) noexcept { return static_cast<T>(std::atan(x)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T sqrt(T x) noexcept { return static_cast<T>(std::sqrt(x)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T power(T base, T exponent) noexcept { return static_cast<T>(std::pow(base, exponent)); }

  template<class T, enable_if_decimal_logic<T>> constexpr inline T deg2rad(T degrees) noexcept { return static_cast<T>(degrees * pi<T> / 180); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T rad2deg(T radians) noexcept { return static_cast<T>(radians * 180 / pi<T>); }

  template<class T, enable_if_decimal_logic<T>> constexpr inline T sqrtSquaresSum(T a, T b) noexcept { return static_cast<T>(std::hypot(a, b)); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T hypotenuse(T a, T b) noexcept { return sqrtSquaresSum<T>(a, b); }
  template<class T, enable_if_decimal_logic<T>> constexpr inline T sqrtSquaresDif(T a, T b) noexcept { return static_cast<T>(sqrt<T>(power<T>(a, 2) - power<T>(b, 2))); }

  template<class T> constexpr inline T min(T a, T b) noexcept { return std::min<T>(a, b); }
  template<class T> constexpr inline T max(T a, T b) noexcept { return std::max<T>(a, b); }
  template<class T> constexpr inline T clamp(T x, T lower, T upper) noexcept { return max<T>(lower, min<T>(x, upper)); }
  template<class T, class U> constexpr inline T lerp(T start, T end, U t) noexcept { return static_cast<T>(start * (static_cast<U>(1.0) - t) + end * t); }
  template<class T> constexpr inline T lerp(T start, T end, T t) noexcept { return lerp<T, T>(start, end, t); }
  template<class T> constexpr inline bool inRange(T x, T start, T end) noexcept { return x >= start and x < end; }

  template<class T, enable_if_decimal_logic<T>> inline T random() noexcept { return static_cast<T>(rand()) / static_cast<T>(RAND_MAX); }
  template<> inline float random<float>() noexcept { return static_cast<float>(rand() >> 8) / (static_cast<float>((RAND_MAX >> 8) + 1)); }
  template<> inline double random<double>() noexcept { return static_cast<double>(rand()) / (static_cast<double>(RAND_MAX + 1LL)); }
  template<class T> inline T randomInRange(T from, T to) noexcept { return lerp<T>(from, to, random<T>()); }
  template<> inline int randomInRange<int>(int from, int to) noexcept { return static_cast<int>(randomInRange<float>(static_cast<float>(from), static_cast<float>(to))); }

  template<class T> constexpr inline T roundUpToPowerOf2(T x) noexcept { return static_cast<T>(power((T)2, ceil(log<T>(2, x)))); }
} // QtEx