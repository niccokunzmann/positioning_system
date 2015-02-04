
#ifndef xoperation_h
#define xoperation_h
#include <xpre.h>

// C++ operator guidelines http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html

struct xpr operator+ (struct xpr a, struct xpr b);

struct xpr operator* (struct xpr a, struct xpr b);

struct xpr operator- (struct xpr a, struct xpr b);

struct xpr operator- (struct xpr a);

bool operator== (const struct xpr a, const struct xpr b);

bool operator!= (const struct xpr a, const struct xpr b);

#endif