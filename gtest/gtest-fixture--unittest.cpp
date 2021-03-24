//#region [Declarations]
#include <iostream>
// include GTest tools
#include "gtest/gtest.h"
//#endregion

// TestSuit level fixture
class MyTestFixture : public ::testing::Test {
  //#region [For set-up / tear-down at the suit level]
public:                          // needs to be publicly accessible (e.g. TEST_P)
  static void SetUpTestSuite() { // /!\ there is no guard if you misspell it
    if (m_verbose)
      std::cout << "MyTestFixture test suit set up\n";
  }
  static void TearDownTestSuite() { // /!\ there is no guard if you misspell it
    if (m_verbose)
      std::cout << "MyTestFixture test suit tear down "
                << "(" << m_count << " auxMethod calls)\n";
  }
  inline static int m_count = 0; // inline static is a C++17 feature

  MyTestFixture() {
    if (m_verbose) // constructor if close to SetUp
      std::cout << "MyTestFixture constructor\n";
  }
  ~MyTestFixture() override { // don't forget 'override' (TODO why ?)
    if (m_verbose) // destructor if close to TearDown but exceptions are _forbidden_
      std::cout << "MyTestFixture destructor\n";
  }
  //#endregion

protected:                // needs to be accessible by sub-classes (e.g. TEST*)
  void SetUp() override { // don't forget 'override' (TODO why ?)
    std::cout << "MyTestFixture test case set up\n";
  }
  void TearDown() override { // don't forget 'override' (TODO why ?)
    std::cout << "MyTestFixture test case tear down\n";
  }

  void auxMethod(const std::string &suitName, const std::string &testCaseName) {
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

TEST_F(MyTestFixture, test1) {
  // Here you are in a sub-class of the fixture... (cf magic macro)
  auxMethod("MyTestFixture", "test1");
  ASSERT_TRUE(true);
}

TEST_F(MyTestFixture, test2) {
  auxMethod("MyTestFixture", "test2");
  EXPECT_LT(1, 2);
}

using MyTestFixtureDeathTest = MyTestFixture; // Special alias for DeathTest suits
TEST_F(MyTestFixtureDeathTest, test3) {
  auxMethod("MyTestFixtureDeathTest", "test3");
  ASSERT_DEATH(
      {
        int *p = new int[10];
        for (int i = 0;; ++i)
          p[i] = 42;
      },
      "");
}

// Optional; if you need something "special"
int main(int argc, char **argv) {
  std::cout << "## I run GoogleTest myself ##\n";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}