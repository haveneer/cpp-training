#include "newton-vectorial--vector.hpp"
#include <cassert>

namespace VectorNewton {

Vector::Vector(std::size_t n) : m_n{n}, m_data{new Real[m_n]} {
  for (std::size_t k = 0; k < m_n; ++k)
    m_data[k] = 0;
}

Real &Vector::operator()(std::size_t i) {
  assert(i < m_n);
  return m_data[i];
}

Real Vector::operator()(std::size_t i) const {
  assert(i < m_n);
  return m_data[i];
}

Vector Vector::copy() const {
  Vector c{m_n};
  for(size_t k=0;k<m_n;++k)
    c.m_data[k] = m_data[k];
  return c;
}


} // namespace VectorNewton