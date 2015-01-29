
#ifndef solver_h
#define solver_h

#include "Arduino.h"

// templates http://www.cprogramming.com/tutorial/templates.html

template <class Number>
class Function
{
  public:
    // constant
    static Function<Number> from_zeros();
    // linear function
    static Function<Number> from_zeros(Number zero1);
    // quadratic function
    static Function<Number> from_zeros(Number zero1, Number zero2);
    // cubic function
    static Function<Number> from_zeros(Number zero1, Number zero2, Number zero3);
    // function of degree 4
    static Function<Number> from_zeros(Number zero1, Number zero2, Number zero3, Number zero4);
    
    // constant 0
    Function(); 
    // constant
    Function(Number e); 
    // linear function
    Function(Number d, Number e);
    // quadratic function
    Function(Number c, Number d, Number e);
    // cubic function
    Function(Number b, Number c, Number d, Number e);
    // function of degree 4
    Function(Number a, Number b, Number c, Number d, Number e);
    
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

    // tests
    const static boolean default_debug = true;
    //static void test_debug_print(char* message, int line, char* file);
    
  private: 
    Number m_a;
    Number m_b;
    Number m_c;
    Number m_d;
    Number m_e;
    Number m_epsilon;
    
    void set_coefficients(Number a, Number b, Number c, Number d, Number e);

};

// instanciate template
// http://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
typedef Function<double> FunctionDouble;
typedef Function<float > FunctionFloat ;

#endif