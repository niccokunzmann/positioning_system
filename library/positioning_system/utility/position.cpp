

#include "position.hpp"
#include "sorting.hpp"

#include "math.h"

namespace position {
  
  typedef MicrophonePosition Point;

  typedef struct NelderPoint {
    double x;
    double y;
    double error;
  } NPoint;


  template <>
  void sort(NPoint *a, NPoint *b) {
    if ((*a.error > *b.error)) {
      exchange(a, b);
    }
  }

  double get_t(NPoint x, Point p) {
    double dx = x.x - p.x;
    double dy = x.y - p.y;
    // maybe one can remove the sqrt
    return sqrt(dx * dx + dy * dy);
  }

  // dt1 = PB - CP
  // dt2 = BP - AP
  double dt1; double dt2;
  // points A, B, C
  Point A;
  Point B;
  Point C;

  double get_error(Point P) {
    // get time to points
    double BP = get_t(P, B);
    double CP = get_t(P, C);
    double AP = get_t(P, A);
    // compute the time differences
    double _dt1 = BP - CP;
    double _dt2 = BP - AP;
    // compute quadratic error
    _dt1 -= dt1;
    _dt2 -= dt2;
    return _dt1 * _dt1 + _dt2 * _dt2;
  }

  NPoint with_error(Point P) {
    Npoint x;
    x.x = P.x;
    x.y = P.y;
    x.error = get_error(P);
    return x;
  }

  // https://en.wikipedia.org/wiki/Nelder%E2%80%93Mead_method
  const double alpha = 1.0; // for reflection
  const double gamma = 2.0; // for expansion
  const double peta = -0.5; // for contraction
  const double delta = 0.5; // for reduction

  double reflect(const double x, const double x0, 
                 const double multiplier) {
    return x0 + m * (x0 - x);
  }

  NPoint reflect(const NPoint x, const NPoint x0;
                 const double multiplier) {
    Point p;
    p.x = reflect(x.x, p.x, multiplier);
    p.x = reflect(x.y, p.y, multiplier);
    return with_error(p);
  }

  const double maximum_error = 1e-10;

  Point minimize() {
    // Nelder Mead in C
    // using the function get_error
    // https://en.wikipedia.org/wiki/Nelder%E2%80%93Mead_method
    int iterations; // for debugging
    NPoint x1 = with_error(A);
    NPoint x2 = with_error(B);
    NPoint x3 = with_error(C); // x[n+1]
    Point x0;
    NPoint xr;
    NPoint xe;
    NPoint xc;
    while (true) {
      ++iterations;
      // 1 
      sort(&x1, &x2, &x3);
      if (x1.error < maximum_error) {
        break;
      }
      // 2
      x0.x = (x1.x + x2.x) / 2;
      x0.y = (x1.y + x2.y) / 2;
      // 3 reflection
      xr = reflect(x3, x0, alpha);
      if ((xr.error < x3.error) && (xr.error >= x1.error)) {
        x3 = xr;
        continue
      }
      // 4 expansion
      if (x1.error > xr.error) {
        xe = reflect(x3, x0, gamma);
        if (xe.error < xv.error) {
          x3 = xe;
          continue;
        } else {
          x3 = xr;
        }
      }
      // 5 contraction
      // assert xr.error >= x2.error
      xc = reflect(x3, x0, peta);
      if (xc.error < xr.error) {
        x3 = xc;
      }
      // 6 reduction
      x0.x = x1.x;
      x0.y = x1.y;
      x2 = reflect(x2, x0, delta);
      x3 = reflect(x3, x0, delta);
      continue;
    }
    return x1;
  }

  Point position(const double _dt1, const double _dt2, 
                const double a, const double b,
                double *_x, double *_y) {
    dt1 = _dt1;
    dt2 = _dt2;

    // compute position of points
    C.x = 0;
    C.y = 0;
    A.x = a;
    A.y = 0;
    B.x = 0;
    B.y = -b;
    return compute_position();
  }
  
  Point compute_position() {
    x1.x = A.x;
    x1.y = A.y;
    x2.x = B.x;
    x2.y = B.y;
    x3.x = C.x;
    x3.y = C.y;
    // find the position
    return minimize();
  }
  
  Point position(const double dt1, const double dt2, 
                 const Point _A, const Point _B, 
                 const Point _C) {
    dt1 = _dt1;
    dt2 = _dt2;

    // compute position of points
    A = _A;
    B = _B;
    C = _C;
    return compute_position();
  }
}

void position(const double dt1, const double dt2, 
              const double a, const double b,
              double *x, double *y) {
  return position::position(dt1, dt2, a, b, x, y);
}

Point position(const double dt1, const double dt2, 
               const Point _A, const Point _B, 
               const Point _C) {
  return position(const double dt1, const double dt2, 
                  const Point _A, const Point _B, 
                  const Point _C);
}
