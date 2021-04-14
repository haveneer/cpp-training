// include GTest tools
#include "gtest/gtest.h"
#include <exception>
#include <gmock/gmock.h>

struct Foo {
  MOCK_METHOD(void, do_something, (int), (const));
};

/***************************************************/

TEST(MultipleExpections, Check) {
  using namespace ::testing;

  Foo foo;

  EXPECT_CALL(foo, do_something(_)); // equivalent to .Times(1)
  EXPECT_CALL(foo, do_something(1))  //
      .Times(3);
  EXPECT_CALL(foo, do_something(Ge(1))) // not Ge() which conflicts the previous
      .Times(2)                         // or use Ge() and disable
      .RetiresOnSaturation();           // this rule on saturation

  foo.do_something(2);
  foo.do_something(2);
  foo.do_something(1);
  foo.do_something(1);
  foo.do_something(1);
  foo.do_something(0);
}
