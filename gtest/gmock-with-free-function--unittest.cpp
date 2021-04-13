#include "NonCopyable.hpp"
#include <cassert>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// There exist external solutions
// * https://github.com/apriorit/gmock-global

#define USE_MOCK

// Pre-defined mandatory interface
// (we cannot use functor)
int function_to_mock(int /*i*/);

int function_to_test(int n) {
  int r = 0;
  for (int i = 0; i < n; ++i)
    r += function_to_mock(i);
  return r;
}

// Each branch of this direction should be in separate .cpp unit
#ifdef USE_MOCK
// Mock implémentation
class FunctionToMock : public Noncopyable {
public:
  FunctionToMock() {
    if (!m_instance)
      m_instance = this;
  }
  ~FunctionToMock() override {
    assert(m_instance == this);
    m_instance = nullptr;
  }
  static FunctionToMock &instance() {
    assert(m_instance);
    return *m_instance;
  }

  MOCK_METHOD(int, call, (int), ());

private:
  inline static FunctionToMock *m_instance = nullptr;
};

// free function mock: just call the global object
int function_to_mock(int i) {
  // We cannot call the original function
  return FunctionToMock::instance().call(i);
}
#else  /* USE_MOCK */
// Default implémentation
int function_to_mock(int i) { return i * i; }
#endif /* USE_MOCK */

TEST(WithFreeFunction, Test) {
  FunctionToMock guard; // build context and destroyed at the end
  using ::testing::_; // _ is the joker argument for expected calls
  using ::testing::DoDefault;
  using ::testing::InSequence;
  using ::testing::Return;

  ON_CALL(FunctionToMock::instance(), call(_)).WillByDefault(Return(0));
  ON_CALL(FunctionToMock::instance(), call(0)).WillByDefault(Return(0));
  ON_CALL(FunctionToMock::instance(), call(1)).WillByDefault(Return(1));
  ON_CALL(FunctionToMock::instance(), call(2)).WillByDefault(Return(4));
  ON_CALL(FunctionToMock::instance(), call(3)).WillByDefault(Return(9));
  ON_CALL(FunctionToMock::instance(), call(4)).WillByDefault(Return(16));
  EXPECT_CALL(FunctionToMock::instance(), call(_)).Times(5);
  EXPECT_EQ(function_to_test(5), 30);
}

// This is the default main.
// If not defined gtest_main will do it for you.
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
