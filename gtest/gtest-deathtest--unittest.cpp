// include GTest tools
#include "gtest/gtest.h"

#include <csignal>
#include <iostream>

/***************************************************/

// /!\ for thread safety: test suit including Death Assertion 
// must be suffixed by DeathTest

TEST(DemoDeathTest, SegFault) {
  ASSERT_DEATH(
      {
        int *p = new int[10];
        for (int i = 0;; ++i)
          p[i] = 42;
      },
      "");
}

TEST(DemoDeathTest, ExitSuccess) {
  EXPECT_EXIT(
      {
        std::cerr << "It is a Success; good bye" << std::endl;
        exit(0);
      },
      ::testing::ExitedWithCode(0), "Success");
}

TEST(DemoDeathTest, ExitFailure) {
  EXPECT_EXIT(
      {
        std::cerr << "Failure" << std::endl;
        exit(1);
      },
      ::testing::ExitedWithCode(1), "Failure");
}

#ifndef WIN32
TEST(DemoDeathTest, ExitSignal) {
  EXPECT_EXIT(
      {
        std::cerr << "Suicide" << std::endl;
        std::raise(SIGKILL);
      },
      ::testing::KilledBySignal(SIGKILL), "Suicide");
}
#endif /* WIN32 */