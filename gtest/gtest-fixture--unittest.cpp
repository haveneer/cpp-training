//#region [Declarations]
#include <iostream>
// include GTest tools
#include "gtest/gtest.h"
//#endregion

class MyTestFixture : public ::testing::Test {
  //#region [For set-up / tear-down at the suit level]
public: // needs to be publicly accessible (e.g. TEST_P)
  static void SetUpTestSuite() { // /!\ there is no guard if you misspell it
    if (m_verbose)
      std::cout << "MyTestFixture test suit set up\n";
  }
  static void TearDownTestSuite() { // /!\ there is no guard if you misspell it
    if (m_verbose)
      std::cout << "MyTestFixture test suit tear down "
                << "(" << m_count << " auxMethod calls)\n";
    ASSERT_EQ(2, m_count);
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

protected: // needs to be accessible by sub-classes (e.g. TEST*)
  void SetUp() override { // don't forget 'override' (TODO why ?)
    std::cout << "MyTestFixture test case set up\n";
  }
  void TearDown() override { // don't forget 'override' (TODO why ?)
    std::cout << "MyTestFixture test case tear down\n";
  }

  void auxMethod(const std::string &suitName, const std::string &testCaseName) {
    std::cout << " in " << suitName << "." << testCaseName << "\n";
    ++m_count;
  }
  inline static bool m_verbose = false; // FIXME // inline static is a C++17 feature
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