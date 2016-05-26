/* header file for clapack 3.2.1 */

#ifndef __CLAPACK_H
#define __CLAPACK_H

extern "C" {

/* Subroutine */ int caxpy_(integer *n, floatcomplex *ca, floatcomplex *cx, integer *
	incx, floatcomplex *cy, integer *incy);

/* Subroutine */ int ccopy_(integer *n, floatcomplex *cx, integer *incx, floatcomplex *
	cy, integer *incy);

/* Complex */ VOID cdotc_(floatcomplex * ret_val, integer *n, floatcomplex *cx, integer 
	*incx, floatcomplex *cy, integer *incy);

/* Complex */ VOID cdotu_(floatcomplex * ret_val, integer *n, floatcomplex *cx, integer 
	*incx, floatcomplex *cy, integer *incy);

/* Subroutine */ int cgbmv_(char *trans, integer *m, integer *n, integer *kl, 
	integer *ku, floatcomplex *alpha, floatcomplex *a, integer *lda, floatcomplex *x, 
	integer *incx, floatcomplex *beta, floatcomplex *y, integer *incy);

/* Subroutine */ int cgemm_(char *transa, char *transb, integer *m, integer *
	n, integer *k, floatcomplex *alpha, floatcomplex *a, integer *lda, floatcomplex *b, 
	integer *ldb, floatcomplex *beta, floatcomplex *c__, integer *ldc);

/* Subroutine */ int cgemv_(char *trans, integer *m, integer *n, floatcomplex *
	alpha, floatcomplex *a, integer *lda, floatcomplex *x, integer *incx, floatcomplex *
	beta, floatcomplex *y, integer *incy);

/* Subroutine */ int cgerc_(integer *m, integer *n, floatcomplex *alpha, floatcomplex *
	x, integer *incx, floatcomplex *y, integer *incy, floatcomplex *a, integer *lda);

/* Subroutine */ int cgeru_(integer *m, integer *n, floatcomplex *alpha, floatcomplex *
	x, integer *incx, floatcomplex *y, integer *incy, floatcomplex *a, integer *lda);

/* Subroutine */ int chbmv_(char *uplo, integer *n, integer *k, floatcomplex *
	alpha, floatcomplex *a, integer *lda, floatcomplex *x, integer *incx, floatcomplex *
	beta, floatcomplex *y, integer *incy);

/* Subroutine */ int chemm_(char *side, char *uplo, integer *m, integer *n, 
	floatcomplex *alpha, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	floatcomplex *beta, floatcomplex *c__, integer *ldc);

/* Subroutine */ int chemv_(char *uplo, integer *n, floatcomplex *alpha, floatcomplex *
	a, integer *lda, floatcomplex *x, integer *incx, floatcomplex *beta, floatcomplex *y, 
	 integer *incy);

/* Subroutine */ int cher_(char *uplo, integer *n, floatreal *alpha, floatcomplex *x, 
	integer *incx, floatcomplex *a, integer *lda);

/* Subroutine */ int cher2_(char *uplo, integer *n, floatcomplex *alpha, floatcomplex *
	x, integer *incx, floatcomplex *y, integer *incy, floatcomplex *a, integer *lda);

/* Subroutine */ int cher2k_(char *uplo, char *trans, integer *n, integer *k, 
	floatcomplex *alpha, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	floatreal *beta, floatcomplex *c__, integer *ldc);

/* Subroutine */ int cherk_(char *uplo, char *trans, integer *n, integer *k, 
	floatreal *alpha, floatcomplex *a, integer *lda, floatreal *beta, floatcomplex *c__, 
	integer *ldc);

/* Subroutine */ int chpmv_(char *uplo, integer *n, floatcomplex *alpha, floatcomplex *
	ap, floatcomplex *x, integer *incx, floatcomplex *beta, floatcomplex *y, integer *
	incy);

/* Subroutine */ int chpr_(char *uplo, integer *n, floatreal *alpha, floatcomplex *x, 
	integer *incx, floatcomplex *ap);

/* Subroutine */ int chpr2_(char *uplo, integer *n, floatcomplex *alpha, floatcomplex *
	x, integer *incx, floatcomplex *y, integer *incy, floatcomplex *ap);

/* Subroutine */ int crotg_(floatcomplex *ca, floatcomplex *cb, floatreal *c__, floatcomplex *s);

/* Subroutine */ int cscal_(integer *n, floatcomplex *ca, floatcomplex *cx, integer *
	incx);

/* Subroutine */ int csrot_(integer *n, floatcomplex *cx, integer *incx, floatcomplex *
	cy, integer *incy, floatreal *c__, floatreal *s);

/* Subroutine */ int csscal_(integer *n, floatreal *sa, floatcomplex *cx, integer *incx);

/* Subroutine */ int cswap_(integer *n, floatcomplex *cx, integer *incx, floatcomplex *
	cy, integer *incy);

/* Subroutine */ int csymm_(char *side, char *uplo, integer *m, integer *n, 
	floatcomplex *alpha, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	floatcomplex *beta, floatcomplex *c__, integer *ldc);

/* Subroutine */ int csyr2k_(char *uplo, char *trans, integer *n, integer *k, 
	floatcomplex *alpha, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	floatcomplex *beta, floatcomplex *c__, integer *ldc);

/* Subroutine */ int csyrk_(char *uplo, char *trans, integer *n, integer *k, 
	floatcomplex *alpha, floatcomplex *a, integer *lda, floatcomplex *beta, floatcomplex *c__, 
	 integer *ldc);

/* Subroutine */ int ctbmv_(char *uplo, char *trans, char *diag, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *x, integer *incx);

/* Subroutine */ int ctbsv_(char *uplo, char *trans, char *diag, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *x, integer *incx);

/* Subroutine */ int ctpmv_(char *uplo, char *trans, char *diag, integer *n, 
	floatcomplex *ap, floatcomplex *x, integer *incx);

/* Subroutine */ int ctpsv_(char *uplo, char *trans, char *diag, integer *n, 
	floatcomplex *ap, floatcomplex *x, integer *incx);

/* Subroutine */ int ctrmm_(char *side, char *uplo, char *transa, char *diag, 
	integer *m, integer *n, floatcomplex *alpha, floatcomplex *a, integer *lda, 
	floatcomplex *b, integer *ldb);

/* Subroutine */ int ctrmv_(char *uplo, char *trans, char *diag, integer *n, 
	floatcomplex *a, integer *lda, floatcomplex *x, integer *incx);

/* Subroutine */ int ctrsm_(char *side, char *uplo, char *transa, char *diag, 
	integer *m, integer *n, floatcomplex *alpha, floatcomplex *a, integer *lda, 
	floatcomplex *b, integer *ldb);

/* Subroutine */ int ctrsv_(char *uplo, char *trans, char *diag, integer *n, 
	floatcomplex *a, integer *lda, floatcomplex *x, integer *incx);

doublereal dasum_(integer *n, doublereal *dx, integer *incx);

/* Subroutine */ int daxpy_(integer *n, doublereal *da, doublereal *dx, 
	integer *incx, doublereal *dy, integer *incy);

doublereal dcabs1_(doublecomplex *z__);

/* Subroutine */ int dcopy_(integer *n, doublereal *dx, integer *incx, 
	doublereal *dy, integer *incy);

doublereal ddot_(integer *n, doublereal *dx, integer *incx, doublereal *dy, 
	integer *incy);

/* Subroutine */ int dgbmv_(char *trans, integer *m, integer *n, integer *kl, 
	integer *ku, doublereal *alpha, doublereal *a, integer *lda, 
	doublereal *x, integer *incx, doublereal *beta, doublereal *y, 
	integer *incy);

/* Subroutine */ int dgemm_(char *transa, char *transb, integer *m, integer *
	n, integer *k, doublereal *alpha, doublereal *a, integer *lda, 
	doublereal *b, integer *ldb, doublereal *beta, doublereal *c__, 
	integer *ldc);

/* Subroutine */ int dgemv_(char *trans, integer *m, integer *n, doublereal *
	alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, 
	doublereal *beta, doublereal *y, integer *incy);

/* Subroutine */ int dger_(integer *m, integer *n, doublereal *alpha, 
	doublereal *x, integer *incx, doublereal *y, integer *incy, 
	doublereal *a, integer *lda);

doublereal dnrm2_(integer *n, doublereal *x, integer *incx);

/* Subroutine */ int drot_(integer *n, doublereal *dx, integer *incx, 
	doublereal *dy, integer *incy, doublereal *c__, doublereal *s);

/* Subroutine */ int drotg_(doublereal *da, doublereal *db, doublereal *c__, 
	doublereal *s);

/* Subroutine */ int drotm_(integer *n, doublereal *dx, integer *incx, 
	doublereal *dy, integer *incy, doublereal *dparam);

/* Subroutine */ int drotmg_(doublereal *dd1, doublereal *dd2, doublereal *
	dx1, doublereal *dy1, doublereal *dparam);

/* Subroutine */ int dsbmv_(char *uplo, integer *n, integer *k, doublereal *
	alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, 
	doublereal *beta, doublereal *y, integer *incy);

/* Subroutine */ int dscal_(integer *n, doublereal *da, doublereal *dx, 
	integer *incx);

doublereal dsdot_(integer *n, floatreal *sx, integer *incx, floatreal *sy, integer *
	incy);

/* Subroutine */ int dspmv_(char *uplo, integer *n, doublereal *alpha, 
	doublereal *ap, doublereal *x, integer *incx, doublereal *beta, 
	doublereal *y, integer *incy);

/* Subroutine */ int dspr_(char *uplo, integer *n, doublereal *alpha, 
	doublereal *x, integer *incx, doublereal *ap);

/* Subroutine */ int dspr2_(char *uplo, integer *n, doublereal *alpha, 
	doublereal *x, integer *incx, doublereal *y, integer *incy, 
	doublereal *ap);

/* Subroutine */ int dswap_(integer *n, doublereal *dx, integer *incx, 
	doublereal *dy, integer *incy);

/* Subroutine */ int dsymm_(char *side, char *uplo, integer *m, integer *n, 
	doublereal *alpha, doublereal *a, integer *lda, doublereal *b, 
	integer *ldb, doublereal *beta, doublereal *c__, integer *ldc);

/* Subroutine */ int dsymv_(char *uplo, integer *n, doublereal *alpha, 
	doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal 
	*beta, doublereal *y, integer *incy);

/* Subroutine */ int dsyr_(char *uplo, integer *n, doublereal *alpha, 
	doublereal *x, integer *incx, doublereal *a, integer *lda);

/* Subroutine */ int dsyr2_(char *uplo, integer *n, doublereal *alpha, 
	doublereal *x, integer *incx, doublereal *y, integer *incy, 
	doublereal *a, integer *lda);

/* Subroutine */ int dsyr2k_(char *uplo, char *trans, integer *n, integer *k, 
	doublereal *alpha, doublereal *a, integer *lda, doublereal *b, 
	integer *ldb, doublereal *beta, doublereal *c__, integer *ldc);

/* Subroutine */ int dsyrk_(char *uplo, char *trans, integer *n, integer *k, 
	doublereal *alpha, doublereal *a, integer *lda, doublereal *beta, 
	doublereal *c__, integer *ldc);

/* Subroutine */ int dtbmv_(char *uplo, char *trans, char *diag, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *x, integer *incx);

/* Subroutine */ int dtbsv_(char *uplo, char *trans, char *diag, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *x, integer *incx);

/* Subroutine */ int dtpmv_(char *uplo, char *trans, char *diag, integer *n, 
	doublereal *ap, doublereal *x, integer *incx);

/* Subroutine */ int dtpsv_(char *uplo, char *trans, char *diag, integer *n, 
	doublereal *ap, doublereal *x, integer *incx);

/* Subroutine */ int dtrmm_(char *side, char *uplo, char *transa, char *diag, 
	integer *m, integer *n, doublereal *alpha, doublereal *a, integer *
	lda, doublereal *b, integer *ldb);

/* Subroutine */ int dtrmv_(char *uplo, char *trans, char *diag, integer *n, 
	doublereal *a, integer *lda, doublereal *x, integer *incx);

/* Subroutine */ int dtrsm_(char *side, char *uplo, char *transa, char *diag, 
	integer *m, integer *n, doublereal *alpha, doublereal *a, integer *
	lda, doublereal *b, integer *ldb);

/* Subroutine */ int dtrsv_(char *uplo, char *trans, char *diag, integer *n, 
	doublereal *a, integer *lda, doublereal *x, integer *incx);

doublereal dzasum_(integer *n, doublecomplex *zx, integer *incx);

doublereal dznrm2_(integer *n, doublecomplex *x, integer *incx);

integer icamax_(integer *n, floatcomplex *cx, integer *incx);

integer idamax_(integer *n, doublereal *dx, integer *incx);

integer isamax_(integer *n, floatreal *sx, integer *incx);

integer izamax_(integer *n, doublecomplex *zx, integer *incx);

logical lsame_(char *ca, char *cb);

doublereal sasum_(integer *n, floatreal *sx, integer *incx);

/* Subroutine */ int saxpy_(integer *n, floatreal *sa, floatreal *sx, integer *incx, 
	floatreal *sy, integer *incy);

doublereal scabs1_(floatcomplex *z__);

doublereal scasum_(integer *n, floatcomplex *cx, integer *incx);

doublereal scnrm2_(integer *n, floatcomplex *x, integer *incx);

/* Subroutine */ int scopy_(integer *n, floatreal *sx, integer *incx, floatreal *sy, 
	integer *incy);

doublereal sdot_(integer *n, floatreal *sx, integer *incx, floatreal *sy, integer *incy);

doublereal sdsdot_(integer *n, floatreal *sb, floatreal *sx, integer *incx, floatreal *sy, 
	integer *incy);

/* Subroutine */ int sgbmv_(char *trans, integer *m, integer *n, integer *kl, 
	integer *ku, floatreal *alpha, floatreal *a, integer *lda, floatreal *x, integer *
	incx, floatreal *beta, floatreal *y, integer *incy);

/* Subroutine */ int sgemm_(char *transa, char *transb, integer *m, integer *
	n, integer *k, floatreal *alpha, floatreal *a, integer *lda, floatreal *b, integer *
	ldb, floatreal *beta, floatreal *c__, integer *ldc);

/* Subroutine */ int sgemv_(char *trans, integer *m, integer *n, floatreal *alpha, 
	floatreal *a, integer *lda, floatreal *x, integer *incx, floatreal *beta, floatreal *y, 
	integer *incy);

/* Subroutine */ int sger_(integer *m, integer *n, floatreal *alpha, floatreal *x, 
	integer *incx, floatreal *y, integer *incy, floatreal *a, integer *lda);

doublereal snrm2_(integer *n, floatreal *x, integer *incx);

/* Subroutine */ int srot_(integer *n, floatreal *sx, integer *incx, floatreal *sy, 
	integer *incy, floatreal *c__, floatreal *s);

/* Subroutine */ int srotg_(floatreal *sa, floatreal *sb, floatreal *c__, floatreal *s);

/* Subroutine */ int srotm_(integer *n, floatreal *sx, integer *incx, floatreal *sy, 
	integer *incy, floatreal *sparam);

/* Subroutine */ int srotmg_(floatreal *sd1, floatreal *sd2, floatreal *sx1, floatreal *sy1, floatreal 
	*sparam);

/* Subroutine */ int ssbmv_(char *uplo, integer *n, integer *k, floatreal *alpha, 
	floatreal *a, integer *lda, floatreal *x, integer *incx, floatreal *beta, floatreal *y, 
	integer *incy);

/* Subroutine */ int sscal_(integer *n, floatreal *sa, floatreal *sx, integer *incx);

/* Subroutine */ int sspmv_(char *uplo, integer *n, floatreal *alpha, floatreal *ap, 
	floatreal *x, integer *incx, floatreal *beta, floatreal *y, integer *incy);

/* Subroutine */ int sspr_(char *uplo, integer *n, floatreal *alpha, floatreal *x, 
	integer *incx, floatreal *ap);

/* Subroutine */ int sspr2_(char *uplo, integer *n, floatreal *alpha, floatreal *x, 
	integer *incx, floatreal *y, integer *incy, floatreal *ap);

/* Subroutine */ int sswap_(integer *n, floatreal *sx, integer *incx, floatreal *sy, 
	integer *incy);

/* Subroutine */ int ssymm_(char *side, char *uplo, integer *m, integer *n, 
	floatreal *alpha, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *beta, 
	 floatreal *c__, integer *ldc);

/* Subroutine */ int ssymv_(char *uplo, integer *n, floatreal *alpha, floatreal *a, 
	integer *lda, floatreal *x, integer *incx, floatreal *beta, floatreal *y, integer *
	incy);

/* Subroutine */ int ssyr_(char *uplo, integer *n, floatreal *alpha, floatreal *x, 
	integer *incx, floatreal *a, integer *lda);

/* Subroutine */ int ssyr2_(char *uplo, integer *n, floatreal *alpha, floatreal *x, 
	integer *incx, floatreal *y, integer *incy, floatreal *a, integer *lda);

/* Subroutine */ int ssyr2k_(char *uplo, char *trans, integer *n, integer *k, 
	floatreal *alpha, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *beta, 
	 floatreal *c__, integer *ldc);

/* Subroutine */ int ssyrk_(char *uplo, char *trans, integer *n, integer *k, 
	floatreal *alpha, floatreal *a, integer *lda, floatreal *beta, floatreal *c__, integer *
	ldc);

/* Subroutine */ int stbmv_(char *uplo, char *trans, char *diag, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *x, integer *incx);

/* Subroutine */ int stbsv_(char *uplo, char *trans, char *diag, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *x, integer *incx);

/* Subroutine */ int stpmv_(char *uplo, char *trans, char *diag, integer *n, 
	floatreal *ap, floatreal *x, integer *incx);

/* Subroutine */ int stpsv_(char *uplo, char *trans, char *diag, integer *n, 
	floatreal *ap, floatreal *x, integer *incx);

/* Subroutine */ int strmm_(char *side, char *uplo, char *transa, char *diag, 
	integer *m, integer *n, floatreal *alpha, floatreal *a, integer *lda, floatreal *b, 
	integer *ldb);

/* Subroutine */ int strmv_(char *uplo, char *trans, char *diag, integer *n, 
	floatreal *a, integer *lda, floatreal *x, integer *incx);

/* Subroutine */ int strsm_(char *side, char *uplo, char *transa, char *diag, 
	integer *m, integer *n, floatreal *alpha, floatreal *a, integer *lda, floatreal *b, 
	integer *ldb);

/* Subroutine */ int strsv_(char *uplo, char *trans, char *diag, integer *n, 
	floatreal *a, integer *lda, floatreal *x, integer *incx);

/* Subroutine */ int xerbla_(char *srname, integer *info);

/* Subroutine */ int xerbla_array__(char *srname_array__, integer *
	srname_len__, integer *info, ftnlen srname_array_len);

/* Subroutine */ int zaxpy_(integer *n, doublecomplex *za, doublecomplex *zx, 
	integer *incx, doublecomplex *zy, integer *incy);

/* Subroutine */ int zcopy_(integer *n, doublecomplex *zx, integer *incx, 
	doublecomplex *zy, integer *incy);

/* Double Complex */ VOID zdotc_(doublecomplex * ret_val, integer *n, 
	doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);

/* Double Complex */ VOID zdotu_(doublecomplex * ret_val, integer *n, 
	doublecomplex *zx, integer *incx, doublecomplex *zy, integer *incy);

/* Subroutine */ int zdrot_(integer *n, doublecomplex *cx, integer *incx, 
	doublecomplex *cy, integer *incy, doublereal *c__, doublereal *s);

/* Subroutine */ int zdscal_(integer *n, doublereal *da, doublecomplex *zx, 
	integer *incx);

/* Subroutine */ int zgbmv_(char *trans, integer *m, integer *n, integer *kl, 
	integer *ku, doublecomplex *alpha, doublecomplex *a, integer *lda, 
	doublecomplex *x, integer *incx, doublecomplex *beta, doublecomplex *
	y, integer *incy);

/* Subroutine */ int zgemm_(char *transa, char *transb, integer *m, integer *
	n, integer *k, doublecomplex *alpha, doublecomplex *a, integer *lda, 
	doublecomplex *b, integer *ldb, doublecomplex *beta, doublecomplex *
	c__, integer *ldc);

/* Subroutine */ int zgemv_(char *trans, integer *m, integer *n, 
	doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *
	x, integer *incx, doublecomplex *beta, doublecomplex *y, integer *
	incy);

/* Subroutine */ int zgerc_(integer *m, integer *n, doublecomplex *alpha, 
	doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, 
	doublecomplex *a, integer *lda);

/* Subroutine */ int zgeru_(integer *m, integer *n, doublecomplex *alpha, 
	doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, 
	doublecomplex *a, integer *lda);

/* Subroutine */ int zhbmv_(char *uplo, integer *n, integer *k, doublecomplex 
	*alpha, doublecomplex *a, integer *lda, doublecomplex *x, integer *
	incx, doublecomplex *beta, doublecomplex *y, integer *incy);

/* Subroutine */ int zhemm_(char *side, char *uplo, integer *m, integer *n, 
	doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *
	b, integer *ldb, doublecomplex *beta, doublecomplex *c__, integer *
	ldc);

/* Subroutine */ int zhemv_(char *uplo, integer *n, doublecomplex *alpha, 
	doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, 
	doublecomplex *beta, doublecomplex *y, integer *incy);

/* Subroutine */ int zher_(char *uplo, integer *n, doublereal *alpha, 
	doublecomplex *x, integer *incx, doublecomplex *a, integer *lda);

/* Subroutine */ int zher2_(char *uplo, integer *n, doublecomplex *alpha, 
	doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, 
	doublecomplex *a, integer *lda);

/* Subroutine */ int zher2k_(char *uplo, char *trans, integer *n, integer *k, 
	doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *
	b, integer *ldb, doublereal *beta, doublecomplex *c__, integer *ldc);

/* Subroutine */ int zherk_(char *uplo, char *trans, integer *n, integer *k, 
	doublereal *alpha, doublecomplex *a, integer *lda, doublereal *beta, 
	doublecomplex *c__, integer *ldc);

/* Subroutine */ int zhpmv_(char *uplo, integer *n, doublecomplex *alpha, 
	doublecomplex *ap, doublecomplex *x, integer *incx, doublecomplex *
	beta, doublecomplex *y, integer *incy);

/* Subroutine */ int zhpr_(char *uplo, integer *n, doublereal *alpha, 
	doublecomplex *x, integer *incx, doublecomplex *ap);

/* Subroutine */ int zhpr2_(char *uplo, integer *n, doublecomplex *alpha, 
	doublecomplex *x, integer *incx, doublecomplex *y, integer *incy, 
	doublecomplex *ap);

/* Subroutine */ int zrotg_(doublecomplex *ca, doublecomplex *cb, doublereal *
	c__, doublecomplex *s);

/* Subroutine */ int zscal_(integer *n, doublecomplex *za, doublecomplex *zx, 
	integer *incx);

/* Subroutine */ int zswap_(integer *n, doublecomplex *zx, integer *incx, 
	doublecomplex *zy, integer *incy);

/* Subroutine */ int zsymm_(char *side, char *uplo, integer *m, integer *n, 
	doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *
	b, integer *ldb, doublecomplex *beta, doublecomplex *c__, integer *
	ldc);

/* Subroutine */ int zsyr2k_(char *uplo, char *trans, integer *n, integer *k, 
	doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *
	b, integer *ldb, doublecomplex *beta, doublecomplex *c__, integer *
	ldc);

/* Subroutine */ int zsyrk_(char *uplo, char *trans, integer *n, integer *k, 
	doublecomplex *alpha, doublecomplex *a, integer *lda, doublecomplex *
	beta, doublecomplex *c__, integer *ldc);

/* Subroutine */ int ztbmv_(char *uplo, char *trans, char *diag, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *x, integer 
	*incx);

/* Subroutine */ int ztbsv_(char *uplo, char *trans, char *diag, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *x, integer 
	*incx);

/* Subroutine */ int ztpmv_(char *uplo, char *trans, char *diag, integer *n, 
	doublecomplex *ap, doublecomplex *x, integer *incx);

/* Subroutine */ int ztpsv_(char *uplo, char *trans, char *diag, integer *n, 
	doublecomplex *ap, doublecomplex *x, integer *incx);

/* Subroutine */ int ztrmm_(char *side, char *uplo, char *transa, char *diag, 
	integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, 
	integer *lda, doublecomplex *b, integer *ldb);

/* Subroutine */ int ztrmv_(char *uplo, char *trans, char *diag, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *x, integer *incx);

/* Subroutine */ int ztrsm_(char *side, char *uplo, char *transa, char *diag, 
	integer *m, integer *n, doublecomplex *alpha, doublecomplex *a, 
	integer *lda, doublecomplex *b, integer *ldb);

/* Subroutine */ int ztrsv_(char *uplo, char *trans, char *diag, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *x, integer *incx);

/* Subroutine */ int cbdsqr_(char *uplo, integer *n, integer *ncvt, integer *
	nru, integer *ncc, floatreal *d__, floatreal *e, floatcomplex *vt, integer *ldvt, 
	floatcomplex *u, integer *ldu, floatcomplex *c__, integer *ldc, floatreal *rwork, 
	integer *info);

/* Subroutine */ int cgbbrd_(char *vect, integer *m, integer *n, integer *ncc, 
	 integer *kl, integer *ku, floatcomplex *ab, integer *ldab, floatreal *d__, 
	floatreal *e, floatcomplex *q, integer *ldq, floatcomplex *pt, integer *ldpt, 
	floatcomplex *c__, integer *ldc, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgbcon_(char *norm, integer *n, integer *kl, integer *ku, 
	 floatcomplex *ab, integer *ldab, integer *ipiv, floatreal *anorm, floatreal *rcond, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgbequ_(integer *m, integer *n, integer *kl, integer *ku, 
	 floatcomplex *ab, integer *ldab, floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal 
	*colcnd, floatreal *amax, integer *info);

/* Subroutine */ int cgbequb_(integer *m, integer *n, integer *kl, integer *
	ku, floatcomplex *ab, integer *ldab, floatreal *r__, floatreal *c__, floatreal *rowcnd, 
	floatreal *colcnd, floatreal *amax, integer *info);

/* Subroutine */ int cgbrfs_(char *trans, integer *n, integer *kl, integer *
	ku, integer *nrhs, floatcomplex *ab, integer *ldab, floatcomplex *afb, integer *
	ldafb, integer *ipiv, floatcomplex *b, integer *ldb, floatcomplex *x, integer *
	ldx, floatreal *ferr, floatreal *berr, floatcomplex *work, floatreal *rwork, integer *
	info);

/* Subroutine */ int cgbrfsx_(char *trans, char *equed, integer *n, integer *
	kl, integer *ku, integer *nrhs, floatcomplex *ab, integer *ldab, floatcomplex *
	afb, integer *ldafb, integer *ipiv, floatreal *r__, floatreal *c__, floatcomplex *b, 
	integer *ldb, floatcomplex *x, integer *ldx, floatreal *rcond, floatreal *berr, 
	integer *n_err_bnds__, floatreal *err_bnds_norm__, floatreal *err_bnds_comp__, 
	integer *nparams, floatreal *params, floatcomplex *work, floatreal *rwork, integer *
	info);

/* Subroutine */ int cgbsv_(integer *n, integer *kl, integer *ku, integer *
	nrhs, floatcomplex *ab, integer *ldab, integer *ipiv, floatcomplex *b, integer *
	ldb, integer *info);

/* Subroutine */ int cgbsvx_(char *fact, char *trans, integer *n, integer *kl, 
	 integer *ku, integer *nrhs, floatcomplex *ab, integer *ldab, floatcomplex *afb, 
	 integer *ldafb, integer *ipiv, char *equed, floatreal *r__, floatreal *c__, 
	floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, floatreal *rcond, floatreal 
	*ferr, floatreal *berr, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgbsvxx_(char *fact, char *trans, integer *n, integer *
	kl, integer *ku, integer *nrhs, floatcomplex *ab, integer *ldab, floatcomplex *
	afb, integer *ldafb, integer *ipiv, char *equed, floatreal *r__, floatreal *c__, 
	 floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, floatreal *rcond, 
	floatreal *rpvgrw, floatreal *berr, integer *n_err_bnds__, floatreal *
	err_bnds_norm__, floatreal *err_bnds_comp__, integer *nparams, floatreal *
	params, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgbtf2_(integer *m, integer *n, integer *kl, integer *ku, 
	 floatcomplex *ab, integer *ldab, integer *ipiv, integer *info);

/* Subroutine */ int cgbtrf_(integer *m, integer *n, integer *kl, integer *ku, 
	 floatcomplex *ab, integer *ldab, integer *ipiv, integer *info);

/* Subroutine */ int cgbtrs_(char *trans, integer *n, integer *kl, integer *
	ku, integer *nrhs, floatcomplex *ab, integer *ldab, integer *ipiv, floatcomplex 
	*b, integer *ldb, integer *info);

/* Subroutine */ int cgebak_(char *job, char *side, integer *n, integer *ilo, 
	integer *ihi, floatreal *scale, integer *m, floatcomplex *v, integer *ldv, 
	integer *info);

/* Subroutine */ int cgebal_(char *job, integer *n, floatcomplex *a, integer *lda, 
	integer *ilo, integer *ihi, floatreal *scale, integer *info);

/* Subroutine */ int cgebd2_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *d__, floatreal *e, floatcomplex *tauq, floatcomplex *taup, floatcomplex *work, 
	integer *info);

/* Subroutine */ int cgebrd_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *d__, floatreal *e, floatcomplex *tauq, floatcomplex *taup, floatcomplex *work, 
	integer *lwork, integer *info);

/* Subroutine */ int cgecon_(char *norm, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *anorm, floatreal *rcond, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgeequ_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal *colcnd, floatreal *amax, 
	integer *info);

/* Subroutine */ int cgeequb_(integer *m, integer *n, floatcomplex *a, integer *
	lda, floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal *colcnd, floatreal *amax, 
	integer *info);

/* Subroutine */ int cgees_(char *jobvs, char *sort, L_fp select, integer *n, 
	floatcomplex *a, integer *lda, integer *sdim, floatcomplex *w, floatcomplex *vs, 
	integer *ldvs, floatcomplex *work, integer *lwork, floatreal *rwork, logical *
	bwork, integer *info);

/* Subroutine */ int cgeesx_(char *jobvs, char *sort, L_fp select, char *
	sense, integer *n, floatcomplex *a, integer *lda, integer *sdim, floatcomplex *
	w, floatcomplex *vs, integer *ldvs, floatreal *rconde, floatreal *rcondv, floatcomplex *
	work, integer *lwork, floatreal *rwork, logical *bwork, integer *info);

/* Subroutine */ int cgeev_(char *jobvl, char *jobvr, integer *n, floatcomplex *a, 
	integer *lda, floatcomplex *w, floatcomplex *vl, integer *ldvl, floatcomplex *vr, 
	integer *ldvr, floatcomplex *work, integer *lwork, floatreal *rwork, integer *
	info);

/* Subroutine */ int cgeevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, floatcomplex *a, integer *lda, floatcomplex *w, floatcomplex *vl, 
	integer *ldvl, floatcomplex *vr, integer *ldvr, integer *ilo, integer *ihi, 
	 floatreal *scale, floatreal *abnrm, floatreal *rconde, floatreal *rcondv, floatcomplex *work, 
	integer *lwork, floatreal *rwork, integer *info);

/* Subroutine */ int cgegs_(char *jobvsl, char *jobvsr, integer *n, floatcomplex *
	a, integer *lda, floatcomplex *b, integer *ldb, floatcomplex *alpha, floatcomplex *
	beta, floatcomplex *vsl, integer *ldvsl, floatcomplex *vsr, integer *ldvsr, 
	floatcomplex *work, integer *lwork, floatreal *rwork, integer *info);

/* Subroutine */ int cgegv_(char *jobvl, char *jobvr, integer *n, floatcomplex *a, 
	integer *lda, floatcomplex *b, integer *ldb, floatcomplex *alpha, floatcomplex *beta, 
	 floatcomplex *vl, integer *ldvl, floatcomplex *vr, integer *ldvr, floatcomplex *
	work, integer *lwork, floatreal *rwork, integer *info);

/* Subroutine */ int cgehd2_(integer *n, integer *ilo, integer *ihi, floatcomplex *
	a, integer *lda, floatcomplex *tau, floatcomplex *work, integer *info);

/* Subroutine */ int cgehrd_(integer *n, integer *ilo, integer *ihi, floatcomplex *
	a, integer *lda, floatcomplex *tau, floatcomplex *work, integer *lwork, integer 
	*info);

/* Subroutine */ int cgelq2_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *info);

/* Subroutine */ int cgelqf_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cgels_(char *trans, integer *m, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, floatcomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int cgelsd_(integer *m, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, floatcomplex *b, integer *ldb, floatreal *s, floatreal *rcond, 
	integer *rank, floatcomplex *work, integer *lwork, floatreal *rwork, integer *
	iwork, integer *info);

/* Subroutine */ int cgelss_(integer *m, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, floatcomplex *b, integer *ldb, floatreal *s, floatreal *rcond, 
	integer *rank, floatcomplex *work, integer *lwork, floatreal *rwork, integer *
	info);

/* Subroutine */ int cgelsx_(integer *m, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, floatcomplex *b, integer *ldb, integer *jpvt, floatreal *rcond, 
	 integer *rank, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgelsy_(integer *m, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, floatcomplex *b, integer *ldb, integer *jpvt, floatreal *rcond, 
	 integer *rank, floatcomplex *work, integer *lwork, floatreal *rwork, integer *
	info);

/* Subroutine */ int cgeql2_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *info);

/* Subroutine */ int cgeqlf_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cgeqp3_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 integer *jpvt, floatcomplex *tau, floatcomplex *work, integer *lwork, floatreal *
	rwork, integer *info);

/* Subroutine */ int cgeqpf_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 integer *jpvt, floatcomplex *tau, floatcomplex *work, floatreal *rwork, integer *
	info);

/* Subroutine */ int cgeqr2_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *info);

/* Subroutine */ int cgeqrf_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cgerfs_(char *trans, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, floatcomplex *af, integer *ldaf, integer *ipiv, floatcomplex *
	b, integer *ldb, floatcomplex *x, integer *ldx, floatreal *ferr, floatreal *berr, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgerfsx_(char *trans, char *equed, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, integer *
	ipiv, floatreal *r__, floatreal *c__, floatcomplex *b, integer *ldb, floatcomplex *x, 
	integer *ldx, floatreal *rcond, floatreal *berr, integer *n_err_bnds__, floatreal *
	err_bnds_norm__, floatreal *err_bnds_comp__, integer *nparams, floatreal *
	params, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgerq2_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *info);

/* Subroutine */ int cgerqf_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cgesc2_(integer *n, floatcomplex *a, integer *lda, floatcomplex *
	rhs, integer *ipiv, integer *jpiv, floatreal *scale);

/* Subroutine */ int cgesdd_(char *jobz, integer *m, integer *n, floatcomplex *a, 
	integer *lda, floatreal *s, floatcomplex *u, integer *ldu, floatcomplex *vt, integer 
	*ldvt, floatcomplex *work, integer *lwork, floatreal *rwork, integer *iwork, 
	integer *info);

/* Subroutine */ int cgesv_(integer *n, integer *nrhs, floatcomplex *a, integer *
	lda, integer *ipiv, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	floatcomplex *a, integer *lda, floatreal *s, floatcomplex *u, integer *ldu, floatcomplex *
	vt, integer *ldvt, floatcomplex *work, integer *lwork, floatreal *rwork, 
	integer *info);

/* Subroutine */ int cgesvx_(char *fact, char *trans, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, integer *
	ipiv, char *equed, floatreal *r__, floatreal *c__, floatcomplex *b, integer *ldb, 
	floatcomplex *x, integer *ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgesvxx_(char *fact, char *trans, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, integer *
	ipiv, char *equed, floatreal *r__, floatreal *c__, floatcomplex *b, integer *ldb, 
	floatcomplex *x, integer *ldx, floatreal *rcond, floatreal *rpvgrw, floatreal *berr, 
	integer *n_err_bnds__, floatreal *err_bnds_norm__, floatreal *err_bnds_comp__, 
	integer *nparams, floatreal *params, floatcomplex *work, floatreal *rwork, integer *
	info);

/* Subroutine */ int cgetc2_(integer *n, floatcomplex *a, integer *lda, integer *
	ipiv, integer *jpiv, integer *info);

/* Subroutine */ int cgetf2_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, integer *info);

/* Subroutine */ int cgetrf_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, integer *info);

/* Subroutine */ int cgetri_(integer *n, floatcomplex *a, integer *lda, integer *
	ipiv, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cgetrs_(char *trans, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, integer *ipiv, floatcomplex *b, integer *ldb, integer *
	info);

/* Subroutine */ int cggbak_(char *job, char *side, integer *n, integer *ilo, 
	integer *ihi, floatreal *lscale, floatreal *rscale, integer *m, floatcomplex *v, 
	integer *ldv, integer *info);

/* Subroutine */ int cggbal_(char *job, integer *n, floatcomplex *a, integer *lda, 
	floatcomplex *b, integer *ldb, integer *ilo, integer *ihi, floatreal *lscale, 
	floatreal *rscale, floatreal *work, integer *info);

/* Subroutine */ int cgges_(char *jobvsl, char *jobvsr, char *sort, L_fp 
	selctg, integer *n, floatcomplex *a, integer *lda, floatcomplex *b, integer *
	ldb, integer *sdim, floatcomplex *alpha, floatcomplex *beta, floatcomplex *vsl, 
	integer *ldvsl, floatcomplex *vsr, integer *ldvsr, floatcomplex *work, integer *
	lwork, floatreal *rwork, logical *bwork, integer *info);

/* Subroutine */ int cggesx_(char *jobvsl, char *jobvsr, char *sort, L_fp 
	selctg, char *sense, integer *n, floatcomplex *a, integer *lda, floatcomplex *b, 
	 integer *ldb, integer *sdim, floatcomplex *alpha, floatcomplex *beta, floatcomplex *
	vsl, integer *ldvsl, floatcomplex *vsr, integer *ldvsr, floatreal *rconde, floatreal 
	*rcondv, floatcomplex *work, integer *lwork, floatreal *rwork, integer *iwork, 
	integer *liwork, logical *bwork, integer *info);

/* Subroutine */ int cggev_(char *jobvl, char *jobvr, integer *n, floatcomplex *a, 
	integer *lda, floatcomplex *b, integer *ldb, floatcomplex *alpha, floatcomplex *beta, 
	 floatcomplex *vl, integer *ldvl, floatcomplex *vr, integer *ldvr, floatcomplex *
	work, integer *lwork, floatreal *rwork, integer *info);

/* Subroutine */ int cggevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	 floatcomplex *alpha, floatcomplex *beta, floatcomplex *vl, integer *ldvl, floatcomplex *
	vr, integer *ldvr, integer *ilo, integer *ihi, floatreal *lscale, floatreal *
	rscale, floatreal *abnrm, floatreal *bbnrm, floatreal *rconde, floatreal *rcondv, floatcomplex 
	*work, integer *lwork, floatreal *rwork, integer *iwork, logical *bwork, 
	integer *info);

/* Subroutine */ int cggglm_(integer *n, integer *m, integer *p, floatcomplex *a, 
	integer *lda, floatcomplex *b, integer *ldb, floatcomplex *d__, floatcomplex *x, 
	floatcomplex *y, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cgghrd_(char *compq, char *compz, integer *n, integer *
	ilo, integer *ihi, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	 floatcomplex *q, integer *ldq, floatcomplex *z__, integer *ldz, integer *info);

/* Subroutine */ int cgglse_(integer *m, integer *n, integer *p, floatcomplex *a, 
	integer *lda, floatcomplex *b, integer *ldb, floatcomplex *c__, floatcomplex *d__, 
	floatcomplex *x, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cggqrf_(integer *n, integer *m, integer *p, floatcomplex *a, 
	integer *lda, floatcomplex *taua, floatcomplex *b, integer *ldb, floatcomplex *taub, 
	floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cggrqf_(integer *m, integer *p, integer *n, floatcomplex *a, 
	integer *lda, floatcomplex *taua, floatcomplex *b, integer *ldb, floatcomplex *taub, 
	floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cggsvd_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *n, integer *p, integer *k, integer *l, floatcomplex *a, integer *
	lda, floatcomplex *b, integer *ldb, floatreal *alpha, floatreal *beta, floatcomplex *u, 
	integer *ldu, floatcomplex *v, integer *ldv, floatcomplex *q, integer *ldq, 
	floatcomplex *work, floatreal *rwork, integer *iwork, integer *info);

/* Subroutine */ int cggsvp_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *p, integer *n, floatcomplex *a, integer *lda, floatcomplex *b, integer 
	*ldb, floatreal *tola, floatreal *tolb, integer *k, integer *l, floatcomplex *u, 
	integer *ldu, floatcomplex *v, integer *ldv, floatcomplex *q, integer *ldq, 
	integer *iwork, floatreal *rwork, floatcomplex *tau, floatcomplex *work, integer *
	info);

/* Subroutine */ int cgtcon_(char *norm, integer *n, floatcomplex *dl, floatcomplex *
	d__, floatcomplex *du, floatcomplex *du2, integer *ipiv, floatreal *anorm, floatreal *
	rcond, floatcomplex *work, integer *info);

/* Subroutine */ int cgtrfs_(char *trans, integer *n, integer *nrhs, floatcomplex *
	dl, floatcomplex *d__, floatcomplex *du, floatcomplex *dlf, floatcomplex *df, floatcomplex *
	duf, floatcomplex *du2, integer *ipiv, floatcomplex *b, integer *ldb, floatcomplex *
	x, integer *ldx, floatreal *ferr, floatreal *berr, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int cgtsv_(integer *n, integer *nrhs, floatcomplex *dl, floatcomplex *
	d__, floatcomplex *du, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cgtsvx_(char *fact, char *trans, integer *n, integer *
	nrhs, floatcomplex *dl, floatcomplex *d__, floatcomplex *du, floatcomplex *dlf, floatcomplex *
	df, floatcomplex *duf, floatcomplex *du2, integer *ipiv, floatcomplex *b, integer *
	ldb, floatcomplex *x, integer *ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cgttrf_(integer *n, floatcomplex *dl, floatcomplex *d__, floatcomplex *
	du, floatcomplex *du2, integer *ipiv, integer *info);

/* Subroutine */ int cgttrs_(char *trans, integer *n, integer *nrhs, floatcomplex *
	dl, floatcomplex *d__, floatcomplex *du, floatcomplex *du2, integer *ipiv, floatcomplex *
	b, integer *ldb, integer *info);

/* Subroutine */ int cgtts2_(integer *itrans, integer *n, integer *nrhs, 
	floatcomplex *dl, floatcomplex *d__, floatcomplex *du, floatcomplex *du2, integer *ipiv, 
	floatcomplex *b, integer *ldb);

/* Subroutine */ int chbev_(char *jobz, char *uplo, integer *n, integer *kd, 
	floatcomplex *ab, integer *ldab, floatreal *w, floatcomplex *z__, integer *ldz, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int chbevd_(char *jobz, char *uplo, integer *n, integer *kd, 
	floatcomplex *ab, integer *ldab, floatreal *w, floatcomplex *z__, integer *ldz, 
	floatcomplex *work, integer *lwork, floatreal *rwork, integer *lrwork, integer *
	iwork, integer *liwork, integer *info);

/* Subroutine */ int chbevx_(char *jobz, char *range, char *uplo, integer *n, 
	integer *kd, floatcomplex *ab, integer *ldab, floatcomplex *q, integer *ldq, 
	floatreal *vl, floatreal *vu, integer *il, integer *iu, floatreal *abstol, integer *
	m, floatreal *w, floatcomplex *z__, integer *ldz, floatcomplex *work, floatreal *rwork, 
	integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int chbgst_(char *vect, char *uplo, integer *n, integer *ka, 
	integer *kb, floatcomplex *ab, integer *ldab, floatcomplex *bb, integer *ldbb, 
	floatcomplex *x, integer *ldx, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int chbgv_(char *jobz, char *uplo, integer *n, integer *ka, 
	integer *kb, floatcomplex *ab, integer *ldab, floatcomplex *bb, integer *ldbb, 
	floatreal *w, floatcomplex *z__, integer *ldz, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int chbgvd_(char *jobz, char *uplo, integer *n, integer *ka, 
	integer *kb, floatcomplex *ab, integer *ldab, floatcomplex *bb, integer *ldbb, 
	floatreal *w, floatcomplex *z__, integer *ldz, floatcomplex *work, integer *lwork, 
	floatreal *rwork, integer *lrwork, integer *iwork, integer *liwork, 
	integer *info);

/* Subroutine */ int chbgvx_(char *jobz, char *range, char *uplo, integer *n, 
	integer *ka, integer *kb, floatcomplex *ab, integer *ldab, floatcomplex *bb, 
	integer *ldbb, floatcomplex *q, integer *ldq, floatreal *vl, floatreal *vu, integer *
	il, integer *iu, floatreal *abstol, integer *m, floatreal *w, floatcomplex *z__, 
	integer *ldz, floatcomplex *work, floatreal *rwork, integer *iwork, integer *
	ifail, integer *info);

/* Subroutine */ int chbtrd_(char *vect, char *uplo, integer *n, integer *kd, 
	floatcomplex *ab, integer *ldab, floatreal *d__, floatreal *e, floatcomplex *q, integer *
	ldq, floatcomplex *work, integer *info);

/* Subroutine */ int checon_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, floatreal *anorm, floatreal *rcond, floatcomplex *work, integer *
	info);

/* Subroutine */ int cheequb_(char *uplo, integer *n, floatcomplex *a, integer *
	lda, floatreal *s, floatreal *scond, floatreal *amax, floatcomplex *work, integer *info);

/* Subroutine */ int cheev_(char *jobz, char *uplo, integer *n, floatcomplex *a, 
	integer *lda, floatreal *w, floatcomplex *work, integer *lwork, floatreal *rwork, 
	integer *info);

/* Subroutine */ int cheevd_(char *jobz, char *uplo, integer *n, floatcomplex *a, 
	integer *lda, floatreal *w, floatcomplex *work, integer *lwork, floatreal *rwork, 
	integer *lrwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int cheevr_(char *jobz, char *range, char *uplo, integer *n, 
	floatcomplex *a, integer *lda, floatreal *vl, floatreal *vu, integer *il, integer *
	iu, floatreal *abstol, integer *m, floatreal *w, floatcomplex *z__, integer *ldz, 
	integer *isuppz, floatcomplex *work, integer *lwork, floatreal *rwork, integer *
	lrwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int cheevx_(char *jobz, char *range, char *uplo, integer *n, 
	floatcomplex *a, integer *lda, floatreal *vl, floatreal *vu, integer *il, integer *
	iu, floatreal *abstol, integer *m, floatreal *w, floatcomplex *z__, integer *ldz, 
	floatcomplex *work, integer *lwork, floatreal *rwork, integer *iwork, integer *
	ifail, integer *info);

/* Subroutine */ int chegs2_(integer *itype, char *uplo, integer *n, floatcomplex *
	a, integer *lda, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int chegst_(integer *itype, char *uplo, integer *n, floatcomplex *
	a, integer *lda, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int chegv_(integer *itype, char *jobz, char *uplo, integer *
	n, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, floatreal *w, 
	floatcomplex *work, integer *lwork, floatreal *rwork, integer *info);

/* Subroutine */ int chegvd_(integer *itype, char *jobz, char *uplo, integer *
	n, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, floatreal *w, 
	floatcomplex *work, integer *lwork, floatreal *rwork, integer *lrwork, integer *
	iwork, integer *liwork, integer *info);

/* Subroutine */ int chegvx_(integer *itype, char *jobz, char *range, char *
	uplo, integer *n, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	floatreal *vl, floatreal *vu, integer *il, integer *iu, floatreal *abstol, integer *
	m, floatreal *w, floatcomplex *z__, integer *ldz, floatcomplex *work, integer *lwork, 
	 floatreal *rwork, integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int cherfs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, floatcomplex *af, integer *ldaf, integer *ipiv, floatcomplex *
	b, integer *ldb, floatcomplex *x, integer *ldx, floatreal *ferr, floatreal *berr, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cherfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, integer *
	ipiv, floatreal *s, floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, 
	floatreal *rcond, floatreal *berr, integer *n_err_bnds__, floatreal *err_bnds_norm__, 
	 floatreal *err_bnds_comp__, integer *nparams, floatreal *params, floatcomplex *work, 
	 floatreal *rwork, integer *info);

/* Subroutine */ int chesv_(char *uplo, integer *n, integer *nrhs, floatcomplex *a, 
	 integer *lda, integer *ipiv, floatcomplex *b, integer *ldb, floatcomplex *work, 
	 integer *lwork, integer *info);

/* Subroutine */ int chesvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, integer *
	ipiv, floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, floatreal *rcond, 
	 floatreal *ferr, floatreal *berr, floatcomplex *work, integer *lwork, floatreal *rwork, 
	integer *info);

/* Subroutine */ int chesvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, integer *
	ipiv, char *equed, floatreal *s, floatcomplex *b, integer *ldb, floatcomplex *x, 
	integer *ldx, floatreal *rcond, floatreal *rpvgrw, floatreal *berr, integer *
	n_err_bnds__, floatreal *err_bnds_norm__, floatreal *err_bnds_comp__, integer *
	nparams, floatreal *params, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int chetd2_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *d__, floatreal *e, floatcomplex *tau, integer *info);

/* Subroutine */ int chetf2_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, integer *info);

/* Subroutine */ int chetrd_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *d__, floatreal *e, floatcomplex *tau, floatcomplex *work, integer *lwork, 
	integer *info);

/* Subroutine */ int chetrf_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int chetri_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, floatcomplex *work, integer *info);

/* Subroutine */ int chetrs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, integer *ipiv, floatcomplex *b, integer *ldb, integer *
	info);

/* Subroutine */ int chfrk_(char *transr, char *uplo, char *trans, integer *n, 
	 integer *k, floatreal *alpha, floatcomplex *a, integer *lda, floatreal *beta, 
	floatcomplex *c__);

/* Subroutine */ int chgeqz_(char *job, char *compq, char *compz, integer *n, 
	integer *ilo, integer *ihi, floatcomplex *h__, integer *ldh, floatcomplex *t, 
	integer *ldt, floatcomplex *alpha, floatcomplex *beta, floatcomplex *q, integer *ldq, 
	 floatcomplex *z__, integer *ldz, floatcomplex *work, integer *lwork, floatreal *
	rwork, integer *info);

/* Character */ VOID chla_transtype__(char *ret_val, ftnlen ret_val_len, 
	integer *trans);

/* Subroutine */ int chpcon_(char *uplo, integer *n, floatcomplex *ap, integer *
	ipiv, floatreal *anorm, floatreal *rcond, floatcomplex *work, integer *info);

/* Subroutine */ int chpev_(char *jobz, char *uplo, integer *n, floatcomplex *ap, 
	floatreal *w, floatcomplex *z__, integer *ldz, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int chpevd_(char *jobz, char *uplo, integer *n, floatcomplex *ap, 
	floatreal *w, floatcomplex *z__, integer *ldz, floatcomplex *work, integer *lwork, 
	floatreal *rwork, integer *lrwork, integer *iwork, integer *liwork, 
	integer *info);

/* Subroutine */ int chpevx_(char *jobz, char *range, char *uplo, integer *n, 
	floatcomplex *ap, floatreal *vl, floatreal *vu, integer *il, integer *iu, floatreal *
	abstol, integer *m, floatreal *w, floatcomplex *z__, integer *ldz, floatcomplex *
	work, floatreal *rwork, integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int chpgst_(integer *itype, char *uplo, integer *n, floatcomplex *
	ap, floatcomplex *bp, integer *info);

/* Subroutine */ int chpgv_(integer *itype, char *jobz, char *uplo, integer *
	n, floatcomplex *ap, floatcomplex *bp, floatreal *w, floatcomplex *z__, integer *ldz, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int chpgvd_(integer *itype, char *jobz, char *uplo, integer *
	n, floatcomplex *ap, floatcomplex *bp, floatreal *w, floatcomplex *z__, integer *ldz, 
	floatcomplex *work, integer *lwork, floatreal *rwork, integer *lrwork, integer *
	iwork, integer *liwork, integer *info);

/* Subroutine */ int chpgvx_(integer *itype, char *jobz, char *range, char *
	uplo, integer *n, floatcomplex *ap, floatcomplex *bp, floatreal *vl, floatreal *vu, 
	integer *il, integer *iu, floatreal *abstol, integer *m, floatreal *w, floatcomplex *
	z__, integer *ldz, floatcomplex *work, floatreal *rwork, integer *iwork, 
	integer *ifail, integer *info);

/* Subroutine */ int chprfs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	ap, floatcomplex *afp, integer *ipiv, floatcomplex *b, integer *ldb, floatcomplex *x, 
	 integer *ldx, floatreal *ferr, floatreal *berr, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int chpsv_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	ap, integer *ipiv, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int chpsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatcomplex *ap, floatcomplex *afp, integer *ipiv, floatcomplex *b, integer *
	ldb, floatcomplex *x, integer *ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int chptrd_(char *uplo, integer *n, floatcomplex *ap, floatreal *d__, 
	floatreal *e, floatcomplex *tau, integer *info);

/* Subroutine */ int chptrf_(char *uplo, integer *n, floatcomplex *ap, integer *
	ipiv, integer *info);

/* Subroutine */ int chptri_(char *uplo, integer *n, floatcomplex *ap, integer *
	ipiv, floatcomplex *work, integer *info);

/* Subroutine */ int chptrs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	ap, integer *ipiv, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int chsein_(char *side, char *eigsrc, char *initv, logical *
	select, integer *n, floatcomplex *h__, integer *ldh, floatcomplex *w, floatcomplex *
	vl, integer *ldvl, floatcomplex *vr, integer *ldvr, integer *mm, integer *
	m, floatcomplex *work, floatreal *rwork, integer *ifaill, integer *ifailr, 
	integer *info);

/* Subroutine */ int chseqr_(char *job, char *compz, integer *n, integer *ilo, 
	 integer *ihi, floatcomplex *h__, integer *ldh, floatcomplex *w, floatcomplex *z__, 
	integer *ldz, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cla_gbamv__(integer *trans, integer *m, integer *n, 
	integer *kl, integer *ku, floatreal *alpha, floatcomplex *ab, integer *ldab, 
	floatcomplex *x, integer *incx, floatreal *beta, floatreal *y, integer *incy);

doublereal cla_gbrcond_c__(char *trans, integer *n, integer *kl, integer *ku, 
	floatcomplex *ab, integer *ldab, floatcomplex *afb, integer *ldafb, integer *
	ipiv, floatreal *c__, logical *capply, integer *info, floatcomplex *work, floatreal *
	rwork, ftnlen trans_len);

doublereal cla_gbrcond_x__(char *trans, integer *n, integer *kl, integer *ku, 
	floatcomplex *ab, integer *ldab, floatcomplex *afb, integer *ldafb, integer *
	ipiv, floatcomplex *x, integer *info, floatcomplex *work, floatreal *rwork, ftnlen 
	trans_len);

/* Subroutine */ int cla_gbrfsx_extended__(integer *prec_type__, integer *
	trans_type__, integer *n, integer *kl, integer *ku, integer *nrhs, 
	floatcomplex *ab, integer *ldab, floatcomplex *afb, integer *ldafb, integer *
	ipiv, logical *colequ, floatreal *c__, floatcomplex *b, integer *ldb, floatcomplex *
	y, integer *ldy, floatreal *berr_out__, integer *n_norms__, floatreal *errs_n__,
	 floatreal *errs_c__, floatcomplex *res, floatreal *ayb, floatcomplex *dy, floatcomplex *
	y_tail__, floatreal *rcond, integer *ithresh, floatreal *rthresh, floatreal *dz_ub__,
	 logical *ignore_cwise__, integer *info);

doublereal cla_gbrpvgrw__(integer *n, integer *kl, integer *ku, integer *
	ncols, floatcomplex *ab, integer *ldab, floatcomplex *afb, integer *ldafb);

/* Subroutine */ int cla_geamv__(integer *trans, integer *m, integer *n, floatreal 
	*alpha, floatcomplex *a, integer *lda, floatcomplex *x, integer *incx, floatreal *
	beta, floatreal *y, integer *incy);

doublereal cla_gercond_c__(char *trans, integer *n, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf, integer *ipiv, floatreal *c__, logical *capply,
	 integer *info, floatcomplex *work, floatreal *rwork, ftnlen trans_len);

doublereal cla_gercond_x__(char *trans, integer *n, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf, integer *ipiv, floatcomplex *x, integer *info, 
	floatcomplex *work, floatreal *rwork, ftnlen trans_len);

/* Subroutine */ int cla_gerfsx_extended__(integer *prec_type__, integer *
	trans_type__, integer *n, integer *nrhs, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf, integer *ipiv, logical *colequ, floatreal *c__,
	 floatcomplex *b, integer *ldb, floatcomplex *y, integer *ldy, floatreal *berr_out__,
	 integer *n_norms__, floatreal *errs_n__, floatreal *errs_c__, floatcomplex *res, 
	floatreal *ayb, floatcomplex *dy, floatcomplex *y_tail__, floatreal *rcond, integer *
	ithresh, floatreal *rthresh, floatreal *dz_ub__, logical *ignore_cwise__, 
	integer *info);

/* Subroutine */ int cla_heamv__(integer *uplo, integer *n, floatreal *alpha, 
	floatcomplex *a, integer *lda, floatcomplex *x, integer *incx, floatreal *beta, floatreal 
	*y, integer *incy);

doublereal cla_hercond_c__(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf, integer *ipiv, floatreal *c__, logical *capply,
	 integer *info, floatcomplex *work, floatreal *rwork, ftnlen uplo_len);

doublereal cla_hercond_x__(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf, integer *ipiv, floatcomplex *x, integer *info, 
	floatcomplex *work, floatreal *rwork, ftnlen uplo_len);

/* Subroutine */ int cla_herfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, floatcomplex *a, integer *lda, floatcomplex *af, 
	integer *ldaf, integer *ipiv, logical *colequ, floatreal *c__, floatcomplex *b, 
	integer *ldb, floatcomplex *y, integer *ldy, floatreal *berr_out__, integer *
	n_norms__, floatreal *errs_n__, floatreal *errs_c__, floatcomplex *res, floatreal *ayb, 
	floatcomplex *dy, floatcomplex *y_tail__, floatreal *rcond, integer *ithresh, floatreal *
	rthresh, floatreal *dz_ub__, logical *ignore_cwise__, integer *info, 
	ftnlen uplo_len);

doublereal cla_herpvgrw__(char *uplo, integer *n, integer *info, floatcomplex *a, 
	integer *lda, floatcomplex *af, integer *ldaf, integer *ipiv, floatreal *work, 
	ftnlen uplo_len);

/* Subroutine */ int cla_lin_berr__(integer *n, integer *nz, integer *nrhs, 
	floatcomplex *res, floatreal *ayb, floatreal *berr);

doublereal cla_porcond_c__(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf, floatreal *c__, logical *capply, integer *info,
	 floatcomplex *work, floatreal *rwork, ftnlen uplo_len);

doublereal cla_porcond_x__(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf, floatcomplex *x, integer *info, floatcomplex *work, 
	floatreal *rwork, ftnlen uplo_len);

/* Subroutine */ int cla_porfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, floatcomplex *a, integer *lda, floatcomplex *af, 
	integer *ldaf, logical *colequ, floatreal *c__, floatcomplex *b, integer *ldb, 
	floatcomplex *y, integer *ldy, floatreal *berr_out__, integer *n_norms__, floatreal *
	errs_n__, floatreal *errs_c__, floatcomplex *res, floatreal *ayb, floatcomplex *dy, 
	floatcomplex *y_tail__, floatreal *rcond, integer *ithresh, floatreal *rthresh, floatreal 
	*dz_ub__, logical *ignore_cwise__, integer *info, ftnlen uplo_len);

doublereal cla_porpvgrw__(char *uplo, integer *ncols, floatcomplex *a, integer *
	lda, floatcomplex *af, integer *ldaf, floatreal *work, ftnlen uplo_len);

doublereal cla_rpvgrw__(integer *n, integer *ncols, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf);

/* Subroutine */ int cla_syamv__(integer *uplo, integer *n, floatreal *alpha, 
	floatcomplex *a, integer *lda, floatcomplex *x, integer *incx, floatreal *beta, floatreal 
	*y, integer *incy);

doublereal cla_syrcond_c__(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf, integer *ipiv, floatreal *c__, logical *capply,
	 integer *info, floatcomplex *work, floatreal *rwork, ftnlen uplo_len);

doublereal cla_syrcond_x__(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	floatcomplex *af, integer *ldaf, integer *ipiv, floatcomplex *x, integer *info, 
	floatcomplex *work, floatreal *rwork, ftnlen uplo_len);

/* Subroutine */ int cla_syrfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, floatcomplex *a, integer *lda, floatcomplex *af, 
	integer *ldaf, integer *ipiv, logical *colequ, floatreal *c__, floatcomplex *b, 
	integer *ldb, floatcomplex *y, integer *ldy, floatreal *berr_out__, integer *
	n_norms__, floatreal *errs_n__, floatreal *errs_c__, floatcomplex *res, floatreal *ayb, 
	floatcomplex *dy, floatcomplex *y_tail__, floatreal *rcond, integer *ithresh, floatreal *
	rthresh, floatreal *dz_ub__, logical *ignore_cwise__, integer *info, 
	ftnlen uplo_len);

doublereal cla_syrpvgrw__(char *uplo, integer *n, integer *info, floatcomplex *a, 
	integer *lda, floatcomplex *af, integer *ldaf, integer *ipiv, floatreal *work, 
	ftnlen uplo_len);

/* Subroutine */ int cla_wwaddw__(integer *n, floatcomplex *x, floatcomplex *y, floatcomplex 
	*w);

/* Subroutine */ int clabrd_(integer *m, integer *n, integer *nb, floatcomplex *a, 
	integer *lda, floatreal *d__, floatreal *e, floatcomplex *tauq, floatcomplex *taup, 
	floatcomplex *x, integer *ldx, floatcomplex *y, integer *ldy);

/* Subroutine */ int clacgv_(integer *n, floatcomplex *x, integer *incx);

/* Subroutine */ int clacn2_(integer *n, floatcomplex *v, floatcomplex *x, floatreal *est, 
	integer *kase, integer *isave);

/* Subroutine */ int clacon_(integer *n, floatcomplex *v, floatcomplex *x, floatreal *est, 
	integer *kase);

/* Subroutine */ int clacp2_(char *uplo, integer *m, integer *n, floatreal *a, 
	integer *lda, floatcomplex *b, integer *ldb);

/* Subroutine */ int clacpy_(char *uplo, integer *m, integer *n, floatcomplex *a, 
	integer *lda, floatcomplex *b, integer *ldb);

/* Subroutine */ int clacrm_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *b, integer *ldb, floatcomplex *c__, integer *ldc, floatreal *rwork);

/* Subroutine */ int clacrt_(integer *n, floatcomplex *cx, integer *incx, floatcomplex *
	cy, integer *incy, floatcomplex *c__, floatcomplex *s);

/* Complex */ VOID cladiv_(floatcomplex * ret_val, floatcomplex *x, floatcomplex *y);

/* Subroutine */ int claed0_(integer *qsiz, integer *n, floatreal *d__, floatreal *e, 
	floatcomplex *q, integer *ldq, floatcomplex *qstore, integer *ldqs, floatreal *rwork, 
	 integer *iwork, integer *info);

/* Subroutine */ int claed7_(integer *n, integer *cutpnt, integer *qsiz, 
	integer *tlvls, integer *curlvl, integer *curpbm, floatreal *d__, floatcomplex *
	q, integer *ldq, floatreal *rho, integer *indxq, floatreal *qstore, integer *
	qptr, integer *prmptr, integer *perm, integer *givptr, integer *
	givcol, floatreal *givnum, floatcomplex *work, floatreal *rwork, integer *iwork, 
	integer *info);

/* Subroutine */ int claed8_(integer *k, integer *n, integer *qsiz, floatcomplex *
	q, integer *ldq, floatreal *d__, floatreal *rho, integer *cutpnt, floatreal *z__, 
	floatreal *dlamda, floatcomplex *q2, integer *ldq2, floatreal *w, integer *indxp, 
	integer *indx, integer *indxq, integer *perm, integer *givptr, 
	integer *givcol, floatreal *givnum, integer *info);

/* Subroutine */ int claein_(logical *rightv, logical *noinit, integer *n, 
	floatcomplex *h__, integer *ldh, floatcomplex *w, floatcomplex *v, floatcomplex *b, 
	integer *ldb, floatreal *rwork, floatreal *eps3, floatreal *smlnum, integer *info);

/* Subroutine */ int claesy_(floatcomplex *a, floatcomplex *b, floatcomplex *c__, floatcomplex *
	rt1, floatcomplex *rt2, floatcomplex *evscal, floatcomplex *cs1, floatcomplex *sn1);

/* Subroutine */ int claev2_(floatcomplex *a, floatcomplex *b, floatcomplex *c__, floatreal *rt1, 
	floatreal *rt2, floatreal *cs1, floatcomplex *sn1);

/* Subroutine */ int clag2z_(integer *m, integer *n, floatcomplex *sa, integer *
	ldsa, doublecomplex *a, integer *lda, integer *info);

/* Subroutine */ int clags2_(logical *upper, floatreal *a1, floatcomplex *a2, floatreal *a3, 
	floatreal *b1, floatcomplex *b2, floatreal *b3, floatreal *csu, floatcomplex *snu, floatreal *csv, 
	floatcomplex *snv, floatreal *csq, floatcomplex *snq);

/* Subroutine */ int clagtm_(char *trans, integer *n, integer *nrhs, floatreal *
	alpha, floatcomplex *dl, floatcomplex *d__, floatcomplex *du, floatcomplex *x, integer *
	ldx, floatreal *beta, floatcomplex *b, integer *ldb);

/* Subroutine */ int clahef_(char *uplo, integer *n, integer *nb, integer *kb, 
	 floatcomplex *a, integer *lda, integer *ipiv, floatcomplex *w, integer *ldw, 
	integer *info);

/* Subroutine */ int clahqr_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, floatcomplex *h__, integer *ldh, floatcomplex *w, 
	integer *iloz, integer *ihiz, floatcomplex *z__, integer *ldz, integer *
	info);

/* Subroutine */ int clahr2_(integer *n, integer *k, integer *nb, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *t, integer *ldt, floatcomplex *y, 
	integer *ldy);

/* Subroutine */ int clahrd_(integer *n, integer *k, integer *nb, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *t, integer *ldt, floatcomplex *y, 
	integer *ldy);

/* Subroutine */ int claic1_(integer *job, integer *j, floatcomplex *x, floatreal *sest, 
	 floatcomplex *w, floatcomplex *gamma, floatreal *sestpr, floatcomplex *s, floatcomplex *c__);

/* Subroutine */ int clals0_(integer *icompq, integer *nl, integer *nr, 
	integer *sqre, integer *nrhs, floatcomplex *b, integer *ldb, floatcomplex *bx, 
	integer *ldbx, integer *perm, integer *givptr, integer *givcol, 
	integer *ldgcol, floatreal *givnum, integer *ldgnum, floatreal *poles, floatreal *
	difl, floatreal *difr, floatreal *z__, integer *k, floatreal *c__, floatreal *s, floatreal *
	rwork, integer *info);

/* Subroutine */ int clalsa_(integer *icompq, integer *smlsiz, integer *n, 
	integer *nrhs, floatcomplex *b, integer *ldb, floatcomplex *bx, integer *ldbx, 
	floatreal *u, integer *ldu, floatreal *vt, integer *k, floatreal *difl, floatreal *difr, 
	floatreal *z__, floatreal *poles, integer *givptr, integer *givcol, integer *
	ldgcol, integer *perm, floatreal *givnum, floatreal *c__, floatreal *s, floatreal *rwork, 
	integer *iwork, integer *info);

/* Subroutine */ int clalsd_(char *uplo, integer *smlsiz, integer *n, integer 
	*nrhs, floatreal *d__, floatreal *e, floatcomplex *b, integer *ldb, floatreal *rcond, 
	integer *rank, floatcomplex *work, floatreal *rwork, integer *iwork, integer *
	info);

doublereal clangb_(char *norm, integer *n, integer *kl, integer *ku, floatcomplex *
	ab, integer *ldab, floatreal *work);

doublereal clange_(char *norm, integer *m, integer *n, floatcomplex *a, integer *
	lda, floatreal *work);

doublereal clangt_(char *norm, integer *n, floatcomplex *dl, floatcomplex *d__, floatcomplex 
	*du);

doublereal clanhb_(char *norm, char *uplo, integer *n, integer *k, floatcomplex *
	ab, integer *ldab, floatreal *work);

doublereal clanhe_(char *norm, char *uplo, integer *n, floatcomplex *a, integer *
	lda, floatreal *work);

doublereal clanhf_(char *norm, char *transr, char *uplo, integer *n, floatcomplex *
	a, floatreal *work);

doublereal clanhp_(char *norm, char *uplo, integer *n, floatcomplex *ap, floatreal *
	work);

doublereal clanhs_(char *norm, integer *n, floatcomplex *a, integer *lda, floatreal *
	work);

doublereal clanht_(char *norm, integer *n, floatreal *d__, floatcomplex *e);

doublereal clansb_(char *norm, char *uplo, integer *n, integer *k, floatcomplex *
	ab, integer *ldab, floatreal *work);

doublereal clansp_(char *norm, char *uplo, integer *n, floatcomplex *ap, floatreal *
	work);

doublereal clansy_(char *norm, char *uplo, integer *n, floatcomplex *a, integer *
	lda, floatreal *work);

doublereal clantb_(char *norm, char *uplo, char *diag, integer *n, integer *k, 
	 floatcomplex *ab, integer *ldab, floatreal *work);

doublereal clantp_(char *norm, char *uplo, char *diag, integer *n, floatcomplex *
	ap, floatreal *work);

doublereal clantr_(char *norm, char *uplo, char *diag, integer *m, integer *n, 
	 floatcomplex *a, integer *lda, floatreal *work);

/* Subroutine */ int clapll_(integer *n, floatcomplex *x, integer *incx, floatcomplex *
	y, integer *incy, floatreal *ssmin);

/* Subroutine */ int clapmt_(logical *forwrd, integer *m, integer *n, floatcomplex 
	*x, integer *ldx, integer *k);

/* Subroutine */ int claqgb_(integer *m, integer *n, integer *kl, integer *ku, 
	 floatcomplex *ab, integer *ldab, floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal 
	*colcnd, floatreal *amax, char *equed);

/* Subroutine */ int claqge_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal *colcnd, floatreal *amax, char *
	equed);

/* Subroutine */ int claqhb_(char *uplo, integer *n, integer *kd, floatcomplex *ab, 
	 integer *ldab, floatreal *s, floatreal *scond, floatreal *amax, char *equed);

/* Subroutine */ int claqhe_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *s, floatreal *scond, floatreal *amax, char *equed);

/* Subroutine */ int claqhp_(char *uplo, integer *n, floatcomplex *ap, floatreal *s, 
	floatreal *scond, floatreal *amax, char *equed);

/* Subroutine */ int claqp2_(integer *m, integer *n, integer *offset, floatcomplex 
	*a, integer *lda, integer *jpvt, floatcomplex *tau, floatreal *vn1, floatreal *vn2, 
	floatcomplex *work);

/* Subroutine */ int claqps_(integer *m, integer *n, integer *offset, integer 
	*nb, integer *kb, floatcomplex *a, integer *lda, integer *jpvt, floatcomplex *
	tau, floatreal *vn1, floatreal *vn2, floatcomplex *auxv, floatcomplex *f, integer *ldf);

/* Subroutine */ int claqr0_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, floatcomplex *h__, integer *ldh, floatcomplex *w, 
	integer *iloz, integer *ihiz, floatcomplex *z__, integer *ldz, floatcomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int claqr1_(integer *n, floatcomplex *h__, integer *ldh, floatcomplex *
	s1, floatcomplex *s2, floatcomplex *v);

/* Subroutine */ int claqr2_(logical *wantt, logical *wantz, integer *n, 
	integer *ktop, integer *kbot, integer *nw, floatcomplex *h__, integer *ldh, 
	 integer *iloz, integer *ihiz, floatcomplex *z__, integer *ldz, integer *
	ns, integer *nd, floatcomplex *sh, floatcomplex *v, integer *ldv, integer *nh, 
	floatcomplex *t, integer *ldt, integer *nv, floatcomplex *wv, integer *ldwv, 
	floatcomplex *work, integer *lwork);

/* Subroutine */ int claqr3_(logical *wantt, logical *wantz, integer *n, 
	integer *ktop, integer *kbot, integer *nw, floatcomplex *h__, integer *ldh, 
	 integer *iloz, integer *ihiz, floatcomplex *z__, integer *ldz, integer *
	ns, integer *nd, floatcomplex *sh, floatcomplex *v, integer *ldv, integer *nh, 
	floatcomplex *t, integer *ldt, integer *nv, floatcomplex *wv, integer *ldwv, 
	floatcomplex *work, integer *lwork);

/* Subroutine */ int claqr4_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, floatcomplex *h__, integer *ldh, floatcomplex *w, 
	integer *iloz, integer *ihiz, floatcomplex *z__, integer *ldz, floatcomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int claqr5_(logical *wantt, logical *wantz, integer *kacc22, 
	integer *n, integer *ktop, integer *kbot, integer *nshfts, floatcomplex *s, 
	 floatcomplex *h__, integer *ldh, integer *iloz, integer *ihiz, floatcomplex *
	z__, integer *ldz, floatcomplex *v, integer *ldv, floatcomplex *u, integer *ldu, 
	 integer *nv, floatcomplex *wv, integer *ldwv, integer *nh, floatcomplex *wh, 
	integer *ldwh);

/* Subroutine */ int claqsb_(char *uplo, integer *n, integer *kd, floatcomplex *ab, 
	 integer *ldab, floatreal *s, floatreal *scond, floatreal *amax, char *equed);

/* Subroutine */ int claqsp_(char *uplo, integer *n, floatcomplex *ap, floatreal *s, 
	floatreal *scond, floatreal *amax, char *equed);

/* Subroutine */ int claqsy_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *s, floatreal *scond, floatreal *amax, char *equed);

/* Subroutine */ int clar1v_(integer *n, integer *b1, integer *bn, floatreal *
	lambda, floatreal *d__, floatreal *l, floatreal *ld, floatreal *lld, floatreal *pivmin, floatreal *
	gaptol, floatcomplex *z__, logical *wantnc, integer *negcnt, floatreal *ztz, 
	floatreal *mingma, integer *r__, integer *isuppz, floatreal *nrminv, floatreal *
	resid, floatreal *rqcorr, floatreal *work);

/* Subroutine */ int clar2v_(integer *n, floatcomplex *x, floatcomplex *y, floatcomplex *z__, 
	 integer *incx, floatreal *c__, floatcomplex *s, integer *incc);

/* Subroutine */ int clarcm_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatcomplex *b, integer *ldb, floatcomplex *c__, integer *ldc, floatreal *rwork);

/* Subroutine */ int clarf_(char *side, integer *m, integer *n, floatcomplex *v, 
	integer *incv, floatcomplex *tau, floatcomplex *c__, integer *ldc, floatcomplex *
	work);

/* Subroutine */ int clarfb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, floatcomplex *v, integer *ldv, 
	floatcomplex *t, integer *ldt, floatcomplex *c__, integer *ldc, floatcomplex *work, 
	integer *ldwork);

/* Subroutine */ int clarfg_(integer *n, floatcomplex *alpha, floatcomplex *x, integer *
	incx, floatcomplex *tau);

/* Subroutine */ int clarfp_(integer *n, floatcomplex *alpha, floatcomplex *x, integer *
	incx, floatcomplex *tau);

/* Subroutine */ int clarft_(char *direct, char *storev, integer *n, integer *
	k, floatcomplex *v, integer *ldv, floatcomplex *tau, floatcomplex *t, integer *ldt);

/* Subroutine */ int clarfx_(char *side, integer *m, integer *n, floatcomplex *v, 
	floatcomplex *tau, floatcomplex *c__, integer *ldc, floatcomplex *work);

/* Subroutine */ int clargv_(integer *n, floatcomplex *x, integer *incx, floatcomplex *
	y, integer *incy, floatreal *c__, integer *incc);

/* Subroutine */ int clarnv_(integer *idist, integer *iseed, integer *n, 
	floatcomplex *x);

/* Subroutine */ int clarrv_(integer *n, floatreal *vl, floatreal *vu, floatreal *d__, floatreal *
	l, floatreal *pivmin, integer *isplit, integer *m, integer *dol, integer *
	dou, floatreal *minrgp, floatreal *rtol1, floatreal *rtol2, floatreal *w, floatreal *werr, 
	floatreal *wgap, integer *iblock, integer *indexw, floatreal *gers, floatcomplex *
	z__, integer *ldz, integer *isuppz, floatreal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int clarscl2_(integer *m, integer *n, floatreal *d__, floatcomplex *x, 
	integer *ldx);

/* Subroutine */ int clartg_(floatcomplex *f, floatcomplex *g, floatreal *cs, floatcomplex *sn, 
	floatcomplex *r__);

/* Subroutine */ int clartv_(integer *n, floatcomplex *x, integer *incx, floatcomplex *
	y, integer *incy, floatreal *c__, floatcomplex *s, integer *incc);

/* Subroutine */ int clarz_(char *side, integer *m, integer *n, integer *l, 
	floatcomplex *v, integer *incv, floatcomplex *tau, floatcomplex *c__, integer *ldc, 
	floatcomplex *work);

/* Subroutine */ int clarzb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, integer *l, floatcomplex *v, 
	integer *ldv, floatcomplex *t, integer *ldt, floatcomplex *c__, integer *ldc, 
	floatcomplex *work, integer *ldwork);

/* Subroutine */ int clarzt_(char *direct, char *storev, integer *n, integer *
	k, floatcomplex *v, integer *ldv, floatcomplex *tau, floatcomplex *t, integer *ldt);

/* Subroutine */ int clascl_(char *type__, integer *kl, integer *ku, floatreal *
	cfrom, floatreal *cto, integer *m, integer *n, floatcomplex *a, integer *lda, 
	integer *info);

/* Subroutine */ int clascl2_(integer *m, integer *n, floatreal *d__, floatcomplex *x, 
	integer *ldx);

/* Subroutine */ int claset_(char *uplo, integer *m, integer *n, floatcomplex *
	alpha, floatcomplex *beta, floatcomplex *a, integer *lda);

/* Subroutine */ int clasr_(char *side, char *pivot, char *direct, integer *m, 
	 integer *n, floatreal *c__, floatreal *s, floatcomplex *a, integer *lda);

/* Subroutine */ int classq_(integer *n, floatcomplex *x, integer *incx, floatreal *
	scale, floatreal *sumsq);

/* Subroutine */ int claswp_(integer *n, floatcomplex *a, integer *lda, integer *
	k1, integer *k2, integer *ipiv, integer *incx);

/* Subroutine */ int clasyf_(char *uplo, integer *n, integer *nb, integer *kb, 
	 floatcomplex *a, integer *lda, integer *ipiv, floatcomplex *w, integer *ldw, 
	integer *info);

/* Subroutine */ int clatbs_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, integer *kd, floatcomplex *ab, integer *ldab, floatcomplex *
	x, floatreal *scale, floatreal *cnorm, integer *info);

/* Subroutine */ int clatdf_(integer *ijob, integer *n, floatcomplex *z__, integer 
	*ldz, floatcomplex *rhs, floatreal *rdsum, floatreal *rdscal, integer *ipiv, integer 
	*jpiv);

/* Subroutine */ int clatps_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, floatcomplex *ap, floatcomplex *x, floatreal *scale, floatreal *cnorm, 
	 integer *info);

/* Subroutine */ int clatrd_(char *uplo, integer *n, integer *nb, floatcomplex *a, 
	integer *lda, floatreal *e, floatcomplex *tau, floatcomplex *w, integer *ldw);

/* Subroutine */ int clatrs_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, floatcomplex *a, integer *lda, floatcomplex *x, floatreal *scale, 
	 floatreal *cnorm, integer *info);

/* Subroutine */ int clatrz_(integer *m, integer *n, integer *l, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *work);

/* Subroutine */ int clatzm_(char *side, integer *m, integer *n, floatcomplex *v, 
	integer *incv, floatcomplex *tau, floatcomplex *c1, floatcomplex *c2, integer *ldc, 
	floatcomplex *work);

/* Subroutine */ int clauu2_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *info);

/* Subroutine */ int clauum_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *info);

/* Subroutine */ int cpbcon_(char *uplo, integer *n, integer *kd, floatcomplex *ab, 
	 integer *ldab, floatreal *anorm, floatreal *rcond, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int cpbequ_(char *uplo, integer *n, integer *kd, floatcomplex *ab, 
	 integer *ldab, floatreal *s, floatreal *scond, floatreal *amax, integer *info);

/* Subroutine */ int cpbrfs_(char *uplo, integer *n, integer *kd, integer *
	nrhs, floatcomplex *ab, integer *ldab, floatcomplex *afb, integer *ldafb, 
	floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, floatreal *ferr, floatreal *
	berr, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cpbstf_(char *uplo, integer *n, integer *kd, floatcomplex *ab, 
	 integer *ldab, integer *info);

/* Subroutine */ int cpbsv_(char *uplo, integer *n, integer *kd, integer *
	nrhs, floatcomplex *ab, integer *ldab, floatcomplex *b, integer *ldb, integer *
	info);

/* Subroutine */ int cpbsvx_(char *fact, char *uplo, integer *n, integer *kd, 
	integer *nrhs, floatcomplex *ab, integer *ldab, floatcomplex *afb, integer *
	ldafb, char *equed, floatreal *s, floatcomplex *b, integer *ldb, floatcomplex *x, 
	integer *ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, floatcomplex *work, 
	floatreal *rwork, integer *info);

/* Subroutine */ int cpbtf2_(char *uplo, integer *n, integer *kd, floatcomplex *ab, 
	 integer *ldab, integer *info);

/* Subroutine */ int cpbtrf_(char *uplo, integer *n, integer *kd, floatcomplex *ab, 
	 integer *ldab, integer *info);

/* Subroutine */ int cpbtrs_(char *uplo, integer *n, integer *kd, integer *
	nrhs, floatcomplex *ab, integer *ldab, floatcomplex *b, integer *ldb, integer *
	info);

/* Subroutine */ int cpftrf_(char *transr, char *uplo, integer *n, floatcomplex *a, 
	 integer *info);

/* Subroutine */ int cpftri_(char *transr, char *uplo, integer *n, floatcomplex *a, 
	 integer *info);

/* Subroutine */ int cpftrs_(char *transr, char *uplo, integer *n, integer *
	nrhs, floatcomplex *a, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cpocon_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 floatreal *anorm, floatreal *rcond, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cpoequ_(integer *n, floatcomplex *a, integer *lda, floatreal *s, 
	floatreal *scond, floatreal *amax, integer *info);

/* Subroutine */ int cpoequb_(integer *n, floatcomplex *a, integer *lda, floatreal *s, 
	floatreal *scond, floatreal *amax, integer *info);

/* Subroutine */ int cporfs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, floatcomplex *af, integer *ldaf, floatcomplex *b, integer *ldb, 
	 floatcomplex *x, integer *ldx, floatreal *ferr, floatreal *berr, floatcomplex *work, 
	floatreal *rwork, integer *info);

/* Subroutine */ int cporfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, floatreal *s, 
	floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, floatreal *rcond, floatreal 
	*berr, integer *n_err_bnds__, floatreal *err_bnds_norm__, floatreal *
	err_bnds_comp__, integer *nparams, floatreal *params, floatcomplex *work, floatreal *
	rwork, integer *info);

/* Subroutine */ int cposv_(char *uplo, integer *n, integer *nrhs, floatcomplex *a, 
	 integer *lda, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cposvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, char *
	equed, floatreal *s, floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, 
	floatreal *rcond, floatreal *ferr, floatreal *berr, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int cposvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, char *
	equed, floatreal *s, floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, 
	floatreal *rcond, floatreal *rpvgrw, floatreal *berr, integer *n_err_bnds__, floatreal *
	err_bnds_norm__, floatreal *err_bnds_comp__, integer *nparams, floatreal *
	params, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cpotf2_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *info);

/* Subroutine */ int cpotrf_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *info);

/* Subroutine */ int cpotri_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *info);

/* Subroutine */ int cpotrs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cppcon_(char *uplo, integer *n, floatcomplex *ap, floatreal *anorm, 
	 floatreal *rcond, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cppequ_(char *uplo, integer *n, floatcomplex *ap, floatreal *s, 
	floatreal *scond, floatreal *amax, integer *info);

/* Subroutine */ int cpprfs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	ap, floatcomplex *afp, floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, 
	floatreal *ferr, floatreal *berr, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cppsv_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	ap, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cppsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatcomplex *ap, floatcomplex *afp, char *equed, floatreal *s, floatcomplex *b, 
	integer *ldb, floatcomplex *x, integer *ldx, floatreal *rcond, floatreal *ferr, floatreal 
	*berr, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int cpptrf_(char *uplo, integer *n, floatcomplex *ap, integer *
	info);

/* Subroutine */ int cpptri_(char *uplo, integer *n, floatcomplex *ap, integer *
	info);

/* Subroutine */ int cpptrs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	ap, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cpstf2_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *piv, integer *rank, floatreal *tol, floatreal *work, integer *info);

/* Subroutine */ int cpstrf_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *piv, integer *rank, floatreal *tol, floatreal *work, integer *info);

/* Subroutine */ int cptcon_(integer *n, floatreal *d__, floatcomplex *e, floatreal *anorm, 
	floatreal *rcond, floatreal *rwork, integer *info);

/* Subroutine */ int cpteqr_(char *compz, integer *n, floatreal *d__, floatreal *e, 
	floatcomplex *z__, integer *ldz, floatreal *work, integer *info);

/* Subroutine */ int cptrfs_(char *uplo, integer *n, integer *nrhs, floatreal *d__, 
	 floatcomplex *e, floatreal *df, floatcomplex *ef, floatcomplex *b, integer *ldb, floatcomplex 
	*x, integer *ldx, floatreal *ferr, floatreal *berr, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int cptsv_(integer *n, integer *nrhs, floatreal *d__, floatcomplex *e, 
	floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cptsvx_(char *fact, integer *n, integer *nrhs, floatreal *d__, 
	 floatcomplex *e, floatreal *df, floatcomplex *ef, floatcomplex *b, integer *ldb, floatcomplex 
	*x, integer *ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, floatcomplex *work, 
	floatreal *rwork, integer *info);

/* Subroutine */ int cpttrf_(integer *n, floatreal *d__, floatcomplex *e, integer *info);

/* Subroutine */ int cpttrs_(char *uplo, integer *n, integer *nrhs, floatreal *d__, 
	 floatcomplex *e, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cptts2_(integer *iuplo, integer *n, integer *nrhs, floatreal *
	d__, floatcomplex *e, floatcomplex *b, integer *ldb);

/* Subroutine */ int crot_(integer *n, floatcomplex *cx, integer *incx, floatcomplex *
	cy, integer *incy, floatreal *c__, floatcomplex *s);

/* Subroutine */ int cspcon_(char *uplo, integer *n, floatcomplex *ap, integer *
	ipiv, floatreal *anorm, floatreal *rcond, floatcomplex *work, integer *info);

/* Subroutine */ int cspmv_(char *uplo, integer *n, floatcomplex *alpha, floatcomplex *
	ap, floatcomplex *x, integer *incx, floatcomplex *beta, floatcomplex *y, integer *
	incy);

/* Subroutine */ int cspr_(char *uplo, integer *n, floatcomplex *alpha, floatcomplex *x, 
	 integer *incx, floatcomplex *ap);

/* Subroutine */ int csprfs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	ap, floatcomplex *afp, integer *ipiv, floatcomplex *b, integer *ldb, floatcomplex *x, 
	 integer *ldx, floatreal *ferr, floatreal *berr, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int cspsv_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	ap, integer *ipiv, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int cspsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatcomplex *ap, floatcomplex *afp, integer *ipiv, floatcomplex *b, integer *
	ldb, floatcomplex *x, integer *ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int csptrf_(char *uplo, integer *n, floatcomplex *ap, integer *
	ipiv, integer *info);

/* Subroutine */ int csptri_(char *uplo, integer *n, floatcomplex *ap, integer *
	ipiv, floatcomplex *work, integer *info);

/* Subroutine */ int csptrs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	ap, integer *ipiv, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int csrscl_(integer *n, floatreal *sa, floatcomplex *sx, integer *incx);

/* Subroutine */ int cstedc_(char *compz, integer *n, floatreal *d__, floatreal *e, 
	floatcomplex *z__, integer *ldz, floatcomplex *work, integer *lwork, floatreal *
	rwork, integer *lrwork, integer *iwork, integer *liwork, integer *
	info);

/* Subroutine */ int cstegr_(char *jobz, char *range, integer *n, floatreal *d__, 
	floatreal *e, floatreal *vl, floatreal *vu, integer *il, integer *iu, floatreal *abstol, 
	integer *m, floatreal *w, floatcomplex *z__, integer *ldz, integer *isuppz, 
	floatreal *work, integer *lwork, integer *iwork, integer *liwork, integer *
	info);

/* Subroutine */ int cstein_(integer *n, floatreal *d__, floatreal *e, integer *m, floatreal 
	*w, integer *iblock, integer *isplit, floatcomplex *z__, integer *ldz, 
	floatreal *work, integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int cstemr_(char *jobz, char *range, integer *n, floatreal *d__, 
	floatreal *e, floatreal *vl, floatreal *vu, integer *il, integer *iu, integer *m, 
	floatreal *w, floatcomplex *z__, integer *ldz, integer *nzc, integer *isuppz, 
	logical *tryrac, floatreal *work, integer *lwork, integer *iwork, integer *
	liwork, integer *info);

/* Subroutine */ int csteqr_(char *compz, integer *n, floatreal *d__, floatreal *e, 
	floatcomplex *z__, integer *ldz, floatreal *work, integer *info);

/* Subroutine */ int csycon_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, floatreal *anorm, floatreal *rcond, floatcomplex *work, integer *
	info);

/* Subroutine */ int csyequb_(char *uplo, integer *n, floatcomplex *a, integer *
	lda, floatreal *s, floatreal *scond, floatreal *amax, floatcomplex *work, integer *info);

/* Subroutine */ int csymv_(char *uplo, integer *n, floatcomplex *alpha, floatcomplex *
	a, integer *lda, floatcomplex *x, integer *incx, floatcomplex *beta, floatcomplex *y, 
	 integer *incy);

/* Subroutine */ int csyr_(char *uplo, integer *n, floatcomplex *alpha, floatcomplex *x, 
	 integer *incx, floatcomplex *a, integer *lda);

/* Subroutine */ int csyrfs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, floatcomplex *af, integer *ldaf, integer *ipiv, floatcomplex *
	b, integer *ldb, floatcomplex *x, integer *ldx, floatreal *ferr, floatreal *berr, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int csyrfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, integer *
	ipiv, floatreal *s, floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, 
	floatreal *rcond, floatreal *berr, integer *n_err_bnds__, floatreal *err_bnds_norm__, 
	 floatreal *err_bnds_comp__, integer *nparams, floatreal *params, floatcomplex *work, 
	 floatreal *rwork, integer *info);

/* Subroutine */ int csysv_(char *uplo, integer *n, integer *nrhs, floatcomplex *a, 
	 integer *lda, integer *ipiv, floatcomplex *b, integer *ldb, floatcomplex *work, 
	 integer *lwork, integer *info);

/* Subroutine */ int csysvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, integer *
	ipiv, floatcomplex *b, integer *ldb, floatcomplex *x, integer *ldx, floatreal *rcond, 
	 floatreal *ferr, floatreal *berr, floatcomplex *work, integer *lwork, floatreal *rwork, 
	integer *info);

/* Subroutine */ int csysvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatcomplex *a, integer *lda, floatcomplex *af, integer *ldaf, integer *
	ipiv, char *equed, floatreal *s, floatcomplex *b, integer *ldb, floatcomplex *x, 
	integer *ldx, floatreal *rcond, floatreal *rpvgrw, floatreal *berr, integer *
	n_err_bnds__, floatreal *err_bnds_norm__, floatreal *err_bnds_comp__, integer *
	nparams, floatreal *params, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int csytf2_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, integer *info);

/* Subroutine */ int csytrf_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int csytri_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 integer *ipiv, floatcomplex *work, integer *info);

/* Subroutine */ int csytrs_(char *uplo, integer *n, integer *nrhs, floatcomplex *
	a, integer *lda, integer *ipiv, floatcomplex *b, integer *ldb, integer *
	info);

/* Subroutine */ int ctbcon_(char *norm, char *uplo, char *diag, integer *n, 
	integer *kd, floatcomplex *ab, integer *ldab, floatreal *rcond, floatcomplex *work, 
	floatreal *rwork, integer *info);

/* Subroutine */ int ctbrfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *kd, integer *nrhs, floatcomplex *ab, integer *ldab, floatcomplex *b, 
	integer *ldb, floatcomplex *x, integer *ldx, floatreal *ferr, floatreal *berr, 
	floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int ctbtrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *kd, integer *nrhs, floatcomplex *ab, integer *ldab, floatcomplex *b, 
	integer *ldb, integer *info);

/* Subroutine */ int ctfsm_(char *transr, char *side, char *uplo, char *trans, 
	 char *diag, integer *m, integer *n, floatcomplex *alpha, floatcomplex *a, 
	floatcomplex *b, integer *ldb);

/* Subroutine */ int ctftri_(char *transr, char *uplo, char *diag, integer *n, 
	 floatcomplex *a, integer *info);

/* Subroutine */ int ctfttp_(char *transr, char *uplo, integer *n, floatcomplex *
	arf, floatcomplex *ap, integer *info);

/* Subroutine */ int ctfttr_(char *transr, char *uplo, integer *n, floatcomplex *
	arf, floatcomplex *a, integer *lda, integer *info);

/* Subroutine */ int ctgevc_(char *side, char *howmny, logical *select, 
	integer *n, floatcomplex *s, integer *lds, floatcomplex *p, integer *ldp, 
	floatcomplex *vl, integer *ldvl, floatcomplex *vr, integer *ldvr, integer *mm, 
	integer *m, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int ctgex2_(logical *wantq, logical *wantz, integer *n, 
	floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, floatcomplex *q, 
	integer *ldq, floatcomplex *z__, integer *ldz, integer *j1, integer *info);

/* Subroutine */ int ctgexc_(logical *wantq, logical *wantz, integer *n, 
	floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, floatcomplex *q, 
	integer *ldq, floatcomplex *z__, integer *ldz, integer *ifst, integer *
	ilst, integer *info);

/* Subroutine */ int ctgsen_(integer *ijob, logical *wantq, logical *wantz, 
	logical *select, integer *n, floatcomplex *a, integer *lda, floatcomplex *b, 
	integer *ldb, floatcomplex *alpha, floatcomplex *beta, floatcomplex *q, integer *ldq, 
	 floatcomplex *z__, integer *ldz, integer *m, floatreal *pl, floatreal *pr, floatreal *
	dif, floatcomplex *work, integer *lwork, integer *iwork, integer *liwork, 
	integer *info);

/* Subroutine */ int ctgsja_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *p, integer *n, integer *k, integer *l, floatcomplex *a, integer *
	lda, floatcomplex *b, integer *ldb, floatreal *tola, floatreal *tolb, floatreal *alpha, 
	floatreal *beta, floatcomplex *u, integer *ldu, floatcomplex *v, integer *ldv, 
	floatcomplex *q, integer *ldq, floatcomplex *work, integer *ncycle, integer *
	info);

/* Subroutine */ int ctgsna_(char *job, char *howmny, logical *select, 
	integer *n, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	floatcomplex *vl, integer *ldvl, floatcomplex *vr, integer *ldvr, floatreal *s, floatreal 
	*dif, integer *mm, integer *m, floatcomplex *work, integer *lwork, integer 
	*iwork, integer *info);

/* Subroutine */ int ctgsy2_(char *trans, integer *ijob, integer *m, integer *
	n, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, floatcomplex *c__, 
	integer *ldc, floatcomplex *d__, integer *ldd, floatcomplex *e, integer *lde, 
	floatcomplex *f, integer *ldf, floatreal *scale, floatreal *rdsum, floatreal *rdscal, 
	integer *info);

/* Subroutine */ int ctgsyl_(char *trans, integer *ijob, integer *m, integer *
	n, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, floatcomplex *c__, 
	integer *ldc, floatcomplex *d__, integer *ldd, floatcomplex *e, integer *lde, 
	floatcomplex *f, integer *ldf, floatreal *scale, floatreal *dif, floatcomplex *work, 
	integer *lwork, integer *iwork, integer *info);

/* Subroutine */ int ctpcon_(char *norm, char *uplo, char *diag, integer *n, 
	floatcomplex *ap, floatreal *rcond, floatcomplex *work, floatreal *rwork, integer *info);

/* Subroutine */ int ctprfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, floatcomplex *ap, floatcomplex *b, integer *ldb, floatcomplex *x, 
	integer *ldx, floatreal *ferr, floatreal *berr, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int ctptri_(char *uplo, char *diag, integer *n, floatcomplex *ap, 
	integer *info);

/* Subroutine */ int ctptrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, floatcomplex *ap, floatcomplex *b, integer *ldb, integer *info);

/* Subroutine */ int ctpttf_(char *transr, char *uplo, integer *n, floatcomplex *
	ap, floatcomplex *arf, integer *info);

/* Subroutine */ int ctpttr_(char *uplo, integer *n, floatcomplex *ap, floatcomplex *a, 
	integer *lda, integer *info);

/* Subroutine */ int ctrcon_(char *norm, char *uplo, char *diag, integer *n, 
	floatcomplex *a, integer *lda, floatreal *rcond, floatcomplex *work, floatreal *rwork, 
	integer *info);

/* Subroutine */ int ctrevc_(char *side, char *howmny, logical *select, 
	integer *n, floatcomplex *t, integer *ldt, floatcomplex *vl, integer *ldvl, 
	floatcomplex *vr, integer *ldvr, integer *mm, integer *m, floatcomplex *work, 
	floatreal *rwork, integer *info);

/* Subroutine */ int ctrexc_(char *compq, integer *n, floatcomplex *t, integer *
	ldt, floatcomplex *q, integer *ldq, integer *ifst, integer *ilst, integer *
	info);

/* Subroutine */ int ctrrfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	floatcomplex *x, integer *ldx, floatreal *ferr, floatreal *berr, floatcomplex *work, floatreal 
	*rwork, integer *info);

/* Subroutine */ int ctrsen_(char *job, char *compq, logical *select, integer 
	*n, floatcomplex *t, integer *ldt, floatcomplex *q, integer *ldq, floatcomplex *w, 
	integer *m, floatreal *s, floatreal *sep, floatcomplex *work, integer *lwork, 
	integer *info);

/* Subroutine */ int ctrsna_(char *job, char *howmny, logical *select, 
	integer *n, floatcomplex *t, integer *ldt, floatcomplex *vl, integer *ldvl, 
	floatcomplex *vr, integer *ldvr, floatreal *s, floatreal *sep, integer *mm, integer *
	m, floatcomplex *work, integer *ldwork, floatreal *rwork, integer *info);

/* Subroutine */ int ctrsyl_(char *trana, char *tranb, integer *isgn, integer 
	*m, integer *n, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	floatcomplex *c__, integer *ldc, floatreal *scale, integer *info);

/* Subroutine */ int ctrti2_(char *uplo, char *diag, integer *n, floatcomplex *a, 
	integer *lda, integer *info);

/* Subroutine */ int ctrtri_(char *uplo, char *diag, integer *n, floatcomplex *a, 
	integer *lda, integer *info);

/* Subroutine */ int ctrtrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, floatcomplex *a, integer *lda, floatcomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int ctrttf_(char *transr, char *uplo, integer *n, floatcomplex *a, 
	 integer *lda, floatcomplex *arf, integer *info);

/* Subroutine */ int ctrttp_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *ap, integer *info);

/* Subroutine */ int ctzrqf_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, integer *info);

/* Subroutine */ int ctzrzf_(integer *m, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cung2l_(integer *m, integer *n, integer *k, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *work, integer *info);

/* Subroutine */ int cung2r_(integer *m, integer *n, integer *k, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *work, integer *info);

/* Subroutine */ int cungbr_(char *vect, integer *m, integer *n, integer *k, 
	floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int cunghr_(integer *n, integer *ilo, integer *ihi, floatcomplex *
	a, integer *lda, floatcomplex *tau, floatcomplex *work, integer *lwork, integer 
	*info);

/* Subroutine */ int cungl2_(integer *m, integer *n, integer *k, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *work, integer *info);

/* Subroutine */ int cunglq_(integer *m, integer *n, integer *k, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *work, integer *lwork, integer *
	info);

/* Subroutine */ int cungql_(integer *m, integer *n, integer *k, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *work, integer *lwork, integer *
	info);

/* Subroutine */ int cungqr_(integer *m, integer *n, integer *k, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *work, integer *lwork, integer *
	info);

/* Subroutine */ int cungr2_(integer *m, integer *n, integer *k, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *work, integer *info);

/* Subroutine */ int cungrq_(integer *m, integer *n, integer *k, floatcomplex *a, 
	integer *lda, floatcomplex *tau, floatcomplex *work, integer *lwork, integer *
	info);

/* Subroutine */ int cungtr_(char *uplo, integer *n, floatcomplex *a, integer *lda, 
	 floatcomplex *tau, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cunm2l_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *c__, 
	integer *ldc, floatcomplex *work, integer *info);

/* Subroutine */ int cunm2r_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *c__, 
	integer *ldc, floatcomplex *work, integer *info);

/* Subroutine */ int cunmbr_(char *vect, char *side, char *trans, integer *m, 
	integer *n, integer *k, floatcomplex *a, integer *lda, floatcomplex *tau, 
	floatcomplex *c__, integer *ldc, floatcomplex *work, integer *lwork, integer *
	info);

/* Subroutine */ int cunmhr_(char *side, char *trans, integer *m, integer *n, 
	integer *ilo, integer *ihi, floatcomplex *a, integer *lda, floatcomplex *tau, 
	floatcomplex *c__, integer *ldc, floatcomplex *work, integer *lwork, integer *
	info);

/* Subroutine */ int cunml2_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *c__, 
	integer *ldc, floatcomplex *work, integer *info);

/* Subroutine */ int cunmlq_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *c__, 
	integer *ldc, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cunmql_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *c__, 
	integer *ldc, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cunmqr_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *c__, 
	integer *ldc, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cunmr2_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *c__, 
	integer *ldc, floatcomplex *work, integer *info);

/* Subroutine */ int cunmr3_(char *side, char *trans, integer *m, integer *n, 
	integer *k, integer *l, floatcomplex *a, integer *lda, floatcomplex *tau, 
	floatcomplex *c__, integer *ldc, floatcomplex *work, integer *info);

/* Subroutine */ int cunmrq_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *c__, 
	integer *ldc, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cunmrz_(char *side, char *trans, integer *m, integer *n, 
	integer *k, integer *l, floatcomplex *a, integer *lda, floatcomplex *tau, 
	floatcomplex *c__, integer *ldc, floatcomplex *work, integer *lwork, integer *
	info);

/* Subroutine */ int cunmtr_(char *side, char *uplo, char *trans, integer *m, 
	integer *n, floatcomplex *a, integer *lda, floatcomplex *tau, floatcomplex *c__, 
	integer *ldc, floatcomplex *work, integer *lwork, integer *info);

/* Subroutine */ int cupgtr_(char *uplo, integer *n, floatcomplex *ap, floatcomplex *
	tau, floatcomplex *q, integer *ldq, floatcomplex *work, integer *info);

/* Subroutine */ int cupmtr_(char *side, char *uplo, char *trans, integer *m, 
	integer *n, floatcomplex *ap, floatcomplex *tau, floatcomplex *c__, integer *ldc, 
	floatcomplex *work, integer *info);

/* Subroutine */ int dbdsdc_(char *uplo, char *compq, integer *n, doublereal *
	d__, doublereal *e, doublereal *u, integer *ldu, doublereal *vt, 
	integer *ldvt, doublereal *q, integer *iq, doublereal *work, integer *
	iwork, integer *info);

/* Subroutine */ int dbdsqr_(char *uplo, integer *n, integer *ncvt, integer *
	nru, integer *ncc, doublereal *d__, doublereal *e, doublereal *vt, 
	integer *ldvt, doublereal *u, integer *ldu, doublereal *c__, integer *
	ldc, doublereal *work, integer *info);

/* Subroutine */ int ddisna_(char *job, integer *m, integer *n, doublereal *
	d__, doublereal *sep, integer *info);

/* Subroutine */ int dgbbrd_(char *vect, integer *m, integer *n, integer *ncc, 
	 integer *kl, integer *ku, doublereal *ab, integer *ldab, doublereal *
	d__, doublereal *e, doublereal *q, integer *ldq, doublereal *pt, 
	integer *ldpt, doublereal *c__, integer *ldc, doublereal *work, 
	integer *info);

/* Subroutine */ int dgbcon_(char *norm, integer *n, integer *kl, integer *ku, 
	 doublereal *ab, integer *ldab, integer *ipiv, doublereal *anorm, 
	doublereal *rcond, doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dgbequ_(integer *m, integer *n, integer *kl, integer *ku, 
	 doublereal *ab, integer *ldab, doublereal *r__, doublereal *c__, 
	doublereal *rowcnd, doublereal *colcnd, doublereal *amax, integer *
	info);

/* Subroutine */ int dgbequb_(integer *m, integer *n, integer *kl, integer *
	ku, doublereal *ab, integer *ldab, doublereal *r__, doublereal *c__, 
	doublereal *rowcnd, doublereal *colcnd, doublereal *amax, integer *
	info);

/* Subroutine */ int dgbrfs_(char *trans, integer *n, integer *kl, integer *
	ku, integer *nrhs, doublereal *ab, integer *ldab, doublereal *afb, 
	integer *ldafb, integer *ipiv, doublereal *b, integer *ldb, 
	doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dgbrfsx_(char *trans, char *equed, integer *n, integer *
	kl, integer *ku, integer *nrhs, doublereal *ab, integer *ldab, 
	doublereal *afb, integer *ldafb, integer *ipiv, doublereal *r__, 
	doublereal *c__, doublereal *b, integer *ldb, doublereal *x, integer *
	ldx, doublereal *rcond, doublereal *berr, integer *n_err_bnds__, 
	doublereal *err_bnds_norm__, doublereal *err_bnds_comp__, integer *
	nparams, doublereal *params, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dgbsv_(integer *n, integer *kl, integer *ku, integer *
	nrhs, doublereal *ab, integer *ldab, integer *ipiv, doublereal *b, 
	integer *ldb, integer *info);

/* Subroutine */ int dgbsvx_(char *fact, char *trans, integer *n, integer *kl, 
	 integer *ku, integer *nrhs, doublereal *ab, integer *ldab, 
	doublereal *afb, integer *ldafb, integer *ipiv, char *equed, 
	doublereal *r__, doublereal *c__, doublereal *b, integer *ldb, 
	doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, 
	doublereal *berr, doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dgbsvxx_(char *fact, char *trans, integer *n, integer *
	kl, integer *ku, integer *nrhs, doublereal *ab, integer *ldab, 
	doublereal *afb, integer *ldafb, integer *ipiv, char *equed, 
	doublereal *r__, doublereal *c__, doublereal *b, integer *ldb, 
	doublereal *x, integer *ldx, doublereal *rcond, doublereal *rpvgrw, 
	doublereal *berr, integer *n_err_bnds__, doublereal *err_bnds_norm__, 
	doublereal *err_bnds_comp__, integer *nparams, doublereal *params, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dgbtf2_(integer *m, integer *n, integer *kl, integer *ku, 
	 doublereal *ab, integer *ldab, integer *ipiv, integer *info);

/* Subroutine */ int dgbtrf_(integer *m, integer *n, integer *kl, integer *ku, 
	 doublereal *ab, integer *ldab, integer *ipiv, integer *info);

/* Subroutine */ int dgbtrs_(char *trans, integer *n, integer *kl, integer *
	ku, integer *nrhs, doublereal *ab, integer *ldab, integer *ipiv, 
	doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dgebak_(char *job, char *side, integer *n, integer *ilo, 
	integer *ihi, doublereal *scale, integer *m, doublereal *v, integer *
	ldv, integer *info);

/* Subroutine */ int dgebal_(char *job, integer *n, doublereal *a, integer *
	lda, integer *ilo, integer *ihi, doublereal *scale, integer *info);

/* Subroutine */ int dgebd2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *
	taup, doublereal *work, integer *info);

/* Subroutine */ int dgebrd_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *
	taup, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dgecon_(char *norm, integer *n, doublereal *a, integer *
	lda, doublereal *anorm, doublereal *rcond, doublereal *work, integer *
	iwork, integer *info);

/* Subroutine */ int dgeequ_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal 
	*colcnd, doublereal *amax, integer *info);

/* Subroutine */ int dgeequb_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal 
	*colcnd, doublereal *amax, integer *info);

/* Subroutine */ int dgees_(char *jobvs, char *sort, L_fp select, integer *n, 
	doublereal *a, integer *lda, integer *sdim, doublereal *wr, 
	doublereal *wi, doublereal *vs, integer *ldvs, doublereal *work, 
	integer *lwork, logical *bwork, integer *info);

/* Subroutine */ int dgeesx_(char *jobvs, char *sort, L_fp select, char *
	sense, integer *n, doublereal *a, integer *lda, integer *sdim, 
	doublereal *wr, doublereal *wi, doublereal *vs, integer *ldvs, 
	doublereal *rconde, doublereal *rcondv, doublereal *work, integer *
	lwork, integer *iwork, integer *liwork, logical *bwork, integer *info);

/* Subroutine */ int dgeev_(char *jobvl, char *jobvr, integer *n, doublereal *
	a, integer *lda, doublereal *wr, doublereal *wi, doublereal *vl, 
	integer *ldvl, doublereal *vr, integer *ldvr, doublereal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int dgeevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, doublereal *a, integer *lda, doublereal *wr, 
	doublereal *wi, doublereal *vl, integer *ldvl, doublereal *vr, 
	integer *ldvr, integer *ilo, integer *ihi, doublereal *scale, 
	doublereal *abnrm, doublereal *rconde, doublereal *rcondv, doublereal 
	*work, integer *lwork, integer *iwork, integer *info);

/* Subroutine */ int dgegs_(char *jobvsl, char *jobvsr, integer *n, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *
	alphar, doublereal *alphai, doublereal *beta, doublereal *vsl, 
	integer *ldvsl, doublereal *vsr, integer *ldvsr, doublereal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int dgegv_(char *jobvl, char *jobvr, integer *n, doublereal *
	a, integer *lda, doublereal *b, integer *ldb, doublereal *alphar, 
	doublereal *alphai, doublereal *beta, doublereal *vl, integer *ldvl, 
	doublereal *vr, integer *ldvr, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dgehd2_(integer *n, integer *ilo, integer *ihi, 
	doublereal *a, integer *lda, doublereal *tau, doublereal *work, 
	integer *info);

/* Subroutine */ int dgehrd_(integer *n, integer *ilo, integer *ihi, 
	doublereal *a, integer *lda, doublereal *tau, doublereal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int dgejsv_(char *joba, char *jobu, char *jobv, char *jobr, 
	char *jobt, char *jobp, integer *m, integer *n, doublereal *a, 
	integer *lda, doublereal *sva, doublereal *u, integer *ldu, 
	doublereal *v, integer *ldv, doublereal *work, integer *lwork, 
	integer *iwork, integer *info);

/* Subroutine */ int dgelq2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *info);

/* Subroutine */ int dgelqf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dgels_(char *trans, integer *m, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dgelsd_(integer *m, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *
	s, doublereal *rcond, integer *rank, doublereal *work, integer *lwork, 
	 integer *iwork, integer *info);

/* Subroutine */ int dgelss_(integer *m, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *
	s, doublereal *rcond, integer *rank, doublereal *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int dgelsx_(integer *m, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *
	jpvt, doublereal *rcond, integer *rank, doublereal *work, integer *
	info);

/* Subroutine */ int dgelsy_(integer *m, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *
	jpvt, doublereal *rcond, integer *rank, doublereal *work, integer *
	lwork, integer *info);

/* Subroutine */ int dgeql2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *info);

/* Subroutine */ int dgeqlf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dgeqp3_(integer *m, integer *n, doublereal *a, integer *
	lda, integer *jpvt, doublereal *tau, doublereal *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int dgeqpf_(integer *m, integer *n, doublereal *a, integer *
	lda, integer *jpvt, doublereal *tau, doublereal *work, integer *info);

/* Subroutine */ int dgeqr2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *info);

/* Subroutine */ int dgeqrf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dgerfs_(char *trans, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *af, integer *ldaf, integer *
	ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, 
	doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dgerfsx_(char *trans, char *equed, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	integer *ipiv, doublereal *r__, doublereal *c__, doublereal *b, 
	integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, 
	doublereal *berr, integer *n_err_bnds__, doublereal *err_bnds_norm__, 
	doublereal *err_bnds_comp__, integer *nparams, doublereal *params, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dgerq2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *info);

/* Subroutine */ int dgerqf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dgesc2_(integer *n, doublereal *a, integer *lda, 
	doublereal *rhs, integer *ipiv, integer *jpiv, doublereal *scale);

/* Subroutine */ int dgesdd_(char *jobz, integer *m, integer *n, doublereal *
	a, integer *lda, doublereal *s, doublereal *u, integer *ldu, 
	doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
	integer *iwork, integer *info);

/* Subroutine */ int dgesv_(integer *n, integer *nrhs, doublereal *a, integer 
	*lda, integer *ipiv, doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
	ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dgesvj_(char *joba, char *jobu, char *jobv, integer *m, 
	integer *n, doublereal *a, integer *lda, doublereal *sva, integer *mv, 
	 doublereal *v, integer *ldv, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dgesvx_(char *fact, char *trans, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	integer *ipiv, char *equed, doublereal *r__, doublereal *c__, 
	doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *
	rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *
	iwork, integer *info);

/* Subroutine */ int dgesvxx_(char *fact, char *trans, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	integer *ipiv, char *equed, doublereal *r__, doublereal *c__, 
	doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *
	rcond, doublereal *rpvgrw, doublereal *berr, integer *n_err_bnds__, 
	doublereal *err_bnds_norm__, doublereal *err_bnds_comp__, integer *
	nparams, doublereal *params, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dgetc2_(integer *n, doublereal *a, integer *lda, integer 
	*ipiv, integer *jpiv, integer *info);

/* Subroutine */ int dgetf2_(integer *m, integer *n, doublereal *a, integer *
	lda, integer *ipiv, integer *info);

/* Subroutine */ int dgetrf_(integer *m, integer *n, doublereal *a, integer *
	lda, integer *ipiv, integer *info);

/* Subroutine */ int dgetri_(integer *n, doublereal *a, integer *lda, integer 
	*ipiv, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dgetrs_(char *trans, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, integer *ipiv, doublereal *b, integer *
	ldb, integer *info);

/* Subroutine */ int dggbak_(char *job, char *side, integer *n, integer *ilo, 
	integer *ihi, doublereal *lscale, doublereal *rscale, integer *m, 
	doublereal *v, integer *ldv, integer *info);

/* Subroutine */ int dggbal_(char *job, integer *n, doublereal *a, integer *
	lda, doublereal *b, integer *ldb, integer *ilo, integer *ihi, 
	doublereal *lscale, doublereal *rscale, doublereal *work, integer *
	info);

/* Subroutine */ int dgges_(char *jobvsl, char *jobvsr, char *sort, L_fp 
	selctg, integer *n, doublereal *a, integer *lda, doublereal *b, 
	integer *ldb, integer *sdim, doublereal *alphar, doublereal *alphai, 
	doublereal *beta, doublereal *vsl, integer *ldvsl, doublereal *vsr, 
	integer *ldvsr, doublereal *work, integer *lwork, logical *bwork, 
	integer *info);

/* Subroutine */ int dggesx_(char *jobvsl, char *jobvsr, char *sort, L_fp 
	selctg, char *sense, integer *n, doublereal *a, integer *lda, 
	doublereal *b, integer *ldb, integer *sdim, doublereal *alphar, 
	doublereal *alphai, doublereal *beta, doublereal *vsl, integer *ldvsl, 
	 doublereal *vsr, integer *ldvsr, doublereal *rconde, doublereal *
	rcondv, doublereal *work, integer *lwork, integer *iwork, integer *
	liwork, logical *bwork, integer *info);

/* Subroutine */ int dggev_(char *jobvl, char *jobvr, integer *n, doublereal *
	a, integer *lda, doublereal *b, integer *ldb, doublereal *alphar, 
	doublereal *alphai, doublereal *beta, doublereal *vl, integer *ldvl, 
	doublereal *vr, integer *ldvr, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dggevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, doublereal *a, integer *lda, doublereal *b, 
	integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *
	beta, doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, 
	integer *ilo, integer *ihi, doublereal *lscale, doublereal *rscale, 
	doublereal *abnrm, doublereal *bbnrm, doublereal *rconde, doublereal *
	rcondv, doublereal *work, integer *lwork, integer *iwork, logical *
	bwork, integer *info);

/* Subroutine */ int dggglm_(integer *n, integer *m, integer *p, doublereal *
	a, integer *lda, doublereal *b, integer *ldb, doublereal *d__, 
	doublereal *x, doublereal *y, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dgghrd_(char *compq, char *compz, integer *n, integer *
	ilo, integer *ihi, doublereal *a, integer *lda, doublereal *b, 
	integer *ldb, doublereal *q, integer *ldq, doublereal *z__, integer *
	ldz, integer *info);

/* Subroutine */ int dgglse_(integer *m, integer *n, integer *p, doublereal *
	a, integer *lda, doublereal *b, integer *ldb, doublereal *c__, 
	doublereal *d__, doublereal *x, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dggqrf_(integer *n, integer *m, integer *p, doublereal *
	a, integer *lda, doublereal *taua, doublereal *b, integer *ldb, 
	doublereal *taub, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dggrqf_(integer *m, integer *p, integer *n, doublereal *
	a, integer *lda, doublereal *taua, doublereal *b, integer *ldb, 
	doublereal *taub, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dggsvd_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *n, integer *p, integer *k, integer *l, doublereal *a, 
	integer *lda, doublereal *b, integer *ldb, doublereal *alpha, 
	doublereal *beta, doublereal *u, integer *ldu, doublereal *v, integer 
	*ldv, doublereal *q, integer *ldq, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dggsvp_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *p, integer *n, doublereal *a, integer *lda, doublereal *b, 
	integer *ldb, doublereal *tola, doublereal *tolb, integer *k, integer 
	*l, doublereal *u, integer *ldu, doublereal *v, integer *ldv, 
	doublereal *q, integer *ldq, integer *iwork, doublereal *tau, 
	doublereal *work, integer *info);

/* Subroutine */ int dgsvj0_(char *jobv, integer *m, integer *n, doublereal *
	a, integer *lda, doublereal *d__, doublereal *sva, integer *mv, 
	doublereal *v, integer *ldv, doublereal *eps, doublereal *sfmin, 
	doublereal *tol, integer *nsweep, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dgsvj1_(char *jobv, integer *m, integer *n, integer *n1, 
	doublereal *a, integer *lda, doublereal *d__, doublereal *sva, 
	integer *mv, doublereal *v, integer *ldv, doublereal *eps, doublereal 
	*sfmin, doublereal *tol, integer *nsweep, doublereal *work, integer *
	lwork, integer *info);

/* Subroutine */ int dgtcon_(char *norm, integer *n, doublereal *dl, 
	doublereal *d__, doublereal *du, doublereal *du2, integer *ipiv, 
	doublereal *anorm, doublereal *rcond, doublereal *work, integer *
	iwork, integer *info);

/* Subroutine */ int dgtrfs_(char *trans, integer *n, integer *nrhs, 
	doublereal *dl, doublereal *d__, doublereal *du, doublereal *dlf, 
	doublereal *df, doublereal *duf, doublereal *du2, integer *ipiv, 
	doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *
	ferr, doublereal *berr, doublereal *work, integer *iwork, integer *
	info);

/* Subroutine */ int dgtsv_(integer *n, integer *nrhs, doublereal *dl, 
	doublereal *d__, doublereal *du, doublereal *b, integer *ldb, integer 
	*info);

/* Subroutine */ int dgtsvx_(char *fact, char *trans, integer *n, integer *
	nrhs, doublereal *dl, doublereal *d__, doublereal *du, doublereal *
	dlf, doublereal *df, doublereal *duf, doublereal *du2, integer *ipiv, 
	doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *
	rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *
	iwork, integer *info);

/* Subroutine */ int dgttrf_(integer *n, doublereal *dl, doublereal *d__, 
	doublereal *du, doublereal *du2, integer *ipiv, integer *info);

/* Subroutine */ int dgttrs_(char *trans, integer *n, integer *nrhs, 
	doublereal *dl, doublereal *d__, doublereal *du, doublereal *du2, 
	integer *ipiv, doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dgtts2_(integer *itrans, integer *n, integer *nrhs, 
	doublereal *dl, doublereal *d__, doublereal *du, doublereal *du2, 
	integer *ipiv, doublereal *b, integer *ldb);

/* Subroutine */ int dhgeqz_(char *job, char *compq, char *compz, integer *n, 
	integer *ilo, integer *ihi, doublereal *h__, integer *ldh, doublereal 
	*t, integer *ldt, doublereal *alphar, doublereal *alphai, doublereal *
	beta, doublereal *q, integer *ldq, doublereal *z__, integer *ldz, 
	doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dhsein_(char *side, char *eigsrc, char *initv, logical *
	select, integer *n, doublereal *h__, integer *ldh, doublereal *wr, 
	doublereal *wi, doublereal *vl, integer *ldvl, doublereal *vr, 
	integer *ldvr, integer *mm, integer *m, doublereal *work, integer *
	ifaill, integer *ifailr, integer *info);

/* Subroutine */ int dhseqr_(char *job, char *compz, integer *n, integer *ilo, 
	 integer *ihi, doublereal *h__, integer *ldh, doublereal *wr, 
	doublereal *wi, doublereal *z__, integer *ldz, doublereal *work, 
	integer *lwork, integer *info);

logical disnan_(doublereal *din);

/* Subroutine */ int dla_gbamv__(integer *trans, integer *m, integer *n, 
	integer *kl, integer *ku, doublereal *alpha, doublereal *ab, integer *
	ldab, doublereal *x, integer *incx, doublereal *beta, doublereal *y, 
	integer *incy);

doublereal dla_gbrcond__(char *trans, integer *n, integer *kl, integer *ku, 
	doublereal *ab, integer *ldab, doublereal *afb, integer *ldafb, 
	integer *ipiv, integer *cmode, doublereal *c__, integer *info, 
	doublereal *work, integer *iwork, ftnlen trans_len);

/* Subroutine */ int dla_gbrfsx_extended__(integer *prec_type__, integer *
	trans_type__, integer *n, integer *kl, integer *ku, integer *nrhs, 
	doublereal *ab, integer *ldab, doublereal *afb, integer *ldafb, 
	integer *ipiv, logical *colequ, doublereal *c__, doublereal *b, 
	integer *ldb, doublereal *y, integer *ldy, doublereal *berr_out__, 
	integer *n_norms__, doublereal *errs_n__, doublereal *errs_c__, 
	doublereal *res, doublereal *ayb, doublereal *dy, doublereal *
	y_tail__, doublereal *rcond, integer *ithresh, doublereal *rthresh, 
	doublereal *dz_ub__, logical *ignore_cwise__, integer *info);

doublereal dla_gbrpvgrw__(integer *n, integer *kl, integer *ku, integer *
	ncols, doublereal *ab, integer *ldab, doublereal *afb, integer *ldafb);

/* Subroutine */ int dla_geamv__(integer *trans, integer *m, integer *n, 
	doublereal *alpha, doublereal *a, integer *lda, doublereal *x, 
	integer *incx, doublereal *beta, doublereal *y, integer *incy);

doublereal dla_gercond__(char *trans, integer *n, doublereal *a, integer *lda,
	 doublereal *af, integer *ldaf, integer *ipiv, integer *cmode, 
	doublereal *c__, integer *info, doublereal *work, integer *iwork, 
	ftnlen trans_len);

/* Subroutine */ int dla_gerfsx_extended__(integer *prec_type__, integer *
	trans_type__, integer *n, integer *nrhs, doublereal *a, integer *lda, 
	doublereal *af, integer *ldaf, integer *ipiv, logical *colequ, 
	doublereal *c__, doublereal *b, integer *ldb, doublereal *y, integer *
	ldy, doublereal *berr_out__, integer *n_norms__, doublereal *errs_n__,
	 doublereal *errs_c__, doublereal *res, doublereal *ayb, doublereal *
	dy, doublereal *y_tail__, doublereal *rcond, integer *ithresh, 
	doublereal *rthresh, doublereal *dz_ub__, logical *ignore_cwise__, 
	integer *info);

/* Subroutine */ int dla_lin_berr__(integer *n, integer *nz, integer *nrhs, 
	doublereal *res, doublereal *ayb, doublereal *berr);

doublereal dla_porcond__(char *uplo, integer *n, doublereal *a, integer *lda, 
	doublereal *af, integer *ldaf, integer *cmode, doublereal *c__, 
	integer *info, doublereal *work, integer *iwork, ftnlen uplo_len);

/* Subroutine */ int dla_porfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *
	af, integer *ldaf, logical *colequ, doublereal *c__, doublereal *b, 
	integer *ldb, doublereal *y, integer *ldy, doublereal *berr_out__, 
	integer *n_norms__, doublereal *errs_n__, doublereal *errs_c__, 
	doublereal *res, doublereal *ayb, doublereal *dy, doublereal *
	y_tail__, doublereal *rcond, integer *ithresh, doublereal *rthresh, 
	doublereal *dz_ub__, logical *ignore_cwise__, integer *info, ftnlen 
	uplo_len);

doublereal dla_porpvgrw__(char *uplo, integer *ncols, doublereal *a, integer *
	lda, doublereal *af, integer *ldaf, doublereal *work, ftnlen uplo_len);

doublereal dla_rpvgrw__(integer *n, integer *ncols, doublereal *a, integer *
	lda, doublereal *af, integer *ldaf);

/* Subroutine */ int dla_syamv__(integer *uplo, integer *n, doublereal *alpha,
	 doublereal *a, integer *lda, doublereal *x, integer *incx, 
	doublereal *beta, doublereal *y, integer *incy);

doublereal dla_syrcond__(char *uplo, integer *n, doublereal *a, integer *lda, 
	doublereal *af, integer *ldaf, integer *ipiv, integer *cmode, 
	doublereal *c__, integer *info, doublereal *work, integer *iwork, 
	ftnlen uplo_len);

/* Subroutine */ int dla_syrfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *
	af, integer *ldaf, integer *ipiv, logical *colequ, doublereal *c__, 
	doublereal *b, integer *ldb, doublereal *y, integer *ldy, doublereal *
	berr_out__, integer *n_norms__, doublereal *errs_n__, doublereal *
	errs_c__, doublereal *res, doublereal *ayb, doublereal *dy, 
	doublereal *y_tail__, doublereal *rcond, integer *ithresh, doublereal 
	*rthresh, doublereal *dz_ub__, logical *ignore_cwise__, integer *info,
	 ftnlen uplo_len);

doublereal dla_syrpvgrw__(char *uplo, integer *n, integer *info, doublereal *
	a, integer *lda, doublereal *af, integer *ldaf, integer *ipiv, 
	doublereal *work, ftnlen uplo_len);

/* Subroutine */ int dla_wwaddw__(integer *n, doublereal *x, doublereal *y, 
	doublereal *w);

/* Subroutine */ int dlabad_(doublereal *small, doublereal *large);

/* Subroutine */ int dlabrd_(integer *m, integer *n, integer *nb, doublereal *
	a, integer *lda, doublereal *d__, doublereal *e, doublereal *tauq, 
	doublereal *taup, doublereal *x, integer *ldx, doublereal *y, integer 
	*ldy);

/* Subroutine */ int dlacn2_(integer *n, doublereal *v, doublereal *x, 
	integer *isgn, doublereal *est, integer *kase, integer *isave);

/* Subroutine */ int dlacon_(integer *n, doublereal *v, doublereal *x, 
	integer *isgn, doublereal *est, integer *kase);

/* Subroutine */ int dlacpy_(char *uplo, integer *m, integer *n, doublereal *
	a, integer *lda, doublereal *b, integer *ldb);

/* Subroutine */ int dladiv_(doublereal *a, doublereal *b, doublereal *c__, 
	doublereal *d__, doublereal *p, doublereal *q);

/* Subroutine */ int dlae2_(doublereal *a, doublereal *b, doublereal *c__, 
	doublereal *rt1, doublereal *rt2);

/* Subroutine */ int dlaebz_(integer *ijob, integer *nitmax, integer *n, 
	integer *mmax, integer *minp, integer *nbmin, doublereal *abstol, 
	doublereal *reltol, doublereal *pivmin, doublereal *d__, doublereal *
	e, doublereal *e2, integer *nval, doublereal *ab, doublereal *c__, 
	integer *mout, integer *nab, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dlaed0_(integer *icompq, integer *qsiz, integer *n, 
	doublereal *d__, doublereal *e, doublereal *q, integer *ldq, 
	doublereal *qstore, integer *ldqs, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dlaed1_(integer *n, doublereal *d__, doublereal *q, 
	integer *ldq, integer *indxq, doublereal *rho, integer *cutpnt, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dlaed2_(integer *k, integer *n, integer *n1, doublereal *
	d__, doublereal *q, integer *ldq, integer *indxq, doublereal *rho, 
	doublereal *z__, doublereal *dlamda, doublereal *w, doublereal *q2, 
	integer *indx, integer *indxc, integer *indxp, integer *coltyp, 
	integer *info);

/* Subroutine */ int dlaed3_(integer *k, integer *n, integer *n1, doublereal *
	d__, doublereal *q, integer *ldq, doublereal *rho, doublereal *dlamda, 
	 doublereal *q2, integer *indx, integer *ctot, doublereal *w, 
	doublereal *s, integer *info);

/* Subroutine */ int dlaed4_(integer *n, integer *i__, doublereal *d__, 
	doublereal *z__, doublereal *delta, doublereal *rho, doublereal *dlam, 
	 integer *info);

/* Subroutine */ int dlaed5_(integer *i__, doublereal *d__, doublereal *z__, 
	doublereal *delta, doublereal *rho, doublereal *dlam);

/* Subroutine */ int dlaed6_(integer *kniter, logical *orgati, doublereal *
	rho, doublereal *d__, doublereal *z__, doublereal *finit, doublereal *
	tau, integer *info);

/* Subroutine */ int dlaed7_(integer *icompq, integer *n, integer *qsiz, 
	integer *tlvls, integer *curlvl, integer *curpbm, doublereal *d__, 
	doublereal *q, integer *ldq, integer *indxq, doublereal *rho, integer 
	*cutpnt, doublereal *qstore, integer *qptr, integer *prmptr, integer *
	perm, integer *givptr, integer *givcol, doublereal *givnum, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dlaed8_(integer *icompq, integer *k, integer *n, integer 
	*qsiz, doublereal *d__, doublereal *q, integer *ldq, integer *indxq, 
	doublereal *rho, integer *cutpnt, doublereal *z__, doublereal *dlamda, 
	 doublereal *q2, integer *ldq2, doublereal *w, integer *perm, integer 
	*givptr, integer *givcol, doublereal *givnum, integer *indxp, integer 
	*indx, integer *info);

/* Subroutine */ int dlaed9_(integer *k, integer *kstart, integer *kstop, 
	integer *n, doublereal *d__, doublereal *q, integer *ldq, doublereal *
	rho, doublereal *dlamda, doublereal *w, doublereal *s, integer *lds, 
	integer *info);

/* Subroutine */ int dlaeda_(integer *n, integer *tlvls, integer *curlvl, 
	integer *curpbm, integer *prmptr, integer *perm, integer *givptr, 
	integer *givcol, doublereal *givnum, doublereal *q, integer *qptr, 
	doublereal *z__, doublereal *ztemp, integer *info);

/* Subroutine */ int dlaein_(logical *rightv, logical *noinit, integer *n, 
	doublereal *h__, integer *ldh, doublereal *wr, doublereal *wi, 
	doublereal *vr, doublereal *vi, doublereal *b, integer *ldb, 
	doublereal *work, doublereal *eps3, doublereal *smlnum, doublereal *
	bignum, integer *info);

/* Subroutine */ int dlaev2_(doublereal *a, doublereal *b, doublereal *c__, 
	doublereal *rt1, doublereal *rt2, doublereal *cs1, doublereal *sn1);

/* Subroutine */ int dlaexc_(logical *wantq, integer *n, doublereal *t, 
	integer *ldt, doublereal *q, integer *ldq, integer *j1, integer *n1, 
	integer *n2, doublereal *work, integer *info);

/* Subroutine */ int dlag2_(doublereal *a, integer *lda, doublereal *b, 
	integer *ldb, doublereal *safmin, doublereal *scale1, doublereal *
	scale2, doublereal *wr1, doublereal *wr2, doublereal *wi);

/* Subroutine */ int dlag2s_(integer *m, integer *n, doublereal *a, integer *
	lda, floatreal *sa, integer *ldsa, integer *info);

/* Subroutine */ int dlags2_(logical *upper, doublereal *a1, doublereal *a2, 
	doublereal *a3, doublereal *b1, doublereal *b2, doublereal *b3, 
	doublereal *csu, doublereal *snu, doublereal *csv, doublereal *snv, 
	doublereal *csq, doublereal *snq);

/* Subroutine */ int dlagtf_(integer *n, doublereal *a, doublereal *lambda, 
	doublereal *b, doublereal *c__, doublereal *tol, doublereal *d__, 
	integer *in, integer *info);

/* Subroutine */ int dlagtm_(char *trans, integer *n, integer *nrhs, 
	doublereal *alpha, doublereal *dl, doublereal *d__, doublereal *du, 
	doublereal *x, integer *ldx, doublereal *beta, doublereal *b, integer 
	*ldb);

/* Subroutine */ int dlagts_(integer *job, integer *n, doublereal *a, 
	doublereal *b, doublereal *c__, doublereal *d__, integer *in, 
	doublereal *y, doublereal *tol, integer *info);

/* Subroutine */ int dlagv2_(doublereal *a, integer *lda, doublereal *b, 
	integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *
	beta, doublereal *csl, doublereal *snl, doublereal *csr, doublereal *
	snr);

/* Subroutine */ int dlahqr_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, doublereal *h__, integer *ldh, doublereal 
	*wr, doublereal *wi, integer *iloz, integer *ihiz, doublereal *z__, 
	integer *ldz, integer *info);

/* Subroutine */ int dlahr2_(integer *n, integer *k, integer *nb, doublereal *
	a, integer *lda, doublereal *tau, doublereal *t, integer *ldt, 
	doublereal *y, integer *ldy);

/* Subroutine */ int dlahrd_(integer *n, integer *k, integer *nb, doublereal *
	a, integer *lda, doublereal *tau, doublereal *t, integer *ldt, 
	doublereal *y, integer *ldy);

/* Subroutine */ int dlaic1_(integer *job, integer *j, doublereal *x, 
	doublereal *sest, doublereal *w, doublereal *gamma, doublereal *
	sestpr, doublereal *s, doublereal *c__);

logical dlaisnan_(doublereal *din1, doublereal *din2);

/* Subroutine */ int dlaln2_(logical *ltrans, integer *na, integer *nw, 
	doublereal *smin, doublereal *ca, doublereal *a, integer *lda, 
	doublereal *d1, doublereal *d2, doublereal *b, integer *ldb, 
	doublereal *wr, doublereal *wi, doublereal *x, integer *ldx, 
	doublereal *scale, doublereal *xnorm, integer *info);

/* Subroutine */ int dlals0_(integer *icompq, integer *nl, integer *nr, 
	integer *sqre, integer *nrhs, doublereal *b, integer *ldb, doublereal 
	*bx, integer *ldbx, integer *perm, integer *givptr, integer *givcol, 
	integer *ldgcol, doublereal *givnum, integer *ldgnum, doublereal *
	poles, doublereal *difl, doublereal *difr, doublereal *z__, integer *
	k, doublereal *c__, doublereal *s, doublereal *work, integer *info);

/* Subroutine */ int dlalsa_(integer *icompq, integer *smlsiz, integer *n, 
	integer *nrhs, doublereal *b, integer *ldb, doublereal *bx, integer *
	ldbx, doublereal *u, integer *ldu, doublereal *vt, integer *k, 
	doublereal *difl, doublereal *difr, doublereal *z__, doublereal *
	poles, integer *givptr, integer *givcol, integer *ldgcol, integer *
	perm, doublereal *givnum, doublereal *c__, doublereal *s, doublereal *
	work, integer *iwork, integer *info);

/* Subroutine */ int dlalsd_(char *uplo, integer *smlsiz, integer *n, integer 
	*nrhs, doublereal *d__, doublereal *e, doublereal *b, integer *ldb, 
	doublereal *rcond, integer *rank, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dlamrg_(integer *n1, integer *n2, doublereal *a, integer 
	*dtrd1, integer *dtrd2, integer *index);

integer dlaneg_(integer *n, doublereal *d__, doublereal *lld, doublereal *
	sigma, doublereal *pivmin, integer *r__);

doublereal dlangb_(char *norm, integer *n, integer *kl, integer *ku, 
	doublereal *ab, integer *ldab, doublereal *work);

doublereal dlange_(char *norm, integer *m, integer *n, doublereal *a, integer 
	*lda, doublereal *work);

doublereal dlangt_(char *norm, integer *n, doublereal *dl, doublereal *d__, 
	doublereal *du);

doublereal dlanhs_(char *norm, integer *n, doublereal *a, integer *lda, 
	doublereal *work);

doublereal dlansb_(char *norm, char *uplo, integer *n, integer *k, doublereal 
	*ab, integer *ldab, doublereal *work);

doublereal dlansf_(char *norm, char *transr, char *uplo, integer *n, 
	doublereal *a, doublereal *work);

doublereal dlansp_(char *norm, char *uplo, integer *n, doublereal *ap, 
	doublereal *work);

doublereal dlanst_(char *norm, integer *n, doublereal *d__, doublereal *e);

doublereal dlansy_(char *norm, char *uplo, integer *n, doublereal *a, integer 
	*lda, doublereal *work);

doublereal dlantb_(char *norm, char *uplo, char *diag, integer *n, integer *k, 
	 doublereal *ab, integer *ldab, doublereal *work);

doublereal dlantp_(char *norm, char *uplo, char *diag, integer *n, doublereal 
	*ap, doublereal *work);

doublereal dlantr_(char *norm, char *uplo, char *diag, integer *m, integer *n, 
	 doublereal *a, integer *lda, doublereal *work);

/* Subroutine */ int dlanv2_(doublereal *a, doublereal *b, doublereal *c__, 
	doublereal *d__, doublereal *rt1r, doublereal *rt1i, doublereal *rt2r, 
	 doublereal *rt2i, doublereal *cs, doublereal *sn);

/* Subroutine */ int dlapll_(integer *n, doublereal *x, integer *incx, 
	doublereal *y, integer *incy, doublereal *ssmin);

/* Subroutine */ int dlapmt_(logical *forwrd, integer *m, integer *n, 
	doublereal *x, integer *ldx, integer *k);

doublereal dlapy2_(doublereal *x, doublereal *y);

doublereal dlapy3_(doublereal *x, doublereal *y, doublereal *z__);

/* Subroutine */ int dlaqgb_(integer *m, integer *n, integer *kl, integer *ku, 
	 doublereal *ab, integer *ldab, doublereal *r__, doublereal *c__, 
	doublereal *rowcnd, doublereal *colcnd, doublereal *amax, char *equed);

/* Subroutine */ int dlaqge_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, doublereal 
	*colcnd, doublereal *amax, char *equed);

/* Subroutine */ int dlaqp2_(integer *m, integer *n, integer *offset, 
	doublereal *a, integer *lda, integer *jpvt, doublereal *tau, 
	doublereal *vn1, doublereal *vn2, doublereal *work);

/* Subroutine */ int dlaqps_(integer *m, integer *n, integer *offset, integer 
	*nb, integer *kb, doublereal *a, integer *lda, integer *jpvt, 
	doublereal *tau, doublereal *vn1, doublereal *vn2, doublereal *auxv, 
	doublereal *f, integer *ldf);

/* Subroutine */ int dlaqr0_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, doublereal *h__, integer *ldh, doublereal 
	*wr, doublereal *wi, integer *iloz, integer *ihiz, doublereal *z__, 
	integer *ldz, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dlaqr1_(integer *n, doublereal *h__, integer *ldh, 
	doublereal *sr1, doublereal *si1, doublereal *sr2, doublereal *si2, 
	doublereal *v);

/* Subroutine */ int dlaqr2_(logical *wantt, logical *wantz, integer *n, 
	integer *ktop, integer *kbot, integer *nw, doublereal *h__, integer *
	ldh, integer *iloz, integer *ihiz, doublereal *z__, integer *ldz, 
	integer *ns, integer *nd, doublereal *sr, doublereal *si, doublereal *
	v, integer *ldv, integer *nh, doublereal *t, integer *ldt, integer *
	nv, doublereal *wv, integer *ldwv, doublereal *work, integer *lwork);

/* Subroutine */ int dlaqr3_(logical *wantt, logical *wantz, integer *n, 
	integer *ktop, integer *kbot, integer *nw, doublereal *h__, integer *
	ldh, integer *iloz, integer *ihiz, doublereal *z__, integer *ldz, 
	integer *ns, integer *nd, doublereal *sr, doublereal *si, doublereal *
	v, integer *ldv, integer *nh, doublereal *t, integer *ldt, integer *
	nv, doublereal *wv, integer *ldwv, doublereal *work, integer *lwork);

/* Subroutine */ int dlaqr4_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, doublereal *h__, integer *ldh, doublereal 
	*wr, doublereal *wi, integer *iloz, integer *ihiz, doublereal *z__, 
	integer *ldz, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dlaqr5_(logical *wantt, logical *wantz, integer *kacc22, 
	integer *n, integer *ktop, integer *kbot, integer *nshfts, doublereal 
	*sr, doublereal *si, doublereal *h__, integer *ldh, integer *iloz, 
	integer *ihiz, doublereal *z__, integer *ldz, doublereal *v, integer *
	ldv, doublereal *u, integer *ldu, integer *nv, doublereal *wv, 
	integer *ldwv, integer *nh, doublereal *wh, integer *ldwh);

/* Subroutine */ int dlaqsb_(char *uplo, integer *n, integer *kd, doublereal *
	ab, integer *ldab, doublereal *s, doublereal *scond, doublereal *amax, 
	 char *equed);

/* Subroutine */ int dlaqsp_(char *uplo, integer *n, doublereal *ap, 
	doublereal *s, doublereal *scond, doublereal *amax, char *equed);

/* Subroutine */ int dlaqsy_(char *uplo, integer *n, doublereal *a, integer *
	lda, doublereal *s, doublereal *scond, doublereal *amax, char *equed);

/* Subroutine */ int dlaqtr_(logical *ltran, logical *lreal, integer *n, 
	doublereal *t, integer *ldt, doublereal *b, doublereal *w, doublereal 
	*scale, doublereal *x, doublereal *work, integer *info);

/* Subroutine */ int dlar1v_(integer *n, integer *b1, integer *bn, doublereal 
	*lambda, doublereal *d__, doublereal *l, doublereal *ld, doublereal *
	lld, doublereal *pivmin, doublereal *gaptol, doublereal *z__, logical 
	*wantnc, integer *negcnt, doublereal *ztz, doublereal *mingma, 
	integer *r__, integer *isuppz, doublereal *nrminv, doublereal *resid, 
	doublereal *rqcorr, doublereal *work);

/* Subroutine */ int dlar2v_(integer *n, doublereal *x, doublereal *y, 
	doublereal *z__, integer *incx, doublereal *c__, doublereal *s, 
	integer *incc);

/* Subroutine */ int dlarf_(char *side, integer *m, integer *n, doublereal *v, 
	 integer *incv, doublereal *tau, doublereal *c__, integer *ldc, 
	doublereal *work);

/* Subroutine */ int dlarfb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, doublereal *v, integer *
	ldv, doublereal *t, integer *ldt, doublereal *c__, integer *ldc, 
	doublereal *work, integer *ldwork);

/* Subroutine */ int dlarfg_(integer *n, doublereal *alpha, doublereal *x, 
	integer *incx, doublereal *tau);

/* Subroutine */ int dlarfp_(integer *n, doublereal *alpha, doublereal *x, 
	integer *incx, doublereal *tau);

/* Subroutine */ int dlarft_(char *direct, char *storev, integer *n, integer *
	k, doublereal *v, integer *ldv, doublereal *tau, doublereal *t, 
	integer *ldt);

/* Subroutine */ int dlarfx_(char *side, integer *m, integer *n, doublereal *
	v, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work);

/* Subroutine */ int dlargv_(integer *n, doublereal *x, integer *incx, 
	doublereal *y, integer *incy, doublereal *c__, integer *incc);

/* Subroutine */ int dlarnv_(integer *idist, integer *iseed, integer *n, 
	doublereal *x);

/* Subroutine */ int dlarra_(integer *n, doublereal *d__, doublereal *e, 
	doublereal *e2, doublereal *spltol, doublereal *tnrm, integer *nsplit, 
	 integer *isplit, integer *info);

/* Subroutine */ int dlarrb_(integer *n, doublereal *d__, doublereal *lld, 
	integer *ifirst, integer *ilast, doublereal *rtol1, doublereal *rtol2, 
	 integer *offset, doublereal *w, doublereal *wgap, doublereal *werr, 
	doublereal *work, integer *iwork, doublereal *pivmin, doublereal *
	spdiam, integer *twist, integer *info);

/* Subroutine */ int dlarrc_(char *jobt, integer *n, doublereal *vl, 
	doublereal *vu, doublereal *d__, doublereal *e, doublereal *pivmin, 
	integer *eigcnt, integer *lcnt, integer *rcnt, integer *info);

/* Subroutine */ int dlarrd_(char *range, char *order, integer *n, doublereal 
	*vl, doublereal *vu, integer *il, integer *iu, doublereal *gers, 
	doublereal *reltol, doublereal *d__, doublereal *e, doublereal *e2, 
	doublereal *pivmin, integer *nsplit, integer *isplit, integer *m, 
	doublereal *w, doublereal *werr, doublereal *wl, doublereal *wu, 
	integer *iblock, integer *indexw, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dlarre_(char *range, integer *n, doublereal *vl, 
	doublereal *vu, integer *il, integer *iu, doublereal *d__, doublereal 
	*e, doublereal *e2, doublereal *rtol1, doublereal *rtol2, doublereal *
	spltol, integer *nsplit, integer *isplit, integer *m, doublereal *w, 
	doublereal *werr, doublereal *wgap, integer *iblock, integer *indexw, 
	doublereal *gers, doublereal *pivmin, doublereal *work, integer *
	iwork, integer *info);

/* Subroutine */ int dlarrf_(integer *n, doublereal *d__, doublereal *l, 
	doublereal *ld, integer *clstrt, integer *clend, doublereal *w, 
	doublereal *wgap, doublereal *werr, doublereal *spdiam, doublereal *
	clgapl, doublereal *clgapr, doublereal *pivmin, doublereal *sigma, 
	doublereal *dplus, doublereal *lplus, doublereal *work, integer *info);

/* Subroutine */ int dlarrj_(integer *n, doublereal *d__, doublereal *e2, 
	integer *ifirst, integer *ilast, doublereal *rtol, integer *offset, 
	doublereal *w, doublereal *werr, doublereal *work, integer *iwork, 
	doublereal *pivmin, doublereal *spdiam, integer *info);

/* Subroutine */ int dlarrk_(integer *n, integer *iw, doublereal *gl, 
	doublereal *gu, doublereal *d__, doublereal *e2, doublereal *pivmin, 
	doublereal *reltol, doublereal *w, doublereal *werr, integer *info);

/* Subroutine */ int dlarrr_(integer *n, doublereal *d__, doublereal *e, 
	integer *info);

/* Subroutine */ int dlarrv_(integer *n, doublereal *vl, doublereal *vu, 
	doublereal *d__, doublereal *l, doublereal *pivmin, integer *isplit, 
	integer *m, integer *dol, integer *dou, doublereal *minrgp, 
	doublereal *rtol1, doublereal *rtol2, doublereal *w, doublereal *werr, 
	 doublereal *wgap, integer *iblock, integer *indexw, doublereal *gers, 
	 doublereal *z__, integer *ldz, integer *isuppz, doublereal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int dlarscl2_(integer *m, integer *n, doublereal *d__, 
	doublereal *x, integer *ldx);

/* Subroutine */ int dlartg_(doublereal *f, doublereal *g, doublereal *cs, 
	doublereal *sn, doublereal *r__);

/* Subroutine */ int dlartv_(integer *n, doublereal *x, integer *incx, 
	doublereal *y, integer *incy, doublereal *c__, doublereal *s, integer 
	*incc);

/* Subroutine */ int dlaruv_(integer *iseed, integer *n, doublereal *x);

/* Subroutine */ int dlarz_(char *side, integer *m, integer *n, integer *l, 
	doublereal *v, integer *incv, doublereal *tau, doublereal *c__, 
	integer *ldc, doublereal *work);

/* Subroutine */ int dlarzb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, integer *l, doublereal *v, 
	 integer *ldv, doublereal *t, integer *ldt, doublereal *c__, integer *
	ldc, doublereal *work, integer *ldwork);

/* Subroutine */ int dlarzt_(char *direct, char *storev, integer *n, integer *
	k, doublereal *v, integer *ldv, doublereal *tau, doublereal *t, 
	integer *ldt);

/* Subroutine */ int dlas2_(doublereal *f, doublereal *g, doublereal *h__, 
	doublereal *ssmin, doublereal *ssmax);

/* Subroutine */ int dlascl_(char *type__, integer *kl, integer *ku, 
	doublereal *cfrom, doublereal *cto, integer *m, integer *n, 
	doublereal *a, integer *lda, integer *info);

/* Subroutine */ int dlascl2_(integer *m, integer *n, doublereal *d__, 
	doublereal *x, integer *ldx);

/* Subroutine */ int dlasd0_(integer *n, integer *sqre, doublereal *d__, 
	doublereal *e, doublereal *u, integer *ldu, doublereal *vt, integer *
	ldvt, integer *smlsiz, integer *iwork, doublereal *work, integer *
	info);

/* Subroutine */ int dlasd1_(integer *nl, integer *nr, integer *sqre, 
	doublereal *d__, doublereal *alpha, doublereal *beta, doublereal *u, 
	integer *ldu, doublereal *vt, integer *ldvt, integer *idxq, integer *
	iwork, doublereal *work, integer *info);

/* Subroutine */ int dlasd2_(integer *nl, integer *nr, integer *sqre, integer 
	*k, doublereal *d__, doublereal *z__, doublereal *alpha, doublereal *
	beta, doublereal *u, integer *ldu, doublereal *vt, integer *ldvt, 
	doublereal *dsigma, doublereal *u2, integer *ldu2, doublereal *vt2, 
	integer *ldvt2, integer *idxp, integer *idx, integer *idxc, integer *
	idxq, integer *coltyp, integer *info);

/* Subroutine */ int dlasd3_(integer *nl, integer *nr, integer *sqre, integer 
	*k, doublereal *d__, doublereal *q, integer *ldq, doublereal *dsigma, 
	doublereal *u, integer *ldu, doublereal *u2, integer *ldu2, 
	doublereal *vt, integer *ldvt, doublereal *vt2, integer *ldvt2, 
	integer *idxc, integer *ctot, doublereal *z__, integer *info);

/* Subroutine */ int dlasd4_(integer *n, integer *i__, doublereal *d__, 
	doublereal *z__, doublereal *delta, doublereal *rho, doublereal *
	sigma, doublereal *work, integer *info);

/* Subroutine */ int dlasd5_(integer *i__, doublereal *d__, doublereal *z__, 
	doublereal *delta, doublereal *rho, doublereal *dsigma, doublereal *
	work);

/* Subroutine */ int dlasd6_(integer *icompq, integer *nl, integer *nr, 
	integer *sqre, doublereal *d__, doublereal *vf, doublereal *vl, 
	doublereal *alpha, doublereal *beta, integer *idxq, integer *perm, 
	integer *givptr, integer *givcol, integer *ldgcol, doublereal *givnum, 
	 integer *ldgnum, doublereal *poles, doublereal *difl, doublereal *
	difr, doublereal *z__, integer *k, doublereal *c__, doublereal *s, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dlasd7_(integer *icompq, integer *nl, integer *nr, 
	integer *sqre, integer *k, doublereal *d__, doublereal *z__, 
	doublereal *zw, doublereal *vf, doublereal *vfw, doublereal *vl, 
	doublereal *vlw, doublereal *alpha, doublereal *beta, doublereal *
	dsigma, integer *idx, integer *idxp, integer *idxq, integer *perm, 
	integer *givptr, integer *givcol, integer *ldgcol, doublereal *givnum, 
	 integer *ldgnum, doublereal *c__, doublereal *s, integer *info);

/* Subroutine */ int dlasd8_(integer *icompq, integer *k, doublereal *d__, 
	doublereal *z__, doublereal *vf, doublereal *vl, doublereal *difl, 
	doublereal *difr, integer *lddifr, doublereal *dsigma, doublereal *
	work, integer *info);

/* Subroutine */ int dlasda_(integer *icompq, integer *smlsiz, integer *n, 
	integer *sqre, doublereal *d__, doublereal *e, doublereal *u, integer 
	*ldu, doublereal *vt, integer *k, doublereal *difl, doublereal *difr, 
	doublereal *z__, doublereal *poles, integer *givptr, integer *givcol, 
	integer *ldgcol, integer *perm, doublereal *givnum, doublereal *c__, 
	doublereal *s, doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dlasdq_(char *uplo, integer *sqre, integer *n, integer *
	ncvt, integer *nru, integer *ncc, doublereal *d__, doublereal *e, 
	doublereal *vt, integer *ldvt, doublereal *u, integer *ldu, 
	doublereal *c__, integer *ldc, doublereal *work, integer *info);

/* Subroutine */ int dlasdt_(integer *n, integer *lvl, integer *nd, integer *
	inode, integer *ndiml, integer *ndimr, integer *msub);

/* Subroutine */ int dlaset_(char *uplo, integer *m, integer *n, doublereal *
	alpha, doublereal *beta, doublereal *a, integer *lda);

/* Subroutine */ int dlasq1_(integer *n, doublereal *d__, doublereal *e, 
	doublereal *work, integer *info);

/* Subroutine */ int dlasq2_(integer *n, doublereal *z__, integer *info);

/* Subroutine */ int dlasq3_(integer *i0, integer *n0, doublereal *z__, 
	integer *pp, doublereal *dmin__, doublereal *sigma, doublereal *desig, 
	 doublereal *qmax, integer *nfail, integer *iter, integer *ndiv, 
	logical *ieee, integer *ttype, doublereal *dmin1, doublereal *dmin2, 
	doublereal *dn, doublereal *dn1, doublereal *dn2, doublereal *g, 
	doublereal *tau);

/* Subroutine */ int dlasq4_(integer *i0, integer *n0, doublereal *z__, 
	integer *pp, integer *n0in, doublereal *dmin__, doublereal *dmin1, 
	doublereal *dmin2, doublereal *dn, doublereal *dn1, doublereal *dn2, 
	doublereal *tau, integer *ttype, doublereal *g);

/* Subroutine */ int dlasq5_(integer *i0, integer *n0, doublereal *z__, 
	integer *pp, doublereal *tau, doublereal *dmin__, doublereal *dmin1, 
	doublereal *dmin2, doublereal *dn, doublereal *dnm1, doublereal *dnm2, 
	 logical *ieee);

/* Subroutine */ int dlasq6_(integer *i0, integer *n0, doublereal *z__, 
	integer *pp, doublereal *dmin__, doublereal *dmin1, doublereal *dmin2, 
	 doublereal *dn, doublereal *dnm1, doublereal *dnm2);

/* Subroutine */ int dlasr_(char *side, char *pivot, char *direct, integer *m, 
	 integer *n, doublereal *c__, doublereal *s, doublereal *a, integer *
	lda);

/* Subroutine */ int dlasrt_(char *id, integer *n, doublereal *d__, integer *
	info);

/* Subroutine */ int dlassq_(integer *n, doublereal *x, integer *incx, 
	doublereal *scale, doublereal *sumsq);

/* Subroutine */ int dlasv2_(doublereal *f, doublereal *g, doublereal *h__, 
	doublereal *ssmin, doublereal *ssmax, doublereal *snr, doublereal *
	csr, doublereal *snl, doublereal *csl);

/* Subroutine */ int dlaswp_(integer *n, doublereal *a, integer *lda, integer 
	*k1, integer *k2, integer *ipiv, integer *incx);

/* Subroutine */ int dlasy2_(logical *ltranl, logical *ltranr, integer *isgn, 
	integer *n1, integer *n2, doublereal *tl, integer *ldtl, doublereal *
	tr, integer *ldtr, doublereal *b, integer *ldb, doublereal *scale, 
	doublereal *x, integer *ldx, doublereal *xnorm, integer *info);

/* Subroutine */ int dlasyf_(char *uplo, integer *n, integer *nb, integer *kb, 
	 doublereal *a, integer *lda, integer *ipiv, doublereal *w, integer *
	ldw, integer *info);

/* Subroutine */ int dlat2s_(char *uplo, integer *n, doublereal *a, integer *
	lda, floatreal *sa, integer *ldsa, integer *info);

/* Subroutine */ int dlatbs_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, integer *kd, doublereal *ab, integer *ldab, 
	doublereal *x, doublereal *scale, doublereal *cnorm, integer *info);

/* Subroutine */ int dlatdf_(integer *ijob, integer *n, doublereal *z__, 
	integer *ldz, doublereal *rhs, doublereal *rdsum, doublereal *rdscal, 
	integer *ipiv, integer *jpiv);

/* Subroutine */ int dlatps_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, doublereal *ap, doublereal *x, doublereal *scale, 
	doublereal *cnorm, integer *info);

/* Subroutine */ int dlatrd_(char *uplo, integer *n, integer *nb, doublereal *
	a, integer *lda, doublereal *e, doublereal *tau, doublereal *w, 
	integer *ldw);

/* Subroutine */ int dlatrs_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, doublereal *a, integer *lda, doublereal *x, 
	doublereal *scale, doublereal *cnorm, integer *info);

/* Subroutine */ int dlatrz_(integer *m, integer *n, integer *l, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work);

/* Subroutine */ int dlatzm_(char *side, integer *m, integer *n, doublereal *
	v, integer *incv, doublereal *tau, doublereal *c1, doublereal *c2, 
	integer *ldc, doublereal *work);

/* Subroutine */ int dlauu2_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *info);

/* Subroutine */ int dlauum_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *info);

/* Subroutine */ int dopgtr_(char *uplo, integer *n, doublereal *ap, 
	doublereal *tau, doublereal *q, integer *ldq, doublereal *work, 
	integer *info);

/* Subroutine */ int dopmtr_(char *side, char *uplo, char *trans, integer *m, 
	integer *n, doublereal *ap, doublereal *tau, doublereal *c__, integer 
	*ldc, doublereal *work, integer *info);

/* Subroutine */ int dorg2l_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *info);

/* Subroutine */ int dorg2r_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *info);

/* Subroutine */ int dorgbr_(char *vect, integer *m, integer *n, integer *k, 
	doublereal *a, integer *lda, doublereal *tau, doublereal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int dorghr_(integer *n, integer *ilo, integer *ihi, 
	doublereal *a, integer *lda, doublereal *tau, doublereal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int dorgl2_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *info);

/* Subroutine */ int dorglq_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dorgql_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dorgqr_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dorgr2_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *info);

/* Subroutine */ int dorgrq_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dorgtr_(char *uplo, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dorm2l_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *info);

/* Subroutine */ int dorm2r_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *info);

/* Subroutine */ int dormbr_(char *vect, char *side, char *trans, integer *m, 
	integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, 
	doublereal *c__, integer *ldc, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dormhr_(char *side, char *trans, integer *m, integer *n, 
	integer *ilo, integer *ihi, doublereal *a, integer *lda, doublereal *
	tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dorml2_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *info);

/* Subroutine */ int dormlq_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dormql_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dormqr_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dormr2_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *info);

/* Subroutine */ int dormr3_(char *side, char *trans, integer *m, integer *n, 
	integer *k, integer *l, doublereal *a, integer *lda, doublereal *tau, 
	doublereal *c__, integer *ldc, doublereal *work, integer *info);

/* Subroutine */ int dormrq_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dormrz_(char *side, char *trans, integer *m, integer *n, 
	integer *k, integer *l, doublereal *a, integer *lda, doublereal *tau, 
	doublereal *c__, integer *ldc, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dormtr_(char *side, char *uplo, char *trans, integer *m, 
	integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dpbcon_(char *uplo, integer *n, integer *kd, doublereal *
	ab, integer *ldab, doublereal *anorm, doublereal *rcond, doublereal *
	work, integer *iwork, integer *info);

/* Subroutine */ int dpbequ_(char *uplo, integer *n, integer *kd, doublereal *
	ab, integer *ldab, doublereal *s, doublereal *scond, doublereal *amax, 
	 integer *info);

/* Subroutine */ int dpbrfs_(char *uplo, integer *n, integer *kd, integer *
	nrhs, doublereal *ab, integer *ldab, doublereal *afb, integer *ldafb, 
	doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *
	ferr, doublereal *berr, doublereal *work, integer *iwork, integer *
	info);

/* Subroutine */ int dpbstf_(char *uplo, integer *n, integer *kd, doublereal *
	ab, integer *ldab, integer *info);

/* Subroutine */ int dpbsv_(char *uplo, integer *n, integer *kd, integer *
	nrhs, doublereal *ab, integer *ldab, doublereal *b, integer *ldb, 
	integer *info);

/* Subroutine */ int dpbsvx_(char *fact, char *uplo, integer *n, integer *kd, 
	integer *nrhs, doublereal *ab, integer *ldab, doublereal *afb, 
	integer *ldafb, char *equed, doublereal *s, doublereal *b, integer *
	ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *ferr, 
	 doublereal *berr, doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dpbtf2_(char *uplo, integer *n, integer *kd, doublereal *
	ab, integer *ldab, integer *info);

/* Subroutine */ int dpbtrf_(char *uplo, integer *n, integer *kd, doublereal *
	ab, integer *ldab, integer *info);

/* Subroutine */ int dpbtrs_(char *uplo, integer *n, integer *kd, integer *
	nrhs, doublereal *ab, integer *ldab, doublereal *b, integer *ldb, 
	integer *info);

/* Subroutine */ int dpftrf_(char *transr, char *uplo, integer *n, doublereal 
	*a, integer *info);

/* Subroutine */ int dpftri_(char *transr, char *uplo, integer *n, doublereal 
	*a, integer *info);

/* Subroutine */ int dpftrs_(char *transr, char *uplo, integer *n, integer *
	nrhs, doublereal *a, doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dpocon_(char *uplo, integer *n, doublereal *a, integer *
	lda, doublereal *anorm, doublereal *rcond, doublereal *work, integer *
	iwork, integer *info);

/* Subroutine */ int dpoequ_(integer *n, doublereal *a, integer *lda, 
	doublereal *s, doublereal *scond, doublereal *amax, integer *info);

/* Subroutine */ int dpoequb_(integer *n, doublereal *a, integer *lda, 
	doublereal *s, doublereal *scond, doublereal *amax, integer *info);

/* Subroutine */ int dporfs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *
	ferr, doublereal *berr, doublereal *work, integer *iwork, integer *
	info);

/* Subroutine */ int dporfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	doublereal *s, doublereal *b, integer *ldb, doublereal *x, integer *
	ldx, doublereal *rcond, doublereal *berr, integer *n_err_bnds__, 
	doublereal *err_bnds_norm__, doublereal *err_bnds_comp__, integer *
	nparams, doublereal *params, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dposv_(char *uplo, integer *n, integer *nrhs, doublereal 
	*a, integer *lda, doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dposvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	char *equed, doublereal *s, doublereal *b, integer *ldb, doublereal *
	x, integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *
	berr, doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dposvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	char *equed, doublereal *s, doublereal *b, integer *ldb, doublereal *
	x, integer *ldx, doublereal *rcond, doublereal *rpvgrw, doublereal *
	berr, integer *n_err_bnds__, doublereal *err_bnds_norm__, doublereal *
	err_bnds_comp__, integer *nparams, doublereal *params, doublereal *
	work, integer *iwork, integer *info);

/* Subroutine */ int dpotf2_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *info);

/* Subroutine */ int dpotrf_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *info);

/* Subroutine */ int dpotri_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *info);

/* Subroutine */ int dpotrs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *
	info);

/* Subroutine */ int dppcon_(char *uplo, integer *n, doublereal *ap, 
	doublereal *anorm, doublereal *rcond, doublereal *work, integer *
	iwork, integer *info);

/* Subroutine */ int dppequ_(char *uplo, integer *n, doublereal *ap, 
	doublereal *s, doublereal *scond, doublereal *amax, integer *info);

/* Subroutine */ int dpprfs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *ap, doublereal *afp, doublereal *b, integer *ldb, 
	doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dppsv_(char *uplo, integer *n, integer *nrhs, doublereal 
	*ap, doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dppsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublereal *ap, doublereal *afp, char *equed, doublereal *s, 
	doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *
	rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *
	iwork, integer *info);

/* Subroutine */ int dpptrf_(char *uplo, integer *n, doublereal *ap, integer *
	info);

/* Subroutine */ int dpptri_(char *uplo, integer *n, doublereal *ap, integer *
	info);

/* Subroutine */ int dpptrs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *ap, doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dpstf2_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *piv, integer *rank, doublereal *tol, doublereal *work, 
	integer *info);

/* Subroutine */ int dpstrf_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *piv, integer *rank, doublereal *tol, doublereal *work, 
	integer *info);

/* Subroutine */ int dptcon_(integer *n, doublereal *d__, doublereal *e, 
	doublereal *anorm, doublereal *rcond, doublereal *work, integer *info);

/* Subroutine */ int dpteqr_(char *compz, integer *n, doublereal *d__, 
	doublereal *e, doublereal *z__, integer *ldz, doublereal *work, 
	integer *info);

/* Subroutine */ int dptrfs_(integer *n, integer *nrhs, doublereal *d__, 
	doublereal *e, doublereal *df, doublereal *ef, doublereal *b, integer 
	*ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, 
	 doublereal *work, integer *info);

/* Subroutine */ int dptsv_(integer *n, integer *nrhs, doublereal *d__, 
	doublereal *e, doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dptsvx_(char *fact, integer *n, integer *nrhs, 
	doublereal *d__, doublereal *e, doublereal *df, doublereal *ef, 
	doublereal *b, integer *ldb, doublereal *x, integer *ldx, doublereal *
	rcond, doublereal *ferr, doublereal *berr, doublereal *work, integer *
	info);

/* Subroutine */ int dpttrf_(integer *n, doublereal *d__, doublereal *e, 
	integer *info);

/* Subroutine */ int dpttrs_(integer *n, integer *nrhs, doublereal *d__, 
	doublereal *e, doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dptts2_(integer *n, integer *nrhs, doublereal *d__, 
	doublereal *e, doublereal *b, integer *ldb);

/* Subroutine */ int drscl_(integer *n, doublereal *sa, doublereal *sx, 
	integer *incx);

/* Subroutine */ int dsbev_(char *jobz, char *uplo, integer *n, integer *kd, 
	doublereal *ab, integer *ldab, doublereal *w, doublereal *z__, 
	integer *ldz, doublereal *work, integer *info);

/* Subroutine */ int dsbevd_(char *jobz, char *uplo, integer *n, integer *kd, 
	doublereal *ab, integer *ldab, doublereal *w, doublereal *z__, 
	integer *ldz, doublereal *work, integer *lwork, integer *iwork, 
	integer *liwork, integer *info);

/* Subroutine */ int dsbevx_(char *jobz, char *range, char *uplo, integer *n, 
	integer *kd, doublereal *ab, integer *ldab, doublereal *q, integer *
	ldq, doublereal *vl, doublereal *vu, integer *il, integer *iu, 
	doublereal *abstol, integer *m, doublereal *w, doublereal *z__, 
	integer *ldz, doublereal *work, integer *iwork, integer *ifail, 
	integer *info);

/* Subroutine */ int dsbgst_(char *vect, char *uplo, integer *n, integer *ka, 
	integer *kb, doublereal *ab, integer *ldab, doublereal *bb, integer *
	ldbb, doublereal *x, integer *ldx, doublereal *work, integer *info);

/* Subroutine */ int dsbgv_(char *jobz, char *uplo, integer *n, integer *ka, 
	integer *kb, doublereal *ab, integer *ldab, doublereal *bb, integer *
	ldbb, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, 
	integer *info);

/* Subroutine */ int dsbgvd_(char *jobz, char *uplo, integer *n, integer *ka, 
	integer *kb, doublereal *ab, integer *ldab, doublereal *bb, integer *
	ldbb, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int dsbgvx_(char *jobz, char *range, char *uplo, integer *n, 
	integer *ka, integer *kb, doublereal *ab, integer *ldab, doublereal *
	bb, integer *ldbb, doublereal *q, integer *ldq, doublereal *vl, 
	doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer 
	*m, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, 
	integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int dsbtrd_(char *vect, char *uplo, integer *n, integer *kd, 
	doublereal *ab, integer *ldab, doublereal *d__, doublereal *e, 
	doublereal *q, integer *ldq, doublereal *work, integer *info);

/* Subroutine */ int dsfrk_(char *transr, char *uplo, char *trans, integer *n, 
	 integer *k, doublereal *alpha, doublereal *a, integer *lda, 
	doublereal *beta, doublereal *c__);

/* Subroutine */ int dsgesv_(integer *n, integer *nrhs, doublereal *a, 
	integer *lda, integer *ipiv, doublereal *b, integer *ldb, doublereal *
	x, integer *ldx, doublereal *work, floatreal *swork, integer *iter, 
	integer *info);

/* Subroutine */ int dspcon_(char *uplo, integer *n, doublereal *ap, integer *
	ipiv, doublereal *anorm, doublereal *rcond, doublereal *work, integer 
	*iwork, integer *info);

/* Subroutine */ int dspev_(char *jobz, char *uplo, integer *n, doublereal *
	ap, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, 
	integer *info);

/* Subroutine */ int dspevd_(char *jobz, char *uplo, integer *n, doublereal *
	ap, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int dspevx_(char *jobz, char *range, char *uplo, integer *n, 
	doublereal *ap, doublereal *vl, doublereal *vu, integer *il, integer *
	iu, doublereal *abstol, integer *m, doublereal *w, doublereal *z__, 
	integer *ldz, doublereal *work, integer *iwork, integer *ifail, 
	integer *info);

/* Subroutine */ int dspgst_(integer *itype, char *uplo, integer *n, 
	doublereal *ap, doublereal *bp, integer *info);

/* Subroutine */ int dspgv_(integer *itype, char *jobz, char *uplo, integer *
	n, doublereal *ap, doublereal *bp, doublereal *w, doublereal *z__, 
	integer *ldz, doublereal *work, integer *info);

/* Subroutine */ int dspgvd_(integer *itype, char *jobz, char *uplo, integer *
	n, doublereal *ap, doublereal *bp, doublereal *w, doublereal *z__, 
	integer *ldz, doublereal *work, integer *lwork, integer *iwork, 
	integer *liwork, integer *info);

/* Subroutine */ int dspgvx_(integer *itype, char *jobz, char *range, char *
	uplo, integer *n, doublereal *ap, doublereal *bp, doublereal *vl, 
	doublereal *vu, integer *il, integer *iu, doublereal *abstol, integer 
	*m, doublereal *w, doublereal *z__, integer *ldz, doublereal *work, 
	integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int dsposv_(char *uplo, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *
	x, integer *ldx, doublereal *work, floatreal *swork, integer *iter, 
	integer *info);

/* Subroutine */ int dsprfs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *ap, doublereal *afp, integer *ipiv, doublereal *b, 
	integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, 
	doublereal *berr, doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dspsv_(char *uplo, integer *n, integer *nrhs, doublereal 
	*ap, integer *ipiv, doublereal *b, integer *ldb, integer *info);

/* Subroutine */ int dspsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublereal *ap, doublereal *afp, integer *ipiv, doublereal *b, 
	integer *ldb, doublereal *x, integer *ldx, doublereal *rcond, 
	doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dsptrd_(char *uplo, integer *n, doublereal *ap, 
	doublereal *d__, doublereal *e, doublereal *tau, integer *info);

/* Subroutine */ int dsptrf_(char *uplo, integer *n, doublereal *ap, integer *
	ipiv, integer *info);

/* Subroutine */ int dsptri_(char *uplo, integer *n, doublereal *ap, integer *
	ipiv, doublereal *work, integer *info);

/* Subroutine */ int dsptrs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *ap, integer *ipiv, doublereal *b, integer *ldb, integer *
	info);

/* Subroutine */ int dstebz_(char *range, char *order, integer *n, doublereal 
	*vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, 
	doublereal *d__, doublereal *e, integer *m, integer *nsplit, 
	doublereal *w, integer *iblock, integer *isplit, doublereal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int dstedc_(char *compz, integer *n, doublereal *d__, 
	doublereal *e, doublereal *z__, integer *ldz, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int dstegr_(char *jobz, char *range, integer *n, doublereal *
	d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, 
	integer *iu, doublereal *abstol, integer *m, doublereal *w, 
	doublereal *z__, integer *ldz, integer *isuppz, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int dstein_(integer *n, doublereal *d__, doublereal *e, 
	integer *m, doublereal *w, integer *iblock, integer *isplit, 
	doublereal *z__, integer *ldz, doublereal *work, integer *iwork, 
	integer *ifail, integer *info);

/* Subroutine */ int dstemr_(char *jobz, char *range, integer *n, doublereal *
	d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, 
	integer *iu, integer *m, doublereal *w, doublereal *z__, integer *ldz, 
	 integer *nzc, integer *isuppz, logical *tryrac, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int dsteqr_(char *compz, integer *n, doublereal *d__, 
	doublereal *e, doublereal *z__, integer *ldz, doublereal *work, 
	integer *info);

/* Subroutine */ int dsterf_(integer *n, doublereal *d__, doublereal *e, 
	integer *info);

/* Subroutine */ int dstev_(char *jobz, integer *n, doublereal *d__, 
	doublereal *e, doublereal *z__, integer *ldz, doublereal *work, 
	integer *info);

/* Subroutine */ int dstevd_(char *jobz, integer *n, doublereal *d__, 
	doublereal *e, doublereal *z__, integer *ldz, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int dstevr_(char *jobz, char *range, integer *n, doublereal *
	d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, 
	integer *iu, doublereal *abstol, integer *m, doublereal *w, 
	doublereal *z__, integer *ldz, integer *isuppz, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int dstevx_(char *jobz, char *range, integer *n, doublereal *
	d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, 
	integer *iu, doublereal *abstol, integer *m, doublereal *w, 
	doublereal *z__, integer *ldz, doublereal *work, integer *iwork, 
	integer *ifail, integer *info);

/* Subroutine */ int dsycon_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *ipiv, doublereal *anorm, doublereal *rcond, doublereal *
	work, integer *iwork, integer *info);

/* Subroutine */ int dsyequb_(char *uplo, integer *n, doublereal *a, integer *
	lda, doublereal *s, doublereal *scond, doublereal *amax, doublereal *
	work, integer *info);

/* Subroutine */ int dsyev_(char *jobz, char *uplo, integer *n, doublereal *a, 
	 integer *lda, doublereal *w, doublereal *work, integer *lwork, 
	integer *info);

/* Subroutine */ int dsyevd_(char *jobz, char *uplo, integer *n, doublereal *
	a, integer *lda, doublereal *w, doublereal *work, integer *lwork, 
	integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int dsyevr_(char *jobz, char *range, char *uplo, integer *n, 
	doublereal *a, integer *lda, doublereal *vl, doublereal *vu, integer *
	il, integer *iu, doublereal *abstol, integer *m, doublereal *w, 
	doublereal *z__, integer *ldz, integer *isuppz, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int dsyevx_(char *jobz, char *range, char *uplo, integer *n, 
	doublereal *a, integer *lda, doublereal *vl, doublereal *vu, integer *
	il, integer *iu, doublereal *abstol, integer *m, doublereal *w, 
	doublereal *z__, integer *ldz, doublereal *work, integer *lwork, 
	integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int dsygs2_(integer *itype, char *uplo, integer *n, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *
	info);

/* Subroutine */ int dsygst_(integer *itype, char *uplo, integer *n, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *
	info);

/* Subroutine */ int dsygv_(integer *itype, char *jobz, char *uplo, integer *
	n, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *w, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dsygvd_(integer *itype, char *jobz, char *uplo, integer *
	n, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *w, doublereal *work, integer *lwork, integer *iwork, 
	integer *liwork, integer *info);

/* Subroutine */ int dsygvx_(integer *itype, char *jobz, char *range, char *
	uplo, integer *n, doublereal *a, integer *lda, doublereal *b, integer 
	*ldb, doublereal *vl, doublereal *vu, integer *il, integer *iu, 
	doublereal *abstol, integer *m, doublereal *w, doublereal *z__, 
	integer *ldz, doublereal *work, integer *lwork, integer *iwork, 
	integer *ifail, integer *info);

/* Subroutine */ int dsyrfs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, doublereal *af, integer *ldaf, integer *
	ipiv, doublereal *b, integer *ldb, doublereal *x, integer *ldx, 
	doublereal *ferr, doublereal *berr, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dsyrfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	integer *ipiv, doublereal *s, doublereal *b, integer *ldb, doublereal 
	*x, integer *ldx, doublereal *rcond, doublereal *berr, integer *
	n_err_bnds__, doublereal *err_bnds_norm__, doublereal *
	err_bnds_comp__, integer *nparams, doublereal *params, doublereal *
	work, integer *iwork, integer *info);

/* Subroutine */ int dsysv_(char *uplo, integer *n, integer *nrhs, doublereal 
	*a, integer *lda, integer *ipiv, doublereal *b, integer *ldb, 
	doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dsysvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	integer *ipiv, doublereal *b, integer *ldb, doublereal *x, integer *
	ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, 
	doublereal *work, integer *lwork, integer *iwork, integer *info);

/* Subroutine */ int dsysvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *af, integer *ldaf, 
	integer *ipiv, char *equed, doublereal *s, doublereal *b, integer *
	ldb, doublereal *x, integer *ldx, doublereal *rcond, doublereal *
	rpvgrw, doublereal *berr, integer *n_err_bnds__, doublereal *
	err_bnds_norm__, doublereal *err_bnds_comp__, integer *nparams, 
	doublereal *params, doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dsytd2_(char *uplo, integer *n, doublereal *a, integer *
	lda, doublereal *d__, doublereal *e, doublereal *tau, integer *info);

/* Subroutine */ int dsytf2_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *ipiv, integer *info);

/* Subroutine */ int dsytrd_(char *uplo, integer *n, doublereal *a, integer *
	lda, doublereal *d__, doublereal *e, doublereal *tau, doublereal *
	work, integer *lwork, integer *info);

/* Subroutine */ int dsytrf_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *ipiv, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dsytri_(char *uplo, integer *n, doublereal *a, integer *
	lda, integer *ipiv, doublereal *work, integer *info);

/* Subroutine */ int dsytrs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *a, integer *lda, integer *ipiv, doublereal *b, integer *
	ldb, integer *info);

/* Subroutine */ int dtbcon_(char *norm, char *uplo, char *diag, integer *n, 
	integer *kd, doublereal *ab, integer *ldab, doublereal *rcond, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dtbrfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *kd, integer *nrhs, doublereal *ab, integer *ldab, doublereal 
	*b, integer *ldb, doublereal *x, integer *ldx, doublereal *ferr, 
	doublereal *berr, doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dtbtrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *kd, integer *nrhs, doublereal *ab, integer *ldab, doublereal 
	*b, integer *ldb, integer *info);

/* Subroutine */ int dtfsm_(char *transr, char *side, char *uplo, char *trans, 
	 char *diag, integer *m, integer *n, doublereal *alpha, doublereal *a, 
	 doublereal *b, integer *ldb);

/* Subroutine */ int dtftri_(char *transr, char *uplo, char *diag, integer *n, 
	 doublereal *a, integer *info);

/* Subroutine */ int dtfttp_(char *transr, char *uplo, integer *n, doublereal 
	*arf, doublereal *ap, integer *info);

/* Subroutine */ int dtfttr_(char *transr, char *uplo, integer *n, doublereal 
	*arf, doublereal *a, integer *lda, integer *info);

/* Subroutine */ int dtgevc_(char *side, char *howmny, logical *select, 
	integer *n, doublereal *s, integer *lds, doublereal *p, integer *ldp, 
	doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, integer 
	*mm, integer *m, doublereal *work, integer *info);

/* Subroutine */ int dtgex2_(logical *wantq, logical *wantz, integer *n, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *
	q, integer *ldq, doublereal *z__, integer *ldz, integer *j1, integer *
	n1, integer *n2, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dtgexc_(logical *wantq, logical *wantz, integer *n, 
	doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *
	q, integer *ldq, doublereal *z__, integer *ldz, integer *ifst, 
	integer *ilst, doublereal *work, integer *lwork, integer *info);

/* Subroutine */ int dtgsen_(integer *ijob, logical *wantq, logical *wantz, 
	logical *select, integer *n, doublereal *a, integer *lda, doublereal *
	b, integer *ldb, doublereal *alphar, doublereal *alphai, doublereal *
	beta, doublereal *q, integer *ldq, doublereal *z__, integer *ldz, 
	integer *m, doublereal *pl, doublereal *pr, doublereal *dif, 
	doublereal *work, integer *lwork, integer *iwork, integer *liwork, 
	integer *info);

/* Subroutine */ int dtgsja_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *p, integer *n, integer *k, integer *l, doublereal *a, 
	integer *lda, doublereal *b, integer *ldb, doublereal *tola, 
	doublereal *tolb, doublereal *alpha, doublereal *beta, doublereal *u, 
	integer *ldu, doublereal *v, integer *ldv, doublereal *q, integer *
	ldq, doublereal *work, integer *ncycle, integer *info);

/* Subroutine */ int dtgsna_(char *job, char *howmny, logical *select, 
	integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr, 
	doublereal *s, doublereal *dif, integer *mm, integer *m, doublereal *
	work, integer *lwork, integer *iwork, integer *info);

/* Subroutine */ int dtgsy2_(char *trans, integer *ijob, integer *m, integer *
	n, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *c__, integer *ldc, doublereal *d__, integer *ldd, 
	doublereal *e, integer *lde, doublereal *f, integer *ldf, doublereal *
	scale, doublereal *rdsum, doublereal *rdscal, integer *iwork, integer 
	*pq, integer *info);

/* Subroutine */ int dtgsyl_(char *trans, integer *ijob, integer *m, integer *
	n, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *c__, integer *ldc, doublereal *d__, integer *ldd, 
	doublereal *e, integer *lde, doublereal *f, integer *ldf, doublereal *
	scale, doublereal *dif, doublereal *work, integer *lwork, integer *
	iwork, integer *info);

/* Subroutine */ int dtpcon_(char *norm, char *uplo, char *diag, integer *n, 
	doublereal *ap, doublereal *rcond, doublereal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int dtprfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, doublereal *ap, doublereal *b, integer *ldb, 
	doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dtptri_(char *uplo, char *diag, integer *n, doublereal *
	ap, integer *info);

/* Subroutine */ int dtptrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, doublereal *ap, doublereal *b, integer *ldb, integer *
	info);

/* Subroutine */ int dtpttf_(char *transr, char *uplo, integer *n, doublereal 
	*ap, doublereal *arf, integer *info);

/* Subroutine */ int dtpttr_(char *uplo, integer *n, doublereal *ap, 
	doublereal *a, integer *lda, integer *info);

/* Subroutine */ int dtrcon_(char *norm, char *uplo, char *diag, integer *n, 
	doublereal *a, integer *lda, doublereal *rcond, doublereal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int dtrevc_(char *side, char *howmny, logical *select, 
	integer *n, doublereal *t, integer *ldt, doublereal *vl, integer *
	ldvl, doublereal *vr, integer *ldvr, integer *mm, integer *m, 
	doublereal *work, integer *info);

/* Subroutine */ int dtrexc_(char *compq, integer *n, doublereal *t, integer *
	ldt, doublereal *q, integer *ldq, integer *ifst, integer *ilst, 
	doublereal *work, integer *info);

/* Subroutine */ int dtrrfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *
	ldb, doublereal *x, integer *ldx, doublereal *ferr, doublereal *berr, 
	doublereal *work, integer *iwork, integer *info);

/* Subroutine */ int dtrsen_(char *job, char *compq, logical *select, integer 
	*n, doublereal *t, integer *ldt, doublereal *q, integer *ldq, 
	doublereal *wr, doublereal *wi, integer *m, doublereal *s, doublereal 
	*sep, doublereal *work, integer *lwork, integer *iwork, integer *
	liwork, integer *info);

/* Subroutine */ int dtrsna_(char *job, char *howmny, logical *select, 
	integer *n, doublereal *t, integer *ldt, doublereal *vl, integer *
	ldvl, doublereal *vr, integer *ldvr, doublereal *s, doublereal *sep, 
	integer *mm, integer *m, doublereal *work, integer *ldwork, integer *
	iwork, integer *info);

/* Subroutine */ int dtrsyl_(char *trana, char *tranb, integer *isgn, integer 
	*m, integer *n, doublereal *a, integer *lda, doublereal *b, integer *
	ldb, doublereal *c__, integer *ldc, doublereal *scale, integer *info);

/* Subroutine */ int dtrti2_(char *uplo, char *diag, integer *n, doublereal *
	a, integer *lda, integer *info);

/* Subroutine */ int dtrtri_(char *uplo, char *diag, integer *n, doublereal *
	a, integer *lda, integer *info);

/* Subroutine */ int dtrtrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *
	ldb, integer *info);

/* Subroutine */ int dtrttf_(char *transr, char *uplo, integer *n, doublereal 
	*a, integer *lda, doublereal *arf, integer *info);

/* Subroutine */ int dtrttp_(char *uplo, integer *n, doublereal *a, integer *
	lda, doublereal *ap, integer *info);

/* Subroutine */ int dtzrqf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, integer *info);

/* Subroutine */ int dtzrzf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);

doublereal dzsum1_(integer *n, doublecomplex *cx, integer *incx);

integer icmax1_(integer *n, floatcomplex *cx, integer *incx);

integer ieeeck_(integer *ispec, floatreal *zero, floatreal *one);

integer ilaclc_(integer *m, integer *n, floatcomplex *a, integer *lda);

integer ilaclr_(integer *m, integer *n, floatcomplex *a, integer *lda);

integer iladiag_(char *diag);

integer iladlc_(integer *m, integer *n, doublereal *a, integer *lda);

integer iladlr_(integer *m, integer *n, doublereal *a, integer *lda);

integer ilaenv_(integer *ispec, char *name__, char *opts, integer *n1, 
	integer *n2, integer *n3, integer *n4);

integer ilaprec_(char *prec);

integer ilaslc_(integer *m, integer *n, floatreal *a, integer *lda);

integer ilaslr_(integer *m, integer *n, floatreal *a, integer *lda);

integer ilatrans_(char *trans);

integer ilauplo_(char *uplo);

/* Subroutine */ int ilaver_(integer *vers_major__, integer *vers_minor__, 
	integer *vers_patch__);

integer ilazlc_(integer *m, integer *n, doublecomplex *a, integer *lda);

integer ilazlr_(integer *m, integer *n, doublecomplex *a, integer *lda);

integer iparmq_(integer *ispec, char *name__, char *opts, integer *n, integer 
	*ilo, integer *ihi, integer *lwork);

integer izmax1_(integer *n, doublecomplex *cx, integer *incx);

logical lsamen_(integer *n, char *ca, char *cb);

integer smaxloc_(floatreal *a, integer *dimm);

/* Subroutine */ int sbdsdc_(char *uplo, char *compq, integer *n, floatreal *d__, 
	floatreal *e, floatreal *u, integer *ldu, floatreal *vt, integer *ldvt, floatreal *q, 
	integer *iq, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sbdsqr_(char *uplo, integer *n, integer *ncvt, integer *
	nru, integer *ncc, floatreal *d__, floatreal *e, floatreal *vt, integer *ldvt, floatreal *
	u, integer *ldu, floatreal *c__, integer *ldc, floatreal *work, integer *info);

doublereal scsum1_(integer *n, floatcomplex *cx, integer *incx);

/* Subroutine */ int sdisna_(char *job, integer *m, integer *n, floatreal *d__, 
	floatreal *sep, integer *info);

/* Subroutine */ int sgbbrd_(char *vect, integer *m, integer *n, integer *ncc, 
	 integer *kl, integer *ku, floatreal *ab, integer *ldab, floatreal *d__, floatreal *
	e, floatreal *q, integer *ldq, floatreal *pt, integer *ldpt, floatreal *c__, integer 
	*ldc, floatreal *work, integer *info);

/* Subroutine */ int sgbcon_(char *norm, integer *n, integer *kl, integer *ku, 
	 floatreal *ab, integer *ldab, integer *ipiv, floatreal *anorm, floatreal *rcond, 
	floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sgbequ_(integer *m, integer *n, integer *kl, integer *ku, 
	 floatreal *ab, integer *ldab, floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal *
	colcnd, floatreal *amax, integer *info);

/* Subroutine */ int sgbequb_(integer *m, integer *n, integer *kl, integer *
	ku, floatreal *ab, integer *ldab, floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal 
	*colcnd, floatreal *amax, integer *info);

/* Subroutine */ int sgbrfs_(char *trans, integer *n, integer *kl, integer *
	ku, integer *nrhs, floatreal *ab, integer *ldab, floatreal *afb, integer *ldafb, 
	 integer *ipiv, floatreal *b, integer *ldb, floatreal *x, integer *ldx, floatreal *
	ferr, floatreal *berr, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sgbrfsx_(char *trans, char *equed, integer *n, integer *
	kl, integer *ku, integer *nrhs, floatreal *ab, integer *ldab, floatreal *afb, 
	integer *ldafb, integer *ipiv, floatreal *r__, floatreal *c__, floatreal *b, integer 
	*ldb, floatreal *x, integer *ldx, floatreal *rcond, floatreal *berr, integer *
	n_err_bnds__, floatreal *err_bnds_norm__, floatreal *err_bnds_comp__, integer *
	nparams, floatreal *params, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sgbsv_(integer *n, integer *kl, integer *ku, integer *
	nrhs, floatreal *ab, integer *ldab, integer *ipiv, floatreal *b, integer *ldb, 
	integer *info);

/* Subroutine */ int sgbsvx_(char *fact, char *trans, integer *n, integer *kl, 
	 integer *ku, integer *nrhs, floatreal *ab, integer *ldab, floatreal *afb, 
	integer *ldafb, integer *ipiv, char *equed, floatreal *r__, floatreal *c__, 
	floatreal *b, integer *ldb, floatreal *x, integer *ldx, floatreal *rcond, floatreal *ferr, 
	 floatreal *berr, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sgbsvxx_(char *fact, char *trans, integer *n, integer *
	kl, integer *ku, integer *nrhs, floatreal *ab, integer *ldab, floatreal *afb, 
	integer *ldafb, integer *ipiv, char *equed, floatreal *r__, floatreal *c__, 
	floatreal *b, integer *ldb, floatreal *x, integer *ldx, floatreal *rcond, floatreal *
	rpvgrw, floatreal *berr, integer *n_err_bnds__, floatreal *err_bnds_norm__, 
	floatreal *err_bnds_comp__, integer *nparams, floatreal *params, floatreal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int sgbtf2_(integer *m, integer *n, integer *kl, integer *ku, 
	 floatreal *ab, integer *ldab, integer *ipiv, integer *info);

/* Subroutine */ int sgbtrf_(integer *m, integer *n, integer *kl, integer *ku, 
	 floatreal *ab, integer *ldab, integer *ipiv, integer *info);

/* Subroutine */ int sgbtrs_(char *trans, integer *n, integer *kl, integer *
	ku, integer *nrhs, floatreal *ab, integer *ldab, integer *ipiv, floatreal *b, 
	integer *ldb, integer *info);

/* Subroutine */ int sgebak_(char *job, char *side, integer *n, integer *ilo, 
	integer *ihi, floatreal *scale, integer *m, floatreal *v, integer *ldv, integer 
	*info);

/* Subroutine */ int sgebal_(char *job, integer *n, floatreal *a, integer *lda, 
	integer *ilo, integer *ihi, floatreal *scale, integer *info);

/* Subroutine */ int sgebd2_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *d__, floatreal *e, floatreal *tauq, floatreal *taup, floatreal *work, integer *info);

/* Subroutine */ int sgebrd_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *d__, floatreal *e, floatreal *tauq, floatreal *taup, floatreal *work, integer *
	lwork, integer *info);

/* Subroutine */ int sgecon_(char *norm, integer *n, floatreal *a, integer *lda, 
	floatreal *anorm, floatreal *rcond, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sgeequ_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal *colcnd, floatreal *amax, integer 
	*info);

/* Subroutine */ int sgeequb_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal *colcnd, floatreal *amax, integer 
	*info);

/* Subroutine */ int sgees_(char *jobvs, char *sort, L_fp select, integer *n, 
	floatreal *a, integer *lda, integer *sdim, floatreal *wr, floatreal *wi, floatreal *vs, 
	integer *ldvs, floatreal *work, integer *lwork, logical *bwork, integer *
	info);

/* Subroutine */ int sgeesx_(char *jobvs, char *sort, L_fp select, char *
	sense, integer *n, floatreal *a, integer *lda, integer *sdim, floatreal *wr, 
	floatreal *wi, floatreal *vs, integer *ldvs, floatreal *rconde, floatreal *rcondv, floatreal *
	work, integer *lwork, integer *iwork, integer *liwork, logical *bwork, 
	 integer *info);

/* Subroutine */ int sgeev_(char *jobvl, char *jobvr, integer *n, floatreal *a, 
	integer *lda, floatreal *wr, floatreal *wi, floatreal *vl, integer *ldvl, floatreal *vr, 
	integer *ldvr, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgeevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, floatreal *a, integer *lda, floatreal *wr, floatreal *wi, floatreal *
	vl, integer *ldvl, floatreal *vr, integer *ldvr, integer *ilo, integer *
	ihi, floatreal *scale, floatreal *abnrm, floatreal *rconde, floatreal *rcondv, floatreal *work, 
	 integer *lwork, integer *iwork, integer *info);

/* Subroutine */ int sgegs_(char *jobvsl, char *jobvsr, integer *n, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, floatreal *alphar, floatreal *alphai, floatreal 
	*beta, floatreal *vsl, integer *ldvsl, floatreal *vsr, integer *ldvsr, floatreal *
	work, integer *lwork, integer *info);

/* Subroutine */ int sgegv_(char *jobvl, char *jobvr, integer *n, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, floatreal *alphar, floatreal *alphai, floatreal 
	*beta, floatreal *vl, integer *ldvl, floatreal *vr, integer *ldvr, floatreal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int sgehd2_(integer *n, integer *ilo, integer *ihi, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sgehrd_(integer *n, integer *ilo, integer *ihi, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgejsv_(char *joba, char *jobu, char *jobv, char *jobr, 
	char *jobt, char *jobp, integer *m, integer *n, floatreal *a, integer *lda, 
	 floatreal *sva, floatreal *u, integer *ldu, floatreal *v, integer *ldv, floatreal *work, 
	integer *lwork, integer *iwork, integer *info);

/* Subroutine */ int sgelq2_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sgelqf_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgels_(char *trans, integer *m, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int sgelsd_(integer *m, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, floatreal *s, floatreal *rcond, integer *
	rank, floatreal *work, integer *lwork, integer *iwork, integer *info);

/* Subroutine */ int sgelss_(integer *m, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, floatreal *s, floatreal *rcond, integer *
	rank, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgelsx_(integer *m, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, integer *jpvt, floatreal *rcond, 
	integer *rank, floatreal *work, integer *info);

/* Subroutine */ int sgelsy_(integer *m, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, integer *jpvt, floatreal *rcond, 
	integer *rank, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgeql2_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sgeqlf_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgeqp3_(integer *m, integer *n, floatreal *a, integer *lda, 
	integer *jpvt, floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgeqpf_(integer *m, integer *n, floatreal *a, integer *lda, 
	integer *jpvt, floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sgeqr2_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sgeqrf_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgerfs_(char *trans, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, floatreal *af, integer *ldaf, integer *ipiv, floatreal *b, 
	integer *ldb, floatreal *x, integer *ldx, floatreal *ferr, floatreal *berr, floatreal *
	work, integer *iwork, integer *info);

/* Subroutine */ int sgerfsx_(char *trans, char *equed, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *af, integer *ldaf, integer *ipiv, 
	floatreal *r__, floatreal *c__, floatreal *b, integer *ldb, floatreal *x, integer *ldx, 
	floatreal *rcond, floatreal *berr, integer *n_err_bnds__, floatreal *err_bnds_norm__, 
	 floatreal *err_bnds_comp__, integer *nparams, floatreal *params, floatreal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int sgerq2_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sgerqf_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgesc2_(integer *n, floatreal *a, integer *lda, floatreal *rhs, 
	integer *ipiv, integer *jpiv, floatreal *scale);

/* Subroutine */ int sgesdd_(char *jobz, integer *m, integer *n, floatreal *a, 
	integer *lda, floatreal *s, floatreal *u, integer *ldu, floatreal *vt, integer *ldvt, 
	 floatreal *work, integer *lwork, integer *iwork, integer *info);

/* Subroutine */ int sgesv_(integer *n, integer *nrhs, floatreal *a, integer *lda, 
	integer *ipiv, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	floatreal *a, integer *lda, floatreal *s, floatreal *u, integer *ldu, floatreal *vt, 
	integer *ldvt, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgesvj_(char *joba, char *jobu, char *jobv, integer *m, 
	integer *n, floatreal *a, integer *lda, floatreal *sva, integer *mv, floatreal *v, 
	integer *ldv, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgesvx_(char *fact, char *trans, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *af, integer *ldaf, integer *ipiv, 
	char *equed, floatreal *r__, floatreal *c__, floatreal *b, integer *ldb, floatreal *x, 
	integer *ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, floatreal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int sgesvxx_(char *fact, char *trans, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *af, integer *ldaf, integer *ipiv, 
	char *equed, floatreal *r__, floatreal *c__, floatreal *b, integer *ldb, floatreal *x, 
	integer *ldx, floatreal *rcond, floatreal *rpvgrw, floatreal *berr, integer *
	n_err_bnds__, floatreal *err_bnds_norm__, floatreal *err_bnds_comp__, integer *
	nparams, floatreal *params, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sgetc2_(integer *n, floatreal *a, integer *lda, integer *ipiv, 
	 integer *jpiv, integer *info);

/* Subroutine */ int sgetf2_(integer *m, integer *n, floatreal *a, integer *lda, 
	integer *ipiv, integer *info);

/* Subroutine */ int sgetrf_(integer *m, integer *n, floatreal *a, integer *lda, 
	integer *ipiv, integer *info);

/* Subroutine */ int sgetri_(integer *n, floatreal *a, integer *lda, integer *ipiv, 
	 floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgetrs_(char *trans, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, integer *ipiv, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sggbak_(char *job, char *side, integer *n, integer *ilo, 
	integer *ihi, floatreal *lscale, floatreal *rscale, integer *m, floatreal *v, 
	integer *ldv, integer *info);

/* Subroutine */ int sggbal_(char *job, integer *n, floatreal *a, integer *lda, 
	floatreal *b, integer *ldb, integer *ilo, integer *ihi, floatreal *lscale, floatreal 
	*rscale, floatreal *work, integer *info);

/* Subroutine */ int sgges_(char *jobvsl, char *jobvsr, char *sort, L_fp 
	selctg, integer *n, floatreal *a, integer *lda, floatreal *b, integer *ldb, 
	integer *sdim, floatreal *alphar, floatreal *alphai, floatreal *beta, floatreal *vsl, 
	integer *ldvsl, floatreal *vsr, integer *ldvsr, floatreal *work, integer *lwork, 
	 logical *bwork, integer *info);

/* Subroutine */ int sggesx_(char *jobvsl, char *jobvsr, char *sort, L_fp 
	selctg, char *sense, integer *n, floatreal *a, integer *lda, floatreal *b, 
	integer *ldb, integer *sdim, floatreal *alphar, floatreal *alphai, floatreal *beta, 
	floatreal *vsl, integer *ldvsl, floatreal *vsr, integer *ldvsr, floatreal *rconde, 
	floatreal *rcondv, floatreal *work, integer *lwork, integer *iwork, integer *
	liwork, logical *bwork, integer *info);

/* Subroutine */ int sggev_(char *jobvl, char *jobvr, integer *n, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, floatreal *alphar, floatreal *alphai, floatreal 
	*beta, floatreal *vl, integer *ldvl, floatreal *vr, integer *ldvr, floatreal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int sggevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal 
	*alphar, floatreal *alphai, floatreal *beta, floatreal *vl, integer *ldvl, floatreal *vr, 
	integer *ldvr, integer *ilo, integer *ihi, floatreal *lscale, floatreal *rscale, 
	 floatreal *abnrm, floatreal *bbnrm, floatreal *rconde, floatreal *rcondv, floatreal *work, 
	integer *lwork, integer *iwork, logical *bwork, integer *info);

/* Subroutine */ int sggglm_(integer *n, integer *m, integer *p, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, floatreal *d__, floatreal *x, floatreal *y, 
	floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgghrd_(char *compq, char *compz, integer *n, integer *
	ilo, integer *ihi, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal 
	*q, integer *ldq, floatreal *z__, integer *ldz, integer *info);

/* Subroutine */ int sgglse_(integer *m, integer *n, integer *p, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, floatreal *c__, floatreal *d__, floatreal *x, 
	floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sggqrf_(integer *n, integer *m, integer *p, floatreal *a, 
	integer *lda, floatreal *taua, floatreal *b, integer *ldb, floatreal *taub, floatreal *
	work, integer *lwork, integer *info);

/* Subroutine */ int sggrqf_(integer *m, integer *p, integer *n, floatreal *a, 
	integer *lda, floatreal *taua, floatreal *b, integer *ldb, floatreal *taub, floatreal *
	work, integer *lwork, integer *info);

/* Subroutine */ int sggsvd_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *n, integer *p, integer *k, integer *l, floatreal *a, integer *lda, 
	 floatreal *b, integer *ldb, floatreal *alpha, floatreal *beta, floatreal *u, integer *
	ldu, floatreal *v, integer *ldv, floatreal *q, integer *ldq, floatreal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int sggsvp_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *p, integer *n, floatreal *a, integer *lda, floatreal *b, integer *ldb, 
	floatreal *tola, floatreal *tolb, integer *k, integer *l, floatreal *u, integer *ldu, 
	 floatreal *v, integer *ldv, floatreal *q, integer *ldq, integer *iwork, floatreal *
	tau, floatreal *work, integer *info);

/* Subroutine */ int sgsvj0_(char *jobv, integer *m, integer *n, floatreal *a, 
	integer *lda, floatreal *d__, floatreal *sva, integer *mv, floatreal *v, integer *
	ldv, floatreal *eps, floatreal *sfmin, floatreal *tol, integer *nsweep, floatreal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int sgsvj1_(char *jobv, integer *m, integer *n, integer *n1, 
	floatreal *a, integer *lda, floatreal *d__, floatreal *sva, integer *mv, floatreal *v, 
	integer *ldv, floatreal *eps, floatreal *sfmin, floatreal *tol, integer *nsweep, 
	floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sgtcon_(char *norm, integer *n, floatreal *dl, floatreal *d__, 
	floatreal *du, floatreal *du2, integer *ipiv, floatreal *anorm, floatreal *rcond, floatreal *
	work, integer *iwork, integer *info);

/* Subroutine */ int sgtrfs_(char *trans, integer *n, integer *nrhs, floatreal *dl, 
	 floatreal *d__, floatreal *du, floatreal *dlf, floatreal *df, floatreal *duf, floatreal *du2, 
	integer *ipiv, floatreal *b, integer *ldb, floatreal *x, integer *ldx, floatreal *
	ferr, floatreal *berr, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sgtsv_(integer *n, integer *nrhs, floatreal *dl, floatreal *d__, 
	floatreal *du, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sgtsvx_(char *fact, char *trans, integer *n, integer *
	nrhs, floatreal *dl, floatreal *d__, floatreal *du, floatreal *dlf, floatreal *df, floatreal *duf, 
	floatreal *du2, integer *ipiv, floatreal *b, integer *ldb, floatreal *x, integer *
	ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, floatreal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int sgttrf_(integer *n, floatreal *dl, floatreal *d__, floatreal *du, floatreal *
	du2, integer *ipiv, integer *info);

/* Subroutine */ int sgttrs_(char *trans, integer *n, integer *nrhs, floatreal *dl, 
	 floatreal *d__, floatreal *du, floatreal *du2, integer *ipiv, floatreal *b, integer *ldb, 
	 integer *info);

/* Subroutine */ int sgtts2_(integer *itrans, integer *n, integer *nrhs, floatreal 
	*dl, floatreal *d__, floatreal *du, floatreal *du2, integer *ipiv, floatreal *b, integer *
	ldb);

/* Subroutine */ int shgeqz_(char *job, char *compq, char *compz, integer *n, 
	integer *ilo, integer *ihi, floatreal *h__, integer *ldh, floatreal *t, integer 
	*ldt, floatreal *alphar, floatreal *alphai, floatreal *beta, floatreal *q, integer *ldq, 
	floatreal *z__, integer *ldz, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int shsein_(char *side, char *eigsrc, char *initv, logical *
	select, integer *n, floatreal *h__, integer *ldh, floatreal *wr, floatreal *wi, floatreal 
	*vl, integer *ldvl, floatreal *vr, integer *ldvr, integer *mm, integer *m, 
	floatreal *work, integer *ifaill, integer *ifailr, integer *info);

/* Subroutine */ int shseqr_(char *job, char *compz, integer *n, integer *ilo, 
	 integer *ihi, floatreal *h__, integer *ldh, floatreal *wr, floatreal *wi, floatreal *z__, 
	 integer *ldz, floatreal *work, integer *lwork, integer *info);

logical sisnan_(floatreal *sin__);

/* Subroutine */ int sla_gbamv__(integer *trans, integer *m, integer *n, 
	integer *kl, integer *ku, floatreal *alpha, floatreal *ab, integer *ldab, floatreal *
	x, integer *incx, floatreal *beta, floatreal *y, integer *incy);

doublereal sla_gbrcond__(char *trans, integer *n, integer *kl, integer *ku, 
	floatreal *ab, integer *ldab, floatreal *afb, integer *ldafb, integer *ipiv, 
	integer *cmode, floatreal *c__, integer *info, floatreal *work, integer *iwork, 
	ftnlen trans_len);

/* Subroutine */ int sla_gbrfsx_extended__(integer *prec_type__, integer *
	trans_type__, integer *n, integer *kl, integer *ku, integer *nrhs, 
	floatreal *ab, integer *ldab, floatreal *afb, integer *ldafb, integer *ipiv, 
	logical *colequ, floatreal *c__, floatreal *b, integer *ldb, floatreal *y, integer *
	ldy, floatreal *berr_out__, integer *n_norms__, floatreal *errs_n__, floatreal *
	errs_c__, floatreal *res, floatreal *ayb, floatreal *dy, floatreal *y_tail__, floatreal *rcond,
	 integer *ithresh, floatreal *rthresh, floatreal *dz_ub__, logical *
	ignore_cwise__, integer *info);

doublereal sla_gbrpvgrw__(integer *n, integer *kl, integer *ku, integer *
	ncols, floatreal *ab, integer *ldab, floatreal *afb, integer *ldafb);

/* Subroutine */ int sla_geamv__(integer *trans, integer *m, integer *n, floatreal 
	*alpha, floatreal *a, integer *lda, floatreal *x, integer *incx, floatreal *beta, 
	floatreal *y, integer *incy);

doublereal sla_gercond__(char *trans, integer *n, floatreal *a, integer *lda, floatreal 
	*af, integer *ldaf, integer *ipiv, integer *cmode, floatreal *c__, integer 
	*info, floatreal *work, integer *iwork, ftnlen trans_len);

/* Subroutine */ int sla_gerfsx_extended__(integer *prec_type__, integer *
	trans_type__, integer *n, integer *nrhs, floatreal *a, integer *lda, floatreal *
	af, integer *ldaf, integer *ipiv, logical *colequ, floatreal *c__, floatreal *b,
	 integer *ldb, floatreal *y, integer *ldy, floatreal *berr_out__, integer *
	n_norms__, floatreal *errs_n__, floatreal *errs_c__, floatreal *res, floatreal *ayb, floatreal 
	*dy, floatreal *y_tail__, floatreal *rcond, integer *ithresh, floatreal *rthresh, 
	floatreal *dz_ub__, logical *ignore_cwise__, integer *info);

/* Subroutine */ int sla_lin_berr__(integer *n, integer *nz, integer *nrhs, 
	floatreal *res, floatreal *ayb, floatreal *berr);

doublereal sla_porcond__(char *uplo, integer *n, floatreal *a, integer *lda, floatreal *
	af, integer *ldaf, integer *cmode, floatreal *c__, integer *info, floatreal *
	work, integer *iwork, ftnlen uplo_len);

/* Subroutine */ int sla_porfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, floatreal *a, integer *lda, floatreal *af, integer *
	ldaf, logical *colequ, floatreal *c__, floatreal *b, integer *ldb, floatreal *y, 
	integer *ldy, floatreal *berr_out__, integer *n_norms__, floatreal *errs_n__, 
	floatreal *errs_c__, floatreal *res, floatreal *ayb, floatreal *dy, floatreal *y_tail__, floatreal *
	rcond, integer *ithresh, floatreal *rthresh, floatreal *dz_ub__, logical *
	ignore_cwise__, integer *info, ftnlen uplo_len);

doublereal sla_porpvgrw__(char *uplo, integer *ncols, floatreal *a, integer *lda, 
	floatreal *af, integer *ldaf, floatreal *work, ftnlen uplo_len);

doublereal sla_rpvgrw__(integer *n, integer *ncols, floatreal *a, integer *lda, 
	floatreal *af, integer *ldaf);

/* Subroutine */ int sla_syamv__(integer *uplo, integer *n, floatreal *alpha, floatreal 
	*a, integer *lda, floatreal *x, integer *incx, floatreal *beta, floatreal *y, 
	integer *incy);

doublereal sla_syrcond__(char *uplo, integer *n, floatreal *a, integer *lda, floatreal *
	af, integer *ldaf, integer *ipiv, integer *cmode, floatreal *c__, integer *
	info, floatreal *work, integer *iwork, ftnlen uplo_len);

/* Subroutine */ int sla_syrfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, floatreal *a, integer *lda, floatreal *af, integer *
	ldaf, integer *ipiv, logical *colequ, floatreal *c__, floatreal *b, integer *
	ldb, floatreal *y, integer *ldy, floatreal *berr_out__, integer *n_norms__, 
	floatreal *errs_n__, floatreal *errs_c__, floatreal *res, floatreal *ayb, floatreal *dy, floatreal *
	y_tail__, floatreal *rcond, integer *ithresh, floatreal *rthresh, floatreal *dz_ub__,
	 logical *ignore_cwise__, integer *info, ftnlen uplo_len);

doublereal sla_syrpvgrw__(char *uplo, integer *n, integer *info, floatreal *a, 
	integer *lda, floatreal *af, integer *ldaf, integer *ipiv, floatreal *work, 
	ftnlen uplo_len);

/* Subroutine */ int sla_wwaddw__(integer *n, floatreal *x, floatreal *y, floatreal *w);

/* Subroutine */ int slabad_(floatreal *small, floatreal *large);

/* Subroutine */ int slabrd_(integer *m, integer *n, integer *nb, floatreal *a, 
	integer *lda, floatreal *d__, floatreal *e, floatreal *tauq, floatreal *taup, floatreal *x, 
	integer *ldx, floatreal *y, integer *ldy);

/* Subroutine */ int slacn2_(integer *n, floatreal *v, floatreal *x, integer *isgn, 
	floatreal *est, integer *kase, integer *isave);

/* Subroutine */ int slacon_(integer *n, floatreal *v, floatreal *x, integer *isgn, 
	floatreal *est, integer *kase);

/* Subroutine */ int slacpy_(char *uplo, integer *m, integer *n, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb);

/* Subroutine */ int sladiv_(floatreal *a, floatreal *b, floatreal *c__, floatreal *d__, floatreal *p, 
	floatreal *q);

/* Subroutine */ int slae2_(floatreal *a, floatreal *b, floatreal *c__, floatreal *rt1, floatreal *rt2);

/* Subroutine */ int slaebz_(integer *ijob, integer *nitmax, integer *n, 
	integer *mmax, integer *minp, integer *nbmin, floatreal *abstol, floatreal *
	reltol, floatreal *pivmin, floatreal *d__, floatreal *e, floatreal *e2, integer *nval, 
	floatreal *ab, floatreal *c__, integer *mout, integer *nab, floatreal *work, integer 
	*iwork, integer *info);

/* Subroutine */ int slaed0_(integer *icompq, integer *qsiz, integer *n, floatreal 
	*d__, floatreal *e, floatreal *q, integer *ldq, floatreal *qstore, integer *ldqs, 
	floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int slaed1_(integer *n, floatreal *d__, floatreal *q, integer *ldq, 
	integer *indxq, floatreal *rho, integer *cutpnt, floatreal *work, integer *
	iwork, integer *info);

/* Subroutine */ int slaed2_(integer *k, integer *n, integer *n1, floatreal *d__, 
	floatreal *q, integer *ldq, integer *indxq, floatreal *rho, floatreal *z__, floatreal *
	dlamda, floatreal *w, floatreal *q2, integer *indx, integer *indxc, integer *
	indxp, integer *coltyp, integer *info);

/* Subroutine */ int slaed3_(integer *k, integer *n, integer *n1, floatreal *d__, 
	floatreal *q, integer *ldq, floatreal *rho, floatreal *dlamda, floatreal *q2, integer *
	indx, integer *ctot, floatreal *w, floatreal *s, integer *info);

/* Subroutine */ int slaed4_(integer *n, integer *i__, floatreal *d__, floatreal *z__, 
	floatreal *delta, floatreal *rho, floatreal *dlam, integer *info);

/* Subroutine */ int slaed5_(integer *i__, floatreal *d__, floatreal *z__, floatreal *delta, 
	floatreal *rho, floatreal *dlam);

/* Subroutine */ int slaed6_(integer *kniter, logical *orgati, floatreal *rho, 
	floatreal *d__, floatreal *z__, floatreal *finit, floatreal *tau, integer *info);

/* Subroutine */ int slaed7_(integer *icompq, integer *n, integer *qsiz, 
	integer *tlvls, integer *curlvl, integer *curpbm, floatreal *d__, floatreal *q, 
	integer *ldq, integer *indxq, floatreal *rho, integer *cutpnt, floatreal *
	qstore, integer *qptr, integer *prmptr, integer *perm, integer *
	givptr, integer *givcol, floatreal *givnum, floatreal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int slaed8_(integer *icompq, integer *k, integer *n, integer 
	*qsiz, floatreal *d__, floatreal *q, integer *ldq, integer *indxq, floatreal *rho, 
	integer *cutpnt, floatreal *z__, floatreal *dlamda, floatreal *q2, integer *ldq2, 
	floatreal *w, integer *perm, integer *givptr, integer *givcol, floatreal *
	givnum, integer *indxp, integer *indx, integer *info);

/* Subroutine */ int slaed9_(integer *k, integer *kstart, integer *kstop, 
	integer *n, floatreal *d__, floatreal *q, integer *ldq, floatreal *rho, floatreal *dlamda, 
	 floatreal *w, floatreal *s, integer *lds, integer *info);

/* Subroutine */ int slaeda_(integer *n, integer *tlvls, integer *curlvl, 
	integer *curpbm, integer *prmptr, integer *perm, integer *givptr, 
	integer *givcol, floatreal *givnum, floatreal *q, integer *qptr, floatreal *z__, 
	floatreal *ztemp, integer *info);

/* Subroutine */ int slaein_(logical *rightv, logical *noinit, integer *n, 
	floatreal *h__, integer *ldh, floatreal *wr, floatreal *wi, floatreal *vr, floatreal *vi, floatreal 
	*b, integer *ldb, floatreal *work, floatreal *eps3, floatreal *smlnum, floatreal *bignum, 
	integer *info);

/* Subroutine */ int slaev2_(floatreal *a, floatreal *b, floatreal *c__, floatreal *rt1, floatreal *
	rt2, floatreal *cs1, floatreal *sn1);

/* Subroutine */ int slaexc_(logical *wantq, integer *n, floatreal *t, integer *
	ldt, floatreal *q, integer *ldq, integer *j1, integer *n1, integer *n2, 
	floatreal *work, integer *info);

/* Subroutine */ int slag2_(floatreal *a, integer *lda, floatreal *b, integer *ldb, 
	floatreal *safmin, floatreal *scale1, floatreal *scale2, floatreal *wr1, floatreal *wr2, floatreal *
	wi);

/* Subroutine */ int slag2d_(integer *m, integer *n, floatreal *sa, integer *ldsa, 
	doublereal *a, integer *lda, integer *info);

/* Subroutine */ int slags2_(logical *upper, floatreal *a1, floatreal *a2, floatreal *a3, 
	floatreal *b1, floatreal *b2, floatreal *b3, floatreal *csu, floatreal *snu, floatreal *csv, floatreal *
	snv, floatreal *csq, floatreal *snq);

/* Subroutine */ int slagtf_(integer *n, floatreal *a, floatreal *lambda, floatreal *b, floatreal 
	*c__, floatreal *tol, floatreal *d__, integer *in, integer *info);

/* Subroutine */ int slagtm_(char *trans, integer *n, integer *nrhs, floatreal *
	alpha, floatreal *dl, floatreal *d__, floatreal *du, floatreal *x, integer *ldx, floatreal *
	beta, floatreal *b, integer *ldb);

/* Subroutine */ int slagts_(integer *job, integer *n, floatreal *a, floatreal *b, floatreal 
	*c__, floatreal *d__, integer *in, floatreal *y, floatreal *tol, integer *info);

/* Subroutine */ int slagv2_(floatreal *a, integer *lda, floatreal *b, integer *ldb, 
	floatreal *alphar, floatreal *alphai, floatreal *beta, floatreal *csl, floatreal *snl, floatreal *
	csr, floatreal *snr);

/* Subroutine */ int slahqr_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, floatreal *h__, integer *ldh, floatreal *wr, floatreal *
	wi, integer *iloz, integer *ihiz, floatreal *z__, integer *ldz, integer *
	info);

/* Subroutine */ int slahr2_(integer *n, integer *k, integer *nb, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *t, integer *ldt, floatreal *y, integer *ldy);

/* Subroutine */ int slahrd_(integer *n, integer *k, integer *nb, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *t, integer *ldt, floatreal *y, integer *ldy);

/* Subroutine */ int slaic1_(integer *job, integer *j, floatreal *x, floatreal *sest, 
	floatreal *w, floatreal *gamma, floatreal *sestpr, floatreal *s, floatreal *c__);

logical slaisnan_(floatreal *sin1, floatreal *sin2);

/* Subroutine */ int slaln2_(logical *ltrans, integer *na, integer *nw, floatreal *
	smin, floatreal *ca, floatreal *a, integer *lda, floatreal *d1, floatreal *d2, floatreal *b, 
	integer *ldb, floatreal *wr, floatreal *wi, floatreal *x, integer *ldx, floatreal *scale, 
	floatreal *xnorm, integer *info);

/* Subroutine */ int slals0_(integer *icompq, integer *nl, integer *nr, 
	integer *sqre, integer *nrhs, floatreal *b, integer *ldb, floatreal *bx, 
	integer *ldbx, integer *perm, integer *givptr, integer *givcol, 
	integer *ldgcol, floatreal *givnum, integer *ldgnum, floatreal *poles, floatreal *
	difl, floatreal *difr, floatreal *z__, integer *k, floatreal *c__, floatreal *s, floatreal *
	work, integer *info);

/* Subroutine */ int slalsa_(integer *icompq, integer *smlsiz, integer *n, 
	integer *nrhs, floatreal *b, integer *ldb, floatreal *bx, integer *ldbx, floatreal *
	u, integer *ldu, floatreal *vt, integer *k, floatreal *difl, floatreal *difr, floatreal *
	z__, floatreal *poles, integer *givptr, integer *givcol, integer *ldgcol, 
	integer *perm, floatreal *givnum, floatreal *c__, floatreal *s, floatreal *work, integer *
	iwork, integer *info);

/* Subroutine */ int slalsd_(char *uplo, integer *smlsiz, integer *n, integer 
	*nrhs, floatreal *d__, floatreal *e, floatreal *b, integer *ldb, floatreal *rcond, 
	integer *rank, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int slamrg_(integer *n1, integer *n2, floatreal *a, integer *
	strd1, integer *strd2, integer *index);

integer slaneg_(integer *n, floatreal *d__, floatreal *lld, floatreal *sigma, floatreal *pivmin, 
	integer *r__);

doublereal slangb_(char *norm, integer *n, integer *kl, integer *ku, floatreal *ab, 
	 integer *ldab, floatreal *work);

doublereal slange_(char *norm, integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *work);

doublereal slangt_(char *norm, integer *n, floatreal *dl, floatreal *d__, floatreal *du);

doublereal slanhs_(char *norm, integer *n, floatreal *a, integer *lda, floatreal *work);

doublereal slansb_(char *norm, char *uplo, integer *n, integer *k, floatreal *ab, 
	integer *ldab, floatreal *work);

doublereal slansf_(char *norm, char *transr, char *uplo, integer *n, floatreal *a, 
	floatreal *work);

doublereal slansp_(char *norm, char *uplo, integer *n, floatreal *ap, floatreal *work);

doublereal slanst_(char *norm, integer *n, floatreal *d__, floatreal *e);

doublereal slansy_(char *norm, char *uplo, integer *n, floatreal *a, integer *lda, 
	floatreal *work);

doublereal slantb_(char *norm, char *uplo, char *diag, integer *n, integer *k, 
	 floatreal *ab, integer *ldab, floatreal *work);

doublereal slantp_(char *norm, char *uplo, char *diag, integer *n, floatreal *ap, 
	floatreal *work);

doublereal slantr_(char *norm, char *uplo, char *diag, integer *m, integer *n, 
	 floatreal *a, integer *lda, floatreal *work);

/* Subroutine */ int slanv2_(floatreal *a, floatreal *b, floatreal *c__, floatreal *d__, floatreal *
	rt1r, floatreal *rt1i, floatreal *rt2r, floatreal *rt2i, floatreal *cs, floatreal *sn);

/* Subroutine */ int slapll_(integer *n, floatreal *x, integer *incx, floatreal *y, 
	integer *incy, floatreal *ssmin);

/* Subroutine */ int slapmt_(logical *forwrd, integer *m, integer *n, floatreal *x, 
	 integer *ldx, integer *k);

doublereal slapy2_(floatreal *x, floatreal *y);

doublereal slapy3_(floatreal *x, floatreal *y, floatreal *z__);

/* Subroutine */ int slaqgb_(integer *m, integer *n, integer *kl, integer *ku, 
	 floatreal *ab, integer *ldab, floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal *
	colcnd, floatreal *amax, char *equed);

/* Subroutine */ int slaqge_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *r__, floatreal *c__, floatreal *rowcnd, floatreal *colcnd, floatreal *amax, char *
	equed);

/* Subroutine */ int slaqp2_(integer *m, integer *n, integer *offset, floatreal *a, 
	 integer *lda, integer *jpvt, floatreal *tau, floatreal *vn1, floatreal *vn2, floatreal *
	work);

/* Subroutine */ int slaqps_(integer *m, integer *n, integer *offset, integer 
	*nb, integer *kb, floatreal *a, integer *lda, integer *jpvt, floatreal *tau, 
	floatreal *vn1, floatreal *vn2, floatreal *auxv, floatreal *f, integer *ldf);

/* Subroutine */ int slaqr0_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, floatreal *h__, integer *ldh, floatreal *wr, floatreal *
	wi, integer *iloz, integer *ihiz, floatreal *z__, integer *ldz, floatreal *work, 
	 integer *lwork, integer *info);

/* Subroutine */ int slaqr1_(integer *n, floatreal *h__, integer *ldh, floatreal *sr1, 
	floatreal *si1, floatreal *sr2, floatreal *si2, floatreal *v);

/* Subroutine */ int slaqr2_(logical *wantt, logical *wantz, integer *n, 
	integer *ktop, integer *kbot, integer *nw, floatreal *h__, integer *ldh, 
	integer *iloz, integer *ihiz, floatreal *z__, integer *ldz, integer *ns, 
	integer *nd, floatreal *sr, floatreal *si, floatreal *v, integer *ldv, integer *nh, 
	floatreal *t, integer *ldt, integer *nv, floatreal *wv, integer *ldwv, floatreal *
	work, integer *lwork);

/* Subroutine */ int slaqr3_(logical *wantt, logical *wantz, integer *n, 
	integer *ktop, integer *kbot, integer *nw, floatreal *h__, integer *ldh, 
	integer *iloz, integer *ihiz, floatreal *z__, integer *ldz, integer *ns, 
	integer *nd, floatreal *sr, floatreal *si, floatreal *v, integer *ldv, integer *nh, 
	floatreal *t, integer *ldt, integer *nv, floatreal *wv, integer *ldwv, floatreal *
	work, integer *lwork);

/* Subroutine */ int slaqr4_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, floatreal *h__, integer *ldh, floatreal *wr, floatreal *
	wi, integer *iloz, integer *ihiz, floatreal *z__, integer *ldz, floatreal *work, 
	 integer *lwork, integer *info);

/* Subroutine */ int slaqr5_(logical *wantt, logical *wantz, integer *kacc22, 
	integer *n, integer *ktop, integer *kbot, integer *nshfts, floatreal *sr, 
	floatreal *si, floatreal *h__, integer *ldh, integer *iloz, integer *ihiz, floatreal 
	*z__, integer *ldz, floatreal *v, integer *ldv, floatreal *u, integer *ldu, 
	integer *nv, floatreal *wv, integer *ldwv, integer *nh, floatreal *wh, integer *
	ldwh);

/* Subroutine */ int slaqsb_(char *uplo, integer *n, integer *kd, floatreal *ab, 
	integer *ldab, floatreal *s, floatreal *scond, floatreal *amax, char *equed);

/* Subroutine */ int slaqsp_(char *uplo, integer *n, floatreal *ap, floatreal *s, floatreal *
	scond, floatreal *amax, char *equed);

/* Subroutine */ int slaqsy_(char *uplo, integer *n, floatreal *a, integer *lda, 
	floatreal *s, floatreal *scond, floatreal *amax, char *equed);

/* Subroutine */ int slaqtr_(logical *ltran, logical *lreal, integer *n, floatreal 
	*t, integer *ldt, floatreal *b, floatreal *w, floatreal *scale, floatreal *x, floatreal *work, 
	integer *info);

/* Subroutine */ int slar1v_(integer *n, integer *b1, integer *bn, floatreal *
	lambda, floatreal *d__, floatreal *l, floatreal *ld, floatreal *lld, floatreal *pivmin, floatreal *
	gaptol, floatreal *z__, logical *wantnc, integer *negcnt, floatreal *ztz, floatreal *
	mingma, integer *r__, integer *isuppz, floatreal *nrminv, floatreal *resid, 
	floatreal *rqcorr, floatreal *work);

/* Subroutine */ int slar2v_(integer *n, floatreal *x, floatreal *y, floatreal *z__, integer 
	*incx, floatreal *c__, floatreal *s, integer *incc);

/* Subroutine */ int slarf_(char *side, integer *m, integer *n, floatreal *v, 
	integer *incv, floatreal *tau, floatreal *c__, integer *ldc, floatreal *work);

/* Subroutine */ int slarfb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, floatreal *v, integer *ldv, 
	floatreal *t, integer *ldt, floatreal *c__, integer *ldc, floatreal *work, integer *
	ldwork);

/* Subroutine */ int slarfg_(integer *n, floatreal *alpha, floatreal *x, integer *incx, 
	floatreal *tau);

/* Subroutine */ int slarfp_(integer *n, floatreal *alpha, floatreal *x, integer *incx, 
	floatreal *tau);

/* Subroutine */ int slarft_(char *direct, char *storev, integer *n, integer *
	k, floatreal *v, integer *ldv, floatreal *tau, floatreal *t, integer *ldt);

/* Subroutine */ int slarfx_(char *side, integer *m, integer *n, floatreal *v, 
	floatreal *tau, floatreal *c__, integer *ldc, floatreal *work);

/* Subroutine */ int slargv_(integer *n, floatreal *x, integer *incx, floatreal *y, 
	integer *incy, floatreal *c__, integer *incc);

/* Subroutine */ int slarnv_(integer *idist, integer *iseed, integer *n, floatreal 
	*x);

/* Subroutine */ int slarra_(integer *n, floatreal *d__, floatreal *e, floatreal *e2, floatreal *
	spltol, floatreal *tnrm, integer *nsplit, integer *isplit, integer *info);

/* Subroutine */ int slarrb_(integer *n, floatreal *d__, floatreal *lld, integer *
	ifirst, integer *ilast, floatreal *rtol1, floatreal *rtol2, integer *offset, 
	floatreal *w, floatreal *wgap, floatreal *werr, floatreal *work, integer *iwork, floatreal *
	pivmin, floatreal *spdiam, integer *twist, integer *info);

/* Subroutine */ int slarrc_(char *jobt, integer *n, floatreal *vl, floatreal *vu, floatreal 
	*d__, floatreal *e, floatreal *pivmin, integer *eigcnt, integer *lcnt, integer *
	rcnt, integer *info);

/* Subroutine */ int slarrd_(char *range, char *order, integer *n, floatreal *vl, 
	floatreal *vu, integer *il, integer *iu, floatreal *gers, floatreal *reltol, floatreal *
	d__, floatreal *e, floatreal *e2, floatreal *pivmin, integer *nsplit, integer *
	isplit, integer *m, floatreal *w, floatreal *werr, floatreal *wl, floatreal *wu, integer *
	iblock, integer *indexw, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int slarre_(char *range, integer *n, floatreal *vl, floatreal *vu, 
	integer *il, integer *iu, floatreal *d__, floatreal *e, floatreal *e2, floatreal *rtol1, 
	floatreal *rtol2, floatreal *spltol, integer *nsplit, integer *isplit, integer *
	m, floatreal *w, floatreal *werr, floatreal *wgap, integer *iblock, integer *indexw, 
	floatreal *gers, floatreal *pivmin, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int slarrf_(integer *n, floatreal *d__, floatreal *l, floatreal *ld, 
	integer *clstrt, integer *clend, floatreal *w, floatreal *wgap, floatreal *werr, 
	floatreal *spdiam, floatreal *clgapl, floatreal *clgapr, floatreal *pivmin, floatreal *sigma, 
	floatreal *dplus, floatreal *lplus, floatreal *work, integer *info);

/* Subroutine */ int slarrj_(integer *n, floatreal *d__, floatreal *e2, integer *ifirst, 
	 integer *ilast, floatreal *rtol, integer *offset, floatreal *w, floatreal *werr, 
	floatreal *work, integer *iwork, floatreal *pivmin, floatreal *spdiam, integer *info);

/* Subroutine */ int slarrk_(integer *n, integer *iw, floatreal *gl, floatreal *gu, 
	floatreal *d__, floatreal *e2, floatreal *pivmin, floatreal *reltol, floatreal *w, floatreal *werr, 
	integer *info);

/* Subroutine */ int slarrr_(integer *n, floatreal *d__, floatreal *e, integer *info);

/* Subroutine */ int slarrv_(integer *n, floatreal *vl, floatreal *vu, floatreal *d__, floatreal *
	l, floatreal *pivmin, integer *isplit, integer *m, integer *dol, integer *
	dou, floatreal *minrgp, floatreal *rtol1, floatreal *rtol2, floatreal *w, floatreal *werr, 
	floatreal *wgap, integer *iblock, integer *indexw, floatreal *gers, floatreal *z__, 
	integer *ldz, integer *isuppz, floatreal *work, integer *iwork, integer *
	info);

/* Subroutine */ int slarscl2_(integer *m, integer *n, floatreal *d__, floatreal *x, 
	integer *ldx);

/* Subroutine */ int slartg_(floatreal *f, floatreal *g, floatreal *cs, floatreal *sn, floatreal *r__);

/* Subroutine */ int slartv_(integer *n, floatreal *x, integer *incx, floatreal *y, 
	integer *incy, floatreal *c__, floatreal *s, integer *incc);

/* Subroutine */ int slaruv_(integer *iseed, integer *n, floatreal *x);

/* Subroutine */ int slarz_(char *side, integer *m, integer *n, integer *l, 
	floatreal *v, integer *incv, floatreal *tau, floatreal *c__, integer *ldc, floatreal *
	work);

/* Subroutine */ int slarzb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, integer *l, floatreal *v, 
	integer *ldv, floatreal *t, integer *ldt, floatreal *c__, integer *ldc, floatreal *
	work, integer *ldwork);

/* Subroutine */ int slarzt_(char *direct, char *storev, integer *n, integer *
	k, floatreal *v, integer *ldv, floatreal *tau, floatreal *t, integer *ldt);

/* Subroutine */ int slas2_(floatreal *f, floatreal *g, floatreal *h__, floatreal *ssmin, floatreal *
	ssmax);

/* Subroutine */ int slascl_(char *type__, integer *kl, integer *ku, floatreal *
	cfrom, floatreal *cto, integer *m, integer *n, floatreal *a, integer *lda, 
	integer *info);

/* Subroutine */ int slascl2_(integer *m, integer *n, floatreal *d__, floatreal *x, 
	integer *ldx);

/* Subroutine */ int slasd0_(integer *n, integer *sqre, floatreal *d__, floatreal *e, 
	floatreal *u, integer *ldu, floatreal *vt, integer *ldvt, integer *smlsiz, 
	integer *iwork, floatreal *work, integer *info);

/* Subroutine */ int slasd1_(integer *nl, integer *nr, integer *sqre, floatreal *
	d__, floatreal *alpha, floatreal *beta, floatreal *u, integer *ldu, floatreal *vt, 
	integer *ldvt, integer *idxq, integer *iwork, floatreal *work, integer *
	info);

/* Subroutine */ int slasd2_(integer *nl, integer *nr, integer *sqre, integer 
	*k, floatreal *d__, floatreal *z__, floatreal *alpha, floatreal *beta, floatreal *u, integer *
	ldu, floatreal *vt, integer *ldvt, floatreal *dsigma, floatreal *u2, integer *ldu2, 
	floatreal *vt2, integer *ldvt2, integer *idxp, integer *idx, integer *idxc, 
	 integer *idxq, integer *coltyp, integer *info);

/* Subroutine */ int slasd3_(integer *nl, integer *nr, integer *sqre, integer 
	*k, floatreal *d__, floatreal *q, integer *ldq, floatreal *dsigma, floatreal *u, integer *
	ldu, floatreal *u2, integer *ldu2, floatreal *vt, integer *ldvt, floatreal *vt2, 
	integer *ldvt2, integer *idxc, integer *ctot, floatreal *z__, integer *
	info);

/* Subroutine */ int slasd4_(integer *n, integer *i__, floatreal *d__, floatreal *z__, 
	floatreal *delta, floatreal *rho, floatreal *sigma, floatreal *work, integer *info);

/* Subroutine */ int slasd5_(integer *i__, floatreal *d__, floatreal *z__, floatreal *delta, 
	floatreal *rho, floatreal *dsigma, floatreal *work);

/* Subroutine */ int slasd6_(integer *icompq, integer *nl, integer *nr, 
	integer *sqre, floatreal *d__, floatreal *vf, floatreal *vl, floatreal *alpha, floatreal *beta, 
	 integer *idxq, integer *perm, integer *givptr, integer *givcol, 
	integer *ldgcol, floatreal *givnum, integer *ldgnum, floatreal *poles, floatreal *
	difl, floatreal *difr, floatreal *z__, integer *k, floatreal *c__, floatreal *s, floatreal *
	work, integer *iwork, integer *info);

/* Subroutine */ int slasd7_(integer *icompq, integer *nl, integer *nr, 
	integer *sqre, integer *k, floatreal *d__, floatreal *z__, floatreal *zw, floatreal *vf, 
	floatreal *vfw, floatreal *vl, floatreal *vlw, floatreal *alpha, floatreal *beta, floatreal *dsigma, 
	 integer *idx, integer *idxp, integer *idxq, integer *perm, integer *
	givptr, integer *givcol, integer *ldgcol, floatreal *givnum, integer *
	ldgnum, floatreal *c__, floatreal *s, integer *info);

/* Subroutine */ int slasd8_(integer *icompq, integer *k, floatreal *d__, floatreal *
	z__, floatreal *vf, floatreal *vl, floatreal *difl, floatreal *difr, integer *lddifr, 
	floatreal *dsigma, floatreal *work, integer *info);

/* Subroutine */ int slasda_(integer *icompq, integer *smlsiz, integer *n, 
	integer *sqre, floatreal *d__, floatreal *e, floatreal *u, integer *ldu, floatreal *vt, 
	integer *k, floatreal *difl, floatreal *difr, floatreal *z__, floatreal *poles, integer *
	givptr, integer *givcol, integer *ldgcol, integer *perm, floatreal *givnum, 
	 floatreal *c__, floatreal *s, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int slasdq_(char *uplo, integer *sqre, integer *n, integer *
	ncvt, integer *nru, integer *ncc, floatreal *d__, floatreal *e, floatreal *vt, 
	integer *ldvt, floatreal *u, integer *ldu, floatreal *c__, integer *ldc, floatreal *
	work, integer *info);

/* Subroutine */ int slasdt_(integer *n, integer *lvl, integer *nd, integer *
	inode, integer *ndiml, integer *ndimr, integer *msub);

/* Subroutine */ int slaset_(char *uplo, integer *m, integer *n, floatreal *alpha, 
	floatreal *beta, floatreal *a, integer *lda);

/* Subroutine */ int slasq1_(integer *n, floatreal *d__, floatreal *e, floatreal *work, 
	integer *info);

/* Subroutine */ int slasq2_(integer *n, floatreal *z__, integer *info);

/* Subroutine */ int slasq3_(integer *i0, integer *n0, floatreal *z__, integer *pp, 
	 floatreal *dmin__, floatreal *sigma, floatreal *desig, floatreal *qmax, integer *nfail, 
	integer *iter, integer *ndiv, logical *ieee, integer *ttype, floatreal *
	dmin1, floatreal *dmin2, floatreal *dn, floatreal *dn1, floatreal *dn2, floatreal *g, floatreal *
	tau);

/* Subroutine */ int slasq4_(integer *i0, integer *n0, floatreal *z__, integer *pp, 
	 integer *n0in, floatreal *dmin__, floatreal *dmin1, floatreal *dmin2, floatreal *dn, 
	floatreal *dn1, floatreal *dn2, floatreal *tau, integer *ttype, floatreal *g);

/* Subroutine */ int slasq5_(integer *i0, integer *n0, floatreal *z__, integer *pp, 
	 floatreal *tau, floatreal *dmin__, floatreal *dmin1, floatreal *dmin2, floatreal *dn, floatreal *
	dnm1, floatreal *dnm2, logical *ieee);

/* Subroutine */ int slasq6_(integer *i0, integer *n0, floatreal *z__, integer *pp, 
	 floatreal *dmin__, floatreal *dmin1, floatreal *dmin2, floatreal *dn, floatreal *dnm1, floatreal *
	dnm2);

/* Subroutine */ int slasr_(char *side, char *pivot, char *direct, integer *m, 
	 integer *n, floatreal *c__, floatreal *s, floatreal *a, integer *lda);

/* Subroutine */ int slasrt_(char *id, integer *n, floatreal *d__, integer *info);

/* Subroutine */ int slassq_(integer *n, floatreal *x, integer *incx, floatreal *scale, 
	floatreal *sumsq);

/* Subroutine */ int slasv2_(floatreal *f, floatreal *g, floatreal *h__, floatreal *ssmin, floatreal *
	ssmax, floatreal *snr, floatreal *csr, floatreal *snl, floatreal *csl);

/* Subroutine */ int slaswp_(integer *n, floatreal *a, integer *lda, integer *k1, 
	integer *k2, integer *ipiv, integer *incx);

/* Subroutine */ int slasy2_(logical *ltranl, logical *ltranr, integer *isgn, 
	integer *n1, integer *n2, floatreal *tl, integer *ldtl, floatreal *tr, integer *
	ldtr, floatreal *b, integer *ldb, floatreal *scale, floatreal *x, integer *ldx, floatreal 
	*xnorm, integer *info);

/* Subroutine */ int slasyf_(char *uplo, integer *n, integer *nb, integer *kb, 
	 floatreal *a, integer *lda, integer *ipiv, floatreal *w, integer *ldw, integer 
	*info);

/* Subroutine */ int slatbs_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, integer *kd, floatreal *ab, integer *ldab, floatreal *x, 
	floatreal *scale, floatreal *cnorm, integer *info);

/* Subroutine */ int slatdf_(integer *ijob, integer *n, floatreal *z__, integer *
	ldz, floatreal *rhs, floatreal *rdsum, floatreal *rdscal, integer *ipiv, integer *
	jpiv);

/* Subroutine */ int slatps_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, floatreal *ap, floatreal *x, floatreal *scale, floatreal *cnorm, 
	integer *info);

/* Subroutine */ int slatrd_(char *uplo, integer *n, integer *nb, floatreal *a, 
	integer *lda, floatreal *e, floatreal *tau, floatreal *w, integer *ldw);

/* Subroutine */ int slatrs_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, floatreal *a, integer *lda, floatreal *x, floatreal *scale, floatreal 
	*cnorm, integer *info);

/* Subroutine */ int slatrz_(integer *m, integer *n, integer *l, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work);

/* Subroutine */ int slatzm_(char *side, integer *m, integer *n, floatreal *v, 
	integer *incv, floatreal *tau, floatreal *c1, floatreal *c2, integer *ldc, floatreal *
	work);

/* Subroutine */ int slauu2_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *info);

/* Subroutine */ int slauum_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *info);

/* Subroutine */ int sopgtr_(char *uplo, integer *n, floatreal *ap, floatreal *tau, 
	floatreal *q, integer *ldq, floatreal *work, integer *info);

/* Subroutine */ int sopmtr_(char *side, char *uplo, char *trans, integer *m, 
	integer *n, floatreal *ap, floatreal *tau, floatreal *c__, integer *ldc, floatreal *work, 
	integer *info);

/* Subroutine */ int sorg2l_(integer *m, integer *n, integer *k, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sorg2r_(integer *m, integer *n, integer *k, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sorgbr_(char *vect, integer *m, integer *n, integer *k, 
	floatreal *a, integer *lda, floatreal *tau, floatreal *work, integer *lwork, integer 
	*info);

/* Subroutine */ int sorghr_(integer *n, integer *ilo, integer *ihi, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sorgl2_(integer *m, integer *n, integer *k, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sorglq_(integer *m, integer *n, integer *k, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sorgql_(integer *m, integer *n, integer *k, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sorgqr_(integer *m, integer *n, integer *k, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sorgr2_(integer *m, integer *n, integer *k, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *info);

/* Subroutine */ int sorgrq_(integer *m, integer *n, integer *k, floatreal *a, 
	integer *lda, floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sorgtr_(char *uplo, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sorm2l_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, integer *ldc, 
	 floatreal *work, integer *info);

/* Subroutine */ int sorm2r_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, integer *ldc, 
	 floatreal *work, integer *info);

/* Subroutine */ int sormbr_(char *vect, char *side, char *trans, integer *m, 
	integer *n, integer *k, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, 
	integer *ldc, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sormhr_(char *side, char *trans, integer *m, integer *n, 
	integer *ilo, integer *ihi, floatreal *a, integer *lda, floatreal *tau, floatreal *
	c__, integer *ldc, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sorml2_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, integer *ldc, 
	 floatreal *work, integer *info);

/* Subroutine */ int sormlq_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, integer *ldc, 
	 floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sormql_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, integer *ldc, 
	 floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sormqr_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, integer *ldc, 
	 floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sormr2_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, integer *ldc, 
	 floatreal *work, integer *info);

/* Subroutine */ int sormr3_(char *side, char *trans, integer *m, integer *n, 
	integer *k, integer *l, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, 
	integer *ldc, floatreal *work, integer *info);

/* Subroutine */ int sormrq_(char *side, char *trans, integer *m, integer *n, 
	integer *k, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, integer *ldc, 
	 floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sormrz_(char *side, char *trans, integer *m, integer *n, 
	integer *k, integer *l, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, 
	integer *ldc, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int sormtr_(char *side, char *uplo, char *trans, integer *m, 
	integer *n, floatreal *a, integer *lda, floatreal *tau, floatreal *c__, integer *ldc, 
	 floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int spbcon_(char *uplo, integer *n, integer *kd, floatreal *ab, 
	integer *ldab, floatreal *anorm, floatreal *rcond, floatreal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int spbequ_(char *uplo, integer *n, integer *kd, floatreal *ab, 
	integer *ldab, floatreal *s, floatreal *scond, floatreal *amax, integer *info);

/* Subroutine */ int spbrfs_(char *uplo, integer *n, integer *kd, integer *
	nrhs, floatreal *ab, integer *ldab, floatreal *afb, integer *ldafb, floatreal *b, 
	integer *ldb, floatreal *x, integer *ldx, floatreal *ferr, floatreal *berr, floatreal *
	work, integer *iwork, integer *info);

/* Subroutine */ int spbstf_(char *uplo, integer *n, integer *kd, floatreal *ab, 
	integer *ldab, integer *info);

/* Subroutine */ int spbsv_(char *uplo, integer *n, integer *kd, integer *
	nrhs, floatreal *ab, integer *ldab, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int spbsvx_(char *fact, char *uplo, integer *n, integer *kd, 
	integer *nrhs, floatreal *ab, integer *ldab, floatreal *afb, integer *ldafb, 
	char *equed, floatreal *s, floatreal *b, integer *ldb, floatreal *x, integer *ldx, 
	floatreal *rcond, floatreal *ferr, floatreal *berr, floatreal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int spbtf2_(char *uplo, integer *n, integer *kd, floatreal *ab, 
	integer *ldab, integer *info);

/* Subroutine */ int spbtrf_(char *uplo, integer *n, integer *kd, floatreal *ab, 
	integer *ldab, integer *info);

/* Subroutine */ int spbtrs_(char *uplo, integer *n, integer *kd, integer *
	nrhs, floatreal *ab, integer *ldab, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int spftrf_(char *transr, char *uplo, integer *n, floatreal *a, 
	integer *info);

/* Subroutine */ int spftri_(char *transr, char *uplo, integer *n, floatreal *a, 
	integer *info);

/* Subroutine */ int spftrs_(char *transr, char *uplo, integer *n, integer *
	nrhs, floatreal *a, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int spocon_(char *uplo, integer *n, floatreal *a, integer *lda, 
	floatreal *anorm, floatreal *rcond, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int spoequ_(integer *n, floatreal *a, integer *lda, floatreal *s, floatreal 
	*scond, floatreal *amax, integer *info);

/* Subroutine */ int spoequb_(integer *n, floatreal *a, integer *lda, floatreal *s, 
	floatreal *scond, floatreal *amax, integer *info);

/* Subroutine */ int sporfs_(char *uplo, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, floatreal *af, integer *ldaf, floatreal *b, integer *ldb, floatreal *x, 
	 integer *ldx, floatreal *ferr, floatreal *berr, floatreal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int sporfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *af, integer *ldaf, floatreal *s, floatreal *
	b, integer *ldb, floatreal *x, integer *ldx, floatreal *rcond, floatreal *berr, 
	integer *n_err_bnds__, floatreal *err_bnds_norm__, floatreal *err_bnds_comp__, 
	integer *nparams, floatreal *params, floatreal *work, integer *iwork, integer *
	info);

/* Subroutine */ int sposv_(char *uplo, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sposvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *af, integer *ldaf, char *equed, 
	floatreal *s, floatreal *b, integer *ldb, floatreal *x, integer *ldx, floatreal *rcond, 
	floatreal *ferr, floatreal *berr, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sposvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *af, integer *ldaf, char *equed, 
	floatreal *s, floatreal *b, integer *ldb, floatreal *x, integer *ldx, floatreal *rcond, 
	floatreal *rpvgrw, floatreal *berr, integer *n_err_bnds__, floatreal *
	err_bnds_norm__, floatreal *err_bnds_comp__, integer *nparams, floatreal *
	params, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int spotf2_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *info);

/* Subroutine */ int spotrf_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *info);

/* Subroutine */ int spotri_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *info);

/* Subroutine */ int spotrs_(char *uplo, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sppcon_(char *uplo, integer *n, floatreal *ap, floatreal *anorm, 
	floatreal *rcond, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sppequ_(char *uplo, integer *n, floatreal *ap, floatreal *s, floatreal *
	scond, floatreal *amax, integer *info);

/* Subroutine */ int spprfs_(char *uplo, integer *n, integer *nrhs, floatreal *ap, 
	floatreal *afp, floatreal *b, integer *ldb, floatreal *x, integer *ldx, floatreal *ferr, 
	floatreal *berr, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sppsv_(char *uplo, integer *n, integer *nrhs, floatreal *ap, 
	floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sppsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatreal *ap, floatreal *afp, char *equed, floatreal *s, floatreal *b, integer *
	ldb, floatreal *x, integer *ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, floatreal 
	*work, integer *iwork, integer *info);

/* Subroutine */ int spptrf_(char *uplo, integer *n, floatreal *ap, integer *info);

/* Subroutine */ int spptri_(char *uplo, integer *n, floatreal *ap, integer *info);

/* Subroutine */ int spptrs_(char *uplo, integer *n, integer *nrhs, floatreal *ap, 
	floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int spstf2_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *piv, integer *rank, floatreal *tol, floatreal *work, integer *info);

/* Subroutine */ int spstrf_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *piv, integer *rank, floatreal *tol, floatreal *work, integer *info);

/* Subroutine */ int sptcon_(integer *n, floatreal *d__, floatreal *e, floatreal *anorm, 
	floatreal *rcond, floatreal *work, integer *info);

/* Subroutine */ int spteqr_(char *compz, integer *n, floatreal *d__, floatreal *e, 
	floatreal *z__, integer *ldz, floatreal *work, integer *info);

/* Subroutine */ int sptrfs_(integer *n, integer *nrhs, floatreal *d__, floatreal *e, 
	floatreal *df, floatreal *ef, floatreal *b, integer *ldb, floatreal *x, integer *ldx, 
	floatreal *ferr, floatreal *berr, floatreal *work, integer *info);

/* Subroutine */ int sptsv_(integer *n, integer *nrhs, floatreal *d__, floatreal *e, 
	floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sptsvx_(char *fact, integer *n, integer *nrhs, floatreal *d__, 
	 floatreal *e, floatreal *df, floatreal *ef, floatreal *b, integer *ldb, floatreal *x, integer 
	*ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, floatreal *work, integer *info);

/* Subroutine */ int spttrf_(integer *n, floatreal *d__, floatreal *e, integer *info);

/* Subroutine */ int spttrs_(integer *n, integer *nrhs, floatreal *d__, floatreal *e, 
	floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sptts2_(integer *n, integer *nrhs, floatreal *d__, floatreal *e, 
	floatreal *b, integer *ldb);

/* Subroutine */ int srscl_(integer *n, floatreal *sa, floatreal *sx, integer *incx);

/* Subroutine */ int ssbev_(char *jobz, char *uplo, integer *n, integer *kd, 
	floatreal *ab, integer *ldab, floatreal *w, floatreal *z__, integer *ldz, floatreal *work, 
	 integer *info);

/* Subroutine */ int ssbevd_(char *jobz, char *uplo, integer *n, integer *kd, 
	floatreal *ab, integer *ldab, floatreal *w, floatreal *z__, integer *ldz, floatreal *work, 
	 integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int ssbevx_(char *jobz, char *range, char *uplo, integer *n, 
	integer *kd, floatreal *ab, integer *ldab, floatreal *q, integer *ldq, floatreal *vl, 
	 floatreal *vu, integer *il, integer *iu, floatreal *abstol, integer *m, floatreal *
	w, floatreal *z__, integer *ldz, floatreal *work, integer *iwork, integer *
	ifail, integer *info);

/* Subroutine */ int ssbgst_(char *vect, char *uplo, integer *n, integer *ka, 
	integer *kb, floatreal *ab, integer *ldab, floatreal *bb, integer *ldbb, floatreal *
	x, integer *ldx, floatreal *work, integer *info);

/* Subroutine */ int ssbgv_(char *jobz, char *uplo, integer *n, integer *ka, 
	integer *kb, floatreal *ab, integer *ldab, floatreal *bb, integer *ldbb, floatreal *
	w, floatreal *z__, integer *ldz, floatreal *work, integer *info);

/* Subroutine */ int ssbgvd_(char *jobz, char *uplo, integer *n, integer *ka, 
	integer *kb, floatreal *ab, integer *ldab, floatreal *bb, integer *ldbb, floatreal *
	w, floatreal *z__, integer *ldz, floatreal *work, integer *lwork, integer *
	iwork, integer *liwork, integer *info);

/* Subroutine */ int ssbgvx_(char *jobz, char *range, char *uplo, integer *n, 
	integer *ka, integer *kb, floatreal *ab, integer *ldab, floatreal *bb, integer *
	ldbb, floatreal *q, integer *ldq, floatreal *vl, floatreal *vu, integer *il, integer 
	*iu, floatreal *abstol, integer *m, floatreal *w, floatreal *z__, integer *ldz, floatreal 
	*work, integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int ssbtrd_(char *vect, char *uplo, integer *n, integer *kd, 
	floatreal *ab, integer *ldab, floatreal *d__, floatreal *e, floatreal *q, integer *ldq, 
	floatreal *work, integer *info);

/* Subroutine */ int ssfrk_(char *transr, char *uplo, char *trans, integer *n, 
	 integer *k, floatreal *alpha, floatreal *a, integer *lda, floatreal *beta, floatreal *
	c__);

/* Subroutine */ int sspcon_(char *uplo, integer *n, floatreal *ap, integer *ipiv, 
	floatreal *anorm, floatreal *rcond, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sspev_(char *jobz, char *uplo, integer *n, floatreal *ap, 
	floatreal *w, floatreal *z__, integer *ldz, floatreal *work, integer *info);

/* Subroutine */ int sspevd_(char *jobz, char *uplo, integer *n, floatreal *ap, 
	floatreal *w, floatreal *z__, integer *ldz, floatreal *work, integer *lwork, integer 
	*iwork, integer *liwork, integer *info);

/* Subroutine */ int sspevx_(char *jobz, char *range, char *uplo, integer *n, 
	floatreal *ap, floatreal *vl, floatreal *vu, integer *il, integer *iu, floatreal *abstol, 
	integer *m, floatreal *w, floatreal *z__, integer *ldz, floatreal *work, integer *
	iwork, integer *ifail, integer *info);

/* Subroutine */ int sspgst_(integer *itype, char *uplo, integer *n, floatreal *ap, 
	 floatreal *bp, integer *info);

/* Subroutine */ int sspgv_(integer *itype, char *jobz, char *uplo, integer *
	n, floatreal *ap, floatreal *bp, floatreal *w, floatreal *z__, integer *ldz, floatreal *work, 
	integer *info);

/* Subroutine */ int sspgvd_(integer *itype, char *jobz, char *uplo, integer *
	n, floatreal *ap, floatreal *bp, floatreal *w, floatreal *z__, integer *ldz, floatreal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int sspgvx_(integer *itype, char *jobz, char *range, char *
	uplo, integer *n, floatreal *ap, floatreal *bp, floatreal *vl, floatreal *vu, integer *il, 
	 integer *iu, floatreal *abstol, integer *m, floatreal *w, floatreal *z__, integer *
	ldz, floatreal *work, integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int ssprfs_(char *uplo, integer *n, integer *nrhs, floatreal *ap, 
	floatreal *afp, integer *ipiv, floatreal *b, integer *ldb, floatreal *x, integer *
	ldx, floatreal *ferr, floatreal *berr, floatreal *work, integer *iwork, integer *
	info);

/* Subroutine */ int sspsv_(char *uplo, integer *n, integer *nrhs, floatreal *ap, 
	integer *ipiv, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sspsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatreal *ap, floatreal *afp, integer *ipiv, floatreal *b, integer *ldb, floatreal 
	*x, integer *ldx, floatreal *rcond, floatreal *ferr, floatreal *berr, floatreal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int ssptrd_(char *uplo, integer *n, floatreal *ap, floatreal *d__, 
	floatreal *e, floatreal *tau, integer *info);

/* Subroutine */ int ssptrf_(char *uplo, integer *n, floatreal *ap, integer *ipiv, 
	integer *info);

/* Subroutine */ int ssptri_(char *uplo, integer *n, floatreal *ap, integer *ipiv, 
	floatreal *work, integer *info);

/* Subroutine */ int ssptrs_(char *uplo, integer *n, integer *nrhs, floatreal *ap, 
	integer *ipiv, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int sstebz_(char *range, char *order, integer *n, floatreal *vl, 
	floatreal *vu, integer *il, integer *iu, floatreal *abstol, floatreal *d__, floatreal *e, 
	integer *m, integer *nsplit, floatreal *w, integer *iblock, integer *
	isplit, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int sstedc_(char *compz, integer *n, floatreal *d__, floatreal *e, 
	floatreal *z__, integer *ldz, floatreal *work, integer *lwork, integer *iwork, 
	integer *liwork, integer *info);

/* Subroutine */ int sstegr_(char *jobz, char *range, integer *n, floatreal *d__, 
	floatreal *e, floatreal *vl, floatreal *vu, integer *il, integer *iu, floatreal *abstol, 
	integer *m, floatreal *w, floatreal *z__, integer *ldz, integer *isuppz, floatreal *
	work, integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int sstein_(integer *n, floatreal *d__, floatreal *e, integer *m, floatreal 
	*w, integer *iblock, integer *isplit, floatreal *z__, integer *ldz, floatreal *
	work, integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int sstemr_(char *jobz, char *range, integer *n, floatreal *d__, 
	floatreal *e, floatreal *vl, floatreal *vu, integer *il, integer *iu, integer *m, 
	floatreal *w, floatreal *z__, integer *ldz, integer *nzc, integer *isuppz, 
	logical *tryrac, floatreal *work, integer *lwork, integer *iwork, integer *
	liwork, integer *info);

/* Subroutine */ int ssteqr_(char *compz, integer *n, floatreal *d__, floatreal *e, 
	floatreal *z__, integer *ldz, floatreal *work, integer *info);

/* Subroutine */ int ssterf_(integer *n, floatreal *d__, floatreal *e, integer *info);

/* Subroutine */ int sstev_(char *jobz, integer *n, floatreal *d__, floatreal *e, floatreal *
	z__, integer *ldz, floatreal *work, integer *info);

/* Subroutine */ int sstevd_(char *jobz, integer *n, floatreal *d__, floatreal *e, floatreal 
	*z__, integer *ldz, floatreal *work, integer *lwork, integer *iwork, 
	integer *liwork, integer *info);

/* Subroutine */ int sstevr_(char *jobz, char *range, integer *n, floatreal *d__, 
	floatreal *e, floatreal *vl, floatreal *vu, integer *il, integer *iu, floatreal *abstol, 
	integer *m, floatreal *w, floatreal *z__, integer *ldz, integer *isuppz, floatreal *
	work, integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int sstevx_(char *jobz, char *range, integer *n, floatreal *d__, 
	floatreal *e, floatreal *vl, floatreal *vu, integer *il, integer *iu, floatreal *abstol, 
	integer *m, floatreal *w, floatreal *z__, integer *ldz, floatreal *work, integer *
	iwork, integer *ifail, integer *info);

/* Subroutine */ int ssycon_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *ipiv, floatreal *anorm, floatreal *rcond, floatreal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int ssyequb_(char *uplo, integer *n, floatreal *a, integer *lda, 
	floatreal *s, floatreal *scond, floatreal *amax, floatreal *work, integer *info);

/* Subroutine */ int ssyev_(char *jobz, char *uplo, integer *n, floatreal *a, 
	integer *lda, floatreal *w, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int ssyevd_(char *jobz, char *uplo, integer *n, floatreal *a, 
	integer *lda, floatreal *w, floatreal *work, integer *lwork, integer *iwork, 
	integer *liwork, integer *info);

/* Subroutine */ int ssyevr_(char *jobz, char *range, char *uplo, integer *n, 
	floatreal *a, integer *lda, floatreal *vl, floatreal *vu, integer *il, integer *iu, 
	floatreal *abstol, integer *m, floatreal *w, floatreal *z__, integer *ldz, integer *
	isuppz, floatreal *work, integer *lwork, integer *iwork, integer *liwork, 
	integer *info);

/* Subroutine */ int ssyevx_(char *jobz, char *range, char *uplo, integer *n, 
	floatreal *a, integer *lda, floatreal *vl, floatreal *vu, integer *il, integer *iu, 
	floatreal *abstol, integer *m, floatreal *w, floatreal *z__, integer *ldz, floatreal *
	work, integer *lwork, integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int ssygs2_(integer *itype, char *uplo, integer *n, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int ssygst_(integer *itype, char *uplo, integer *n, floatreal *a, 
	integer *lda, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int ssygv_(integer *itype, char *jobz, char *uplo, integer *
	n, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *w, floatreal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int ssygvd_(integer *itype, char *jobz, char *uplo, integer *
	n, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *w, floatreal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int ssygvx_(integer *itype, char *jobz, char *range, char *
	uplo, integer *n, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *
	vl, floatreal *vu, integer *il, integer *iu, floatreal *abstol, integer *m, 
	floatreal *w, floatreal *z__, integer *ldz, floatreal *work, integer *lwork, integer 
	*iwork, integer *ifail, integer *info);

/* Subroutine */ int ssyrfs_(char *uplo, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, floatreal *af, integer *ldaf, integer *ipiv, floatreal *b, 
	integer *ldb, floatreal *x, integer *ldx, floatreal *ferr, floatreal *berr, floatreal *
	work, integer *iwork, integer *info);

/* Subroutine */ int ssyrfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *af, integer *ldaf, integer *ipiv, 
	floatreal *s, floatreal *b, integer *ldb, floatreal *x, integer *ldx, floatreal *rcond, 
	floatreal *berr, integer *n_err_bnds__, floatreal *err_bnds_norm__, floatreal *
	err_bnds_comp__, integer *nparams, floatreal *params, floatreal *work, integer *
	iwork, integer *info);

/* Subroutine */ int ssysv_(char *uplo, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, integer *ipiv, floatreal *b, integer *ldb, floatreal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int ssysvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *af, integer *ldaf, integer *ipiv, 
	floatreal *b, integer *ldb, floatreal *x, integer *ldx, floatreal *rcond, floatreal *ferr, 
	 floatreal *berr, floatreal *work, integer *lwork, integer *iwork, integer *
	info);

/* Subroutine */ int ssysvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, floatreal *a, integer *lda, floatreal *af, integer *ldaf, integer *ipiv, 
	char *equed, floatreal *s, floatreal *b, integer *ldb, floatreal *x, integer *ldx, 
	floatreal *rcond, floatreal *rpvgrw, floatreal *berr, integer *n_err_bnds__, floatreal *
	err_bnds_norm__, floatreal *err_bnds_comp__, integer *nparams, floatreal *
	params, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int ssytd2_(char *uplo, integer *n, floatreal *a, integer *lda, 
	floatreal *d__, floatreal *e, floatreal *tau, integer *info);

/* Subroutine */ int ssytf2_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *ipiv, integer *info);

/* Subroutine */ int ssytrd_(char *uplo, integer *n, floatreal *a, integer *lda, 
	floatreal *d__, floatreal *e, floatreal *tau, floatreal *work, integer *lwork, integer *
	info);

/* Subroutine */ int ssytrf_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *ipiv, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int ssytri_(char *uplo, integer *n, floatreal *a, integer *lda, 
	integer *ipiv, floatreal *work, integer *info);

/* Subroutine */ int ssytrs_(char *uplo, integer *n, integer *nrhs, floatreal *a, 
	integer *lda, integer *ipiv, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int stbcon_(char *norm, char *uplo, char *diag, integer *n, 
	integer *kd, floatreal *ab, integer *ldab, floatreal *rcond, floatreal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int stbrfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *kd, integer *nrhs, floatreal *ab, integer *ldab, floatreal *b, integer 
	*ldb, floatreal *x, integer *ldx, floatreal *ferr, floatreal *berr, floatreal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int stbtrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *kd, integer *nrhs, floatreal *ab, integer *ldab, floatreal *b, integer 
	*ldb, integer *info);

/* Subroutine */ int stfsm_(char *transr, char *side, char *uplo, char *trans, 
	 char *diag, integer *m, integer *n, floatreal *alpha, floatreal *a, floatreal *b, 
	integer *ldb);

/* Subroutine */ int stftri_(char *transr, char *uplo, char *diag, integer *n, 
	 floatreal *a, integer *info);

/* Subroutine */ int stfttp_(char *transr, char *uplo, integer *n, floatreal *arf, 
	floatreal *ap, integer *info);

/* Subroutine */ int stfttr_(char *transr, char *uplo, integer *n, floatreal *arf, 
	floatreal *a, integer *lda, integer *info);

/* Subroutine */ int stgevc_(char *side, char *howmny, logical *select, 
	integer *n, floatreal *s, integer *lds, floatreal *p, integer *ldp, floatreal *vl, 
	integer *ldvl, floatreal *vr, integer *ldvr, integer *mm, integer *m, floatreal 
	*work, integer *info);

/* Subroutine */ int stgex2_(logical *wantq, logical *wantz, integer *n, floatreal 
	*a, integer *lda, floatreal *b, integer *ldb, floatreal *q, integer *ldq, floatreal *
	z__, integer *ldz, integer *j1, integer *n1, integer *n2, floatreal *work, 
	integer *lwork, integer *info);

/* Subroutine */ int stgexc_(logical *wantq, logical *wantz, integer *n, floatreal 
	*a, integer *lda, floatreal *b, integer *ldb, floatreal *q, integer *ldq, floatreal *
	z__, integer *ldz, integer *ifst, integer *ilst, floatreal *work, integer *
	lwork, integer *info);

/* Subroutine */ int stgsen_(integer *ijob, logical *wantq, logical *wantz, 
	logical *select, integer *n, floatreal *a, integer *lda, floatreal *b, integer *
	ldb, floatreal *alphar, floatreal *alphai, floatreal *beta, floatreal *q, integer *ldq, 
	floatreal *z__, integer *ldz, integer *m, floatreal *pl, floatreal *pr, floatreal *dif, 
	floatreal *work, integer *lwork, integer *iwork, integer *liwork, integer *
	info);

/* Subroutine */ int stgsja_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *p, integer *n, integer *k, integer *l, floatreal *a, integer *lda, 
	 floatreal *b, integer *ldb, floatreal *tola, floatreal *tolb, floatreal *alpha, floatreal *
	beta, floatreal *u, integer *ldu, floatreal *v, integer *ldv, floatreal *q, integer *
	ldq, floatreal *work, integer *ncycle, integer *info);

/* Subroutine */ int stgsna_(char *job, char *howmny, logical *select, 
	integer *n, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *vl, 
	integer *ldvl, floatreal *vr, integer *ldvr, floatreal *s, floatreal *dif, integer *
	mm, integer *m, floatreal *work, integer *lwork, integer *iwork, integer *
	info);

/* Subroutine */ int stgsy2_(char *trans, integer *ijob, integer *m, integer *
	n, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *c__, integer *
	ldc, floatreal *d__, integer *ldd, floatreal *e, integer *lde, floatreal *f, integer 
	*ldf, floatreal *scale, floatreal *rdsum, floatreal *rdscal, integer *iwork, integer 
	*pq, integer *info);

/* Subroutine */ int stgsyl_(char *trans, integer *ijob, integer *m, integer *
	n, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *c__, integer *
	ldc, floatreal *d__, integer *ldd, floatreal *e, integer *lde, floatreal *f, integer 
	*ldf, floatreal *scale, floatreal *dif, floatreal *work, integer *lwork, integer *
	iwork, integer *info);

/* Subroutine */ int stpcon_(char *norm, char *uplo, char *diag, integer *n, 
	floatreal *ap, floatreal *rcond, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int stprfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, floatreal *ap, floatreal *b, integer *ldb, floatreal *x, integer *ldx, 
	 floatreal *ferr, floatreal *berr, floatreal *work, integer *iwork, integer *info);

/* Subroutine */ int stptri_(char *uplo, char *diag, integer *n, floatreal *ap, 
	integer *info);

/* Subroutine */ int stptrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, floatreal *ap, floatreal *b, integer *ldb, integer *info);

/* Subroutine */ int stpttf_(char *transr, char *uplo, integer *n, floatreal *ap, 
	floatreal *arf, integer *info);

/* Subroutine */ int stpttr_(char *uplo, integer *n, floatreal *ap, floatreal *a, 
	integer *lda, integer *info);

/* Subroutine */ int strcon_(char *norm, char *uplo, char *diag, integer *n, 
	floatreal *a, integer *lda, floatreal *rcond, floatreal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int strevc_(char *side, char *howmny, logical *select, 
	integer *n, floatreal *t, integer *ldt, floatreal *vl, integer *ldvl, floatreal *vr, 
	integer *ldvr, integer *mm, integer *m, floatreal *work, integer *info);

/* Subroutine */ int strexc_(char *compq, integer *n, floatreal *t, integer *ldt, 
	floatreal *q, integer *ldq, integer *ifst, integer *ilst, floatreal *work, 
	integer *info);

/* Subroutine */ int strrfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *x, 
	integer *ldx, floatreal *ferr, floatreal *berr, floatreal *work, integer *iwork, 
	integer *info);

/* Subroutine */ int strsen_(char *job, char *compq, logical *select, integer 
	*n, floatreal *t, integer *ldt, floatreal *q, integer *ldq, floatreal *wr, floatreal *wi, 
	integer *m, floatreal *s, floatreal *sep, floatreal *work, integer *lwork, integer *
	iwork, integer *liwork, integer *info);

/* Subroutine */ int strsna_(char *job, char *howmny, logical *select, 
	integer *n, floatreal *t, integer *ldt, floatreal *vl, integer *ldvl, floatreal *vr, 
	integer *ldvr, floatreal *s, floatreal *sep, integer *mm, integer *m, floatreal *
	work, integer *ldwork, integer *iwork, integer *info);

/* Subroutine */ int strsyl_(char *trana, char *tranb, integer *isgn, integer 
	*m, integer *n, floatreal *a, integer *lda, floatreal *b, integer *ldb, floatreal *
	c__, integer *ldc, floatreal *scale, integer *info);

/* Subroutine */ int strti2_(char *uplo, char *diag, integer *n, floatreal *a, 
	integer *lda, integer *info);

/* Subroutine */ int strtri_(char *uplo, char *diag, integer *n, floatreal *a, 
	integer *lda, integer *info);

/* Subroutine */ int strtrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, floatreal *a, integer *lda, floatreal *b, integer *ldb, integer *
	info);

/* Subroutine */ int strttf_(char *transr, char *uplo, integer *n, floatreal *a, 
	integer *lda, floatreal *arf, integer *info);

/* Subroutine */ int strttp_(char *uplo, integer *n, floatreal *a, integer *lda, 
	floatreal *ap, integer *info);

/* Subroutine */ int stzrqf_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, integer *info);

/* Subroutine */ int stzrzf_(integer *m, integer *n, floatreal *a, integer *lda, 
	floatreal *tau, floatreal *work, integer *lwork, integer *info);

/* Subroutine */ int xerbla_(char *srname, integer *info);

/* Subroutine */ int xerbla_array__(char *srname_array__, integer *
	srname_len__, integer *info, ftnlen srname_array_len);

/* Subroutine */ int zbdsqr_(char *uplo, integer *n, integer *ncvt, integer *
	nru, integer *ncc, doublereal *d__, doublereal *e, doublecomplex *vt, 
	integer *ldvt, doublecomplex *u, integer *ldu, doublecomplex *c__, 
	integer *ldc, doublereal *rwork, integer *info);

/* Subroutine */ int zcgesv_(integer *n, integer *nrhs, doublecomplex *a, 
	integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublecomplex *work, floatcomplex *swork, 
	doublereal *rwork, integer *iter, integer *info);

/* Subroutine */ int zcposv_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublecomplex *work, floatcomplex *swork, 
	doublereal *rwork, integer *iter, integer *info);

/* Subroutine */ int zdrscl_(integer *n, doublereal *sa, doublecomplex *sx, 
	integer *incx);

/* Subroutine */ int zgbbrd_(char *vect, integer *m, integer *n, integer *ncc, 
	 integer *kl, integer *ku, doublecomplex *ab, integer *ldab, 
	doublereal *d__, doublereal *e, doublecomplex *q, integer *ldq, 
	doublecomplex *pt, integer *ldpt, doublecomplex *c__, integer *ldc, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zgbcon_(char *norm, integer *n, integer *kl, integer *ku, 
	 doublecomplex *ab, integer *ldab, integer *ipiv, doublereal *anorm, 
	doublereal *rcond, doublecomplex *work, doublereal *rwork, integer *
	info);

/* Subroutine */ int zgbequ_(integer *m, integer *n, integer *kl, integer *ku, 
	 doublecomplex *ab, integer *ldab, doublereal *r__, doublereal *c__, 
	doublereal *rowcnd, doublereal *colcnd, doublereal *amax, integer *
	info);

/* Subroutine */ int zgbequb_(integer *m, integer *n, integer *kl, integer *
	ku, doublecomplex *ab, integer *ldab, doublereal *r__, doublereal *
	c__, doublereal *rowcnd, doublereal *colcnd, doublereal *amax, 
	integer *info);

/* Subroutine */ int zgbrfs_(char *trans, integer *n, integer *kl, integer *
	ku, integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *
	afb, integer *ldafb, integer *ipiv, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zgbrfsx_(char *trans, char *equed, integer *n, integer *
	kl, integer *ku, integer *nrhs, doublecomplex *ab, integer *ldab, 
	doublecomplex *afb, integer *ldafb, integer *ipiv, doublereal *r__, 
	doublereal *c__, doublecomplex *b, integer *ldb, doublecomplex *x, 
	integer *ldx, doublereal *rcond, doublereal *berr, integer *
	n_err_bnds__, doublereal *err_bnds_norm__, doublereal *
	err_bnds_comp__, integer *nparams, doublereal *params, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zgbsv_(integer *n, integer *kl, integer *ku, integer *
	nrhs, doublecomplex *ab, integer *ldab, integer *ipiv, doublecomplex *
	b, integer *ldb, integer *info);

/* Subroutine */ int zgbsvx_(char *fact, char *trans, integer *n, integer *kl, 
	 integer *ku, integer *nrhs, doublecomplex *ab, integer *ldab, 
	doublecomplex *afb, integer *ldafb, integer *ipiv, char *equed, 
	doublereal *r__, doublereal *c__, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, 
	doublereal *berr, doublecomplex *work, doublereal *rwork, integer *
	info);

/* Subroutine */ int zgbsvxx_(char *fact, char *trans, integer *n, integer *
	kl, integer *ku, integer *nrhs, doublecomplex *ab, integer *ldab, 
	doublecomplex *afb, integer *ldafb, integer *ipiv, char *equed, 
	doublereal *r__, doublereal *c__, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *rpvgrw, 
	 doublereal *berr, integer *n_err_bnds__, doublereal *err_bnds_norm__, 
	 doublereal *err_bnds_comp__, integer *nparams, doublereal *params, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zgbtf2_(integer *m, integer *n, integer *kl, integer *ku, 
	 doublecomplex *ab, integer *ldab, integer *ipiv, integer *info);

/* Subroutine */ int zgbtrf_(integer *m, integer *n, integer *kl, integer *ku, 
	 doublecomplex *ab, integer *ldab, integer *ipiv, integer *info);

/* Subroutine */ int zgbtrs_(char *trans, integer *n, integer *kl, integer *
	ku, integer *nrhs, doublecomplex *ab, integer *ldab, integer *ipiv, 
	doublecomplex *b, integer *ldb, integer *info);

/* Subroutine */ int zgebak_(char *job, char *side, integer *n, integer *ilo, 
	integer *ihi, doublereal *scale, integer *m, doublecomplex *v, 
	integer *ldv, integer *info);

/* Subroutine */ int zgebal_(char *job, integer *n, doublecomplex *a, integer 
	*lda, integer *ilo, integer *ihi, doublereal *scale, integer *info);

/* Subroutine */ int zgebd2_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublereal *d__, doublereal *e, doublecomplex *tauq, 
	doublecomplex *taup, doublecomplex *work, integer *info);

/* Subroutine */ int zgebrd_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublereal *d__, doublereal *e, doublecomplex *tauq, 
	doublecomplex *taup, doublecomplex *work, integer *lwork, integer *
	info);

/* Subroutine */ int zgecon_(char *norm, integer *n, doublecomplex *a, 
	integer *lda, doublereal *anorm, doublereal *rcond, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zgeequ_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, 
	doublereal *colcnd, doublereal *amax, integer *info);

/* Subroutine */ int zgeequb_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, 
	doublereal *colcnd, doublereal *amax, integer *info);

/* Subroutine */ int zgees_(char *jobvs, char *sort, L_fp select, integer *n, 
	doublecomplex *a, integer *lda, integer *sdim, doublecomplex *w, 
	doublecomplex *vs, integer *ldvs, doublecomplex *work, integer *lwork, 
	 doublereal *rwork, logical *bwork, integer *info);

/* Subroutine */ int zgeesx_(char *jobvs, char *sort, L_fp select, char *
	sense, integer *n, doublecomplex *a, integer *lda, integer *sdim, 
	doublecomplex *w, doublecomplex *vs, integer *ldvs, doublereal *
	rconde, doublereal *rcondv, doublecomplex *work, integer *lwork, 
	doublereal *rwork, logical *bwork, integer *info);

/* Subroutine */ int zgeev_(char *jobvl, char *jobvr, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *w, doublecomplex *vl, 
	integer *ldvl, doublecomplex *vr, integer *ldvr, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zgeevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, doublecomplex *a, integer *lda, doublecomplex *w, 
	doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, 
	integer *ilo, integer *ihi, doublereal *scale, doublereal *abnrm, 
	doublereal *rconde, doublereal *rcondv, doublecomplex *work, integer *
	lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zgegs_(char *jobvsl, char *jobvsr, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *alpha, doublecomplex *beta, doublecomplex *vsl, 
	integer *ldvsl, doublecomplex *vsr, integer *ldvsr, doublecomplex *
	work, integer *lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zgegv_(char *jobvl, char *jobvr, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *alpha, doublecomplex *beta, doublecomplex *vl, integer 
	*ldvl, doublecomplex *vr, integer *ldvr, doublecomplex *work, integer 
	*lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zgehd2_(integer *n, integer *ilo, integer *ihi, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *info);

/* Subroutine */ int zgehrd_(integer *n, integer *ilo, integer *ihi, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int zgelq2_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);

/* Subroutine */ int zgelqf_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zgels_(char *trans, integer *m, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *work, integer *lwork, integer *info);

/* Subroutine */ int zgelsd_(integer *m, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublereal *s, doublereal *rcond, integer *rank, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *iwork, integer *info);

/* Subroutine */ int zgelss_(integer *m, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublereal *s, doublereal *rcond, integer *rank, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zgelsx_(integer *m, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	integer *jpvt, doublereal *rcond, integer *rank, doublecomplex *work, 
	doublereal *rwork, integer *info);

/* Subroutine */ int zgelsy_(integer *m, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	integer *jpvt, doublereal *rcond, integer *rank, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zgeql2_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);

/* Subroutine */ int zgeqlf_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zgeqp3_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, integer *jpvt, doublecomplex *tau, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zgeqpf_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, integer *jpvt, doublecomplex *tau, doublecomplex *work, 
	doublereal *rwork, integer *info);

/* Subroutine */ int zgeqr2_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);

/* Subroutine */ int zgeqrf_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zgerfs_(char *trans, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, 
	integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, 
	integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, 
	 doublereal *rwork, integer *info);

/* Subroutine */ int zgerfsx_(char *trans, char *equed, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, integer *ipiv, doublereal *r__, doublereal *c__, doublecomplex *
	b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, 
	doublereal *berr, integer *n_err_bnds__, doublereal *err_bnds_norm__, 
	doublereal *err_bnds_comp__, integer *nparams, doublereal *params, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zgerq2_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *info);

/* Subroutine */ int zgerqf_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zgesc2_(integer *n, doublecomplex *a, integer *lda, 
	doublecomplex *rhs, integer *ipiv, integer *jpiv, doublereal *scale);

/* Subroutine */ int zgesdd_(char *jobz, integer *m, integer *n, 
	doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u, 
	integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *iwork, integer *info);

/* Subroutine */ int zgesv_(integer *n, integer *nrhs, doublecomplex *a, 
	integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, integer *
	info);

/* Subroutine */ int zgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u, 
	integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zgesvx_(char *fact, char *trans, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, integer *ipiv, char *equed, doublereal *r__, doublereal *c__, 
	doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zgesvxx_(char *fact, char *trans, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, integer *ipiv, char *equed, doublereal *r__, doublereal *c__, 
	doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	doublereal *rcond, doublereal *rpvgrw, doublereal *berr, integer *
	n_err_bnds__, doublereal *err_bnds_norm__, doublereal *
	err_bnds_comp__, integer *nparams, doublereal *params, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zgetc2_(integer *n, doublecomplex *a, integer *lda, 
	integer *ipiv, integer *jpiv, integer *info);

/* Subroutine */ int zgetf2_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, integer *info);

/* Subroutine */ int zgetrf_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, integer *info);

/* Subroutine */ int zgetri_(integer *n, doublecomplex *a, integer *lda, 
	integer *ipiv, doublecomplex *work, integer *lwork, integer *info);

/* Subroutine */ int zgetrs_(char *trans, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, 
	integer *ldb, integer *info);

/* Subroutine */ int zggbak_(char *job, char *side, integer *n, integer *ilo, 
	integer *ihi, doublereal *lscale, doublereal *rscale, integer *m, 
	doublecomplex *v, integer *ldv, integer *info);

/* Subroutine */ int zggbal_(char *job, integer *n, doublecomplex *a, integer 
	*lda, doublecomplex *b, integer *ldb, integer *ilo, integer *ihi, 
	doublereal *lscale, doublereal *rscale, doublereal *work, integer *
	info);

/* Subroutine */ int zgges_(char *jobvsl, char *jobvsr, char *sort, L_fp 
	selctg, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, 
	integer *ldb, integer *sdim, doublecomplex *alpha, doublecomplex *
	beta, doublecomplex *vsl, integer *ldvsl, doublecomplex *vsr, integer 
	*ldvsr, doublecomplex *work, integer *lwork, doublereal *rwork, 
	logical *bwork, integer *info);

/* Subroutine */ int zggesx_(char *jobvsl, char *jobvsr, char *sort, L_fp 
	selctg, char *sense, integer *n, doublecomplex *a, integer *lda, 
	doublecomplex *b, integer *ldb, integer *sdim, doublecomplex *alpha, 
	doublecomplex *beta, doublecomplex *vsl, integer *ldvsl, 
	doublecomplex *vsr, integer *ldvsr, doublereal *rconde, doublereal *
	rcondv, doublecomplex *work, integer *lwork, doublereal *rwork, 
	integer *iwork, integer *liwork, logical *bwork, integer *info);

/* Subroutine */ int zggev_(char *jobvl, char *jobvr, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *alpha, doublecomplex *beta, doublecomplex *vl, integer 
	*ldvl, doublecomplex *vr, integer *ldvr, doublecomplex *work, integer 
	*lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zggevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, 
	integer *ldb, doublecomplex *alpha, doublecomplex *beta, 
	doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, 
	integer *ilo, integer *ihi, doublereal *lscale, doublereal *rscale, 
	doublereal *abnrm, doublereal *bbnrm, doublereal *rconde, doublereal *
	rcondv, doublecomplex *work, integer *lwork, doublereal *rwork, 
	integer *iwork, logical *bwork, integer *info);

/* Subroutine */ int zggglm_(integer *n, integer *m, integer *p, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *d__, doublecomplex *x, doublecomplex *y, doublecomplex 
	*work, integer *lwork, integer *info);

/* Subroutine */ int zgghrd_(char *compq, char *compz, integer *n, integer *
	ilo, integer *ihi, doublecomplex *a, integer *lda, doublecomplex *b, 
	integer *ldb, doublecomplex *q, integer *ldq, doublecomplex *z__, 
	integer *ldz, integer *info);

/* Subroutine */ int zgglse_(integer *m, integer *n, integer *p, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *c__, doublecomplex *d__, doublecomplex *x, 
	doublecomplex *work, integer *lwork, integer *info);

/* Subroutine */ int zggqrf_(integer *n, integer *m, integer *p, 
	doublecomplex *a, integer *lda, doublecomplex *taua, doublecomplex *b, 
	 integer *ldb, doublecomplex *taub, doublecomplex *work, integer *
	lwork, integer *info);

/* Subroutine */ int zggrqf_(integer *m, integer *p, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *taua, doublecomplex *b, 
	 integer *ldb, doublecomplex *taub, doublecomplex *work, integer *
	lwork, integer *info);

/* Subroutine */ int zggsvd_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *n, integer *p, integer *k, integer *l, doublecomplex *a, 
	integer *lda, doublecomplex *b, integer *ldb, doublereal *alpha, 
	doublereal *beta, doublecomplex *u, integer *ldu, doublecomplex *v, 
	integer *ldv, doublecomplex *q, integer *ldq, doublecomplex *work, 
	doublereal *rwork, integer *iwork, integer *info);

/* Subroutine */ int zggsvp_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *p, integer *n, doublecomplex *a, integer *lda, doublecomplex 
	*b, integer *ldb, doublereal *tola, doublereal *tolb, integer *k, 
	integer *l, doublecomplex *u, integer *ldu, doublecomplex *v, integer 
	*ldv, doublecomplex *q, integer *ldq, integer *iwork, doublereal *
	rwork, doublecomplex *tau, doublecomplex *work, integer *info);

/* Subroutine */ int zgtcon_(char *norm, integer *n, doublecomplex *dl, 
	doublecomplex *d__, doublecomplex *du, doublecomplex *du2, integer *
	ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *work, 
	integer *info);

/* Subroutine */ int zgtrfs_(char *trans, integer *n, integer *nrhs, 
	doublecomplex *dl, doublecomplex *d__, doublecomplex *du, 
	doublecomplex *dlf, doublecomplex *df, doublecomplex *duf, 
	doublecomplex *du2, integer *ipiv, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zgtsv_(integer *n, integer *nrhs, doublecomplex *dl, 
	doublecomplex *d__, doublecomplex *du, doublecomplex *b, integer *ldb, 
	 integer *info);

/* Subroutine */ int zgtsvx_(char *fact, char *trans, integer *n, integer *
	nrhs, doublecomplex *dl, doublecomplex *d__, doublecomplex *du, 
	doublecomplex *dlf, doublecomplex *df, doublecomplex *duf, 
	doublecomplex *du2, integer *ipiv, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, 
	doublereal *berr, doublecomplex *work, doublereal *rwork, integer *
	info);

/* Subroutine */ int zgttrf_(integer *n, doublecomplex *dl, doublecomplex *
	d__, doublecomplex *du, doublecomplex *du2, integer *ipiv, integer *
	info);

/* Subroutine */ int zgttrs_(char *trans, integer *n, integer *nrhs, 
	doublecomplex *dl, doublecomplex *d__, doublecomplex *du, 
	doublecomplex *du2, integer *ipiv, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zgtts2_(integer *itrans, integer *n, integer *nrhs, 
	doublecomplex *dl, doublecomplex *d__, doublecomplex *du, 
	doublecomplex *du2, integer *ipiv, doublecomplex *b, integer *ldb);

/* Subroutine */ int zhbev_(char *jobz, char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, doublereal *w, doublecomplex *z__, 
	integer *ldz, doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zhbevd_(char *jobz, char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, doublereal *w, doublecomplex *z__, 
	integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, 
	integer *lrwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int zhbevx_(char *jobz, char *range, char *uplo, integer *n, 
	integer *kd, doublecomplex *ab, integer *ldab, doublecomplex *q, 
	integer *ldq, doublereal *vl, doublereal *vu, integer *il, integer *
	iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, 
	 integer *ldz, doublecomplex *work, doublereal *rwork, integer *iwork, 
	 integer *ifail, integer *info);

/* Subroutine */ int zhbgst_(char *vect, char *uplo, integer *n, integer *ka, 
	integer *kb, doublecomplex *ab, integer *ldab, doublecomplex *bb, 
	integer *ldbb, doublecomplex *x, integer *ldx, doublecomplex *work, 
	doublereal *rwork, integer *info);

/* Subroutine */ int zhbgv_(char *jobz, char *uplo, integer *n, integer *ka, 
	integer *kb, doublecomplex *ab, integer *ldab, doublecomplex *bb, 
	integer *ldbb, doublereal *w, doublecomplex *z__, integer *ldz, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zhbgvd_(char *jobz, char *uplo, integer *n, integer *ka, 
	integer *kb, doublecomplex *ab, integer *ldab, doublecomplex *bb, 
	integer *ldbb, doublereal *w, doublecomplex *z__, integer *ldz, 
	doublecomplex *work, integer *lwork, doublereal *rwork, integer *
	lrwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int zhbgvx_(char *jobz, char *range, char *uplo, integer *n, 
	integer *ka, integer *kb, doublecomplex *ab, integer *ldab, 
	doublecomplex *bb, integer *ldbb, doublecomplex *q, integer *ldq, 
	doublereal *vl, doublereal *vu, integer *il, integer *iu, doublereal *
	abstol, integer *m, doublereal *w, doublecomplex *z__, integer *ldz, 
	doublecomplex *work, doublereal *rwork, integer *iwork, integer *
	ifail, integer *info);

/* Subroutine */ int zhbtrd_(char *vect, char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, doublereal *d__, doublereal *e, 
	doublecomplex *q, integer *ldq, doublecomplex *work, integer *info);

/* Subroutine */ int zhecon_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, doublereal *anorm, doublereal *rcond, 
	doublecomplex *work, integer *info);

/* Subroutine */ int zheequb_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublereal *s, doublereal *scond, doublereal *amax, 
	doublecomplex *work, integer *info);

/* Subroutine */ int zheev_(char *jobz, char *uplo, integer *n, doublecomplex 
	*a, integer *lda, doublereal *w, doublecomplex *work, integer *lwork, 
	doublereal *rwork, integer *info);

/* Subroutine */ int zheevd_(char *jobz, char *uplo, integer *n, 
	doublecomplex *a, integer *lda, doublereal *w, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, 
	integer *liwork, integer *info);

/* Subroutine */ int zheevr_(char *jobz, char *range, char *uplo, integer *n, 
	doublecomplex *a, integer *lda, doublereal *vl, doublereal *vu, 
	integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *
	w, doublecomplex *z__, integer *ldz, integer *isuppz, doublecomplex *
	work, integer *lwork, doublereal *rwork, integer *lrwork, integer *
	iwork, integer *liwork, integer *info);

/* Subroutine */ int zheevx_(char *jobz, char *range, char *uplo, integer *n, 
	doublecomplex *a, integer *lda, doublereal *vl, doublereal *vu, 
	integer *il, integer *iu, doublereal *abstol, integer *m, doublereal *
	w, doublecomplex *z__, integer *ldz, doublecomplex *work, integer *
	lwork, doublereal *rwork, integer *iwork, integer *ifail, integer *
	info);

/* Subroutine */ int zhegs2_(integer *itype, char *uplo, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zhegst_(integer *itype, char *uplo, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zhegv_(integer *itype, char *jobz, char *uplo, integer *
	n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublereal *w, doublecomplex *work, integer *lwork, doublereal *rwork, 
	 integer *info);

/* Subroutine */ int zhegvd_(integer *itype, char *jobz, char *uplo, integer *
	n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublereal *w, doublecomplex *work, integer *lwork, doublereal *rwork, 
	 integer *lrwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int zhegvx_(integer *itype, char *jobz, char *range, char *
	uplo, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, 
	integer *ldb, doublereal *vl, doublereal *vu, integer *il, integer *
	iu, doublereal *abstol, integer *m, doublereal *w, doublecomplex *z__, 
	 integer *ldz, doublecomplex *work, integer *lwork, doublereal *rwork, 
	 integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int zherfs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, 
	integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, 
	integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, 
	 doublereal *rwork, integer *info);

/* Subroutine */ int zherfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, integer *ipiv, doublereal *s, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *berr, 
	integer *n_err_bnds__, doublereal *err_bnds_norm__, doublereal *
	err_bnds_comp__, integer *nparams, doublereal *params, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zhesv_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, 
	integer *ldb, doublecomplex *work, integer *lwork, integer *info);

/* Subroutine */ int zhesvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, 
	 integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, 
	doublecomplex *work, integer *lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zhesvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, integer *ipiv, char *equed, doublereal *s, doublecomplex *b, 
	integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, 
	doublereal *rpvgrw, doublereal *berr, integer *n_err_bnds__, 
	doublereal *err_bnds_norm__, doublereal *err_bnds_comp__, integer *
	nparams, doublereal *params, doublecomplex *work, doublereal *rwork, 
	integer *info);

/* Subroutine */ int zhetd2_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublereal *d__, doublereal *e, doublecomplex *tau, 
	integer *info);

/* Subroutine */ int zhetf2_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, integer *info);

/* Subroutine */ int zhetrd_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublereal *d__, doublereal *e, doublecomplex *tau, 
	doublecomplex *work, integer *lwork, integer *info);

/* Subroutine */ int zhetrf_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, doublecomplex *work, integer *lwork, 
	integer *info);

/* Subroutine */ int zhetri_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, doublecomplex *work, integer *info);

/* Subroutine */ int zhetrs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, 
	integer *ldb, integer *info);

/* Subroutine */ int zhfrk_(char *transr, char *uplo, char *trans, integer *n, 
	 integer *k, doublereal *alpha, doublecomplex *a, integer *lda, 
	doublereal *beta, doublecomplex *c__);

/* Subroutine */ int zhgeqz_(char *job, char *compq, char *compz, integer *n, 
	integer *ilo, integer *ihi, doublecomplex *h__, integer *ldh, 
	doublecomplex *t, integer *ldt, doublecomplex *alpha, doublecomplex *
	beta, doublecomplex *q, integer *ldq, doublecomplex *z__, integer *
	ldz, doublecomplex *work, integer *lwork, doublereal *rwork, integer *
	info);

/* Subroutine */ int zhpcon_(char *uplo, integer *n, doublecomplex *ap, 
	integer *ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *
	work, integer *info);

/* Subroutine */ int zhpev_(char *jobz, char *uplo, integer *n, doublecomplex 
	*ap, doublereal *w, doublecomplex *z__, integer *ldz, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zhpevd_(char *jobz, char *uplo, integer *n, 
	doublecomplex *ap, doublereal *w, doublecomplex *z__, integer *ldz, 
	doublecomplex *work, integer *lwork, doublereal *rwork, integer *
	lrwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int zhpevx_(char *jobz, char *range, char *uplo, integer *n, 
	doublecomplex *ap, doublereal *vl, doublereal *vu, integer *il, 
	integer *iu, doublereal *abstol, integer *m, doublereal *w, 
	doublecomplex *z__, integer *ldz, doublecomplex *work, doublereal *
	rwork, integer *iwork, integer *ifail, integer *info);

/* Subroutine */ int zhpgst_(integer *itype, char *uplo, integer *n, 
	doublecomplex *ap, doublecomplex *bp, integer *info);

/* Subroutine */ int zhpgv_(integer *itype, char *jobz, char *uplo, integer *
	n, doublecomplex *ap, doublecomplex *bp, doublereal *w, doublecomplex 
	*z__, integer *ldz, doublecomplex *work, doublereal *rwork, integer *
	info);

/* Subroutine */ int zhpgvd_(integer *itype, char *jobz, char *uplo, integer *
	n, doublecomplex *ap, doublecomplex *bp, doublereal *w, doublecomplex 
	*z__, integer *ldz, doublecomplex *work, integer *lwork, doublereal *
	rwork, integer *lrwork, integer *iwork, integer *liwork, integer *
	info);

/* Subroutine */ int zhpgvx_(integer *itype, char *jobz, char *range, char *
	uplo, integer *n, doublecomplex *ap, doublecomplex *bp, doublereal *
	vl, doublereal *vu, integer *il, integer *iu, doublereal *abstol, 
	integer *m, doublereal *w, doublecomplex *z__, integer *ldz, 
	doublecomplex *work, doublereal *rwork, integer *iwork, integer *
	ifail, integer *info);

/* Subroutine */ int zhprfs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, doublecomplex *afp, integer *ipiv, doublecomplex *
	b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, 
	doublereal *berr, doublecomplex *work, doublereal *rwork, integer *
	info);

/* Subroutine */ int zhpsv_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, integer *ipiv, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zhpsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublecomplex *ap, doublecomplex *afp, integer *ipiv, 
	doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zhptrd_(char *uplo, integer *n, doublecomplex *ap, 
	doublereal *d__, doublereal *e, doublecomplex *tau, integer *info);

/* Subroutine */ int zhptrf_(char *uplo, integer *n, doublecomplex *ap, 
	integer *ipiv, integer *info);

/* Subroutine */ int zhptri_(char *uplo, integer *n, doublecomplex *ap, 
	integer *ipiv, doublecomplex *work, integer *info);

/* Subroutine */ int zhptrs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, integer *ipiv, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zhsein_(char *side, char *eigsrc, char *initv, logical *
	select, integer *n, doublecomplex *h__, integer *ldh, doublecomplex *
	w, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, 
	 integer *mm, integer *m, doublecomplex *work, doublereal *rwork, 
	integer *ifaill, integer *ifailr, integer *info);

/* Subroutine */ int zhseqr_(char *job, char *compz, integer *n, integer *ilo, 
	 integer *ihi, doublecomplex *h__, integer *ldh, doublecomplex *w, 
	doublecomplex *z__, integer *ldz, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zla_gbamv__(integer *trans, integer *m, integer *n, 
	integer *kl, integer *ku, doublereal *alpha, doublecomplex *ab, 
	integer *ldab, doublecomplex *x, integer *incx, doublereal *beta, 
	doublereal *y, integer *incy);

doublereal zla_gbrcond_c__(char *trans, integer *n, integer *kl, integer *ku, 
	doublecomplex *ab, integer *ldab, doublecomplex *afb, integer *ldafb, 
	integer *ipiv, doublereal *c__, logical *capply, integer *info, 
	doublecomplex *work, doublereal *rwork, ftnlen trans_len);

doublereal zla_gbrcond_x__(char *trans, integer *n, integer *kl, integer *ku, 
	doublecomplex *ab, integer *ldab, doublecomplex *afb, integer *ldafb, 
	integer *ipiv, doublecomplex *x, integer *info, doublecomplex *work, 
	doublereal *rwork, ftnlen trans_len);

/* Subroutine */ int zla_gbrfsx_extended__(integer *prec_type__, integer *
	trans_type__, integer *n, integer *kl, integer *ku, integer *nrhs, 
	doublecomplex *ab, integer *ldab, doublecomplex *afb, integer *ldafb, 
	integer *ipiv, logical *colequ, doublereal *c__, doublecomplex *b, 
	integer *ldb, doublecomplex *y, integer *ldy, doublereal *berr_out__, 
	integer *n_norms__, doublereal *errs_n__, doublereal *errs_c__, 
	doublecomplex *res, doublereal *ayb, doublecomplex *dy, doublecomplex 
	*y_tail__, doublereal *rcond, integer *ithresh, doublereal *rthresh, 
	doublereal *dz_ub__, logical *ignore_cwise__, integer *info);

doublereal zla_gbrpvgrw__(integer *n, integer *kl, integer *ku, integer *
	ncols, doublecomplex *ab, integer *ldab, doublecomplex *afb, integer *
	ldafb);

/* Subroutine */ int zla_geamv__(integer *trans, integer *m, integer *n, 
	doublereal *alpha, doublecomplex *a, integer *lda, doublecomplex *x, 
	integer *incx, doublereal *beta, doublereal *y, integer *incy);

doublereal zla_gercond_c__(char *trans, integer *n, doublecomplex *a, integer 
	*lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublereal *
	c__, logical *capply, integer *info, doublecomplex *work, doublereal *
	rwork, ftnlen trans_len);

doublereal zla_gercond_x__(char *trans, integer *n, doublecomplex *a, integer 
	*lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublecomplex *
	x, integer *info, doublecomplex *work, doublereal *rwork, ftnlen 
	trans_len);

/* Subroutine */ int zla_gerfsx_extended__(integer *prec_type__, integer *
	trans_type__, integer *n, integer *nrhs, doublecomplex *a, integer *
	lda, doublecomplex *af, integer *ldaf, integer *ipiv, logical *colequ,
	 doublereal *c__, doublecomplex *b, integer *ldb, doublecomplex *y, 
	integer *ldy, doublereal *berr_out__, integer *n_norms__, doublereal *
	errs_n__, doublereal *errs_c__, doublecomplex *res, doublereal *ayb, 
	doublecomplex *dy, doublecomplex *y_tail__, doublereal *rcond, 
	integer *ithresh, doublereal *rthresh, doublereal *dz_ub__, logical *
	ignore_cwise__, integer *info);

/* Subroutine */ int zla_heamv__(integer *uplo, integer *n, doublereal *alpha,
	 doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, 
	doublereal *beta, doublereal *y, integer *incy);

doublereal zla_hercond_c__(char *uplo, integer *n, doublecomplex *a, integer *
	lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublereal *c__,
	 logical *capply, integer *info, doublecomplex *work, doublereal *
	rwork, ftnlen uplo_len);

doublereal zla_hercond_x__(char *uplo, integer *n, doublecomplex *a, integer *
	lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublecomplex *
	x, integer *info, doublecomplex *work, doublereal *rwork, ftnlen 
	uplo_len);

/* Subroutine */ int zla_herfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, doublecomplex *a, integer *lda, 
	doublecomplex *af, integer *ldaf, integer *ipiv, logical *colequ, 
	doublereal *c__, doublecomplex *b, integer *ldb, doublecomplex *y, 
	integer *ldy, doublereal *berr_out__, integer *n_norms__, doublereal *
	errs_n__, doublereal *errs_c__, doublecomplex *res, doublereal *ayb, 
	doublecomplex *dy, doublecomplex *y_tail__, doublereal *rcond, 
	integer *ithresh, doublereal *rthresh, doublereal *dz_ub__, logical *
	ignore_cwise__, integer *info, ftnlen uplo_len);

doublereal zla_herpvgrw__(char *uplo, integer *n, integer *info, 
	doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, 
	integer *ipiv, doublereal *work, ftnlen uplo_len);

/* Subroutine */ int zla_lin_berr__(integer *n, integer *nz, integer *nrhs, 
	doublecomplex *res, doublereal *ayb, doublereal *berr);

doublereal zla_porcond_c__(char *uplo, integer *n, doublecomplex *a, integer *
	lda, doublecomplex *af, integer *ldaf, doublereal *c__, logical *
	capply, integer *info, doublecomplex *work, doublereal *rwork, ftnlen 
	uplo_len);

doublereal zla_porcond_x__(char *uplo, integer *n, doublecomplex *a, integer *
	lda, doublecomplex *af, integer *ldaf, doublecomplex *x, integer *
	info, doublecomplex *work, doublereal *rwork, ftnlen uplo_len);

/* Subroutine */ int zla_porfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, doublecomplex *a, integer *lda, 
	doublecomplex *af, integer *ldaf, logical *colequ, doublereal *c__, 
	doublecomplex *b, integer *ldb, doublecomplex *y, integer *ldy, 
	doublereal *berr_out__, integer *n_norms__, doublereal *errs_n__, 
	doublereal *errs_c__, doublecomplex *res, doublereal *ayb, 
	doublecomplex *dy, doublecomplex *y_tail__, doublereal *rcond, 
	integer *ithresh, doublereal *rthresh, doublereal *dz_ub__, logical *
	ignore_cwise__, integer *info, ftnlen uplo_len);

doublereal zla_porpvgrw__(char *uplo, integer *ncols, doublecomplex *a, 
	integer *lda, doublecomplex *af, integer *ldaf, doublereal *work, 
	ftnlen uplo_len);

doublereal zla_rpvgrw__(integer *n, integer *ncols, doublecomplex *a, integer 
	*lda, doublecomplex *af, integer *ldaf);

/* Subroutine */ int zla_syamv__(integer *uplo, integer *n, doublereal *alpha,
	 doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, 
	doublereal *beta, doublereal *y, integer *incy);

doublereal zla_syrcond_c__(char *uplo, integer *n, doublecomplex *a, integer *
	lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublereal *c__,
	 logical *capply, integer *info, doublecomplex *work, doublereal *
	rwork, ftnlen uplo_len);

doublereal zla_syrcond_x__(char *uplo, integer *n, doublecomplex *a, integer *
	lda, doublecomplex *af, integer *ldaf, integer *ipiv, doublecomplex *
	x, integer *info, doublecomplex *work, doublereal *rwork, ftnlen 
	uplo_len);

/* Subroutine */ int zla_syrfsx_extended__(integer *prec_type__, char *uplo, 
	integer *n, integer *nrhs, doublecomplex *a, integer *lda, 
	doublecomplex *af, integer *ldaf, integer *ipiv, logical *colequ, 
	doublereal *c__, doublecomplex *b, integer *ldb, doublecomplex *y, 
	integer *ldy, doublereal *berr_out__, integer *n_norms__, doublereal *
	errs_n__, doublereal *errs_c__, doublecomplex *res, doublereal *ayb, 
	doublecomplex *dy, doublecomplex *y_tail__, doublereal *rcond, 
	integer *ithresh, doublereal *rthresh, doublereal *dz_ub__, logical *
	ignore_cwise__, integer *info, ftnlen uplo_len);

doublereal zla_syrpvgrw__(char *uplo, integer *n, integer *info, 
	doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, 
	integer *ipiv, doublereal *work, ftnlen uplo_len);

/* Subroutine */ int zla_wwaddw__(integer *n, doublecomplex *x, doublecomplex 
	*y, doublecomplex *w);

/* Subroutine */ int zlabrd_(integer *m, integer *n, integer *nb, 
	doublecomplex *a, integer *lda, doublereal *d__, doublereal *e, 
	doublecomplex *tauq, doublecomplex *taup, doublecomplex *x, integer *
	ldx, doublecomplex *y, integer *ldy);

/* Subroutine */ int zlacgv_(integer *n, doublecomplex *x, integer *incx);

/* Subroutine */ int zlacn2_(integer *n, doublecomplex *v, doublecomplex *x, 
	doublereal *est, integer *kase, integer *isave);

/* Subroutine */ int zlacon_(integer *n, doublecomplex *v, doublecomplex *x, 
	doublereal *est, integer *kase);

/* Subroutine */ int zlacp2_(char *uplo, integer *m, integer *n, doublereal *
	a, integer *lda, doublecomplex *b, integer *ldb);

/* Subroutine */ int zlacpy_(char *uplo, integer *m, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb);

/* Subroutine */ int zlacrm_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublereal *b, integer *ldb, doublecomplex *c__, 
	integer *ldc, doublereal *rwork);

/* Subroutine */ int zlacrt_(integer *n, doublecomplex *cx, integer *incx, 
	doublecomplex *cy, integer *incy, doublecomplex *c__, doublecomplex *
	s);

/* Double Complex */ VOID zladiv_(doublecomplex * ret_val, doublecomplex *x, 
	doublecomplex *y);

/* Subroutine */ int zlaed0_(integer *qsiz, integer *n, doublereal *d__, 
	doublereal *e, doublecomplex *q, integer *ldq, doublecomplex *qstore, 
	integer *ldqs, doublereal *rwork, integer *iwork, integer *info);

/* Subroutine */ int zlaed7_(integer *n, integer *cutpnt, integer *qsiz, 
	integer *tlvls, integer *curlvl, integer *curpbm, doublereal *d__, 
	doublecomplex *q, integer *ldq, doublereal *rho, integer *indxq, 
	doublereal *qstore, integer *qptr, integer *prmptr, integer *perm, 
	integer *givptr, integer *givcol, doublereal *givnum, doublecomplex *
	work, doublereal *rwork, integer *iwork, integer *info);

/* Subroutine */ int zlaed8_(integer *k, integer *n, integer *qsiz, 
	doublecomplex *q, integer *ldq, doublereal *d__, doublereal *rho, 
	integer *cutpnt, doublereal *z__, doublereal *dlamda, doublecomplex *
	q2, integer *ldq2, doublereal *w, integer *indxp, integer *indx, 
	integer *indxq, integer *perm, integer *givptr, integer *givcol, 
	doublereal *givnum, integer *info);

/* Subroutine */ int zlaein_(logical *rightv, logical *noinit, integer *n, 
	doublecomplex *h__, integer *ldh, doublecomplex *w, doublecomplex *v, 
	doublecomplex *b, integer *ldb, doublereal *rwork, doublereal *eps3, 
	doublereal *smlnum, integer *info);

/* Subroutine */ int zlaesy_(doublecomplex *a, doublecomplex *b, 
	doublecomplex *c__, doublecomplex *rt1, doublecomplex *rt2, 
	doublecomplex *evscal, doublecomplex *cs1, doublecomplex *sn1);

/* Subroutine */ int zlaev2_(doublecomplex *a, doublecomplex *b, 
	doublecomplex *c__, doublereal *rt1, doublereal *rt2, doublereal *cs1, 
	 doublecomplex *sn1);

/* Subroutine */ int zlag2c_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, floatcomplex *sa, integer *ldsa, integer *info);

/* Subroutine */ int zlags2_(logical *upper, doublereal *a1, doublecomplex *
	a2, doublereal *a3, doublereal *b1, doublecomplex *b2, doublereal *b3, 
	 doublereal *csu, doublecomplex *snu, doublereal *csv, doublecomplex *
	snv, doublereal *csq, doublecomplex *snq);

/* Subroutine */ int zlagtm_(char *trans, integer *n, integer *nrhs, 
	doublereal *alpha, doublecomplex *dl, doublecomplex *d__, 
	doublecomplex *du, doublecomplex *x, integer *ldx, doublereal *beta, 
	doublecomplex *b, integer *ldb);

/* Subroutine */ int zlahef_(char *uplo, integer *n, integer *nb, integer *kb, 
	 doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *w, 
	integer *ldw, integer *info);

/* Subroutine */ int zlahqr_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, doublecomplex *h__, integer *ldh, 
	doublecomplex *w, integer *iloz, integer *ihiz, doublecomplex *z__, 
	integer *ldz, integer *info);

/* Subroutine */ int zlahr2_(integer *n, integer *k, integer *nb, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *t, 
	integer *ldt, doublecomplex *y, integer *ldy);

/* Subroutine */ int zlahrd_(integer *n, integer *k, integer *nb, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *t, 
	integer *ldt, doublecomplex *y, integer *ldy);

/* Subroutine */ int zlaic1_(integer *job, integer *j, doublecomplex *x, 
	doublereal *sest, doublecomplex *w, doublecomplex *gamma, doublereal *
	sestpr, doublecomplex *s, doublecomplex *c__);

/* Subroutine */ int zlals0_(integer *icompq, integer *nl, integer *nr, 
	integer *sqre, integer *nrhs, doublecomplex *b, integer *ldb, 
	doublecomplex *bx, integer *ldbx, integer *perm, integer *givptr, 
	integer *givcol, integer *ldgcol, doublereal *givnum, integer *ldgnum, 
	 doublereal *poles, doublereal *difl, doublereal *difr, doublereal *
	z__, integer *k, doublereal *c__, doublereal *s, doublereal *rwork, 
	integer *info);

/* Subroutine */ int zlalsa_(integer *icompq, integer *smlsiz, integer *n, 
	integer *nrhs, doublecomplex *b, integer *ldb, doublecomplex *bx, 
	integer *ldbx, doublereal *u, integer *ldu, doublereal *vt, integer *
	k, doublereal *difl, doublereal *difr, doublereal *z__, doublereal *
	poles, integer *givptr, integer *givcol, integer *ldgcol, integer *
	perm, doublereal *givnum, doublereal *c__, doublereal *s, doublereal *
	rwork, integer *iwork, integer *info);

/* Subroutine */ int zlalsd_(char *uplo, integer *smlsiz, integer *n, integer 
	*nrhs, doublereal *d__, doublereal *e, doublecomplex *b, integer *ldb, 
	 doublereal *rcond, integer *rank, doublecomplex *work, doublereal *
	rwork, integer *iwork, integer *info);

doublereal zlangb_(char *norm, integer *n, integer *kl, integer *ku, 
	doublecomplex *ab, integer *ldab, doublereal *work);

doublereal zlange_(char *norm, integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublereal *work);

doublereal zlangt_(char *norm, integer *n, doublecomplex *dl, doublecomplex *
	d__, doublecomplex *du);

doublereal zlanhb_(char *norm, char *uplo, integer *n, integer *k, 
	doublecomplex *ab, integer *ldab, doublereal *work);

doublereal zlanhe_(char *norm, char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublereal *work);

doublereal zlanhf_(char *norm, char *transr, char *uplo, integer *n, 
	doublecomplex *a, doublereal *work);

doublereal zlanhp_(char *norm, char *uplo, integer *n, doublecomplex *ap, 
	doublereal *work);

doublereal zlanhs_(char *norm, integer *n, doublecomplex *a, integer *lda, 
	doublereal *work);

doublereal zlanht_(char *norm, integer *n, doublereal *d__, doublecomplex *e);

doublereal zlansb_(char *norm, char *uplo, integer *n, integer *k, 
	doublecomplex *ab, integer *ldab, doublereal *work);

doublereal zlansp_(char *norm, char *uplo, integer *n, doublecomplex *ap, 
	doublereal *work);

doublereal zlansy_(char *norm, char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublereal *work);

doublereal zlantb_(char *norm, char *uplo, char *diag, integer *n, integer *k, 
	 doublecomplex *ab, integer *ldab, doublereal *work);

doublereal zlantp_(char *norm, char *uplo, char *diag, integer *n, 
	doublecomplex *ap, doublereal *work);

doublereal zlantr_(char *norm, char *uplo, char *diag, integer *m, integer *n, 
	 doublecomplex *a, integer *lda, doublereal *work);

/* Subroutine */ int zlapll_(integer *n, doublecomplex *x, integer *incx, 
	doublecomplex *y, integer *incy, doublereal *ssmin);

/* Subroutine */ int zlapmt_(logical *forwrd, integer *m, integer *n, 
	doublecomplex *x, integer *ldx, integer *k);

/* Subroutine */ int zlaqgb_(integer *m, integer *n, integer *kl, integer *ku, 
	 doublecomplex *ab, integer *ldab, doublereal *r__, doublereal *c__, 
	doublereal *rowcnd, doublereal *colcnd, doublereal *amax, char *equed);

/* Subroutine */ int zlaqge_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublereal *r__, doublereal *c__, doublereal *rowcnd, 
	doublereal *colcnd, doublereal *amax, char *equed);

/* Subroutine */ int zlaqhb_(char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, doublereal *s, doublereal *scond, 
	doublereal *amax, char *equed);

/* Subroutine */ int zlaqhe_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublereal *s, doublereal *scond, doublereal *amax, 
	char *equed);

/* Subroutine */ int zlaqhp_(char *uplo, integer *n, doublecomplex *ap, 
	doublereal *s, doublereal *scond, doublereal *amax, char *equed);

/* Subroutine */ int zlaqp2_(integer *m, integer *n, integer *offset, 
	doublecomplex *a, integer *lda, integer *jpvt, doublecomplex *tau, 
	doublereal *vn1, doublereal *vn2, doublecomplex *work);

/* Subroutine */ int zlaqps_(integer *m, integer *n, integer *offset, integer 
	*nb, integer *kb, doublecomplex *a, integer *lda, integer *jpvt, 
	doublecomplex *tau, doublereal *vn1, doublereal *vn2, doublecomplex *
	auxv, doublecomplex *f, integer *ldf);

/* Subroutine */ int zlaqr0_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, doublecomplex *h__, integer *ldh, 
	doublecomplex *w, integer *iloz, integer *ihiz, doublecomplex *z__, 
	integer *ldz, doublecomplex *work, integer *lwork, integer *info);

/* Subroutine */ int zlaqr1_(integer *n, doublecomplex *h__, integer *ldh, 
	doublecomplex *s1, doublecomplex *s2, doublecomplex *v);

/* Subroutine */ int zlaqr2_(logical *wantt, logical *wantz, integer *n, 
	integer *ktop, integer *kbot, integer *nw, doublecomplex *h__, 
	integer *ldh, integer *iloz, integer *ihiz, doublecomplex *z__, 
	integer *ldz, integer *ns, integer *nd, doublecomplex *sh, 
	doublecomplex *v, integer *ldv, integer *nh, doublecomplex *t, 
	integer *ldt, integer *nv, doublecomplex *wv, integer *ldwv, 
	doublecomplex *work, integer *lwork);

/* Subroutine */ int zlaqr3_(logical *wantt, logical *wantz, integer *n, 
	integer *ktop, integer *kbot, integer *nw, doublecomplex *h__, 
	integer *ldh, integer *iloz, integer *ihiz, doublecomplex *z__, 
	integer *ldz, integer *ns, integer *nd, doublecomplex *sh, 
	doublecomplex *v, integer *ldv, integer *nh, doublecomplex *t, 
	integer *ldt, integer *nv, doublecomplex *wv, integer *ldwv, 
	doublecomplex *work, integer *lwork);

/* Subroutine */ int zlaqr4_(logical *wantt, logical *wantz, integer *n, 
	integer *ilo, integer *ihi, doublecomplex *h__, integer *ldh, 
	doublecomplex *w, integer *iloz, integer *ihiz, doublecomplex *z__, 
	integer *ldz, doublecomplex *work, integer *lwork, integer *info);

/* Subroutine */ int zlaqr5_(logical *wantt, logical *wantz, integer *kacc22, 
	integer *n, integer *ktop, integer *kbot, integer *nshfts, 
	doublecomplex *s, doublecomplex *h__, integer *ldh, integer *iloz, 
	integer *ihiz, doublecomplex *z__, integer *ldz, doublecomplex *v, 
	integer *ldv, doublecomplex *u, integer *ldu, integer *nv, 
	doublecomplex *wv, integer *ldwv, integer *nh, doublecomplex *wh, 
	integer *ldwh);

/* Subroutine */ int zlaqsb_(char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, doublereal *s, doublereal *scond, 
	doublereal *amax, char *equed);

/* Subroutine */ int zlaqsp_(char *uplo, integer *n, doublecomplex *ap, 
	doublereal *s, doublereal *scond, doublereal *amax, char *equed);

/* Subroutine */ int zlaqsy_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublereal *s, doublereal *scond, doublereal *amax, 
	char *equed);

/* Subroutine */ int zlar1v_(integer *n, integer *b1, integer *bn, doublereal 
	*lambda, doublereal *d__, doublereal *l, doublereal *ld, doublereal *
	lld, doublereal *pivmin, doublereal *gaptol, doublecomplex *z__, 
	logical *wantnc, integer *negcnt, doublereal *ztz, doublereal *mingma, 
	 integer *r__, integer *isuppz, doublereal *nrminv, doublereal *resid, 
	 doublereal *rqcorr, doublereal *work);

/* Subroutine */ int zlar2v_(integer *n, doublecomplex *x, doublecomplex *y, 
	doublecomplex *z__, integer *incx, doublereal *c__, doublecomplex *s, 
	integer *incc);

/* Subroutine */ int zlarcm_(integer *m, integer *n, doublereal *a, integer *
	lda, doublecomplex *b, integer *ldb, doublecomplex *c__, integer *ldc, 
	 doublereal *rwork);

/* Subroutine */ int zlarf_(char *side, integer *m, integer *n, doublecomplex 
	*v, integer *incv, doublecomplex *tau, doublecomplex *c__, integer *
	ldc, doublecomplex *work);

/* Subroutine */ int zlarfb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, doublecomplex *v, integer 
	*ldv, doublecomplex *t, integer *ldt, doublecomplex *c__, integer *
	ldc, doublecomplex *work, integer *ldwork);

/* Subroutine */ int zlarfg_(integer *n, doublecomplex *alpha, doublecomplex *
	x, integer *incx, doublecomplex *tau);

/* Subroutine */ int zlarfp_(integer *n, doublecomplex *alpha, doublecomplex *
	x, integer *incx, doublecomplex *tau);

/* Subroutine */ int zlarft_(char *direct, char *storev, integer *n, integer *
	k, doublecomplex *v, integer *ldv, doublecomplex *tau, doublecomplex *
	t, integer *ldt);

/* Subroutine */ int zlarfx_(char *side, integer *m, integer *n, 
	doublecomplex *v, doublecomplex *tau, doublecomplex *c__, integer *
	ldc, doublecomplex *work);

/* Subroutine */ int zlargv_(integer *n, doublecomplex *x, integer *incx, 
	doublecomplex *y, integer *incy, doublereal *c__, integer *incc);

/* Subroutine */ int zlarnv_(integer *idist, integer *iseed, integer *n, 
	doublecomplex *x);

/* Subroutine */ int zlarrv_(integer *n, doublereal *vl, doublereal *vu, 
	doublereal *d__, doublereal *l, doublereal *pivmin, integer *isplit, 
	integer *m, integer *dol, integer *dou, doublereal *minrgp, 
	doublereal *rtol1, doublereal *rtol2, doublereal *w, doublereal *werr, 
	 doublereal *wgap, integer *iblock, integer *indexw, doublereal *gers, 
	 doublecomplex *z__, integer *ldz, integer *isuppz, doublereal *work, 
	integer *iwork, integer *info);

/* Subroutine */ int zlarscl2_(integer *m, integer *n, doublereal *d__, 
	doublecomplex *x, integer *ldx);

/* Subroutine */ int zlartg_(doublecomplex *f, doublecomplex *g, doublereal *
	cs, doublecomplex *sn, doublecomplex *r__);

/* Subroutine */ int zlartv_(integer *n, doublecomplex *x, integer *incx, 
	doublecomplex *y, integer *incy, doublereal *c__, doublecomplex *s, 
	integer *incc);

/* Subroutine */ int zlarz_(char *side, integer *m, integer *n, integer *l, 
	doublecomplex *v, integer *incv, doublecomplex *tau, doublecomplex *
	c__, integer *ldc, doublecomplex *work);

/* Subroutine */ int zlarzb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, integer *l, doublecomplex 
	*v, integer *ldv, doublecomplex *t, integer *ldt, doublecomplex *c__, 
	integer *ldc, doublecomplex *work, integer *ldwork);

/* Subroutine */ int zlarzt_(char *direct, char *storev, integer *n, integer *
	k, doublecomplex *v, integer *ldv, doublecomplex *tau, doublecomplex *
	t, integer *ldt);

/* Subroutine */ int zlascl_(char *type__, integer *kl, integer *ku, 
	doublereal *cfrom, doublereal *cto, integer *m, integer *n, 
	doublecomplex *a, integer *lda, integer *info);

/* Subroutine */ int zlascl2_(integer *m, integer *n, doublereal *d__, 
	doublecomplex *x, integer *ldx);

/* Subroutine */ int zlaset_(char *uplo, integer *m, integer *n, 
	doublecomplex *alpha, doublecomplex *beta, doublecomplex *a, integer *
	lda);

/* Subroutine */ int zlasr_(char *side, char *pivot, char *direct, integer *m, 
	 integer *n, doublereal *c__, doublereal *s, doublecomplex *a, 
	integer *lda);

/* Subroutine */ int zlassq_(integer *n, doublecomplex *x, integer *incx, 
	doublereal *scale, doublereal *sumsq);

/* Subroutine */ int zlaswp_(integer *n, doublecomplex *a, integer *lda, 
	integer *k1, integer *k2, integer *ipiv, integer *incx);

/* Subroutine */ int zlasyf_(char *uplo, integer *n, integer *nb, integer *kb, 
	 doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *w, 
	integer *ldw, integer *info);

/* Subroutine */ int zlat2c_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, floatcomplex *sa, integer *ldsa, integer *info);

/* Subroutine */ int zlatbs_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, integer *kd, doublecomplex *ab, integer *ldab, 
	doublecomplex *x, doublereal *scale, doublereal *cnorm, integer *info);

/* Subroutine */ int zlatdf_(integer *ijob, integer *n, doublecomplex *z__, 
	integer *ldz, doublecomplex *rhs, doublereal *rdsum, doublereal *
	rdscal, integer *ipiv, integer *jpiv);

/* Subroutine */ int zlatps_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, doublecomplex *ap, doublecomplex *x, doublereal *
	scale, doublereal *cnorm, integer *info);

/* Subroutine */ int zlatrd_(char *uplo, integer *n, integer *nb, 
	doublecomplex *a, integer *lda, doublereal *e, doublecomplex *tau, 
	doublecomplex *w, integer *ldw);

/* Subroutine */ int zlatrs_(char *uplo, char *trans, char *diag, char *
	normin, integer *n, doublecomplex *a, integer *lda, doublecomplex *x, 
	doublereal *scale, doublereal *cnorm, integer *info);

/* Subroutine */ int zlatrz_(integer *m, integer *n, integer *l, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work);

/* Subroutine */ int zlatzm_(char *side, integer *m, integer *n, 
	doublecomplex *v, integer *incv, doublecomplex *tau, doublecomplex *
	c1, doublecomplex *c2, integer *ldc, doublecomplex *work);

/* Subroutine */ int zlauu2_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *info);

/* Subroutine */ int zlauum_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *info);

/* Subroutine */ int zpbcon_(char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, doublereal *anorm, doublereal *
	rcond, doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zpbequ_(char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, doublereal *s, doublereal *scond, 
	doublereal *amax, integer *info);

/* Subroutine */ int zpbrfs_(char *uplo, integer *n, integer *kd, integer *
	nrhs, doublecomplex *ab, integer *ldab, doublecomplex *afb, integer *
	ldafb, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	 doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *
	rwork, integer *info);

/* Subroutine */ int zpbstf_(char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, integer *info);

/* Subroutine */ int zpbsv_(char *uplo, integer *n, integer *kd, integer *
	nrhs, doublecomplex *ab, integer *ldab, doublecomplex *b, integer *
	ldb, integer *info);

/* Subroutine */ int zpbsvx_(char *fact, char *uplo, integer *n, integer *kd, 
	integer *nrhs, doublecomplex *ab, integer *ldab, doublecomplex *afb, 
	integer *ldafb, char *equed, doublereal *s, doublecomplex *b, integer 
	*ldb, doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *
	ferr, doublereal *berr, doublecomplex *work, doublereal *rwork, 
	integer *info);

/* Subroutine */ int zpbtf2_(char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, integer *info);

/* Subroutine */ int zpbtrf_(char *uplo, integer *n, integer *kd, 
	doublecomplex *ab, integer *ldab, integer *info);

/* Subroutine */ int zpbtrs_(char *uplo, integer *n, integer *kd, integer *
	nrhs, doublecomplex *ab, integer *ldab, doublecomplex *b, integer *
	ldb, integer *info);

/* Subroutine */ int zpftrf_(char *transr, char *uplo, integer *n, 
	doublecomplex *a, integer *info);

/* Subroutine */ int zpftri_(char *transr, char *uplo, integer *n, 
	doublecomplex *a, integer *info);

/* Subroutine */ int zpftrs_(char *transr, char *uplo, integer *n, integer *
	nrhs, doublecomplex *a, doublecomplex *b, integer *ldb, integer *info);

/* Subroutine */ int zpocon_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublereal *anorm, doublereal *rcond, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zpoequ_(integer *n, doublecomplex *a, integer *lda, 
	doublereal *s, doublereal *scond, doublereal *amax, integer *info);

/* Subroutine */ int zpoequb_(integer *n, doublecomplex *a, integer *lda, 
	doublereal *s, doublereal *scond, doublereal *amax, integer *info);

/* Subroutine */ int zporfs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, 
	doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *
	rwork, integer *info);

/* Subroutine */ int zporfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, doublereal *s, doublecomplex *b, integer *ldb, doublecomplex *x, 
	 integer *ldx, doublereal *rcond, doublereal *berr, integer *
	n_err_bnds__, doublereal *err_bnds_norm__, doublereal *
	err_bnds_comp__, integer *nparams, doublereal *params, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zposv_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zposvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, char *equed, doublereal *s, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *ferr, 
	doublereal *berr, doublecomplex *work, doublereal *rwork, integer *
	info);

/* Subroutine */ int zposvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, char *equed, doublereal *s, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *rpvgrw, 
	 doublereal *berr, integer *n_err_bnds__, doublereal *err_bnds_norm__, 
	 doublereal *err_bnds_comp__, integer *nparams, doublereal *params, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zpotf2_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *info);

/* Subroutine */ int zpotrf_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *info);

/* Subroutine */ int zpotri_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *info);

/* Subroutine */ int zpotrs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zppcon_(char *uplo, integer *n, doublecomplex *ap, 
	doublereal *anorm, doublereal *rcond, doublecomplex *work, doublereal 
	*rwork, integer *info);

/* Subroutine */ int zppequ_(char *uplo, integer *n, doublecomplex *ap, 
	doublereal *s, doublereal *scond, doublereal *amax, integer *info);

/* Subroutine */ int zpprfs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, doublecomplex *afp, doublecomplex *b, integer *ldb, 
	 doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int zppsv_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, doublecomplex *b, integer *ldb, integer *info);

/* Subroutine */ int zppsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublecomplex *ap, doublecomplex *afp, char *equed, doublereal *
	s, doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zpptrf_(char *uplo, integer *n, doublecomplex *ap, 
	integer *info);

/* Subroutine */ int zpptri_(char *uplo, integer *n, doublecomplex *ap, 
	integer *info);

/* Subroutine */ int zpptrs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, doublecomplex *b, integer *ldb, integer *info);

/* Subroutine */ int zpstf2_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *piv, integer *rank, doublereal *tol, 
	doublereal *work, integer *info);

/* Subroutine */ int zpstrf_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *piv, integer *rank, doublereal *tol, 
	doublereal *work, integer *info);

/* Subroutine */ int zptcon_(integer *n, doublereal *d__, doublecomplex *e, 
	doublereal *anorm, doublereal *rcond, doublereal *rwork, integer *
	info);

/* Subroutine */ int zpteqr_(char *compz, integer *n, doublereal *d__, 
	doublereal *e, doublecomplex *z__, integer *ldz, doublereal *work, 
	integer *info);

/* Subroutine */ int zptrfs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *d__, doublecomplex *e, doublereal *df, doublecomplex *ef, 
	doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *
	rwork, integer *info);

/* Subroutine */ int zptsv_(integer *n, integer *nrhs, doublereal *d__, 
	doublecomplex *e, doublecomplex *b, integer *ldb, integer *info);

/* Subroutine */ int zptsvx_(char *fact, integer *n, integer *nrhs, 
	doublereal *d__, doublecomplex *e, doublereal *df, doublecomplex *ef, 
	doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zpttrf_(integer *n, doublereal *d__, doublecomplex *e, 
	integer *info);

/* Subroutine */ int zpttrs_(char *uplo, integer *n, integer *nrhs, 
	doublereal *d__, doublecomplex *e, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zptts2_(integer *iuplo, integer *n, integer *nrhs, 
	doublereal *d__, doublecomplex *e, doublecomplex *b, integer *ldb);

/* Subroutine */ int zrot_(integer *n, doublecomplex *cx, integer *incx, 
	doublecomplex *cy, integer *incy, doublereal *c__, doublecomplex *s);

/* Subroutine */ int zspcon_(char *uplo, integer *n, doublecomplex *ap, 
	integer *ipiv, doublereal *anorm, doublereal *rcond, doublecomplex *
	work, integer *info);

/* Subroutine */ int zspmv_(char *uplo, integer *n, doublecomplex *alpha, 
	doublecomplex *ap, doublecomplex *x, integer *incx, doublecomplex *
	beta, doublecomplex *y, integer *incy);

/* Subroutine */ int zspr_(char *uplo, integer *n, doublecomplex *alpha, 
	doublecomplex *x, integer *incx, doublecomplex *ap);

/* Subroutine */ int zsprfs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, doublecomplex *afp, integer *ipiv, doublecomplex *
	b, integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, 
	doublereal *berr, doublecomplex *work, doublereal *rwork, integer *
	info);

/* Subroutine */ int zspsv_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, integer *ipiv, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zspsvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublecomplex *ap, doublecomplex *afp, integer *ipiv, 
	doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	doublereal *rcond, doublereal *ferr, doublereal *berr, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zsptrf_(char *uplo, integer *n, doublecomplex *ap, 
	integer *ipiv, integer *info);

/* Subroutine */ int zsptri_(char *uplo, integer *n, doublecomplex *ap, 
	integer *ipiv, doublecomplex *work, integer *info);

/* Subroutine */ int zsptrs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *ap, integer *ipiv, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int zstedc_(char *compz, integer *n, doublereal *d__, 
	doublereal *e, doublecomplex *z__, integer *ldz, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *lrwork, integer *iwork, 
	integer *liwork, integer *info);

/* Subroutine */ int zstegr_(char *jobz, char *range, integer *n, doublereal *
	d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, 
	integer *iu, doublereal *abstol, integer *m, doublereal *w, 
	doublecomplex *z__, integer *ldz, integer *isuppz, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int zstein_(integer *n, doublereal *d__, doublereal *e, 
	integer *m, doublereal *w, integer *iblock, integer *isplit, 
	doublecomplex *z__, integer *ldz, doublereal *work, integer *iwork, 
	integer *ifail, integer *info);

/* Subroutine */ int zstemr_(char *jobz, char *range, integer *n, doublereal *
	d__, doublereal *e, doublereal *vl, doublereal *vu, integer *il, 
	integer *iu, integer *m, doublereal *w, doublecomplex *z__, integer *
	ldz, integer *nzc, integer *isuppz, logical *tryrac, doublereal *work, 
	 integer *lwork, integer *iwork, integer *liwork, integer *info);

/* Subroutine */ int zsteqr_(char *compz, integer *n, doublereal *d__, 
	doublereal *e, doublecomplex *z__, integer *ldz, doublereal *work, 
	integer *info);

/* Subroutine */ int zsycon_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, doublereal *anorm, doublereal *rcond, 
	doublecomplex *work, integer *info);

/* Subroutine */ int zsyequb_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublereal *s, doublereal *scond, doublereal *amax, 
	doublecomplex *work, integer *info);

/* Subroutine */ int zsymv_(char *uplo, integer *n, doublecomplex *alpha, 
	doublecomplex *a, integer *lda, doublecomplex *x, integer *incx, 
	doublecomplex *beta, doublecomplex *y, integer *incy);

/* Subroutine */ int zsyr_(char *uplo, integer *n, doublecomplex *alpha, 
	doublecomplex *x, integer *incx, doublecomplex *a, integer *lda);

/* Subroutine */ int zsyrfs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, doublecomplex *af, integer *ldaf, 
	integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, 
	integer *ldx, doublereal *ferr, doublereal *berr, doublecomplex *work, 
	 doublereal *rwork, integer *info);

/* Subroutine */ int zsyrfsx_(char *uplo, char *equed, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, integer *ipiv, doublereal *s, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *rcond, doublereal *berr, 
	integer *n_err_bnds__, doublereal *err_bnds_norm__, doublereal *
	err_bnds_comp__, integer *nparams, doublereal *params, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int zsysv_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, 
	integer *ldb, doublecomplex *work, integer *lwork, integer *info);

/* Subroutine */ int zsysvx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, integer *ipiv, doublecomplex *b, integer *ldb, doublecomplex *x, 
	 integer *ldx, doublereal *rcond, doublereal *ferr, doublereal *berr, 
	doublecomplex *work, integer *lwork, doublereal *rwork, integer *info);

/* Subroutine */ int zsysvxx_(char *fact, char *uplo, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *af, integer *
	ldaf, integer *ipiv, char *equed, doublereal *s, doublecomplex *b, 
	integer *ldb, doublecomplex *x, integer *ldx, doublereal *rcond, 
	doublereal *rpvgrw, doublereal *berr, integer *n_err_bnds__, 
	doublereal *err_bnds_norm__, doublereal *err_bnds_comp__, integer *
	nparams, doublereal *params, doublecomplex *work, doublereal *rwork, 
	integer *info);

/* Subroutine */ int zsytf2_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, integer *info);

/* Subroutine */ int zsytrf_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, doublecomplex *work, integer *lwork, 
	integer *info);

/* Subroutine */ int zsytri_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, doublecomplex *work, integer *info);

/* Subroutine */ int zsytrs_(char *uplo, integer *n, integer *nrhs, 
	doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, 
	integer *ldb, integer *info);

/* Subroutine */ int ztbcon_(char *norm, char *uplo, char *diag, integer *n, 
	integer *kd, doublecomplex *ab, integer *ldab, doublereal *rcond, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int ztbrfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *kd, integer *nrhs, doublecomplex *ab, integer *ldab, 
	doublecomplex *b, integer *ldb, doublecomplex *x, integer *ldx, 
	doublereal *ferr, doublereal *berr, doublecomplex *work, doublereal *
	rwork, integer *info);

/* Subroutine */ int ztbtrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *kd, integer *nrhs, doublecomplex *ab, integer *ldab, 
	doublecomplex *b, integer *ldb, integer *info);

/* Subroutine */ int ztfsm_(char *transr, char *side, char *uplo, char *trans, 
	 char *diag, integer *m, integer *n, doublecomplex *alpha, 
	doublecomplex *a, doublecomplex *b, integer *ldb);

/* Subroutine */ int ztftri_(char *transr, char *uplo, char *diag, integer *n, 
	 doublecomplex *a, integer *info);

/* Subroutine */ int ztfttp_(char *transr, char *uplo, integer *n, 
	doublecomplex *arf, doublecomplex *ap, integer *info);

/* Subroutine */ int ztfttr_(char *transr, char *uplo, integer *n, 
	doublecomplex *arf, doublecomplex *a, integer *lda, integer *info);

/* Subroutine */ int ztgevc_(char *side, char *howmny, logical *select, 
	integer *n, doublecomplex *s, integer *lds, doublecomplex *p, integer 
	*ldp, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *
	ldvr, integer *mm, integer *m, doublecomplex *work, doublereal *rwork, 
	 integer *info);

/* Subroutine */ int ztgex2_(logical *wantq, logical *wantz, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *q, integer *ldq, doublecomplex *z__, integer *ldz, 
	integer *j1, integer *info);

/* Subroutine */ int ztgexc_(logical *wantq, logical *wantz, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *q, integer *ldq, doublecomplex *z__, integer *ldz, 
	integer *ifst, integer *ilst, integer *info);

/* Subroutine */ int ztgsen_(integer *ijob, logical *wantq, logical *wantz, 
	logical *select, integer *n, doublecomplex *a, integer *lda, 
	doublecomplex *b, integer *ldb, doublecomplex *alpha, doublecomplex *
	beta, doublecomplex *q, integer *ldq, doublecomplex *z__, integer *
	ldz, integer *m, doublereal *pl, doublereal *pr, doublereal *dif, 
	doublecomplex *work, integer *lwork, integer *iwork, integer *liwork, 
	integer *info);

/* Subroutine */ int ztgsja_(char *jobu, char *jobv, char *jobq, integer *m, 
	integer *p, integer *n, integer *k, integer *l, doublecomplex *a, 
	integer *lda, doublecomplex *b, integer *ldb, doublereal *tola, 
	doublereal *tolb, doublereal *alpha, doublereal *beta, doublecomplex *
	u, integer *ldu, doublecomplex *v, integer *ldv, doublecomplex *q, 
	integer *ldq, doublecomplex *work, integer *ncycle, integer *info);

/* Subroutine */ int ztgsna_(char *job, char *howmny, logical *select, 
	integer *n, doublecomplex *a, integer *lda, doublecomplex *b, integer 
	*ldb, doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *
	ldvr, doublereal *s, doublereal *dif, integer *mm, integer *m, 
	doublecomplex *work, integer *lwork, integer *iwork, integer *info);

/* Subroutine */ int ztgsy2_(char *trans, integer *ijob, integer *m, integer *
	n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *c__, integer *ldc, doublecomplex *d__, integer *ldd, 
	doublecomplex *e, integer *lde, doublecomplex *f, integer *ldf, 
	doublereal *scale, doublereal *rdsum, doublereal *rdscal, integer *
	info);

/* Subroutine */ int ztgsyl_(char *trans, integer *ijob, integer *m, integer *
	n, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *c__, integer *ldc, doublecomplex *d__, integer *ldd, 
	doublecomplex *e, integer *lde, doublecomplex *f, integer *ldf, 
	doublereal *scale, doublereal *dif, doublecomplex *work, integer *
	lwork, integer *iwork, integer *info);

/* Subroutine */ int ztpcon_(char *norm, char *uplo, char *diag, integer *n, 
	doublecomplex *ap, doublereal *rcond, doublecomplex *work, doublereal 
	*rwork, integer *info);

/* Subroutine */ int ztprfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, doublecomplex *ap, doublecomplex *b, integer *ldb, 
	doublecomplex *x, integer *ldx, doublereal *ferr, doublereal *berr, 
	doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int ztptri_(char *uplo, char *diag, integer *n, 
	doublecomplex *ap, integer *info);

/* Subroutine */ int ztptrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, doublecomplex *ap, doublecomplex *b, integer *ldb, 
	integer *info);

/* Subroutine */ int ztpttf_(char *transr, char *uplo, integer *n, 
	doublecomplex *ap, doublecomplex *arf, integer *info);

/* Subroutine */ int ztpttr_(char *uplo, integer *n, doublecomplex *ap, 
	doublecomplex *a, integer *lda, integer *info);

/* Subroutine */ int ztrcon_(char *norm, char *uplo, char *diag, integer *n, 
	doublecomplex *a, integer *lda, doublereal *rcond, doublecomplex *
	work, doublereal *rwork, integer *info);

/* Subroutine */ int ztrevc_(char *side, char *howmny, logical *select, 
	integer *n, doublecomplex *t, integer *ldt, doublecomplex *vl, 
	integer *ldvl, doublecomplex *vr, integer *ldvr, integer *mm, integer 
	*m, doublecomplex *work, doublereal *rwork, integer *info);

/* Subroutine */ int ztrexc_(char *compq, integer *n, doublecomplex *t, 
	integer *ldt, doublecomplex *q, integer *ldq, integer *ifst, integer *
	ilst, integer *info);

/* Subroutine */ int ztrrfs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, 
	integer *ldb, doublecomplex *x, integer *ldx, doublereal *ferr, 
	doublereal *berr, doublecomplex *work, doublereal *rwork, integer *
	info);

/* Subroutine */ int ztrsen_(char *job, char *compq, logical *select, integer 
	*n, doublecomplex *t, integer *ldt, doublecomplex *q, integer *ldq, 
	doublecomplex *w, integer *m, doublereal *s, doublereal *sep, 
	doublecomplex *work, integer *lwork, integer *info);

/* Subroutine */ int ztrsna_(char *job, char *howmny, logical *select, 
	integer *n, doublecomplex *t, integer *ldt, doublecomplex *vl, 
	integer *ldvl, doublecomplex *vr, integer *ldvr, doublereal *s, 
	doublereal *sep, integer *mm, integer *m, doublecomplex *work, 
	integer *ldwork, doublereal *rwork, integer *info);

/* Subroutine */ int ztrsyl_(char *trana, char *tranb, integer *isgn, integer 
	*m, integer *n, doublecomplex *a, integer *lda, doublecomplex *b, 
	integer *ldb, doublecomplex *c__, integer *ldc, doublereal *scale, 
	integer *info);

/* Subroutine */ int ztrti2_(char *uplo, char *diag, integer *n, 
	doublecomplex *a, integer *lda, integer *info);

/* Subroutine */ int ztrtri_(char *uplo, char *diag, integer *n, 
	doublecomplex *a, integer *lda, integer *info);

/* Subroutine */ int ztrtrs_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, doublecomplex *a, integer *lda, doublecomplex *b, 
	integer *ldb, integer *info);

/* Subroutine */ int ztrttf_(char *transr, char *uplo, integer *n, 
	doublecomplex *a, integer *lda, doublecomplex *arf, integer *info);

/* Subroutine */ int ztrttp_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *ap, integer *info);

/* Subroutine */ int ztzrqf_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, integer *info);

/* Subroutine */ int ztzrzf_(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zung2l_(integer *m, integer *n, integer *k, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *info);

/* Subroutine */ int zung2r_(integer *m, integer *n, integer *k, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *info);

/* Subroutine */ int zungbr_(char *vect, integer *m, integer *n, integer *k, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int zunghr_(integer *n, integer *ilo, integer *ihi, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int zungl2_(integer *m, integer *n, integer *k, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *info);

/* Subroutine */ int zunglq_(integer *m, integer *n, integer *k, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int zungql_(integer *m, integer *n, integer *k, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int zungqr_(integer *m, integer *n, integer *k, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int zungr2_(integer *m, integer *n, integer *k, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *info);

/* Subroutine */ int zungrq_(integer *m, integer *n, integer *k, 
	doublecomplex *a, integer *lda, doublecomplex *tau, doublecomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int zungtr_(char *uplo, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zunm2l_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, 
	doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info);

/* Subroutine */ int zunm2r_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, 
	doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info);

/* Subroutine */ int zunmbr_(char *vect, char *side, char *trans, integer *m, 
	integer *n, integer *k, doublecomplex *a, integer *lda, doublecomplex 
	*tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *
	lwork, integer *info);

/* Subroutine */ int zunmhr_(char *side, char *trans, integer *m, integer *n, 
	integer *ilo, integer *ihi, doublecomplex *a, integer *lda, 
	doublecomplex *tau, doublecomplex *c__, integer *ldc, doublecomplex *
	work, integer *lwork, integer *info);

/* Subroutine */ int zunml2_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, 
	doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info);

/* Subroutine */ int zunmlq_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, 
	doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zunmql_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, 
	doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zunmqr_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, 
	doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zunmr2_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, 
	doublecomplex *c__, integer *ldc, doublecomplex *work, integer *info);

/* Subroutine */ int zunmr3_(char *side, char *trans, integer *m, integer *n, 
	integer *k, integer *l, doublecomplex *a, integer *lda, doublecomplex 
	*tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *
	info);

/* Subroutine */ int zunmrq_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublecomplex *a, integer *lda, doublecomplex *tau, 
	doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zunmrz_(char *side, char *trans, integer *m, integer *n, 
	integer *k, integer *l, doublecomplex *a, integer *lda, doublecomplex 
	*tau, doublecomplex *c__, integer *ldc, doublecomplex *work, integer *
	lwork, integer *info);

/* Subroutine */ int zunmtr_(char *side, char *uplo, char *trans, integer *m, 
	integer *n, doublecomplex *a, integer *lda, doublecomplex *tau, 
	doublecomplex *c__, integer *ldc, doublecomplex *work, integer *lwork, 
	 integer *info);

/* Subroutine */ int zupgtr_(char *uplo, integer *n, doublecomplex *ap, 
	doublecomplex *tau, doublecomplex *q, integer *ldq, doublecomplex *
	work, integer *info);

/* Subroutine */ int zupmtr_(char *side, char *uplo, char *trans, integer *m, 
	integer *n, doublecomplex *ap, doublecomplex *tau, doublecomplex *c__, 
	 integer *ldc, doublecomplex *work, integer *info);

/* Subroutine */ int dlamc1_(integer *beta, integer *t, logical *rnd, logical 
	*ieee1);

doublereal dsecnd_();

/* Subroutine */ int ilaver_(integer *vers_major__, integer *vers_minor__, 
	integer *vers_patch__);

logical lsame_(char *ca, char *cb);

doublereal second_();

doublereal slamch_(char *cmach);

/* Subroutine */ int slamc1_(integer *beta, integer *t, logical *rnd, logical 
	*ieee1);

/* Subroutine */ int slamc2_(integer *beta, integer *t, logical *rnd, floatreal *
		    eps, integer *emin, floatreal *rmin, integer *emax, floatreal *rmax);

doublereal slamc3_(floatreal *a, floatreal *b);

/* Subroutine */ int slamc4_(integer *emin, floatreal *start, integer *base);

/* Subroutine */ int slamc5_(integer *beta, integer *p, integer *emin,
		    logical *ieee, integer *emax, floatreal *rmax);


doublereal dlamch_(char *cmach);

/* Subroutine */ int dlamc1_(integer *beta, integer *t, logical *rnd, logical
		    *ieee1);

/* Subroutine */ int dlamc2_(integer *beta, integer *t, logical *rnd,
		    doublereal *eps, integer *emin, doublereal *rmin, integer *emax,
			    doublereal *rmax);

doublereal dlamc3_(doublereal *a, doublereal *b);

/* Subroutine */ int dlamc4_(integer *emin, doublereal *start, integer *base);

/* Subroutine */ int dlamc5_(integer *beta, integer *p, integer *emin,
		    logical *ieee, integer *emax, doublereal *rmax);

integer ilaenv_(integer *ispec, char *name__, char *opts, integer *n1, 
	integer *n2, integer *n3, integer *n4);

}

#endif /* __CLAPACK_H */
