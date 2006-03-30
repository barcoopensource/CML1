/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief A set of very simple examples of current CML functionality.
 */

#include "cml_config.h"         // Must be first (for now)!

#include <iostream>
#include <cmath>
#include <cml/cml.h>
using namespace cml;

using std::cout;
using std::endl;
using std::sqrt;

/* Note: this has to have the same template params as cml::vector<>: */
template<typename E, class AT> std::ostream&
operator<<(std::ostream& os, const cml::vector<E,AT>& v)
{
    os << "[";
    for(size_t i = 0; i < v.size(); ++i) {
        os << " " << v[i];
    }
    os << " ]";
    return os;
}

/* Note: this has to have the same template params as cml::matrix<>: */
template<typename E, class AT, class L> std::ostream&
operator<<(std::ostream& os, const cml::matrix<E,AT,L>& m)
{
    os << "[" << endl;
    for(size_t i = 0; i < m.rows(); ++i) {
        os << "[";
        for(size_t j = 0; j < m.cols(); ++j) {
            os << " " << m(i,j);
        }
        os << "]" << endl;
    }
    os << "]";
    return os;
}

#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
template<typename VecT> std::ostream&
operator<<(std::ostream& os, const cml::quaternion<VecT>& q)
{
    os << ((q[0] < 0)?" - ":"") << std::fabs(q[0]);
    os << ((q[1] < 0)?" - ":" + ") << std::fabs(q[1]) << "i";
    os << ((q[2] < 0)?" - ":" + ") << std::fabs(q[2]) << "j";
    os << ((q[3] < 0)?" - ":" + ") << std::fabs(q[3]) << "k";
    return os;
}
#else
template<typename VecT> std::ostream&
operator<<(std::ostream& os, const cml::quaternion<VecT>& q)
{
    os << ((q[0] < 0)?" - ":"") << std::fabs(q[0]) << "i";
    os << ((q[1] < 0)?" - ":" + ") << std::fabs(q[1]) << "j";
    os << ((q[2] < 0)?" - ":" + ") << std::fabs(q[2]) << "k";
    os << ((q[3] < 0)?" - ":" + ") << std::fabs(q[3]);
    return os;
}
#endif

void example1()
{
    cout << std::endl << "Example1:" << endl;

    /* 3-space column vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    vector_d3 u, v;
    u[0] = 0.; u[1] = 0.; u[2] = 1.;
    v[0] = 1.; v[1] = 0.; v[2] = 0.;

    cout << "  u = " << u << endl;
    cout << "  v = " << v << endl;
    cout << "  dot(u,v) = " << dot(u,v) << endl;
    cout << "  dot(u,u) = " << dot(u,u) << endl;
    cout << "  dot(u+v,v) = " << dot(u+v,v) << endl;
    cout << "  cos(u,v) = " << dot(u,v)/sqrt(dot(u,u)*dot(v,v))
        << endl;
}

void example2()
{
    cout << std::endl << "Example2:" << endl;

    /* 3-space column vector, dynamic length, double coordinates: */
    typedef cml::vector< double, dynamic<> > vector_d;

    vector_d u(3), v(3);
    u[0] = 0.; u[1] = 0.; u[2] = 1.;
    v[0] = 1.; v[1] = 0.; v[2] = 0.;

    cout << "  dot(u,v) = " << dot(u,v) << endl;
    cout << "  dot(u,u) = " << dot(u,u) << endl;
    cout << "  dot(u+v,v) = " << dot(u+v,v) << endl;
    cout << "  cos(u,v) = " << dot(u,v)/sqrt(dot(u,u)*dot(v,v))
        << endl;
}

void example3()
{
    cout << std::endl << "Example3:" << endl;

    /* 3-space matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    matrix_d3 A, B, C;

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = T(A)+B;
    cout << "  C(0,0) = " << C(0,0) << endl;
    cout << "  C(2,0) = " << C(2,0) << endl;
}

void example4()
{
    cout << std::endl << "Example4:" << endl;

    /* 3-space matrix, fixed size, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    /* 3-space matrix, dynamic size, double coordinates: */
    typedef cml::matrix< double, dynamic<> > matrix_d;

    matrix_d3 A, C;
    matrix_d B(3,3);

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 0.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = A+B;
    cout << "  C(0,0) = " << C(0,0) << endl;
}

void example5()
{
    cout << std::endl << "Example4:" << endl;

    /* 3-space matrix, fixed size, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    /* 3-space matrix, dynamic size, double coordinates: */
    typedef cml::matrix< double, dynamic<> > matrix_d;

    matrix_d3 A, B;
    matrix_d C(3,3);

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 0.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = A+B;
    cout << "  C(0,0) = " << C(0,0) << endl;
    cout << C << endl;

    C = A+T(B);
    cout << C << endl;
}

