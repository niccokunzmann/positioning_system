
#ifndef test_solver_h
#define test_solver_h

#include "Arduino.h"

#include "solver.h"

template <class Number>
class TestFunction
{
  public:
    TestFunction();
    
    void test_all();
    
    void test_instanciation();
    void test_instanciation0();
    void test_instanciation1();
    void test_instanciation2();
    void test_instanciation3();
    void test_instanciation4();
    void test_instanciation5();
    
    void test_call();
    void test_from_zeros();
    void test_from_zeros0();
    void test_from_zeros1();
    void test_from_zeros2();
    void test_from_zeros3();
    void test_from_zeros4();
    
    boolean success();
    
  private:
    boolean m_success;
    
};
    
typedef TestFunction<double> TestFunctionDouble;
typedef TestFunction<float > TestFunctionFloat ;

#endif