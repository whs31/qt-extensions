/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 26.09.23
  *  @copyright Radar-MMS 2023
  */

#pragma once

#include <gtest/gtest.h>

#define execute_tests() int main(int argc, char** argv) { testing::InitGoogleTest(&argc, argv); return RUN_ALL_TESTS(); }
#define log_test_case qInfo() << "Test case prints" <<
#define declare_test_case(suite, name) TEST(suite, name) {
#define end_test_case }
#define pass_if_floats_equal(a, b) EXPECT_FLOAT_EQ(a, b);
#define pass_if_doubles_equal(a, b) EXPECT_DOUBLE_EQ(a, b);
#define pass_if_any_floating_point_equal(a, b, c, d) pass_if_floats_equal(a, b) pass_if_doubles_equal(a, b)
#define pass_if_template_decimal_equal(a, a1, a2) pass_if_floats_equal(a<float>, a1) pass_if_doubles_equal(a<double>, a2)
#define pass_if_equal(a, b) EXPECT_EQ(a, b);
#define pass_if(a) EXPECT_TRUE(a);
#define pass_if_not(a) EXPECT_FALSE(a);
#define pass_if_near(a, b, error) ASSERT_NEAR(a, b, error);
#define pass_always EXPECT_TRUE(true);
#define pass