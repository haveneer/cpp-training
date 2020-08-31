#ifndef CPP_TRAINING_SOLUTIONS_NEWTON_VECTORIAL__FUNCTIONS_HPP
#define CPP_TRAINING_SOLUTIONS_NEWTON_VECTORIAL__FUNCTIONS_HPP

#include "newton-vectorial--matrix.hpp"
#include "newton-vectorial--vector.hpp"
#include <iostream>

namespace VectorNewton {

std::ostream &operator<<(std::ostream &o, const Matrix &m);
std::ostream &operator<<(std::ostream &o, const Vector &v);
Vector operator*(const Matrix &m, const Vector &x);
Vector operator-(const Vector &a, const Vector &b);
Vector operator-(const Vector &a);
void operator+=(Vector &a, const Vector &b);
Real norm2(const Vector &x);

Vector solve(const Matrix &A, const Vector &b, Real * condition_number = nullptr);

} // namespace VectorNewton

#endif // CPP_TRAINING_SOLUTIONS_NEWTON_VECTORIAL__FUNCTIONS_HPP
