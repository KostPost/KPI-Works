#include <stdio.h>
#include <math.h>


int main() {
    double aSide, bSide = 0, cSide = 0;
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

        printf("Enter length for a side: ");
        scanf("%lf", &aSide);

        printf("Enter length for b side: ");
        scanf("%lf", &bSide);

        printf("Enter length for c side: ");
        scanf("%lf", &cSide);

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
