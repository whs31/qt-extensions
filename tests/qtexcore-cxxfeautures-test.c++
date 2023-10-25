#include <QtExtensions/Test>
#include <QtExtensions/Global>
#include <Libra/Expected>
#include <range/v3/view/enumerate.hpp>

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

declare_test_case(Expected, Expected)
  pass_if(Testing::split_phone_number(79805557214))
  pass_if(String("+7(980)-555-72-14") == Testing::split_phone_number(79805557214).value());
  pass_if(Testing::split_phone_number(79805557220))
  pass_if("+7(980)-555-72-20" == Testing::split_phone_number(79805557220).value());
  pass_if_not(Testing::split_phone_number(123))
  pass_if(Testing::InputError == Testing::split_phone_number(123).error());
  pass_if_not(Testing::split_phone_number(1234))
  pass_if(Testing::InputError == Testing::split_phone_number(1234).error());
end_test_case

declare_test_case(Ranges, Enumerate)
  vector<char> v = {'A', 'B', 'C', 'D'};
  for(auto const [index, letter] : ranges::view::enumerate(v))
  {
    pass_if(index >= 0 and index < 4)
    pass_if(letter == 'A' or letter == 'B' or letter == 'C' or letter == 'D')
  }
end_test_case