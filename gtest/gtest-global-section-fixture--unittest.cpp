//#region [Declarations]
#include <iostream>
// include GTest tools
#include "gtest/gtest.h"
#include <algorithm>
#include <sstream>
#include <tuple>
//#endregion

// Existing global data
struct GlobalSection {
  const static size_t field_size = 10;
  int id;
  int fields[field_size];
};

struct GlobalSection_t {
  struct GlobalSection *p;
};

extern struct GlobalSection_t p_global_section;
// Existing global data (END)

// TestSuit level fixture
class GlobalSectionFixture : public ::testing::Test {
  //#region [For set-up / tear-down at the suit level]
public:                          // needs to be publicly accessible (e.g. TEST_P)
  static void SetUpTestSuite() { // /!\ there is no guard if you misspell it
    if (m_verbose)
      std::cout << "GlobalSectionFixture test suit set up [" << p_global_section.p
                << "]\n";
  }
  static void TearDownTestSuite() { // /!\ there is no guard if you misspell it
    if (m_verbose)
      std::cout << "GlobalSectionFixture test suit tear down [" << p_global_section.p
                << "]\n";
  }

  GlobalSectionFixture() {
    if (m_verbose) // constructor if close to SetUp
      std::cout << "GlobalSectionFixture constructor\n";
    assert(p_global_section.p == nullptr);
  }
  ~GlobalSectionFixture() override { // don't forget 'override' (TODO why ?)
    if (m_verbose) // destructor if close to TearDown but exceptions are _forbidden_
      std::cout << "GlobalSectionFixture destructor\n";
    delete p_global_section.p;
    p_global_section.p = nullptr;
  }
  //#endregion

protected:                // needs to be accessible by sub-classes (e.g. TEST*)
  void SetUp() override { // don't forget 'override' (TODO why ?)
    std::cout << "GlobalSectionFixture test case set up\n";
    p_global_section.p = new GlobalSection{};
  }
  void TearDown() override { // don't forget 'override' (TODO why ?)
    std::cout << "GlobalSectionFixture test case tear down\n";
  }

  inline static bool m_verbose = true; // FIXME // inline static is a C++17 feature
};

TEST_F(GlobalSectionFixture, test1) {
  // Here you are in a sub-class of the fixture... (cf magic macro)
  std::cout << test_info_->name() << "\n";
  ASSERT_TRUE(true);
}

TEST_F(GlobalSectionFixture, test2) {
  std::cout << test_info_->name() << "\n";
  EXPECT_LT(1, 2);
}

// TestSuit level parametric fixture
class GlobalSectionFixtureAlt
    : public GlobalSectionFixture,
      public testing::WithParamInterface<std::tuple<int, double>> {};

TEST_P(GlobalSectionFixtureAlt, DISABLED_JobA) {
  auto [id, val] = GetParam(); // destructing or use std::get
  std::cout << ::testing::UnitTest::GetInstance()->current_test_info()->name()
            << " (" << id << ", " << val << ")\n";
  p_global_section.p->id = id;
  usleep(10000);
  EXPECT_EQ(p_global_section.p->id, id);
}

TEST_P(GlobalSectionFixtureAlt, JobB) {
  auto [id, val] = GetParam(); // destructing or use std::get
  std::cout << ::testing::UnitTest::GetInstance()->current_test_info()->name()
            << " (" << id << ", " << val << ")\n";
  p_global_section.p->id = id;
  usleep(10000);
  EXPECT_EQ(p_global_section.p->id, id);
}

INSTANTIATE_TEST_SUITE_P(Part1, GlobalSectionFixtureAlt,
                         testing::Combine(testing::Values(1, 2),
                                          testing::Range(0.0, 1.0, 0.1)));

auto parametricTestName(
    const testing::TestParamInfo<GlobalSectionFixtureAlt::ParamType> &info)
    -> std::string {
  std::ostringstream oss;
  oss << "id_" << std::get<0>(info.param) << "__";
  oss << "val_" << std::get<1>(info.param);
  std::string name = oss.str();
  std::replace_if(
      name.begin(), name.end(), [](auto c) { return c != '_' && !std::isalnum(c); },
      '_'); // replace all 'x' to 'y'

  return name; // must be a valid identifier
}

INSTANTIATE_TEST_SUITE_P(Part2, GlobalSectionFixtureAlt,
                         testing::Combine(testing::Values(1, 2),
                                          testing::Range(1.0, 2.0, 0.33)),
                         parametricTestName); // using special name printer disabled
                                              // tests seems to be bypassed

struct GlobalSection_t p_global_section;
int main(int argc, char **argv) {
  std::cout << "## I run GoogleTest myself ##\n";
  p_global_section.p = nullptr;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}