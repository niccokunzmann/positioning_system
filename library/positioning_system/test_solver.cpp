

#ifndef test_solver_cpp
#define test_solver_cpp13

#include "Arduino.h"
#include "test_solver.h"


template<typename Number> TestFunction<Number>::TestFunction() {
  m_success = true;
}

template<typename Number> boolean TestFunction<Number>::success() {
  return m_success;
}


void test_debug_print(const char* message, int line, const char* file) {
  if (Serial) {
    Serial.print("In "); 
    Serial.print(file); 
    Serial.print(" in line "); 
    Serial.print(line); 
    Serial.println(":"); 
    Serial.print("  "); 
    Serial.println(message); 
  }
};

void test_debug_print(int line) {
  if (Serial) {
    Serial.print("In "); 
    //Serial.print(file); 
    Serial.print(" in line "); 
    //Serial.print(line); 
    Serial.println(":"); 
    Serial.print("  "); 
    //Serial.println(message); 
  }
};

// Macros
// https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#Standard-Predefined-Macros
#define assert2(truth, Message) \
  if (!(truth)) { \
    test_debug_print(Message, __LINE__, __FILE__); \
    m_success = false; \
  };
  
#define assert1(truth) assert2(truth, #truth)

#define assert_equals2(A, B, Message) assert2((A) == (B), #Message)
#define _assert_equals(A, B, Message) assert_equals2(A, B, #Message)
#define assert_equals(A, B) _assert_equals(A, B, A == B)

#define assert_not_equals2(A, B, Message) assert2((A) != (B), #Message)
#define _assert_not_equals(A, B, Message) assert_not_equals2(A, B, #Message)
#define assert_not_equals(A, B) _assert_not_equals(A, B, A != B)

const char *ASSERTION_STRING_1 = "In ";

template<class Number> void TestFunction<Number>::test_all() {
  Serial.println(__LINE__);
  Serial.print("hallo"); 
  if (!(1 == 2)) { 
    //test_debug_print("1 == 2", __LINE__, __FILE__); 
    //if (Serial) {
      //Serial.print(ASSERTION_STRING_1); 
      //Serial.print(file); 
      //Serial.print(" in line "); 
      //Serial.print(line); 
      //Serial.println(":"); 
      //Serial.print("  "); 
      //Serial.println(message); 
    //}
    m_success = false; 
  };
  //assert2(1 == 2, "test!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  Serial.println(__LINE__);
  /*TestFunction<Number>::test_instanciation();
  TestFunction<Number>::test_call();
  TestFunction<Number>::test_from_zeros();
  
  */
  
};



template<typename Number> void TestFunction<Number>::test_instanciation() {
  TestFunction<Number>::test_instanciation0();
  TestFunction<Number>::test_instanciation1();
  TestFunction<Number>::test_instanciation2();
  TestFunction<Number>::test_instanciation3();
  TestFunction<Number>::test_instanciation4();
  TestFunction<Number>::test_instanciation5();
  
}

template<typename Number> void TestFunction<Number>::test_instanciation0() {
  Function<Number> f = Function<Number>();
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 0);
  assert_equals(f.c(), 0);
  assert_equals(f.d(), 0);
  assert_equals(f.e(), 0);
  
}

template<typename Number> void TestFunction<Number>::test_instanciation1() {
  Function<Number> f = Function<Number>(12);
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 0);
  assert_equals(f.c(), 0);
  assert_equals(f.d(), 0);
  assert_equals(f.e(), 12);
  
}

template<typename Number> void TestFunction<Number>::test_instanciation2() {
  Function<Number> f = Function<Number>(22, 12);
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 0);
  assert_equals(f.c(), 0);
  assert_equals(f.d(), 22);
  assert_equals(f.e(), 12);
  
}

template<typename Number> void TestFunction<Number>::test_instanciation3() {
  Function<Number> f = Function<Number>(100, 99, 8);
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 0);
  assert_equals(f.c(), 100);
  assert_equals(f.d(), 99);
  assert_equals(f.e(), 8);
  
}

