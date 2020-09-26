// include guard using #ifndef - #define (all versions of C++)
#ifndef DICHO__DICHO_HPP
#define DICHO__DICHO_HPP

// full argument version
void dicho(double &a, double &b, double eps, int * niter);

// function override: simplified version
double dicho(double a, double b);

#endif // DICHO__DICHO_HPP
