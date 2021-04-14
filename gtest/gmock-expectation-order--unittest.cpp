// include GTest tools
#include "gtest/gtest.h"
#include <gmock/gmock.h>

struct Foo {
  MOCK_METHOD(void, init1, (), (const));
  MOCK_METHOD(void, init2, (), (const));
  MOCK_METHOD(void, proceed, (), (const));
  MOCK_METHOD(void, print, (), (const));
  MOCK_METHOD(void, save, (), (const));
};

/***************************************************/

void f(Foo &foo) {
  foo.init2();
  foo.init1();
  foo.proceed();
}

TEST(ExpectationOrder, Singles) {
  using ::testing::Expectation;

  Foo foo;

  Expectation init1 = EXPECT_CALL(foo, init1());
  Expectation init2 = EXPECT_CALL(foo, init2());
  EXPECT_CALL(foo, proceed()) //
      .After(init1, init2);

  f(foo);
}

TEST(ExpectationOrder, Set) {
  using ::testing::ExpectationSet;

  Foo foo;

  ExpectationSet expectations;
  expectations += EXPECT_CALL(foo, init1());
  expectations += EXPECT_CALL(foo, init2());
  EXPECT_CALL(foo, proceed()) //
      .After(expectations);

  f(foo);
}

TEST(ExpectationOrder, Sequence) {
  using ::testing::Sequence;

  Foo foo;

  Sequence s1, s2;

  EXPECT_CALL(foo, proceed()) //
      .InSequence(s1, s2);
  EXPECT_CALL(foo, print()) //
      .InSequence(s1);
  EXPECT_CALL(foo, save()) //
      .InSequence(s2);

  foo.proceed(); // before any print() or save()
  foo.print();   // order of print()
  foo.save();    //    or save() does'nt matter
}