#ifndef CPP_TRAINING_GTEST_GTEST_TRIVIAL_COMPONENT_HPP
#define CPP_TRAINING_GTEST_GTEST_TRIVIAL_COMPONENT_HPP

class Component {
public:
  Component() = default;
  void initialize() {}
  int getInitValue() { return m_field; }

private:
  int m_field;
};

#endif // CPP_TRAINING_GTEST_GTEST_TRIVIAL_COMPONENT_HPP