void example6()
{
    cout << std::endl << "Example6:" << endl;

    /* 3-space matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    /* Column vector of the matrix: */
    typedef matrix_d3::col_vector_type cvector_d3;

    matrix_d3 A, B, C;

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = T(A)+B;
    cout << "  T(A)+B = " << C << endl;

    cvector_d3 v = col(C,0);
    cout << "  C(0) = " << endl << v << endl;
    v = col(C,1);
    cout << "  C(1) = " << endl << v << endl;
    v = col(C,2);
    cout << "  C(2) = " << endl << v << endl;

    v = col(T(A)+B,2);
    cout << "  (T(A)+B)(2) = " << endl << v << endl;
}

void example7()
{
    cout << std::endl << "Example7:" << endl;

    /* 3-space matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<3,3> > matrix_d3;

    matrix_d3 A, B, C;

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;

    B(0,0) = 1.0; B(0,1) = 0.0; B(0,2) = 1.0;
    B(1,0) = 0.0; B(1,1) = 1.0; B(1,2) = 0.0;
    B(2,0) = 0.0; B(2,1) = 0.0; B(2,2) = 1.0;

    C = A*B;
    cout << "  A = " << A << endl;
    cout << "  B = " << B << endl;
    cout << "  A*B = " << C << endl;
}

void example8()
{
    cout << std::endl << "Example8:" << endl;

    /* 3-space column vector, fixed length, double coordinates: */
    typedef cml::vector< double, external<3> > vector_d3;

    double c_u[3] = {0.,0.,1.};
    double c_v[3] = {1.,0.,0.};
    vector_d3 u(c_u), v(c_v);

    cout << "  u = " << u << endl;
    cout << "  v = " << v << endl;
    cout << "  dot(u,v) = " << dot(u,v) << endl;
    cout << "  dot(u,u) = " << dot(u,u) << endl;
    cout << "  dot(v,v) = " << dot(v,v) << endl;
    cout << "  dot(u+v,v) = " << dot(u+v,v) << endl;
    cout << "  cos(u,v) = " << dot(u,v)/sqrt(dot(u,u)*dot(v,v))
        << endl;
}

#if defined(CML_ENABLE_DOT_OPERATOR)
void example9()
{
    cout << std::endl << "Example9:" << endl;

    /* 3-space column vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    vector_d3 u, v;
    u[0] = 0.; u[1] = 0.; u[2] = 1.;
    v[0] = 1.; v[1] = 0.; v[2] = 0.;

    cout << "  u = " << u << endl;
    cout << "  v = " << v << endl;

    cout << "  dot(u,v) = " << u*v << endl;
    cout << "  dot(u,u) = " << u*u << endl;
    cout << "  dot(u+v,v) = " << (u+v)*v << endl;
    cout << "  cos(u,v) = " << (u*v)/sqrt((u*u)*(v*v)) << endl;
}
#endif

void example10()
{
    cout << std::endl << "Example10:" << endl;

    /* 4x3 matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<4,3>, cml::col_major > matrix_d43;

    /* 3-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    /* 4-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<4> > vector_d4;

    matrix_d43 A;

    A(0,0) = 1.0; A(0,1) = 1.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 1.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;
    A(3,0) = 0.0; A(3,1) = 0.0; A(3,2) = 1.0;

    vector_d3 x;

    x[0] = 1.; x[1] = 0.; x[2] = 1.;

    cout << "A = " << A << endl;
    cout << "x = " << x << endl;

    vector_d4 y = A*x;
    cout << "y = A*x = " << y << endl;

    vector_d3 yp = y*A;
    cout << "yp = mul(y,A) = " << yp << endl;

    vector_d4 ypp = A*yp;
    cout << "ypp = mul(A,yp) = " << ypp << endl;

    matrix_d43::transposed_type B = T(A);
    cout << "T(A) = " << B << endl;

    vector_d4 z = yp*B;
    cout << "z = yp*T(A) = " << z << endl;
}

void example11()
{
    cout << std::endl << "Example11:" << endl;

    /* 4x3 matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<4,3>, cml::col_major > matrix_d43;

    /* 3-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    /* 4-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<4> > vector_d4;

    matrix_d43 A;

    A(0,0) = 1.0; A(0,1) = 1.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 1.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;
    A(3,0) = 0.0; A(3,1) = 0.0; A(3,2) = 1.0;

    vector_d3 x;
    x[0] = 1.; x[1] = 0.; x[2] = 1.;

    cout << "A = " << A << endl;
    cout << "x = " << x << endl;

    vector_d4 y = A*x;
    cout << "y = A*x = " << y << endl;

    matrix_d43 B = outer(y,x);
    cout << "B = outer(y,x) = " << B << endl;
}

void example12()
{
    /* 4x3 matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<4,3>, cml::col_major > matrix_d43;

    /* 3-space matrix, fixed length, float coordinates: */
    typedef cml::matrix< float, fixed<3,3>, cml::col_major > matrix_f33;

    /* 3-space vector, fixed length, double coordinates: */
    typedef cml::vector< double, fixed<3> > vector_d3;

    /* 4-space vector, fixed length, double coordinates: */
    typedef cml::vector< float, fixed<4> > vector_d4;

    cout << std::endl << "Example12:" << endl;

    matrix_d43 A;

    A(0,0) = 1.0; A(0,1) = 1.0; A(0,2) = 1.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 1.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;
    A(3,0) = 0.0; A(3,1) = 0.0; A(3,2) = 1.0;

    matrix_f33 B = T(A)*A;

    cout << "A = " << A << endl;
    cout << "B[f33] = T(A)*A = " << B << endl;
}

