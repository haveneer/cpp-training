#ifndef CPP_TRAINING_SOLUTIONS_NEWTON_VECTORIAL__VECTOR_HPP
#define CPP_TRAINING_SOLUTIONS_NEWTON_VECTORIAL__VECTOR_HPP

#include "newton-vectorial--common.hpp"
#include <memory>

namespace VectorNewton {
class Vector {
public:
  explicit Vector(std::size_t n);
  Real &operator()(std::size_t i);
  Real operator()(std::size_t i) const;
  std::size_t size() const { return m_n; }
  Vector copy() const;

private:
  std::size_t m_n;
  std::unique_ptr<Real[]> m_data;
};
} // namespace VectorNewton

#endif // CPP_TRAINING_SOLUTIONS_NEWTON_VECTORIAL__VECTOR_HPP
