#ifndef CPP_TRAINING_SOLUTIONS_NEWTON_VECTORIAL__MATRIX_HPP
#define CPP_TRAINING_SOLUTIONS_NEWTON_VECTORIAL__MATRIX_HPP

#include "newton-vectorial--common.hpp"
#include "newton-vectorial--matrix.hpp"
#include <memory>

namespace VectorNewton {

// Matrice carrée dense
// Implicitement non copiable à cause du unique_ptr
class Matrix {
public:
  explicit Matrix(std::size_t n); // 3-5-0 rule
  Real &operator()(std::size_t i, std::size_t j);
  Real operator()(std::size_t i, std::size_t j) const;
  std::size_t size() const { return m_n; }
  Matrix copy() const;
  
private:
  const std::size_t m_n;
  std::unique_ptr<Real[]> m_data;
};

} // namespace VectorNewton

#endif // CPP_TRAINING_SOLUTIONS_NEWTON_VECTORIAL__MATRIX_HPP
