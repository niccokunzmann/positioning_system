/*
 *
 *
 */

#include "Arduino.h"
#include "solver.h"

// Member functions of template classes 
// https://msdn.microsoft.com/en-us/library/80dx1bas.aspx
// test

#define ASSERT(truth, string) if (!(truth)) { if (Function<Number>::default_debug) { Serial.println(string); }; return false; }

template<class Number> boolean Function<Number>::test_all() {
  ASSERT(Function<Number>::test_from_zeros(), "test_from_zeros failed");
  return true;
};

// undef via https://msdn.microsoft.com/en-us/library/ts4w8783.aspx



template<typename Number> boolean Function<Number>::test_from_zeros() {
  return true;
}




#undef ASSERT
// end of test 
/*
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
   
    // constant 0
template<typename Number> Function<Number>::Function() {
  
}
    // constant
template<typename Number> Function<Number>::Function(Number a) {
  
}    // linear function
template<typename Number> Function<Number>::Function(Number a, Number b) {
  
}    // quadratic function
template<typename Number> Function<Number>::Function(Number a, Number b, Number c) {
  
}    // cubic function
template<typename Number> Function<Number>::Function(Number a, Number b, Number c, Number d) {
  
}    // function of degree 4
template<typename Number> Function<Number>::Function(Number a, Number b, Number c, Number d, Number e) {
  
}
/*    
    //// getter and setter
    //// http://stackoverflow.com/questions/760777/c-getters-setters-coding-style
    // The function is a * x^4 + b * x^3 + c * x^2 + d * x + e
    Number const& a() const;
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