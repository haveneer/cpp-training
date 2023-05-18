/*
  Author: Matthew Might
  Site:   http://matt.might.net/

  This program is a simple demonstration of how to create a
  lambda-like construct for anonymous functions in C++.

  For example:

    lambda<int> (x) --> 3*x + 7

  is a function that multiplies its argument by 3 and adds 7 to the
  result; while

    lambda<int> (x,y) --> x + y

  becomes a synonym for the addition function; and

    B = (lambda<int> (x) --> 3*x + 1).map(n,A)

  produces a new array B in which B[i] = 3*A[i] + 1.


  Lambda terms can also capture free variables and perform Currying;
  for instance, given:

    Function2<int,int,int> h(int a, int b) {
     return lambda<int> (x,y) --> a*x + b*y ;
    }

  the value of h(3,4)(1,1) is 7.


  Internally, the implementation exploits templates, operator
  overloading and function pointers (but not a single macro) to
  construct a type-safe domain-specific embedded language (DSEL) for
  describing anonymous functions.


  WARNING: This is a demonstration!  It has not been optimized for
  performance; (obvious) memory leaks remain; and no synchronization
  has been added to make the code thread safe!

 */

#include <stdio.h>
#include <stdlib.h>

/**
  Counts the number of meta-variables; used to allocate a unique
  variable id (++MaxVar) each time one is created.
 */
unsigned int MaxVar = 0;

/**
   An Exp<T> expression is a syntax tree in the DSEL that describes a
   computation of type T.
 */
template <typename T> struct Exp {

  /**
    Sets the cell associated with the variable identified by id.
   */
  virtual void set(unsigned int id, void *p) {
    throw "Can't set in a generic expression!";
  }

  /**
     Evaluates the current expression.
   */
  virtual T eval() { throw "Can't evaluate a generic expression!"; }

  /**
     Clones this expression.
   */
  virtual Exp<T> *clone() { throw "Can't clone a generic expression!"; }
};

/**
   A Const<T> expression always returns the same value.
 */
template <typename T> class Const : public Exp<T> {
private:
  T value;

public:
  Const<T>(T value) { this->value = value; }

  virtual void set(unsigned int id, void *p) {
    // There is no variable in this node, and it has no children, so
    // there is nothing to set.
  }

  virtual T eval() { return value; }

  virtual Exp<T> *clone() { return new Const<T>(value); }
};

/**
   A Var<T> expression represents an input variable of type T.
 */
template <typename T> class Var : public Exp<T> {
public:
  /**
     Points to the value of this variable.
   */
  T *value;

  /**
     Holds a unique id for this variable.
   */
  unsigned int id;

  /**
     When a fresh variable is created, it gets a unique id.
   */
  Var<T>() {
    this->value = NULL;
    this->id = ++MaxVar;
  }

  /**
     When a variable is copied, it retains the old id.
   */
  Var<T>(const Var<T> &that) {
    this->value = that.value;
    this->id = that.id;
  }

  /**
     Sets the memory cell if the ids match.
   */
  virtual void set(unsigned int id, void *p) {
    if (this->id == id) {
      this->value = (T *)p;
    }
  }

  virtual Exp<T> *clone() { return new Var(*this); }

  virtual T eval() { return *value; }
};

/**
   A BinOp expression represents a binary operation on two
   expressions.
 */
template <typename T> class BinOp : public Exp<T> {
private:
  T (*op)(T, T);
  Exp<T> *lhs;
  Exp<T> *rhs;

public:
  BinOp<T>(T (*op)(T, T), Exp<T> *left, Exp<T> *right) {
    this->lhs = left;
    this->rhs = right;
    this->op = op;
  }

  virtual void set(unsigned int id, void *p) {
    this->lhs->set(id, p);
    this->rhs->set(id, p);
  }

  virtual T eval() { return op(lhs->eval(), rhs->eval()); }

  virtual Exp<T> *clone() { return new BinOp(op, lhs, rhs); }
};

/**
   Computes the sum of two integers.
 */
int sum(int x, int y) { return x + y; }

/**
   Computes the product of two integers.
 */
int product(int x, int y) { return x * y; }

/**
   Integer expressions support the + and * operations.

   Using a specialization of Exp over int provides static type safety.
 */
template <> struct Exp<int> {
  virtual int eval() { throw "Can't evaluate a generic (int) expression!"; }

  virtual Exp<int> *clone() { throw "Can't clone a generic (int) expression!"; }

  virtual void set(unsigned int id, void *p) {
    throw "Can't set in a generic expression!";
  }

  /**
     Represents addition with another expression.
   */
  Exp<int> &operator+(Exp<int> &that) {
    return *(new BinOp<int>(sum, this->clone(), that.clone()));
  }

  /**
     Represents multiplication with another expression.
   */
  Exp<int> &operator*(Exp<int> &that) {
    return *(new BinOp<int>(product, this->clone(), that.clone()));
  }

  /**
     Represents addition with an integer constant.
   */
  Exp<int> &operator+(int n) {
    return *(new BinOp<int>(sum, this->clone(), new Const<int>(n)));
  }

  /**
     Represents multiplication with an integer constant.
   */
  Exp<int> &operator*(int n) {
    return *(new BinOp<int>(product, this->clone(), new Const<int>(n)));
  }
};