template<typename Number> void TestFunction<Number>::test_instanciation4() {
  Function<Number> f = Function<Number>(23, 100, 99, 8);
  assert_equals(f.a(), 0);
  assert_equals(f.b(), 23);
  assert_equals(f.c(), 100);
  assert_equals(f.d(), 99);
  assert_equals(f.e(), 8);
  
}

template<typename Number> void TestFunction<Number>::test_instanciation5() {
  Function<Number> f = Function<Number>(11, 99, 100, 98, 8);
  assert_equals(f.a(), 11);
  assert_equals(f.b(), 99);
  assert_equals(f.c(), 100);
  assert_equals(f.d(), 98);
  assert_equals(f.e(), 8);
  
}

template<typename Number> Number call_function(Number a, Number b, Number c, Number d, Number e, Number x) {
  Function<Number> f = Function<Number>(a, b, c, d, e);
  Number y = f(x);
  return y;
}

template<typename Number> void TestFunction<Number>::test_call() {
  assert_equals(call_function<Number>(1, 2, 3, 4, 5,    0), 5);
  assert_equals(call_function<Number>(1, 2, 3, 4, 5,    1), 15);
  assert_equals(call_function<Number>(3, 0, 0, 0, 0,    2), 3 * 16);
  assert_equals(call_function<Number>(0, 2, 0, 0, 0,    3), 2 * 27);
  assert_equals(call_function<Number>(0, 1, 1, 0, 0,   -2), -8 + 4);
  assert_equals(call_function<Number>(0, 0, 0, 33, 0,  -2), -66);
  assert_equals(call_function<Number>(1, 2, 3, 4, 5,  0.1), 5.4321);
  assert_equals(call_function<Number>(1, 2, 3, 4, 5,   10), 12345);
  
}

template<typename Number> void TestFunction<Number>::test_from_zeros0() {
  assert_equals(Function<Number>::from_zeros()(0), 0);
  assert_equals(Function<Number>::from_zeros()(1), 0);
  
  assert_equals(Function<Number>::from_zeros().a(), 0);
  assert_equals(Function<Number>::from_zeros().b(), 0);
  assert_equals(Function<Number>::from_zeros().c(), 0);
  assert_equals(Function<Number>::from_zeros().d(), 0);
  assert_equals(Function<Number>::from_zeros().e(), 0);
  
}

template<typename Number> void TestFunction<Number>::test_from_zeros1() {
  assert_not_equals(Function<Number>::from_zeros( 1)(0), 0);
  assert_not_equals(Function<Number>::from_zeros( 1)(2), 0);
  assert_not_equals(Function<Number>::from_zeros(-1)(0), 0);
  assert_equals(Function<Number>::from_zeros(1)(1), 0);
  
  assert_equals(Function<Number>::from_zeros(1).a(), 0);
  assert_equals(Function<Number>::from_zeros(1).b(), 0);
  assert_equals(Function<Number>::from_zeros(1).c(), 0);
  assert_equals(Function<Number>::from_zeros(1).d(), 1);
  assert_not_equals(Function<Number>::from_zeros(1).e(), 0);
  
}

