

#include "xoperations.hpp"

// C++ operator guidelines http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html

struct xpr operator+ (struct xpr a, struct xpr b) {
  return xadd(a, b, 0);
}

struct xpr operator* (struct xpr a, struct xpr b) {
  return xmul(a, b);
}

struct xpr operator- (struct xpr a, struct xpr b) {
  return xadd(a, b, 1);
}

struct xpr operator- (struct xpr a) {
  return xneg(a);
}

bool operator== (const struct xpr a, const struct xpr b) {
  struct xpr zero = a - b;
  return xis0(&zero);
}

bool operator!= (const struct xpr a, const struct xpr b) {
  return !(a == b);
}
