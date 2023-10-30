#include <QtExtensions/Test>
#include <QtExtensions/Global>
#include <Libra/Expected>

using Qt::String;
using std::vector;

namespace Testing
{
  enum ExpectationError
  {
    InputError,
    UnknownError
  };

  auto add_minus(String num) -> expected<String, ExpectationError> { return num.insert(num.size() - 4, "-").insert(num.size() - 2, "-"); }
  auto add_braces(String num) -> expected<String, ExpectationError> { return num.insert(2, "(").insert(6, ")-"); }
  auto prepend_plus(String num) -> expected<String, ExpectationError> { return num.prepend("+"); }
  auto convert(long long num) -> expected<String, ExpectationError>
  {
    if(num < 10000000000)
      return unexpected(InputError);
    return String::number(num, 10);
  }

  auto split_phone_number(long long num) -> expected<String, ExpectationError>
  {
    return convert(num)
           .and_then(prepend_plus)
           .and_then(add_braces)
           .and_then(add_minus);
  }
} // Testing