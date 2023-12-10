#include <stdio.h>
#include <math.h>

int main() {
    // Circuit parameters
    double R1, R2, L, C;
    // Current frequency
    double frequency;

    // Input circuit parameters
    printf("Enter R1 (Ohms): ");
    scanf("%lf", &R1);
    printf("Enter R2 (Ohms): ");
    scanf("%lf", &R2);
    printf("Enter L (mH): ");
    scanf("%lf", &L);
    printf("Enter C (uF): ");
    scanf("%lf", &C);

    // Input current frequency
    printf("Enter current frequency (Hz): ");
    scanf("%lf", &frequency);

    // Calculate resonant frequency
    double resonantFrequency = 1.0 / (2.0 * M_PI * sqrt(L * 1e-3 * C * 1e-6));

    // Calculate impedance
    double angularFrequency = 2.0 * M_PI * frequency;
    double impedanceReal = R1 + (R2 * angularFrequency * L * 1e-3) / (1 + R2 * R2 * angularFrequency * angularFrequency * L * 1e-3 * C * 1e-6);
    double impedanceImaginary = -(R2 * angularFrequency * L * 1e-3) / (1 + R2 * R2 * angularFrequency * angularFrequency * L * 1e-3 * C * 1e-6);

    printf("Resonant Frequency: %.2lf Hz\n", resonantFrequency);
    printf("Impedance at %.2lf Hz: %.2lf + %.2lfi Ohms\n", frequency, impedanceReal, impedanceImaginary);

    return 0;
}
