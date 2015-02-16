
#include "numbers.hpp"
#include "position.hpp"
#include "math.h"
#include "positioning_system_test.h"


namespace positioning {

  struct point {
    double x;
    double y;
  };
  
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
  double M;
  
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
    A = b - Ps[Ps_i].x;
    A *= A;
    A += n;
    A = sqrt(A);
    println2("w: ", A);
    // v
    B = a + Ps[Ps_i].y;
    B *= B;
    B += p;
    B = sqrt(B);
    println2("v: ", B);
    // u
    C = sqrt(p + n);
    println2("u: ", C);
    
    g1 = B - C;
    g2 = B - A;
    g3 = C - A;
    pvar(g1);
    pvar(g2);
    pvar(g3);
    
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
    pvar(g1);
    pvar(g2);
    pvar(g3);
    
    a_2 = a * a;
    g_2 = g1 * g1;
    
    n = 4 * g_2;
    q = (a_2 - g_2);
    // d = o - n
    d = 4 * q;
    p = 4 * a * q;
    q *= q;
    pvar(n);
    pvar(p);
    pvar(q);
    
    
    a_2 = b * b;
    g_2 = g3 * g3;
    
    r = 4 * g_2;
    s = 4 * a_2;
    v = (g_2 - a_2);
    // e = s - r
    e = -4 * v;
    t = 4 * b * v;
    v *= v;
    pvar(r);
    pvar(s);
    pvar(t);
    pvar(v); // could be better
    
    pvar(d);
    pvar(e);
    
    // compute y
    // if (r == 0) // unimportant we divide by n
    if (n == 0) {
      println1("{{position}} n == 0");
      println6("{{position}} solving: ", d, " ", q, " ", p);
      solve_equation(d, p, q, 
                     &(Ps[0].y), &(Ps[2].y));
      println4("{{position}} y1: ", Ps[0].y, " y2: ", Ps[2].y);
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
      
      C = L - M;
      E = H * q;
      A = E + C;
      D = (E + A) * p;
      E = A * q + v * v;
      C *= D;
      C -= 2 * r * v;
      B = H * d;
      A = (B + K) * d + r * r;
      B += B;
      C += (B + K) * q + H * p * p;
      B += K;
      B *= p;
      
      solve_equation(A, B, C, D, E, 
                     &(Ps[0]).y, &(Ps[2]).y, &(Ps[4]).y, &(Ps[6]).y);
      max_i = 8;
    }
    // compute x
    println1(F("{{position}} computing x"));
    for (int i = 0; i < max_i; i += 2) {
      if (is_not_a_number(Ps[i].y)) {
        continue;
      }
      Ps[i+1].y = Ps[i].y;
      println2("{{position}} y: ", Ps[i].y);
      println6("{{position}} solving: ", e, " ", t, " ", v - r * Ps[i].y * Ps[i].y);
      solve_equation(e, t, v - r * Ps[i].y * Ps[i].y, 
                     &(Ps[i].x), &(Ps[i+1].x));
      println4("{{position}} x1: ", Ps[i].x, " x2: ", Ps[i+1].x);
    }
    // find x, y with lowest error
    // we do not need other variables than Ps any more
    min_error = get_not_a_number(); 
    *x = get_not_a_number();
    *y = get_not_a_number();
    for (int i = 1; i < max_i; ++i) {
      if (is_not_a_number(Ps[i].x) || is_not_a_number(Ps[i].y)) {
        continue;
      }
      println6("{{position}} Ps: ", Ps[i].x, "\t", Ps[i].y, "\t", error);
      compute_error(i, dt1, dt2, a, b);
      if (is_not_a_number(min_error) || (error < min_error)) {
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