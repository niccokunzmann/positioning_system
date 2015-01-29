/*
 *
 *
 */


#ifndef solver_cpp
#define solver_cpp
 
#include "Arduino.h"
#include "solver.h"


// Member functions of template classes 
// https://msdn.microsoft.com/en-us/library/80dx1bas.aspx

    // constant 0
template<typename Number> Function<Number>::Function() {
  set_coefficients(0, 0, 0, 0, 0);
}
    // constant
template<typename Number> Function<Number>::Function(Number e) {
  set_coefficients(0, 0, 0, 0,  e);
}    // linear function
template<typename Number> Function<Number>::Function(Number d, Number e) {
  set_coefficients(0, 0, 0, d, e);
}    // quadratic function
template<typename Number> Function<Number>::Function(Number c, Number d, Number e) {
  set_coefficients(0, 0, c, d, e);
}    // cubic function
template<typename Number> Function<Number>::Function(Number b, Number c, Number d, Number e) {
  set_coefficients(0, b, c, d, e);
}    // function of degree 4
template<typename Number> Function<Number>::Function(Number a, Number b, Number c, Number d, Number e) {
  set_coefficients(a, b, c, d, e);
}

template<typename Number> void Function<Number>::set_coefficients(Number a, Number b, Number c, Number d, Number e) {
  m_a = a;
  m_b = b;
  m_c = c;
  m_d = d;
  m_e = e;
}
    
template<typename Number> Number const& Function<Number>::a() const {
  return m_a;
}
template<typename Number> Number const& Function<Number>::b() const {
  return m_b;
}
template<typename Number> Number const& Function<Number>::c() const {
  return m_c;
}
template<typename Number> Number const& Function<Number>::d() const {
  return m_d;
}
template<typename Number> Number const& Function<Number>::e() const {
  return m_e;
}

template<typename Number> Number Function<Number>::operator()(Number x) const {
  return (((a() * x + b()) * x + c()) * x + d()) * x + e();
}

// constant
template<typename Number> Function<Number> Function<Number>::from_zeros(){
  return Function<Number>(0);
}
template<typename Number> Function<Number> Function<Number>::from_zeros(Number zero1){
  return Function<Number>(1, -zero1);
}
template<typename Number> Function<Number> Function<Number>::from_zeros(Number zero1, Number zero2){
  return Function<Number>(1, -zero1 -zero2, zero1 * zero2);
}
template<typename Number> Function<Number> Function<Number>::from_zeros(Number zero1, Number zero2, Number zero3){
  return Function<Number>(1, -zero1 - zero2 - zero3, zero1 * zero2);
}
template<typename Number> Function<Number> Function<Number>::from_zeros(Number zero1, Number zero2, Number zero3, Number zero4){
  return Function<Number>(1, -zero1 -zero2, zero1 * zero2);
}
 

/*      Number const&  const;
    Number const& b() const;
    Number const& c() const;
    Number const& d() const;
    Number const& e() const;
    
   Number call(Number x);
    //// call operator 
    //// http://stackoverflow.com/questions/2349867/how-can-it-be-useful-to-overload-the-function-call-operator
    Number operator()(Number x) const;

    // set the error that is tolerated for equality tests
    Number const& epsilon() const;              // Getter
    void epsilon(Number const& new_epsilon);    // Setter

    // compare two values for equality using epsilon
    boolean approximates(Number a, Number b);
    
    boolean const& debug() const;                 // Getter
    void debug(boolean const& new_debug_mode);    // Setter
    
    void add(Number n);
    void multiply(Number n); 

*/
// instanciate template
// http://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor

template class Function<float >;
template class Function<double>;

#endif