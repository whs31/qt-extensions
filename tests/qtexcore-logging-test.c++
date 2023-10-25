//
// Created by whs31 on 02.10.23.
//

#include <QtExtensions/Test>
#include <QtExtensions/Logging>

using namespace QtEx;

declare_test_case(Logging, Logging)
  Log::setLoggingPattern();
  Log::log(Debug) << scope_information << "Example debug log";
  Log::log(Info) << scope_information << "Example info log";
  Log::log(Warning) << scope_information << "Example warning log";
  Log::log(Error) << scope_information << "Example error log";
  pass_always
end_test_case