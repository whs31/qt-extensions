#include <QtExtensions/Test>
#include <QtExtensions/Math>

#if defined(Q_OS_WIN)
#include <QtCore/QtMath>
#define M_PIf float(M_PI)
#define M_Ef float(M_E)
#define M_SQRT2f float(M_SQRT2)
#endif

using namespace QtEx;

declare_test_case(Math, Constants)
  pass_if_template_decimal_equal(pi, M_PIf, M_PI)
  pass_if_template_decimal_equal(e, M_Ef, M_E)
  pass_if_template_decimal_equal(phi, float(1.618033988749894), 1.618033988749894)
  pass_if_template_decimal_equal(sqrt2, M_SQRT2f, M_SQRT2)
  pass_if_template_decimal_equal(sqrt3, float(1.732050807568877293), 1.732050807568877293)
  pass_if_template_decimal_equal(sqrt5, float(2.236067977499789696), 2.236067977499789696)
end_test_case

declare_test_case(Math, Logarithms)
  pass_if_floats_equal(ln<float>(e<float>), 1.f)
  pass_if_floats_equal(ln<float>(10), 2.30258509f)
  pass_if_floats_equal(ln<float>(0.01f), -4.60517019f)
  pass_if_floats_equal(ln<float>(9999), 9.21024037f)

  pass_if_floats_equal(log2<float>(2), 1.f)
  pass_if_floats_equal(log2<float>(256), 8.f)
  pass_if_floats_equal(log2<float>(.25), -2.f)
  pass_if_floats_equal(log2<float>(99999), 16.609627f)

  pass_if_floats_equal(log10<float>(2), 0.30102999566)
  pass_if_floats_equal(log10<float>(256), 2.4082399653)
  pass_if_floats_equal(log10<float>(.25), -0.6020599913)
  pass_if_floats_equal(log10<float>(99999), 4.99999565703)

  pass_if_floats_equal(log<float>(123, 321), 1.19933915596701)
  pass_if_floats_equal(log<float>(256, 512), 1.125)
  pass_if_floats_equal(log<float>(.25, 15), -1.9534452978042592)
  pass_if_floats_equal(log<float>(99, 100), 1.00218717600003557)
end_test_case

declare_test_case(Math, Comparsion)
  pass_if(compare<float>(0.1, 1.f/10))
  pass_if(compare<float>(0, 0))
  pass_if(compare<float>(.1 + .1 + .1, .3))
  pass_if(compare<float>(.1 * 10, 1.f))
end_test_case

declare_test_case(Math, Rounding)
  pass_if_equal(ceil(pi<float>), 4)
  pass_if_equal(floor(pi<float>), 3)
  pass_if_equal(floor(e<float>), 2)
  pass_if_equal(ceil(e<float>), 3)
end_test_case

declare_test_case(Math, Absolute)
  pass_if_floats_equal(abs<float>(0.f), 0.f)
  pass_if_floats_equal(abs<float>(-512.f), 512.f)
end_test_case

declare_test_case(Math, BasicTrigonometry)
  pass_if_floats_equal(sin<float>(123), -0.45990348)
  pass_if_floats_equal(sin<float>(-123), -sin<float>(123))
  pass_if_floats_equal(cos<float>(123), -0.8879689066)
  pass_if_floats_equal(cos<float>(-123), cos<float>(123))
  pass_if_floats_equal(tg<float>(123), 0.51792747)
  pass_if_floats_equal(tg<float>(-123), -tg<float>(123))
  pass_if_floats_equal(tg<float>(123), tan<float>(123))
end_test_case

declare_test_case(Math, ArcTrigonometry)
  pass_if_floats_equal(arcsin<float>(1), pi<float> / 2)
  pass_if_floats_equal(arcsin<float>(-1), -pi<float> / 2)
  pass_if_floats_equal(arccos<float>(1), 0)
  pass_if_floats_equal(arccos<float>(-1), pi<float>)
  pass_if_floats_equal(arctg<float>(123), 1.5626664246)
  pass_if_floats_equal(arctg<float>(-123), -arctg<float>(123))
  pass_if_floats_equal(arctg<float>(-123), arctg<float>(-123))
end_test_case

declare_test_case(Math, Root)
  pass_if_floats_equal(sqrt<float>(2), sqrt2<float>)
  pass_if_floats_equal(sqrt<float>(10), 3.16227766016)
  pass_if_floats_equal(sqrt<float>(20), 2 * sqrt5<float>)
  pass_if_floats_equal(sqrt<float>(100), 10)
end_test_case

declare_test_case(Math, Power)
  pass_if_floats_equal(power<float>(2, 8), 256)
  pass_if_floats_equal(power<float>(2, 10), 1024)
  pass_if_floats_equal(power<float>(2, 11), 2048)
  pass_if_floats_equal(power<float>(9, 5), 59'049)
  pass_if_floats_equal(power<float>(-2, 2), 4)
  pass_if_floats_equal(power<float>(-2, -3), -.125f)
end_test_case

declare_test_case(Math, RadianDegreeConversion)
  pass_if_floats_equal(deg2rad<float>(180), pi<float>)
  pass_if_floats_equal(deg2rad<float>(360), 2 * pi<float>)
  pass_if_floats_equal(deg2rad<float>(54), 3 * pi<float> / 10)
  pass_if_floats_equal(deg2rad<float>(154), 77 * pi<float> / 90)
  pass_if_floats_equal(rad2deg<float>(180), 10313.240312)
  pass_if_floats_equal(rad2deg<float>(360), 20626.480625)
  pass_if_floats_equal(rad2deg<float>(54), 3093.9720937)
  pass_if_floats_equal(rad2deg<float>(154), 8823.550045)
end_test_case

declare_test_case(Math, SquareSumUnderRoot)
  pass_if_floats_equal(hypotenuse<float>(3, 5), sqrtSquaresSum<float>(3, 5))
  pass_if_floats_equal(hypotenuse<float>(3, 5), 5.83095189484530047087415)
  pass_if_floats_equal(sqrtSquaresDif<float>(5, 3), 4)
  pass_if_floats_equal(sqrtSquaresDif<float>(15, 3), 6 * sqrt<float>(6))
end_test_case

declare_test_case(Math, Clamping)
  pass_if_floats_equal(min<float>(123, 321), 123)
  pass_if_floats_equal(max<float>(123, 321), 321)
  pass_if_floats_equal(clamp<float>(123, 15, 100), 100)
  pass_if_floats_equal(clamp<float>(4, 15, 100), 15)
  pass_if(inRange<float>(15, 14, 60))
end_test_case

declare_test_case(Math, LinearInterpolation)
  pass_if_floats_equal(lerp<float>(0, 100, .5f), 50)
  pass_if_floats_equal(lerp<float>(0, 1000, .5f), 500)
end_test_case

declare_test_case(Math, Random)
  pass_if(inRange<float>(random<float>(), 0.f, 1.f))
  pass_if(inRange<double>(random<double>(), 0., 1.))
  pass_if(inRange<float>(randomInRange<float>(15, 16), 15.f, 16.f))
  pass_if(inRange<float>(randomInRange<float>(-5, 600), -5.f, 600.f))
end_test_case