Exp<int> &operator+(int n, Exp<int> &thiss) {
  return *(new BinOp<int>(sum, new Const<int>(n), thiss.clone()));
}

Exp<int> &operator*(int n, Exp<int> &thiss) {
  return *(new BinOp<int>(product, new Const<int>(n), thiss.clone()));
}

/**
   A Function1<Y,X1> object maps X1 into Y.
 */
template <typename Y, typename X1> class Function1 {
private:
  /**
     The expression corresponding to the first input.
   */
  Var<X1> param1;

  /**
     The body of this function.
   */
  Exp<Y> *body;

public:
  Function1<Y, X1>() {}

  Function1<Y, X1>(Var<X1> &p1) : param1(p1) {}

  /**
     We combine -- and > to fake a --> operator.
   */
  Function1<Y, X1> &operator--(int) { return *this; }

  Function1<Y, X1> &operator>(Exp<Y> &body) {
    this->body = body.clone();
    this->body->set(param1.id, param1.value);
    return *this;
  }

  Function1<Y, X1> &operator>(Y y) {
    this->body = new Const<Y>(y);
    this->body->set(param1.id, param1.value);
    return *this;
  }

  /**
     Applies this function to an input.
   */
  Y operator()(const X1 &x1) {
    *this->param1.value = x1;
    return body->eval();
  }

  /**
     Maps this funtion over an array.
   */
  Y *map(unsigned int size, X1 input[]) {
    Y *out = new Y[size];
    for (unsigned int i = 0; i < size; ++i) {
      out[i] = (*this)(input[i]);
    }
    return out;
  }
};

/**
   Creates a new anonymous function of one argument.
 */
template <typename Y, typename X1> Function1<Y, X1> lambda(Var<X1> &x1) {
  // Allocate space for the argument value:
  x1.value = (X1 *)malloc(sizeof(X1));
  Function1<Y, X1> ret(x1);
  return ret;
}

/**
   A Function2<Y,X1,X2> object maps (X1,X2) into Y.
 */
template <typename Y, typename X1, typename X2> class Function2 {
private:
  Var<X1> param1;
  Var<X2> param2;

  Exp<Y> *body;

public:
  Function2<Y, X1, X2>() {}

  Function2<Y, X1, X2>(Var<X1> &p1, Var<X2> &p2) : param1(p1), param2(p2) {}

  /**
     We combine -- and > to fake a --> operator.
   */
  Function2<Y, X1, X2> &operator--(int) { return *this; }

  Function2<Y, X1, X2> &operator>(Exp<Y> &body) {
    this->body = body.clone();
    this->body->set(param1.id, param1.value);
    this->body->set(param2.id, param2.value);
    return *this;
  }

  Function1<Y, X1> &operator>(Y y) {
    this->body = new Const<Y>(y);
    this->body->set(param1.id, param1.value);
    this->body->set(param2.id, param2.value);
    return *this;
  }

  /**
     Applies this function to an input.
   */
  Y operator()(const X1 &x1, const X2 &x2) {
    *this->param1.value = x1;
    *this->param2.value = x2;
    return body->eval();
  }
};

/**
   Creates a new anonymous function of two arguments.
 */
template <typename Y, typename X1, typename X2>
Function2<Y, X1, X2> lambda(Var<X1> &x1, Var<X2> &x2) {
  // Allocate space for the argument value:
  x1.value = (X1 *)malloc(sizeof(X1));
  x2.value = (X2 *)malloc(sizeof(X2));
  Function2<Y, X1, X2> ret(x1, x2);
  return ret;
}

/* TESTING */

// All parameters to lambda terms have to be declared somewhere; x and
// y are the metavariables used in the examples:
Var<int> x;
Var<int> y;

// A Curried higher-order function:
Function2<int, int, int> h(int a, int b) {
  return lambda<int>(x, y)-- > a * x + b * y;
}

int main() {

  // Declare two DSEL function metavariables:
  Function1<int, int> f;
  Function2<int, int, int> g;

  f = lambda<int>(x)-- > 3 * x + 7;

  int a = 3, b = 6;

  g = lambda<int>(x, y)-- > a * x + b * y;

  int nums[] = {1, 2, 3};

  int *incs = (lambda<int>(x)-- > x + 1).map(3, nums);

  printf("f(3) = %i\n", f(3)); // 16

  printf("g(2,4) = %i\n", g(2, 4)); // 30

  printf("h(3,4)(1,1) = %i\n", h(3, 4)(1, 1)); // 7

  printf("(lambda<int> (x) --> x*x)(9) = %i\n", (lambda<int>(x)-- > x * x)(9)); // 81

  printf("incs = { %i, %i, %i }\n", incs[0], incs[1], incs[2]); // 2, 3, 4

  return EXIT_SUCCESS;
}
