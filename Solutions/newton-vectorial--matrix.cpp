#include "newton-vectorial--matrix.hpp"
#include <cassert>

namespace VectorNewton {

Matrix::Matrix(std::size_t n) : m_n{n}, m_data{new Real[n * n]} {
  // 2D array implemented using linearized 1D array
  for (size_t k = 0; k < n * n; ++k)
    m_data[k] = 0;
}

Real &Matrix::operator()(std::size_t i, std::size_t j) {
  assert(i < m_n);
  assert(j < m_n);
  return m_data[i * m_n + j];
}

Real Matrix::operator()(std::size_t i, std::size_t j) const {
  assert(i < m_n);
  assert(j < m_n);
  return m_data[i * m_n + j];
}

Matrix Matrix::copy() const {
  Matrix c{m_n};
  for(size_t k=0;k<m_n*m_n;++k)
    c.m_data[k] = m_data[k];
  return c;
}

} // namespace VectorNewton