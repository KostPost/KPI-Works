#include <stdio.h>
#include <math.h>

// Функція для обчислення комплексного опору
void calculateImpedance(double frequency, double R1, double R2, double L, double C, double resonanceFrequency) {
    double omega = 2 * M_PI * frequency;

    // Реактивний опір від конденсатора та котушки
    double reactance_capacitance = 1.0 / (omega * C);
    double reactance_inductance = omega * L;

    // Реальна та уявна частини опору
    double real_part = R1 + R2;
    double imaginary_part = reactance_inductance - reactance_capacitance;

    // Обчислення опору при резонансі
    if (frequency == resonanceFrequency) {
        printf("At resonance:\n");
        real_part = R1 + R2;
        imaginary_part = 0;
    }

    // Виведення результатів обчислення
    printf("Frequency: %.2lf Hz\n", frequency);
    printf("Impedance (Real): %.2lf Ohms\n", real_part);
    printf("Impedance (Imaginary): %.2lf Ohms\n", imaginary_part);
    printf("Total Impedance: %.2lf Ohms\n", sqrt(real_part * real_part + imaginary_part * imaginary_part));
}

int main() {
    double R1 = 100; // Опір R1 (в Омах)
    double R2 = 150; // Опір R2 (в Омах)
    double L = 10;   // Індуктивність L (в мГн)
    double C = 10;   // Ємність C (в мкФ)
    double resonanceFrequency = 1.0 / (2 * M_PI * sqrt(L * 0.001 * C * 0.000001)); // Резонансна частота (в Гц)

    // Параметри для тестування на різних частотах
    double frequencies[] = { resonanceFrequency * 0.5, resonanceFrequency, resonanceFrequency * 1.5 };

    for (int i = 0; i < 3; ++i) {
        calculateImpedance(frequencies[i], R1, R2, L * 0.001, C * 0.000001, resonanceFrequency);
        printf("\n");
    }

    return 0;
}