void example13()
{
    cout << std::endl << "Example13:" << endl;

    /* 4x4 matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<4,4>, cml::col_major > matrix_d44;

    matrix_d44 M,A;
    M(0,0) = 1.0; M(0,1) = 1.0; M(0,2) = 1.0; M(0,3) = 1.0;
    M(1,0) = 0.0; M(1,1) = 1.0; M(1,2) = 1.0; M(1,3) = 1.0;
    M(2,0) = 0.0; M(2,1) = 0.0; M(2,2) = 1.0; M(2,3) = 1.0;
    M(3,0) = 0.0; M(3,1) = 0.0; M(3,2) = 0.0; M(3,3) = 1.0;

    cout << "M = " << M << endl;
    cout << "M = LU = " << cml::lu(M) << endl;
    cout << "det(M) = " << determinant(M) << endl;

    A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 0.0; A(0,3) = 0.0;
    A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0; A(1,3) = 0.0;
    A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0; A(2,3) = 0.0;
    A(3,0) = 0.0; A(3,1) = 0.0; A(3,2) = 0.0; A(3,3) = 1.0;

    matrix_d44 D = M+A;
    cout << "M+A = " << D << endl;
    cout << "M+A = LU = " << cml::lu(M+A) << endl;
    cout << "det(M+A) = " << determinant(M+A) << endl;
}

void example14()
{
    cout << std::endl << "Example14:" << endl;

    /* 4x4 matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, dynamic<>, cml::col_major > matrix_d44;
    typedef matrix_d44::col_vector_type vector_d4;

    matrix_d44 M(4,4);

    M(0,0) = 1.0;  M(0,1) = 8.0;  M(0,2) = 3.0; M(0,3) = 11.0;
    M(1,0) = 9.0;  M(1,1) = 5.0;  M(1,2) = 2.0; M(1,3) = 17.0;
    M(2,0) = 12.0; M(2,1) = 12.0; M(2,2) = 7.0; M(2,3) = 2.0;
    M(3,0) = 15.0; M(3,1) = 17.0; M(3,2) = 9.0; M(3,3) = 16.0;

    matrix_d44 LU(4,4); LU = cml::lu(M);
    cout << "M = " << M << endl;
    cout << "LU(M) = " << LU << endl;

    vector_d4 y(4), x(4);
    y[0] = 1.; y[1] = 7.; y[2] = 13.; y[3] = 6.;
    cout << "y = " << y << endl;

    x = cml::lu_solve(LU,y);
    cout << "x = lu_solve(M,y) = " << x << endl;

    y = M*x;
    cout << "y = M*x = " << y << endl;
}

void example15()
{
    cout << std::endl << "Example15:" << endl;

    /* 4x4 matrix, fixed length, double coordinates: */
    typedef cml::matrix< double, fixed<4,4>, cml::col_major > matrix_d44;
    typedef matrix_d44::col_vector_type vector_d4;

    matrix_d44 M;
    M(0,0) = 1.0;  M(0,1) = 8.0;  M(0,2) = 3.0; M(0,3) = 11.0;
    M(1,0) = 9.0;  M(1,1) = 5.0;  M(1,2) = 2.0; M(1,3) = 17.0;
    M(2,0) = 12.0; M(2,1) = 12.0; M(2,2) = 7.0; M(2,3) = 2.0;
    M(3,0) = 15.0; M(3,1) = 17.0; M(3,2) = 9.0; M(3,3) = 16.0;

    matrix_d44 LU = cml::lu(M);
    cout << "M = " << M << endl;
    cout << "M = LU = " << LU << endl;

    vector_d4 x, y;
    y[0] = 1.; y[1] = 7.; y[2] = 13.; y[3] = 6.;
    cout << "y = " << y << endl;

    matrix_d44 Minv = inverse(M);
    cout << "Minv = " << Minv << endl;

    x = Minv*y;
    y = M*x;
    cout << "x = Minv*y = " << x << endl;
    cout << "y = M*x = " << y << endl;

    double D = determinant(M);
    cout << "det(M) = " << D << endl;
    cout << "det(M)[lu] = "
        << cml::detail::determinant_f<matrix_d44,0>()(M) << endl;
}

