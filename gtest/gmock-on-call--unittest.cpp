// include GTest tools
#include "gtest/gtest.h"
#include <exception>
#include <gmock/gmock.h>

struct Rng {
  MOCK_METHOD(int, rand, (int, int), (const));
};

/***************************************************/

TEST(OnCall, Check) {
  using namespace ::testing;

  Rng rng;

  ON_CALL(rng, rand(_, _)) // default rule first
      .WillByDefault(ReturnArg<0>());
  ON_CALL(rng, rand(0, 10)) //
      .WillByDefault(Return(5));
  ON_CALL(rng, rand(0, 10)) // last ON_CALL rules are first matches
      .WillByDefault(Return(4));
  ON_CALL(rng, rand(Lt(0), _)) //
      .WillByDefault(Throw(std::out_of_range("Negative low bound")));

  EXPECT_CALL(rng, rand(_, _))      // before any mock call
      .Times(AtLeast(0))            // to avoid runtime warnings
      .WillRepeatedly(DoDefault()); // (this is the default behavior)

  EXPECT_EQ(rng.rand(10, 20), 10);
  EXPECT_EQ(rng.rand(0, 2), 0);
  EXPECT_EQ(rng.rand(0, 10), 4); // last ON_CALL rules are first matches
  EXPECT_THROW(rng.rand(-1, 20), std::out_of_range); //
}
