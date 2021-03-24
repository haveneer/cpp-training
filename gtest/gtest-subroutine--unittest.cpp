// include GTest tools
#include "gtest/gtest-spi.h" // for (EXCEPT/ASSERT)_FATAL_FAILURE
#include "gtest/gtest.h"

/***************************************************/

void will_not_fail() {
  SUCCEED() << "Because I want to succeed"; // Do nothing useful
  std::cout << "So far, so good" << std::endl;
}

void will_fail_hard() {
  FAIL() << "Because I have to fail"; // explicit fatal failure + additional info
  std::cerr << "Dead code here" << std::endl;
}

void will_fail_soft() {
  ADD_FAILURE() << "Fail and continue"; // explicit non-fatal failure
  std::cerr << "Continue after non-fatal failure" << std::endl;
}

// Using DISABLED_ prefix, test will not be run
TEST(SubroutineTest, DISABLED_FailureInSubroutineButStillContinue) {
  will_fail_hard();
  std::cerr << "Could you read me after soft failure?" << std::endl;
}

TEST(SubroutineTest, CheckNoFatalFailureInSubroutine) {
  ASSERT_NO_FATAL_FAILURE(will_not_fail());
}

TEST(SubroutineTest, CheckFatalFailureInSubroutine) {
  // When failure is the expected result
  EXPECT_FATAL_FAILURE(will_fail_hard(), "");
}

// Using DISABLED_ prefix, test will not be run
TEST(SubroutineTest, DISABLED_FailureInSubroutineAndStopNow) {
  ASSERT_NO_FATAL_FAILURE(
      // EXCEPT or ADD_FAILURE are not fatal failure : continue
      will_fail_soft());
  ASSERT_NO_FATAL_FAILURE(
      // ASSERT or FAIL are fatal failures : stop now
      will_fail_hard());
  // Following code is executed without ASSERT_NO_FATAL_FAILURE
  std::cerr << "You shouldn't read this" << std::endl;
}

// Using DISABLED_ prefix, test will not be run
TEST(SubroutineTest, DISABLED_FailureInSubroutineAndTestIt) {
  will_fail_hard();
  if (HasFatalFailure())                  // callable only from main test
    return;                               // Stop now
  if (::testing::Test::HasFatalFailure()) // same but callable from anywhere
    return;                               // Stop now
  std::cerr << "You shouldn't read this" << std::endl;
}

TEST(SubroutineTest, DISABLED_CollectTraceBeforeFailing) {
  SCOPED_TRACE("In main block");
  {
    SCOPED_TRACE("In first block");
    std::cerr << "OK" << std::endl;
  }
  {
    SCOPED_TRACE("In second block");
    EXPECT_TRUE(false);
  }
  EXPECT_FALSE(true);
}

TEST(SubroutineTest, LogAdditionalInfo) {
  // Additional info could be saved in report (if requested cf command line)
  //   --gtest_output=(json|xml)[:DIRECTORY_PATH/|:FILE_PATH]
  //   Generate a JSON or XML report in the given directory or with the given
  //   file name. FILE_PATH defaults to test_detail.xml.
  RecordProperty("MagicNumber", 43);
  RecordProperty("MagicNumber", 42); // one value by keyword (the last one)
}