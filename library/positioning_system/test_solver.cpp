
// test


#ifndef test_solver_cpp
#define test_solver_cpp

#include "Arduino.h"
#include "solver.h"

#define assert2(truth, Message) if (!(truth)) { if (Function<Number>::default_debug) { Serial.println(Message); }; return false; }
#define assert1(truth) assert2((truth), #truth)
#define assert_equals2(A, B, Message) assert2(A == B, #Message)
#define _assert_equals(A, B, Message) assert_equals2(A, B, #Message)
#define assert_equals(A, B) _assert_equals(A, B, A == B)

template<class Number> boolean Function<Number>::test_all() {
  assert2(Function<Number>::test_instanciation(), "test_instanciation failed");
  assert2(Function<Number>::test_from_zeros(), "test_from_zeros failed");
  return true;
};


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
  Function<Number> f = Function<Number>(11, 99, 100, 98, 8);
  assert_equals(f.a(), 11);
  assert_equals(f.b(), 99);
  assert_equals(f.c(), 100);
  assert_equals(f.d(), 98);
  assert_equals(f.e(), 8);
  return true;
}

template<typename Number> boolean Function<Number>::test_from_zeros() {
  //assert2(Function<Number>::test_instanciation5(), "test_instanciation5 failed");
  return true;
}

// undef via https://msdn.microsoft.com/en-us/library/ts4w8783.aspx
#undef assert1
#undef assert2
#undef assert_equals
#undef assert_equals2
#undef _assert_equals2

// end of test 
  
  
#endif