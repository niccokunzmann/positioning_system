/*
 *
 *
 */

#include "Arduino.h"
#include "solver.h"

// Member functions of template classes 
// https://msdn.microsoft.com/en-us/library/80dx1bas.aspx
// test

#define assert2(truth, Message) if (!(truth)) { if (Function<Number>::default_debug) { Serial.println(Message); }; return false; }
#define assert1(truth) assert2((truth), #truth)
#define assert_equals2(A, B, Message) assert2((truth), #Message)
#define _assert_equals2(A, B, Message) assert_equals2(A, B, #Message)
#define assert_equals(A, B) assert2(A == B, A == B)

template<class Number> boolean Function<Number>::test_all() {
  assert2(Function<Number>::test_instanciation(), "test_instanciation failed");
  assert2(Function<Number>::test_from_zeros(), "test_from_zeros failed");
  return true;
};

template<typename Number> boolean Function<Number>::test_from_zeros() {
  return true;
}

template<typename Number> boolean Function<Number>::test_instanciation() {
  assert2(Function<Number>::test_instanciation0(), "test_instanciation0 failed");
  assert2(Function<Number>::test_instanciation1(), "test_instanciation1 failed");
  assert2(Function<Number>::test_instanciation2(), "test_instanciation2 failed");
  assert2(Function<Number>::test_instanciation3(), "test_instanciation3 failed");
  assert2(Function<Number>::test_instanciation4(), "test_instanciation4 failed");
  assert2(Function<Number>::test_instanciation5(), "test_instanciation5 failed");
  return true;
}

template<typename Number> boolean Function<Number>::test_instanciation0() {
  Function<Number> f = Function<Number>();
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 0);
  assert_equals(f.c(), 0);
  assert_equals(f.d(), 0);
  assert_equals(f.e(), 0);
  return true;
}

template<typename Number> boolean Function<Number>::test_instanciation1() {
  Function<Number> f = Function<Number>(12);
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 0);
  assert_equals(f.c(), 0);
  assert_equals(f.d(), 0);
  assert_equals(f.e(), 12);
  return true;
}

template<typename Number> boolean Function<Number>::test_instanciation2() {
  Function<Number> f = Function<Number>(22, 12);
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 0);
  assert_equals(f.c(), 0);
  assert_equals(f.d(), 22);
  assert_equals(f.e(), 12);
  return true;
}

template<typename Number> boolean Function<Number>::test_instanciation3() {
  Function<Number> f = Function<Number>(100, 99, 8);
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 0);
  assert_equals(f.c(), 100);
  assert_equals(f.d(), 99);
  assert_equals(f.e(), 8);
  return true;
}

template<typename Number> boolean Function<Number>::test_instanciation4() {
  Function<Number> f = Function<Number>(23, 100, 99, 8);
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 23);
  assert_equals(f.c(), 100);
  assert_equals(f.d(), 99);
  assert_equals(f.e(), 8);
  return true;
}

template<typename Number> boolean Function<Number>::test_instanciation5() {
  Function<Number> f = Function<Number>(11, 99, 100, 99, 8);
  assert_equals(f.a(), 11);
  assert_equals(f.b(), 99);
  assert_equals(f.c(), 100);
  assert_equals(f.d(), 99);
  assert_equals(f.e(), 8);
  return true;
}



// undef via https://msdn.microsoft.com/en-us/library/ts4w8783.aspx
#undef assert1
#undef assert2
#undef assert_equals
#undef assert_equals2
#undef _assert_equals2

// end of test 
  
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


// constant
template<typename Number> Function<Number> Function<Number>::from_zeros(){
  
}
template<typename Number> Function<Number> Function<Number>::from_zeros(Number zero1){
  
}
template<typename Number> Function<Number> Function<Number>::from_zeros(Number zero1, Number zero2){
  
}
template<typename Number> Function<Number> Function<Number>::from_zeros(Number zero1, Number zero2, Number zero3){
  
}
template<typename Number> Function<Number> Function<Number>::from_zeros(Number zero1, Number zero2, Number zero3, Number zero4){
  
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