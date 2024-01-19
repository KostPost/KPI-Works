#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <slcurses.h>
#include <stdbool.h>
#include <string.h>

double get_valid_double(char side) {
    double number = 0;
    char input[50];
    int success;

    do {
        success = 1;
        printf("Enter length for %c side: ", side);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Input error");
            exit(EXIT_FAILURE);
        }

        if (sscanf(input, "%lf", &number) != 1 || strchr(input, '\n') == NULL) {
            success = 0;
        }
        for (int i = 0; input[i] != '\0'; ++i) {
            if (!isdigit(input[i]) && input[i] != '-' && input[i] != '+' && input[i] != '.' && input[i] != '\n') {
                success = 0;
                break;
            }
        }
        if (!success) {
            printf("Invalid input.\n");
        }

    } while (!success);

    return number;
}

int main() {
    double aSide, bSide, cSide;
    double square;
    double perimeter, semiPerimeter;
    int choice;

    do {
        do {

            printf("1 - Start program\n2 - Exit\n");
            if (scanf("%d", &choice) != 1) {
                while (getchar() != '\n');
                continue;
            }

        } while (choice != 1 && choice != 2);

        if (choice == 2) return 0;

        aSide = get_valid_double('A');

        bSide = get_valid_double('B');

        cSide = get_valid_double('C');

        if (aSide + bSide > cSide && aSide + cSide > bSide && bSide + cSide > aSide) {


            perimeter = aSide + bSide + cSide;
            printf("\nperimeter = %f\n\n", perimeter);


            semiPerimeter = perimeter / 2;
            square = sqrt(semiPerimeter * (semiPerimeter - aSide) * (semiPerimeter - bSide) * (semiPerimeter - cSide));
            printf("square = %f\n\n", square);


            double aHeight, bHeight, cHeight;
            aHeight = (2.0 * square) / aSide;
            bHeight = (2.0 * square) / bSide;
            cHeight = (2.0 * square) / cSide;
            printf("Height A = %f\n", aHeight);
            printf("Height B = %f\n", bHeight);
            printf("Height C = %f\n\n", cHeight);


            double aBisector, bBisector, cBisector;
            aBisector = (2.0 * sqrt(bSide * cSide * semiPerimeter * (semiPerimeter - aSide))) / (bSide + cSide);
            bBisector = (2.0 * sqrt(cSide * aSide * semiPerimeter * (semiPerimeter - bSide))) / (cSide + aSide);
            cBisector = (2.0 * sqrt(aSide * bSide * semiPerimeter * (semiPerimeter - cSide))) / (aSide + bSide);
            printf("Bisector A = %f\n", aBisector);
            printf("Bisector B = %f\n", bBisector);
            printf("Bisector C = %f\n\n", cBisector);


            double aMedian, bMedian, cMedian;
            aMedian = 0.5 * sqrt(2 * bSide * bSide + 2 * cSide * cSide - aSide * aSide);
            bMedian = 0.5 * sqrt(2 * aSide * aSide + 2 * cSide * cSide - bSide * bSide);
            cMedian = 0.5 * sqrt(2 * aSide * aSide + 2 * bSide * bSide - cSide * cSide);
            printf("Median AM = %f\n", aMedian);
            printf("Median BM = %f\n", bMedian);
            printf("Median CM = %f\n", cMedian);

        } else {
            printf("This triangle doesn't exist\n");
        }

    } while (choice != 2);


    return 0;
}
