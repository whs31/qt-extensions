/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 26.09.23
  *  @copyright Radar-MMS 2023
  */

#include <QtCore/QCoreApplication>
#include <QtExtensions/Test>
declare_test_case(TestingCheck, GTestInitialised)
  pass_always
end_test_case

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  //QCoreApplication::exec();
  return RUN_ALL_TESTS();
}