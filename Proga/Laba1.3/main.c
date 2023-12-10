#include <stdio.h>
#include <math.h>
#include <stdbool.h>

 void Find_Y_3_1(){

     printf("\n\n---Find_Y_3_1---\n");

    double x = 8, k = 3, epsilon = 0;
    printf("Enter x:");
    scanf("%lf", &x);

    printf("Enter k:");
    scanf("%lf", &k);

//    printf("Enter epsilon:");
//    scanf("%f", &epsilon);


    bool working = true;
    do {
        printf("Enter epsilon (choose one option):\n");
        printf("1. The number of decimal places is (3)\n");
        printf("2. The real number is (08.001)\n");
        printf("3. Exponential form - 1E-3\n");

        int epsilonOption = 0;
        scanf("%d", &epsilonOption);

        switch (epsilonOption) {
            case 1:
                printf("Enter the number of decimal places (e.g., 3): ");
                int decimalPlaces;
                scanf("%d", &decimalPlaces);
                epsilon = pow(10, -decimalPlaces);
                working = false;
                break;
            case 2:
                printf("Enter a real number (e.g., 0.001): ");
                scanf("%lf", &epsilon);
                working = false;
                break;
            case 3:
                printf("Enter in exponential form (e.g., 1E-8): ");
                double exponent;
                scanf("%lf", &exponent);
                epsilon = pow(10, exponent);
                working = false;
                break;
            default:
                printf("Invalid option. Using default epsilon = 0.\n");
                break;
        }
    }while(working);


    printf("x = %f\t k = %f\t e = %fe\n", x, k, epsilon);
    printf("\n\ne = %f\n\n", epsilon);

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

void Calendar_3_2(){

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

    }while(day < 1 || day > maxDaysInMonth);

    if (month < 3) {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;

    int dayOfWeek = (day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    char *days[] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
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

void CubicEquation_3_3(){

    printf("\n\n---CubicEquation---\n");
    double a, b, c;

    printf("Enter a:");
    scanf("%lf", &a);

    printf("Enter b:");
    scanf("%lf", &b);

    printf("Enter c:6");
    scanf("%lf", &c);

    double left = -1000.0; // Ліва границя для пошуку кореня
    double right = 1000.0; // Права границя для пошуку кореня
    double epsilon = 0.00001; // Точність розв'язання

    double root = findRoot(a, b, c, left, right, epsilon);

    printf("The root of a cubic equation: %.6lf\n", root);
}


int main() {

    Find_Y_3_1();

    Calendar_3_2();

    CubicEquation_3_3();




    return 0;


}

