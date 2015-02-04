
double newton(double a, double b, double c, double d, double e, double x, double epsilon) {
  return newton(a, b, c, d, e, x, epsilon, 100000);
}

double newton(double a, double b, double c, double d, double e, double x, double epsilon, long maximum_iterations) {
  // differenciation
  double da = 0;
  double db = 4 * a;
  double dc = 3 * b;
  double dd = 2 * c;
  double de = d;

  double y;    
  double last_x1 = x;
  double last_x2 = x;
  while (maximum_iterations > 0) {
    --maximum_iterations;
    //test_println("y: ", y);
    y = call(a, b, c, d, e, x);
    if (y == 0) {
      break;
    }
    double slope = call(da, db, dc, dd, de, x);
    //test_println("slope: ", slope);
    if (slope == 0) {
      return x;
    }
    last_x2 = last_x1;
    last_x1 = x;
    x = (slope * x - y) / slope;
    //test_println("x: ", x);
    if (last_x1 == x) {
      break;
    }
    if (abs(last_x1 - x) > abs(last_x2 - last_x1)) {
      // hypothesis: if the step size increased we shot over our goal.
      test_println("step increased x: ", x, " last_x1: ", last_x1, " last_x2: ", last_x2);
    }
  }
  test_println("maximum_iterations: ", maximum_iterations);
  return x;
}

void refine_zeros_of_order_3_with_3_solutions(double b, double c, double d, double e, double *zero1, double *zero2, double *zero3) {
  sort_numbers(zero1, zero2, zero3);
  double difference1 = (*zero2 - *zero1) / 2;
  double difference2 = (*zero3 - *zero2) / 2;
  double new_zero1 = refine_zero(0, b, c, d, e, *zero1 - difference1, *zero1 + difference1);
  double new_zero2 = refine_zero(0, b, c, d, e, *zero2 - difference1, *zero2 + difference2);
  double new_zero3 = refine_zero(0, b, c, d, e, *zero3 - difference2, *zero3 + difference2);
  *zero1 = new_zero1;
  *zero2 = new_zero2;
  *zero3 = new_zero3;
}

double refine_zero(double a, double b, double c, double d, double e, double upper_bound, double lower_bound) {
  double lower_y = call(a, b, c, d, e, lower_bound);
  double upper_y = call(a, b, c, d, e, upper_bound);
  if (upper_y == 0) {
    return upper_bound;
  }
  if (lower_y == 0) {
    return lower_bound;
  }
  if (((lower_y > 0) && (upper_y > 0)) || ((lower_y < 0) && (upper_y < 0))) {
    test_print("refine_zero: upper and lower bound have same sign - can not refine zero ");
    test_println(" -> upper_bound: ", upper_bound, " lower_bound: ", lower_bound);
    test_println(" -> upper_y: ", upper_y, " lower_y: ", lower_y);
    test_print(" -> "); print_coefficients_to_serial(0, b, c, d, e); test_println();
    return get_not_a_number();
  }
  if (lower_y > 0) {
    switch_numbers(&upper_bound, &lower_bound);
  }
  double last_bound = lower_bound;
  double new_bound = upper_bound;
  while (1) {
    last_bound = new_bound;
    new_bound = (lower_bound + upper_bound) / 2;
    if (last_bound == new_bound) {
      return new_bound;
    }
    double new_y = call(a, b, c, d, e, new_bound);
    if (new_y == 0) {
      return new_bound;
    } else if (new_y < 0) {
      lower_bound = new_bound;
    } else {
      upper_bound = new_bound;
    }
  }
}

