#include <stdio.h>
#include <math.h>

double equation(double x) {
    return x * x * x - 4 * x - 9;
}

double bisectionMethod(double a, double b, double precision) {
    double c = (a + b) / 2.0;
    while ((b - a) >= precision) {
        c = (a + b) / 2.0;

        if (equation(c) == 0.0)
            break;
        else if (equation(c) * equation(a) < 0) //
            b = c;
        else
            a = c;
    }
    return c;
}


double derivative(double x) {
}

double newtonMethod(double x, double precision) {
    double h = equation(x) / derivative(x);
    while (fabs(h) >= precision) {
        h = equation(x) / derivative(x);

        x = x - h;
    }
    return x;
}

int main() {
    int choice;

    do {

        printf("1 - Bisection method\n2 - Newton method\n3 - Exit\n");
        scanf("%d", &choice);


        switch (choice) {

            case 1: {
                double a, b;
                printf("Enter interval a");
                scanf("%lf", &a);

                printf("Enter interval b");
                scanf("%lf", &b);

                double precision;
                printf("Enter precision");
                scanf("%lf", &precision);

                if (equation(a) * equation(b) >= 0) {
                    printf("incorrect interval");
                    break;
                }

                double root = bisectionMethod(a, b, precision);
                printf("Корінь рівняння: %lf\n", root);
                break;
            }

            case 2: {
                double initialGuess;
                printf("Enter the initial approximation: ");
                scanf("%lf", &initialGuess);

                double precision;
                printf("Enter precision");
                scanf("%lf", &precision);

                double root = newtonMethod(initialGuess, precision);
                printf("Root of the equation: %lf\n", root);
                break;
            }
        }
    } while (choice != 3);

    return 0;
}
