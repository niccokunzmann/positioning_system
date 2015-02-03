/*
   Copyright (C)  2000    Daniel A. Atkinson  <DanAtk@aol.com>
   Copyright (C)  2004    Ivano Primi  <ivprimi@libero.it>    

   This file is part of the HPA Library.

   The HPA Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The HPA Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the HPA Library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
   02110-1301 USA.
*/

#ifndef _XPRE_H_
#define _XPRE_H_

#include"hpaconf.h"

/* This macro has been added by Ivano Primi - 12/21/2004 */
#define XMAX_10EX  4931

/* This macro has been added by Ivano Primi - 05/10/2004 */
/* It is used in the file xchcof.c                       */
#define XMAX_DEGREE 50

/* Dealing with errors. Added by Ivano Primi - 01/04/2005 */
#ifndef XERR_IGN

#define XENONE   0
#define XEDIV    1
#define XEDOM    2
#define XEBADEXP 3
#define XFPOFLOW 4		/* Floating point overflow */

#define XNERR    4
#define XEINV    5		/* == XNERR + 1 */

#endif /* !XERR_IGN */

#ifdef __cplusplus
extern "C"
{
#endif

  struct xpr
  {
    unsigned short nmm[XDIM + 1];
  };

  extern const unsigned short xM_sgn, xM_exp;
  extern const short xBias;
  extern const int xItt_div, xK_tanh;
  extern const int xMS_exp, xMS_trg, xMS_hyp;
  extern const short xMax_p, xK_lin;
  extern const short xD_bias, xD_max, xD_lex;
  extern const short xF_bias, xF_max, xF_lex;
  extern const struct xpr xZero, xOne, xTwo, xTen;
  extern const struct xpr xPinf, xMinf, xNaN;
  extern const struct xpr xPi, xPi2, xPi4, xEe, xSqrt2;
  extern const struct xpr xLn2, xLn10, xLog2_e, xLog2_10, xLog10_e;
  extern const struct xpr xRndcorr, xFixcorr;
  extern const struct xpr xVSV, xVGV, xEmax, xEmin, xE2min, xE2max;

  struct xpr xadd (struct xpr a, struct xpr b, int k);
  struct xpr xmul (struct xpr s, struct xpr t);
  struct xpr xdiv (struct xpr s, struct xpr t);
/* strtox() has been added by Ivano Primi - 12/21/2004 */
  struct xpr strtox (const char *q, char **endptr);
  struct xpr atox (const char *s);
  struct xpr dbltox (double y);
/* flttox() has been added by Ivano Primi - 11/22/2004 */
  struct xpr flttox (float y);
  struct xpr inttox (long n);
  struct xpr uinttox (unsigned long n);
  int xprcmp (const struct xpr *p, const struct xpr *q);
  int xeq (struct xpr x1, struct xpr x2); 
  int xneq (struct xpr x1, struct xpr x2);
  int xgt (struct xpr x1, struct xpr x2);  
  int xge (struct xpr x1, struct xpr x2); 
  int xlt (struct xpr x1, struct xpr x2);
  int xle (struct xpr x1, struct xpr x2);  
  int xisNaN (const struct xpr *u);
  int xisPinf (const struct xpr *u);
  int xisMinf (const struct xpr *u);
  int xisordnumb (const struct xpr *u);
  int xis0 (const struct xpr *u);
  int xnot0 (const struct xpr *u);
  int xsgn (const struct xpr *u);
  int x_neg (const struct xpr *p);
  int x_exp (const struct xpr *p);
  struct xpr xsfmod (struct xpr t, int *p);
  struct xpr xpwr (struct xpr s, int n);
  struct xpr xpr2 (struct xpr s, int n);
  struct xpr xneg (struct xpr s);
  struct xpr xabs (struct xpr s);
  struct xpr xfrexp (struct xpr s, int *p);
/* xfmod() has been modified by Ivano Primi - 01/30/2005 */
  struct xpr xfmod (struct xpr s, struct xpr t, struct xpr *q);
/* xfrac() and xtrunc() have been added by Ivano Primi - 12/11/2004 */
  struct xpr xfrac (struct xpr x);
  struct xpr xtrunc (struct xpr x);
/* xround(), xceil() and xfloor() have been added by Ivano Primi - 01/05/2004 */
  struct xpr xround (struct xpr x);
  struct xpr xceil (struct xpr x);
  struct xpr xfloor (struct xpr x);
/* xfix() has been added by Ivano Primi - 05/01/2004 */
  struct xpr xfix (struct xpr x);

  double xtodbl (struct xpr s);
/* xtoflt() has been added by Ivano Primi - 11/22/2004 */
  float xtoflt (struct xpr s);
  struct xpr xtan (struct xpr x);
  struct xpr xsin (struct xpr x);
  struct xpr xcos (struct xpr x);
  struct xpr xatan (struct xpr a);
  struct xpr xasin (struct xpr a);
  struct xpr xacos (struct xpr a);
  struct xpr xatan2 (struct xpr y, struct xpr x);
  struct xpr xsqrt (struct xpr u);
  struct xpr xexp (struct xpr u);
  struct xpr xexp2 (struct xpr u);
  struct xpr xexp10 (struct xpr u);
  struct xpr xlog (struct xpr u);
  struct xpr xlog2 (struct xpr u);
  struct xpr xlog10 (struct xpr u);
  struct xpr xtanh (struct xpr v);
  struct xpr xsinh (struct xpr v);
  struct xpr xcosh (struct xpr v);
  struct xpr xatanh (struct xpr v);
  struct xpr xasinh (struct xpr v);
  struct xpr xacosh (struct xpr v);
  struct xpr xpow (struct xpr x, struct xpr y);

  struct xpr* xchcof (int m, struct xpr (*xfunc) (struct xpr));
  struct xpr xevtch (struct xpr z, struct xpr *a, int m);
/* The following 4 functions have been added */
/* by Ivano Primi 11/29/2004                 */

#include<stdio.h>

  void xpr_print (FILE * stream, struct xpr u, int sc_not, int sign, int lim);
  char *xpr_asprint (struct xpr u, int sc_not, int sign, int lim);
  char *xtoa (struct xpr u, int lim);
  void xbprint (FILE * stream, struct xpr u);
  void xprxpr (struct xpr u, int m);
  void xprint (FILE * stream, struct xpr u);
  void xlshift (int i, unsigned short *p, int k);
  void xrshift (int i, unsigned short *p, int k);

/* The next special output functions have been added by Ivano Primi, */
/* 01/06/2005.                                                       */

#define XOUT_FIXED      0
#define XOUT_SCIENTIFIC 1

#define XDEF_LIM        6

  struct xoutflags
  {
    short fmt, notat, sf, mfwd, lim;
    signed char padding, ldel, rdel;
  };

/* Special output functions */
/* Remark: xfout(), xout() and xsout() actually ignore the fields ofs.fmt,  */
/* ofs.ldel and ofs.rdel .                                                  */
/* These fields are only used by cxfout(),cxout() and cxsout()(see cxpre.h).*/
  int xfout (FILE * pf, struct xoutflags ofs, struct xpr x);
  int xout (struct xoutflags ofs, struct xpr x);
  unsigned long
    xsout (char *s, unsigned long n, struct xoutflags ofs, struct xpr x);

#ifndef XERR_IGN
  int xsigerr (int errcond, int errcode, const char *where);
#else
#define xsigerr(errcond, errcode, where) 0
#endif

#define xsum(a, b) xadd (a, b, 0)
#define xsub(a, b) xadd (a, b, 1)

#ifdef __cplusplus
}
#endif
#endif				/* _XPRE_H_ */
