#ifndef CPP_TRAINING_GTEST_GTEST_TRIVIAL_FACTORIAL_HPP
#define CPP_TRAINING_GTEST_GTEST_TRIVIAL_FACTORIAL_HPP

int factorial(int n) {
  if (n < 0)
    return 0;
  int result = 1;
  for (int i = 2; i <= n; ++i)
    result *= i;
  return result;
}

#endif // CPP_TRAINING_GTEST_GTEST_TRIVIAL_FACTORIAL_HPP