template<typename Number> void TestFunction<Number>::test_from_zeros2() {
  assert_not_equals(Function<Number>::from_zeros( 1, 3)(0), 0);
  assert_not_equals(Function<Number>::from_zeros( 1, 3)(2), 0);
  assert_not_equals(Function<Number>::from_zeros(-1, 2)(0), 0);
  assert_equals(Function<Number>::from_zeros(1, 3)(1), 0);
  assert_equals(Function<Number>::from_zeros(1, 3)(3), 0);
  assert_equals(Function<Number>::from_zeros(1, 1)(1), 0);
  assert_not_equals(Function<Number>::from_zeros(1, 1)(2.33), 0);
  Serial.println("test!");
}/*
  assert_equals(Function<Number>::from_zeros(1,2).a(), 0); // this is the line!
  assert_equals(Function<Number>::from_zeros(1,2).b(), 0);
  assert_equals(Function<Number>::from_zeros(1,2).c(), 1);
  assert_not_equals(Function<Number>::from_zeros(1,2).d(), 0);
  assert_not_equals(Function<Number>::from_zeros(1,2).e(), 0);
  
}
/*
template<typename Number> void TestFunction<Number>::test_from_zeros3() {
  assert_not_equals(Function<Number>::from_zeros( 1, 3, 5)(0), 0);
  assert_not_equals(Function<Number>::from_zeros( 1, 3, 5)(2), 0);
  assert_not_equals(Function<Number>::from_zeros(-1, 2, 9)(0), 0);
  assert_not_equals(Function<Number>::from_zeros(-1, 2, 9)(0), 0);
  assert_equals(Function<Number>::from_zeros(-1, 2, 7)(0), 100);
  assert_not_equals(Function<Number>::from_zeros(-1, 2, 8)(0), 0);

  assert_equals(Function<Number>::from_zeros(1, 3, 5)(1), 0);
  assert_equals(Function<Number>::from_zeros(1, 3, 5)(3), 0);
  assert_equals(Function<Number>::from_zeros(1, 3, 5)(5), 0);
  
  assert_equals(Function<Number>::from_zeros(1, 1, 1)(1), 0);
  assert_not_equals(Function<Number>::from_zeros(1, 1, 1)(2.33), 0);

  
  assert_equals(Function<Number>::from_zeros(1,2,66).a(), 0);
  assert_equals(Function<Number>::from_zeros(1,2,66).b(), 1);
  assert_not_equals(Function<Number>::from_zeros(1,2,66).c(), 0);
  assert_not_equals(Function<Number>::from_zeros(1,2,66).d(), 0);
  assert_not_equals(Function<Number>::from_zeros(1,2,66).e(), 0);

  
}

template<typename Number> void TestFunction<Number>::test_from_zeros4() {
  assert_not_equals(Function<Number>::from_zeros( 1, 3, 5, 4)(0), 0);
  assert_not_equals(Function<Number>::from_zeros( 1, 3, 5, 4)(2), 0);
  assert_not_equals(Function<Number>::from_zeros(-1, 2, 9, 4)(10), 0);
  
  assert_equals(Function<Number>::from_zeros(1, 3, 5, 9)(1), 0);
  assert_equals(Function<Number>::from_zeros(1, 3, 5, 9)(3), 0);
  assert_equals(Function<Number>::from_zeros(1, 3, 5, 9)(5), 0);
  assert_equals(Function<Number>::from_zeros(1, 3, 5, 9)(9), 0);
  
  assert_equals(Function<Number>::from_zeros(1, 1, 1, 1)(1), 0);
  assert_not_equals(Function<Number>::from_zeros(1, 1, 1, 1)(2.33), 0);
  
  assert_equals(Function<Number>::from_zeros(1,2,3,4).a(), 1);
  assert_not_equals(Function<Number>::from_zeros(1,2,3,4).b(), 0);
  assert_not_equals(Function<Number>::from_zeros(1,2,3,4).c(), 0);
  assert_not_equals(Function<Number>::from_zeros(1,2,3,4).d(), 0);
  assert_not_equals(Function<Number>::from_zeros(1,2,3,4).e(), 0);
  
}


template<typename Number> void TestFunction<Number>::test_from_zeros() {
  //TestFunction<Number>::test_from_zeros0();  
  //TestFunction<Number>::test_from_zeros1();  
  //TestFunction<Number>::test_from_zeros2();  
  //TestFunction<Number>::test_from_zeros3();  
  //TestFunction<Number>::test_from_zeros4();  
  
}*/


// undef via https://msdn.microsoft.com/en-us/library/ts4w8783.aspx
#undef assert1
#undef assert2

#undef assert_equals
#undef assert_equals2
#undef _assert_equals2

#undef assert_not_equals
#undef assert_not_equals2
#undef _assert_not_equals2

template class TestFunction<float >;
template class TestFunction<double>;
  
#endif