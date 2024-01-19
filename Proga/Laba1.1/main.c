#include <stdio.h>

int main(){
    long choice;

    do
    {
        printf("1 - Convert num\n2 - Exit\n");
        scanf("%ld",&choice);

        if(choice == 1) {
            int num;

            do {
                printf("Enter a number (1-3999): ");
                scanf("%d", &num);

                if (num <= 0 || num > 3999) {
                    printf("Invalid input. Please enter a number between 1 and 3999.\n");
                }

            } while (num <= 0 || num > 3999);

            int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
            const char* romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

            printf("Roman Numeral: ");
            for (int i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
                while (num >= values[i]) {
                    printf("%s", romanNumerals[i]);
                    num -= values[i];
                }
            }

            printf("\n");
        }

    }while(choice != 2);
}

