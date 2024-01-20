#include <stdio.h>
#include <math.h>
#include <complex.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

double addReal(double a, double b) {
    return a + b;
}

double addImag(double a, double b) {
    return a + b;
}

void fun1(double R, double L, double C, double f_min, double f_max, double df) {
    double f0 = 1 / (2 * M_PI * sqrt(L * C));
    printf("\nf0: %fHz\n\n", f0);

    for (double f = f_min; f <= f_max; f += df) {
        double w = 2 * M_PI * f;
        double jwL_real = 0;
        double jwL_imag = -w * L;
        double one_over_jwC_real = 0;
        double one_over_jwC_imag = 1 / (w * C);

        double Z_real = addReal(addReal(R, jwL_real), one_over_jwC_real);
        double Z_imag = addImag(jwL_imag, one_over_jwC_imag);

        printf("Current Z is %e + %ei at f = %.5fHz\n", Z_real, Z_imag, f);
    }
}

void fun2(double R, double L, double C, double f_min, double f_max, double df) {

    double complex Z;

    for (double f = f_min; f <= f_max; f += df) {
        Z = R + (I * 2 * M_PI * f * L) / C;

        if (isfinite(cimag(Z))) {
            printf("f = %f Hz, Z = %f + %f j\n", f, creal(Z), cimag(Z));
        } else {
            printf("f = %f Hz, Z = %f\n", f, creal(Z));
        }
    }
}


int main() {
    double R, L, C, f_min, f_max, df;

    int choice;
    do {
        printf("Enter 1 - 4\n");
        scanf("%d", &choice);

        getchar();
        if (choice == 1 || choice == 2) {
            printf("Enter R: ");
            scanf("%lf", &R);

            printf("Enter L: ");
            scanf("%lf", &L);

            printf("Enter C: ");
            scanf("%lf", &C);

            printf("Enter fmin (Hz): ");
            scanf("%lf", &f_min);

            printf("Enter fmax (Hz): ");
            scanf("%lf", &f_max);

            printf("Enter df: ");
            scanf("%lf", &df);

            if (choice == 1) {
                printf("qwe");
                fun1(R, L, C, f_min, f_max, df);
            } else {
                fun2(R, L, C, f_min, f_max, df);
            }
        } else if (choice == 3 || choice == 4) {
            double frequency, resistance1, resistance2, inductance, capacitance;

            printf("Enter frequency (in radians): ");
            scanf("%lf", &frequency);

            printf("Enter resistance1: ");
            scanf("%lf", &resistance1);

            printf("Enter resistance2: ");
            scanf("%lf", &resistance2);

            printf("Enter inductance: ");
            scanf("%lf", &inductance);

            printf("Enter capacitance: ");
            scanf("%lf", &capacitance);

            double complex impedance;

            if (choice == 1) {
                impedance = 1 / (resistance1 + resistance2 + 1j * frequency * inductance) * 1 / capacitance;
            } else {
                impedance = 1 / (resistance1 + resistance2 + frequency * inductance * capacitance) * 1 / capacitance;
            }

            printf("Complex impedance: %g\n", impedance);
        }


    } while (choice != 5);

    return 0;
}