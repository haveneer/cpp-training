// include GTest tools
#include "gtest/gtest.h"
#include <exception>
#include <gmock/gmock.h>

struct Rng {
  MOCK_METHOD(int, rand, (int, int), (const));
  MOCK_METHOD(int, rand0, (int), (const));
  MOCK_METHOD(void, something_else, (), (const));
};

/***************************************************/

TEST(UninterestingCall, Check) {
  using namespace ::testing;

  // Rng rng;            // uninteresting calls are warnings
  // NaggyMock<Rng> rng; // (same)
  // default mock will fail on rand0 calls
  // Uninteresting mock function call:
  // rng.rand0(2), rng.rand0(10), rng.something_else()

  NiceMock<Rng> rng; // uninteresting calls are not warnings
  // StrictMock<Rng> rng; // uninteresting calls are errors

  static_assert(std::is_base_of_v<Rng, decltype(rng)>);
  
  ON_CALL(rng, rand(_, _)) // default rule first
      .WillByDefault(ReturnArg<0>());
  ON_CALL(rng, rand(0, _)) // use second arg if first in 0
      .WillByDefault(Invoke([&](auto a, auto b) { return rng.rand0(b); }));
  ON_CALL(rng, rand0(_)).WillByDefault(ReturnArg<0>());

  EXPECT_CALL(rng, rand(_, _)) // before any mock call
      .Times(3);

  EXPECT_EQ(rng.rand(10, 20), 10);
  EXPECT_EQ(rng.rand(0, 2), 2);
  EXPECT_EQ(rng.rand(0, 10), 10);
  rng.something_else();
}
