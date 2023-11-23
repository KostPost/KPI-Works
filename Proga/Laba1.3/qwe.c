//#include <stdio.h>
//#include <math.h>
//
//double f(double x, double a, double b, double c) {
//    return x * x * x + a * x * x + b * x + c;
//}
//
//double df(double x, double a, double b) {
//    return 3 * x * x + 2 * a * x + b;
//}
//
//double solveCubic(double a, double b, double c, double x0) {
//    double x = x0;
//    double delta;
//
//    do {
//        delta = f(x, a, b, c) / df(x, a, b);
//        x -= delta;
//    } while (fabs(delta) >= 1e-6);  // Use a small fixed value as precision
//
//    return x;
//}
//
//int main() {
//    double a, b, c;
//
//    printf("Enter a: ");
//    scanf("%lf", &a);
//    printf("Enter b: ");
//    scanf("%lf", &b);
//    printf("Enter c: ");
//    scanf("%lf", &c);
//
//    // Initial guess for the root
//    double x0 = 0.0;
//
//    double root = solveCubic(a, b, c, x0);
//
//    printf("The root of the cubic equation is: %.6lf\n", root);
//
//    return 0;
//}
