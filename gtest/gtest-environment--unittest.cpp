//#region [Declarations]
#include <iostream>
// include GTest tools
#include "gtest/gtest.h"
//#endregion

// Program level fixture
class MyEnvironment : public ::testing::Environment {
  //#region [For set-up / tear-down at the suit level]
private: // called from ::testing::Environment, private visibility is sufficient
  void SetUp() override { // don't forget 'override'
    if (m_verbose)
      std::cout << "MyEnvironment global set up\n";
  }
  void TearDown() override { // don't forget 'override'
    if (m_verbose)
      std::cout << "MyEnvironment global tear down "
                << "(" << m_count << " auxMethod calls)\n";
  }
  inline static int m_count = 0; // inline static is a C++17 feature

public:
  MyEnvironment() {
    if (m_verbose) // constructor if close to SetUp
      std::cout << "MyTestFixture constructor\n";
  }
  ~MyEnvironment() override { // don't forget 'override' (TODO why ?)
    if (m_verbose) // destructor if close to TearDown but exceptions are _forbidden_
      std::cout << "MyEnvironment destructor\n";
  }
  //#endregion

  static void auxMethod(const std::string &suitName,
                        const std::string &testCaseName) {
    std::cout << " in " << suitName << "." << testCaseName << "\n";

    // Retrieve info about running test
    const testing::TestInfo *const test_info =
        testing::UnitTest::GetInstance()->current_test_info();

    EXPECT_EQ(suitName, test_info->test_suite_name());
    EXPECT_EQ(testCaseName, test_info->name());

    ++m_count;
  }

  inline static bool m_verbose = true; // FIXME // inline static is a C++17 feature
};

TEST(MyEnvTestSuit, test1) {
  MyEnvironment::auxMethod("MyEnvTestSuit", "test1");
  ASSERT_TRUE(true);
}

TEST(MyEnvTestSuit, test2) {
  MyEnvironment::auxMethod("MyEnvTestSuit", "test2");
  EXPECT_LT(1, 2);
}

// Optional; if you need something "special"
int main(int argc, char **argv) {
  std::cout << "## I run GoogleTest myself ##\n";
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::Environment *const env =
      ::testing::AddGlobalTestEnvironment(new MyEnvironment{});

  return RUN_ALL_TESTS();
}