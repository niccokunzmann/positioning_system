
#ifndef approximation_hpp
#define approximation_hpp

bool approximates(double a, double b);
bool approximates(double a, double b, double epsilon);
double get_epsilon();
double get_default_epsilon();
void set_epsilon(double new_epsilon);

#endif