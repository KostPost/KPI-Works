#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void Find_Y_3_1() {

    printf("\n\n---Find_Y_3_1---\n");

    double x = 8, k = 3, epsilon;
//    printf("Enter x:");
//    scanf("%lf", &x);
//
//    printf("Enter k:");
//    scanf("%lf", &k);

    int choice;
    printf("Введіть як ви хочете ввести точність:\n");
    printf("1. Кількість знаків після коми \n");
    printf("2. Дійсне число \n");
    printf("3. Експоненціальний вигляд )\n");

    scanf("%d", &choice);

    int numDigits;
    char exp[20];

    switch (choice) {
        case 1:
            printf("Введіть кількість знаків після коми: ");
            scanf("%d", &numDigits);
            numDigits /= 2;
            epsilon = 1.0 / pow(10, numDigits);
            for (int i = 0; i < numDigits; ++i) {
                epsilon /= 10.0;
            }
            printf("Точність: %.*e\n", numDigits, epsilon);
            break;
        case 2:
            printf("Введіть дійсне число: ");
            scanf("%lf", &epsilon);
            break;
        case 3:
            printf("Введіть точність у форматі експоненції (наприклад, 1E-3): ");
            scanf("%19s", exp);
            epsilon = atof(exp);
            printf("Точність: %.*e\n", 3, epsilon);
            break;
        default:
            printf("Невірний вибір.\n");
            break;
    }

    printf("x = %.3f\t k = %.6f\t e = %.6e\n", x, k, epsilon);

    double delta = 1.0;
    double y = 1.0;

    printf("delta = %f\n", delta);
    printf("y = %f\n\n", y);

    while (fabs(delta) >= epsilon) {
        delta = 1.0 / k * (x / pow(y, k - 1) - y);
        y += delta;

        printf("delta = %f\n", delta);
        printf("y = %f\n\n", y);
    }
}


int isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int getDaysInMonth(int year, int month) {
    if (month < 1 || month > 12)
        return 0;

    if (month == 2)
        return isLeapYear(year) ? 29 : 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

void Calendar_3_2() {

    printf("\n\n---Calendar---\n");
    int day, month, year;

    do {
        printf("Enter the year:");
        scanf("%d", &year);

        if (year < 0) {
            printf("Error: Year must be a positive number.\n");
        }

    } while (year <= 0);


    do {
        printf("Enter the month (1-12):");
        scanf("%d", &month);

        if (month < 1 || month > 12) {
            printf("Error: Month must be in the range from 1 to 12.\n");
        }
    } while (month < 1 || month > 12);

    int maxDaysInMonth = getDaysInMonth(year, month);

    if (maxDaysInMonth == 0) {
        printf("Error: Invalid month.\n");
    }

    do {
        printf("Enter the day (1-%d):", maxDaysInMonth);
        scanf("%d", &day);

        if (day < 1 || day > maxDaysInMonth) {
            printf("Error: Day must be in the range from 1 to %d.\n", maxDaysInMonth);
        }

    } while (day < 1 || day > maxDaysInMonth);

    if (month < 3) {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;

    int dayOfWeek = (day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    char *days[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    printf("The day of the week is: %s\n", days[dayOfWeek]);
}


double cubicEquation(double a, double b, double c, double x) {
    return x * x * x + a * x * x + b * x + c;
}

double findRoot(double a, double b, double c, double left, double right, double epsilon) {
    double mid;

    while ((right - left) > epsilon) {
        mid = (left + right) / 2.0;
        if (cubicEquation(a, b, c, mid) == 0.0) {
            return mid;
        } else if (cubicEquation(a, b, c, left) * cubicEquation(a, b, c, mid) < 0.0) {
            right = mid;
        } else {
            left = mid;
        }
    }

    return (left + right) / 2.0;
}

void CubicEquation_3_3() {

    printf("\n\n---CubicEquation---\n");
    double a, b, c;

    printf("Enter a:");
    scanf("%lf", &a);

    printf("Enter b:");
    scanf("%lf", &b);

    printf("Enter c:6");
    scanf("%lf", &c);

    double left = -1000.0;
    double right = 1000.0;
    double epsilon = 0.00001;

    double root = findRoot(a, b, c, left, right, epsilon);

    printf("The root of a cubic equation: %.6lf\n", root);
}


int main() {

    int choice;


    do {
        printf("1 - Find Y 3.1\n2 - Calendar 3.2\n3 - CubicEquation 3.3\n4 - Exit");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                Find_Y_3_1();
                break;

            case 2:
                Calendar_3_2();
                break;

            case 3:
                CubicEquation_3_3();
                break;
        }
    } while (choice != 4);


    return 0;


}

