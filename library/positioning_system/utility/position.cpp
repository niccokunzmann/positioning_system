

#include "position.hpp"
#include "sorting.hpp"
#include "positioning_system_test.h"

#include "math.h"

namespace Position {
  typedef struct NelderPoint {
    double x;
    double y;
    double error;
  } NPoint;
}

template <>
void sort(Position::NPoint *a, Position::NPoint *b) {
  if ((a->error > b->error)) {
    exchange(a, b);
  }
}

namespace Position {
  
  typedef MicrophonePosition Point;

  double get_t(Point x, Point p) {
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

  double get_error(const Point P) {
    // get time to points
    double AP = get_t(P, A);
    double BP = get_t(P, B);
    double CP = get_t(P, C);
    // compute the time differences
    double _dt1 = BP - CP;
    double _dt2 = BP - AP;
//    println4("x: ", P.x, "y: ", P.y);
//    pvar(AP);
//    pvar(BP);
//    pvar(CP);
//    pvar(dt1);
//    pvar(dt2);
    // compute quadratic error
    _dt1 -= dt1;
    _dt2 -= dt2;
    return _dt1 * _dt1 + _dt2 * _dt2;
  }

  NPoint with_error(Point P) {
    NPoint x;
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
    return x0 + multiplier * (x0 - x);
  }

  NPoint reflect(const NPoint x, const Point x0,
                 const double multiplier) {
    Point p;
    p.x = reflect(x.x, x0.x, multiplier);
    p.y = reflect(x.y, x0.y, multiplier);
    return with_error(p);
  }

  const double maximum_error = 1e-15;

  Point minimize() {
    // Nelder Mead in C
    // using the function get_error
    // https://en.wikipedia.org/wiki/Nelder%E2%80%93Mead_method
    int iterations = 0; // for debugging
    NPoint x1 = with_error(A);
    NPoint x2 = with_error(B);
    NPoint x3 = with_error(C); // x[n+1]
    Point x0;
    NPoint xr;
    NPoint xe;
    NPoint xc;
    while (iterations < 300) {
      ++iterations;
      // 1 
      sort(&x1, &x2, &x3);
      //print4("x1: ", x1.x, ",", x1.y);
      //print4(" x2: ", x2.x, ",", x2.y);
      //println4(" x3: ", x3.x, ",", x3.y);
      //println6("error: ", x1.error, ",", x2.error, ", ", x3.error);
      if (x1.error < maximum_error) {
        break;
      }
      // 2
      x0.x = (x1.x + x2.x) / 2;
      x0.y = (x1.y + x2.y) / 2;
      //println4("x0: ", x0.x, ",", x0.y);
      // 3 reflection
      xr = reflect(x3, x0, alpha);
      //pvar(xr.x); pvar(xr.y); pvar(xr.error);
      if ((xr.error < x2.error) && (xr.error >= x1.error)) {
        x3 = xr;
        continue;
      }
      // 4 expansion
      if (x1.error > xr.error) {
        xe = reflect(x3, x0, gamma);
        //pvar(xe.x); pvar(xe.y); pvar(xe.error);
        if (xe.error < xr.error) {
          x3 = xe;
          continue;
        } else {
          x3 = xr;
          continue;
        }
      }
      // 5 contraction
      // assert xr.error >= x2.error
      xc = reflect(x3, x0, peta);
      //pvar(xc.x); pvar(xc.y); pvar(xc.error);
      if (xc.error < xr.error) {
        x3 = xc;
        continue;
      }
      // 6 reduction
      x0.x = x1.x;
      x0.y = x1.y;
      x2 = reflect(x2, x0, delta);
      x3 = reflect(x3, x0, delta);
      continue;
    }
    println2("iterations:", iterations);
    x0.x = x1.x;
    x0.y = x1.y;
    return x0;
  }

  void position(const double _dt1, const double _dt2, 
                const double a, const double b,
                double *_x, double *_y) {
    dt1 = _dt1;
    dt2 = _dt2;

    // compute position of points
    A.x = a;
    A.y = 0;
    B.x = 0;
    B.y = -b;
    C.x = 0;
    C.y = 0;
    Point p =  minimize();
    *_x = p.x;
    *_y = p.y;
  }
  
  Point position(const double _dt1, const double _dt2, 
                 const Point _A, const Point _B, 
                 const Point _C) {
    dt1 = _dt1;
    dt2 = _dt2;

    // compute position of points
    A = _A;
    B = _B;
    C = _C;
    return minimize();
  }
}

void position(const double dt1, const double dt2, 
              const double a, const double b,
              double *x, double *y) {
  Position::position(dt1, dt2, a, b, x, y);
}

MicrophonePosition position(
               const double dt1, const double dt2, 
               const SpeakerPosition A, 
               const SpeakerPosition B, 
               const SpeakerPosition C) {
  return Position::position(dt1, dt2, A, B, C);
}