void example16()
{
    cout << std::endl << "Example16:" << endl;

    /* 4x4 matrix, dynamic length, double coordinates: */
    typedef cml::matrix< double, dynamic<>, cml::col_major > matrix_d44;
    typedef matrix_d44::col_vector_type vector_d4;

    matrix_d44 M(4,4);
    M(0,0) = 1.0;  M(0,1) = 8.0;  M(0,2) = 3.0; M(0,3) = 11.0;
    M(1,0) = 9.0;  M(1,1) = 5.0;  M(1,2) = 2.0; M(1,3) = 17.0;
    M(2,0) = 12.0; M(2,1) = 12.0; M(2,2) = 7.0; M(2,3) = 2.0;
    M(3,0) = 15.0; M(3,1) = 17.0; M(3,2) = 9.0; M(3,3) = 16.0;

    matrix_d44 Minv(4,4); Minv = inverse(M);
    cout << "M^-1 = " << Minv << endl;
    cout << "M^-1[lu] = "
        << cml::detail::inverse_f<matrix_d44,0>()(M) << endl;

    vector_d4 x(4), y(4);
    y[0] = 1.; y[1] = 7.; y[2] = 13.; y[3] = 6.;
    cout << "y = " << y << endl;

    x = Minv*y;
    y = M*x;
    cout << "x = Minv*y = " << x << endl;
    cout << "y = M*x = " << y << endl;
}

void example17()
{
    cout << std::endl << "Example17:" << endl;

    /* 4x4 matrix, dynamic length, double coordinates: */
    typedef cml::matrix< double, fixed<4,4>, cml::col_major > matrix_d44;
    typedef cml::vector< double, fixed<4> > vector_d4;

    /* XXX This currently doesn't work for dynamic-size matrices: */
    double _M[4][4] = {
        { 1.0,  8.0,  3.0, 11.0 },
        { 9.0,  5.0,  2.0, 17.0 },
        { 12.0, 12.0, 7.0, 2.0  },
        { 15.0, 17.0, 9.0, 16.0 }
    };
    matrix_d44 M(_M);

    matrix_d44 Minv = inverse(M);
    cout << "M^-1 = " << Minv << endl;
    cout << "M^-1[lu] = "
        << cml::detail::inverse_f<matrix_d44,0>()(M) << endl;

    double _y[] = {1.,7.,13.,6.};
    vector_d4 x, y(_y);
    cout << "y = " << y << endl;

    x = Minv*y;
    y = M*x;
    cout << "x = Minv*y = " << x << endl;
    cout << "y = M*x = " << y << endl;
}

void example18()
{
    cout << std::endl << "Example18:" << endl;

    typedef vector< double, fixed<3> > vector_type;
    typedef quaternion<vector_type> quaternion_type;

#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
    quaternion_type p(1.,1.,0.,0.), q(1.,0.,1.,0.), r, s;
#else
    quaternion_type p(1.,0.,0.,1.), q(0.,1.,0.,1.), r, s;
#endif
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    
    r = ~p;
    cout << "r = ~p = " << r << endl;

    r = ~q;
    cout << "r = ~q = " << r << endl;

    r = p + q;
    cout << "r = p+q = " << r << endl;

    r = p + ~q;
    cout << "r = p+~q = " << r << endl;

    /* Note: parens are required here! */
    r = p + ~(2.*q);
    cout << "r = p+~(2*q) = " << r << endl;

    r = p + ~q*2.;
    cout << "r = p+~q*2 = " << r << endl;

    r = p*q;
    cout << "r = p*q = " << r << endl;

    r = p*p;
    cout << "r = p*p = " << r << endl;

    r = p*conj(p);
    cout << "r = p*~p = " << r << endl;

    r = (~p)/real(p*~p);
    cout << "r = ~p/real(p*~p) = " << r << endl;

    s = r*p;
    cout << "s = r*p = " << s << endl;

    r = ~p/norm(p);
    cout << "r = ~p/norm(p) = " << r << endl;

    s = r*p;
    cout << "s = r*p = " << s << endl;

    r = inverse(p);
    cout << "r = inverse(p) = " << r << endl;

    s = r*p;
    cout << "s = r*p = " << s << endl;
}

int main()
{
#if 0
    example1();
    example2();
    example3();
    example4();
    example5();
    example6();
    example7();
    example8();
#if defined(CML_ENABLE_DOT_OPERATOR)
    example9();
#endif
    example10();
    example11();
    example12();
    example13();
    example14();
    example15();
    example16();
    example17();
#endif
    example18();
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
