#include <stdio.h>
#include <math.h>

double f(double x, double y) {
    return cos(y / x) - 2 * sin(1 / x) + 1 / x;
}

double df_dx(double x, double y) {
    double h = 1e-5;
    return (f(x + h, y) - f(x, y)) / h;
}

double df_dy(double x, double y) {
    double h = 1e-5;
    return (f(x, y + h) - f(x, y)) / h;
}

int main() {
    double a1, a2;
    double epsilon;
    double x0, y0;

    printf("Enter the start of the interval (a1): ");
    scanf("%lf", &a1);
    printf("Enter the end of the interval (a2): ");
    scanf("%lf", &a2);
    printf("Enter the tolerance (epsilon): ");
    scanf("%lf", &epsilon);

    printf("Enter the initial approximation for x0: ");
    scanf("%lf", &x0);
    printf("Enter the initial approximation for y0: ");
    scanf("%lf", &y0);

    int maxIterations;
    int iterations = 0;

    do {
        double delta_x = -f(x0, y0) / df_dx(x0, y0);
        double delta_y = -f(x0, y0) / df_dy(x0, y0);
        x0 += delta_x;
        y0 += delta_y;
        iterations++;
    } while (fabs(f(x0, y0)) > epsilon && iterations < maxIterations);

    if (iterations < maxIterations) {
        printf("Solution: x = %.6f, y = %.6f\n", x0, y0);
    } else {
        printf("Unable to find a solution with the specified tolerance.\n");
    }

    return 0;
}
