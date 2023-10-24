/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 24.10.23
  *  @copyright Radar-MMS 2023
  */

#include <Libra/Platform>
#include <QtExCore/Test>
#include <QtExCore/Logging>

declare_test_case(Libra, Platform)
  llog(Info) (int)Libra::Platform::os();
  llog(Info) (int)Libra::Platform::endianness();
  llog(Info) (int)Libra::Platform::compiler();
  llog(Info) (int)Libra::Platform::architecture();
  llog(Info) (int)Libra::Platform::standardVersion();
  llog(Info) Libra::Platform::wordSize();
  llog(Info) Libra::Platform::qtVersion() << Libra::Platform::qtVersionMajor()
          << Libra::Platform::qtVersionMinor() << Libra::Platform::qtVersionPatch();
  pass_always
end_test_case