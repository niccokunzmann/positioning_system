
#include "numbers.hpp"
#include "position.hpp"
#include "math.h"


namespace positioning {

  struct point {
    double x;
    double y;
  }
  
  double g1;
  double g2;
  double g3;
  
  double n;
  //double o;
  double p;
  double q;

  double r;
  double s;
  double t;
  double v;
  
  double d;
  double e;
  
  double a_2;
  double g_2;
  
  double H;
  double K;
  double L;
  double m;
  
  double A;
  double B;
  double C;
  double D;
  double E;
  
  double e_n;
  
  struct point Ps[8]; // (x, y)
  
  int max_i;
  double min_error; // could remove these two variables
  double error;
  
  void compute_error(
          const int Ps_i, 
          const double dt1, const double dt2,
          const double a, const double b) {
    // y_2
    n = Ps[Ps_i].y;
    n *= n;
    // x_2
    p = Ps[Ps_i].x;
    p *= p;
    // sture the delta t in g1, g2, g3
    // w
    A = b - Ps[Ps_i].y;
    A *= A;
    A += n;
    A = sqrt(A);
    // v
    B = b - Ps[Ps_i].x;
    B *= B;
    B += p;
    B = sqrt(B);
    // u
    C = sqrt(p + n);
    
    g1 = B - C;
    g2 = B - A;
    g3 = C - A;
    
    g1 -= dt1;
    g2 -= dt2;
    // dt3 = dt2 - dt1
    g3 += dt1 - dt2;
    
    g1 *= g1;
    g2 *= g2;
    g3 *= g3;

    error = g1 + g2 + g3;
  }
  
  void compute_position(
          const double dt1, const double dt2, 
          const double a, const double b,
          double *x, double* y) {
    // dt1 = PB - CP
    // dt2 = BP - AP
    
    g1 = dt1;
    g2 = dt2;
    g3 = g2 - g1;
    
    a_2 = a * a;
    g_2 = g1 * g1;
    
    n = 4 * g_2;
    q = (a_2 - g_2);
    // d = o - n
    d = 4 * q;
    p = 4 * a * q;
    q *= q;
    
    
    a_2 = b * b;
    g_2 = g3 * g3;
    
    r = 4 * g_2;
    s = 4 * a_2;
    v = (g_2 - a_2);
    // e = s - r
    e = -4 * v;
    t = 4 * b * v;
    v *= v;
    
    // compute y
    // if (r == 0) // unimportant we divide by n
    if (n == 0) {
      solve_equation(d, p, q, 
                     &(Ps[0].y), &(Ps[2].y));
      max_i = 4;
    } else {
      /*
        F = -2 * e * r
        G =  2 * e * v
        H = e*e / n/n
        K = F / n
        L = G / n
        M = t*t / n

        A = H * d*d + K * d + r*r
        B = 2 * H * d * p + K * p
        C = 2 * H * d * q + H * p*p + K * q + 
            L * d - 2 * r * v - M * d
        D = 2 * H * p * q + L * p - M * p
        E = H * q*q + L * q + v*v - M * q
      */
      e_n = e / n;
      H = e_n * e_n;
      K = -2 * r * e_n;
      L = 2 * v * e_n;
      M = t * t / n;
      
      A = (H * d + K) * d + r * r;
      B = 2 * H * d;
      C = L - M;
      E = H * q;
      D = (E + E + C) * p;
      E = (E + C) * q + v * v;
      C * = D;
      C -= 2 * r * v;
      C += (B + K) * q + H * p * p;
      B += K;
      B *= p;
      
      solve_equation(A, B, C, D, E, 
                     &(Ps[0]).y, &(Ps[2]).y, &(Ps[4]).y, &(Ps[6]).y);
      max_i = 8;
    }
    // compute x
    for (int i = 0; i < max_i; i += 2) {
      Ps[i+1].y = Ps[i].y;
      solve_equation(e, t, v - r * Ps[i].y * Ps[i].y, 
                     &(Ps[i].x), &(Ps[i+1].x));
    }
    // find x, y with lowest error
    // we do not need other variables than Ps any more
    *x = Ps[0].x;
    *y = Ps[0].y;
    compute_error(0, dt1, dt2, a, b);
    min_error = error; 
    for (int i = 1; i < max_i, ++i) {
      compute_error(i, dt1, dt2, a, b);
      if (error < min_error) {
        min_error = error;
        *x = Ps[i].x;
        *y = Ps[i].y;
      }
    }
  }
}

void position(const double dt1, const double dt2, 
              const double a, const double b,
              double *x, double* y) {
  positioning::compute_position(dt1, dt2, a, b, x, y);
}