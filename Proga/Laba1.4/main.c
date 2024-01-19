#include <stdio.h>
#include <math.h>
#include <malloc.h>


double factorial(int n) {
    return (n == 0 || n == 1) ? 1.0 : n * factorial(n - 1);
}

double taylorSin(double x, double epsilon) {
    double result = x;
    double term = x;
    int i = 1;

    while (fabs(term) >= epsilon) {
        term = pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
        result += term;
        i++;
    }

    return result;
}

double taylorCos(double x, double epsilon) {
    double result = 1.0;
    double term = 1.0;
    int i = 1;

    while (fabs(term) >= epsilon) {
        term = pow(-1, i) * pow(x, 2 * i) / factorial(2 * i);
        result += term;
        i++;
    }

    return result;
}

void FindTayolrs() {
    double startX = 1, endX = 7, dx = 1, epsilon = 0.1, x;
    int choice;

    do {
        printf("1 - sin\n2 - cos\n ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("\"You need to enter 1 or 2\\n\");\n");
            continue;
        }
    } while (choice != 1 && choice != 2);


    printf("Enter start X: ");
    scanf("%lf", &startX);

    printf("Enter end X: ");
    scanf("%lf", &endX);

    printf("Enter end dx: ");
    scanf("%lf", &dx);

    printf("Enter end Epsilon: ");
    scanf("%lf", &epsilon);


    if (choice == 1) {

        double count, mustBe;
        if (startX > endX) {
            mustBe = endX - 1;
            count = startX;
            dx *= -1;
        } else {
            mustBe = endX + 1;
            count = startX;

        }

        printf("\n");
        printf("x\t\t\tsin\t\t\tsin(Taylor)\tsin - sin(Taylor)\n");

        while (count != mustBe) {

            x = count * M_PI / 180;
            double sinValue = taylorSin(x, epsilon);
            printf("%f\t", count);
            printf("%f\t", sinValue);
            printf("%f\t", sin(x));
            printf("%f", sinValue - sin(x));
            printf("\n");


            count += dx;
        }
    } else if (choice == 2) {


        double count, mustBe;
        if (startX > endX) {
            mustBe = endX - 1;
            count = startX;
            dx *= -1;
        } else {
            mustBe = endX + 1;
            count = startX;
            dx = 1;
        }


        printf("\n");
        printf("x\t\t\tcos\t\t\tcos(Taylor)s\tcos - cos(Taylor)\n");

        while (count != mustBe) {

            x = count * M_PI / 180;
            double cosValue = taylorCos(x, epsilon);
            printf("%f\t", count);
            printf("%f\t", cosValue);
            printf("%f\t", cos(x));
            printf("%f", cosValue - cos(x));
            printf("\n");


            count += dx;
        }
    }

}

void Sorting() {
    float *nums = NULL;

    size_t size = 0;
    int choiceSize = 0;
    float newElement;

    do {
        printf("Choice amount of elements: ");
        scanf("%d", &choiceSize);

        size = choiceSize;
        nums = (float *) realloc(nums, size * sizeof(float));

    } while (choiceSize <= 1);

    int element = 0;
    do {
        printf("Enter a num to Array: ");
        scanf("%f", &newElement);
        nums[element] = newElement;
        element++;
        printf("\n");
    } while (element < size);

    for (int x = 0; x < size; x++) {
        printf("%1f   ", nums[x]);
    }
    printf("\n\n");

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {

            if (nums[i] > nums[j]) {
                float temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }

        }
        for (int x = 0; x < size; x++) {
            printf("%1f   ", nums[x]);
        }
        printf("\n\n");

    }
    free(nums);
}

int main() {


    int choice;

    do {
        printf("1 - Find Taylor\n2 - Sorting\n3 - Exit\n");
        scanf("%d",&choice);

        switch (choice) {

            case 1:
                FindTayolrs();
                break;


            case 2:
                Sorting();
                break;
        }


    } while (choice != 3);

    return 0;
}















