
#include "test_positioning_system.h"
#include "Arduino.h"
#include "test_solve.h"
//#include "string.h"


void test_succeeded(const char* message, int line, const char* file) {
  if (Serial) {
    if (verbose_tests) {
     test_print("."); 
    };
  };
};

void test_failed(const char* message, int line, const char* file) {
  if (Serial) {
    if (verbose_tests) {
      test_print("In line "); 
      test_print(line); 
      test_print("\tin file "); 
      test_println(file); 
      test_print("AssertionError: "); 
      test_println(message); 
    } else {
      test_print("F");
    }
  }
}


void test_all() {
  test_println("a2");
  test_coefficients();
}

////////////////////// Output //////////////////////

void test_delay(const char* bytes) {
  // strlen https://www.gnu.org/software/libc/manual/html_node/String-Length.html
  test_delay(strlen(bytes));
} 
void test_delay(int bytes) {
  delay(1 + bytes / 9);
}


void test_print(const char* message){
  Serial.print(message);
  test_delay(message);
}

void test_println() {
  test_print("\n");
}
void test_println(const char* message) {
  test_print(message);
  test_println();
}
void test_print(int message) {
  int digits = 1;
  while (message) {
    ++digits;
    message /= 10;
  }
  Serial.print(message);
  test_delay(digits);
}
void test_println(int message) {
  test_print(message);
  test_println();
}
void test_print(double message){
  // 0.3333333333333333 18 bytes
  Serial.print(message);
  test_delay(18);
}
void test_println(double message){
  test_print(message);
  test_println();
}

void test_print(const char* message1, double message2) {
  test_print(message1);
  test_print(message2);
}
void test_println(const char* message1, double message2) {
  test_print(message1);
  test_println(message2);
}
void test_print(const char* message1, double message2, const char* message3, double message4) {
  test_print(message1, message2);
  test_print(message3, message4);
}
void test_println(const char* message1, double message2, const char* message3, double message4) {
  test_print(message1, message2);
  test_println(message3, message4);
}

void test_print(const char* message1, double message2, const char* message3, double message4, 
                const char* message5, double message6) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
}
void test_println(const char* message1, double message2, const char* message3, double message4, 
                  const char* message5, double message6) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_println(message5, message6);
}
void test_print(const char* message1, double message2, const char* message3, double message4, 
                const char* message5, double message6, const char* message7, double message8) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_print(message7, message8);
}
void test_println(const char* message1, double message2, const char* message3, double message4, 
                  const char* message5, double message6, const char* message7, double message8) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_println(message7, message8);
}

void test_print(const char* message1, double message2, const char* message3, double message4, 
                const char* message5, double message6, const char* message7, double message8, 
                const char* message9, double message10) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_print(message7, message8);
  test_print(message9, message10);
}
void test_println(const char* message1, double message2, const char* message3, double message4, 
                  const char* message5, double message6, const char* message7, double message8, 
                  const char* message9, double message10) {
  test_print(message1, message2);
  test_print(message3, message4);
  test_print(message5, message6);
  test_print(message7, message8);
  test_println(message9, message10);
}


