#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>



int Numbers(char roman_np_value)
{
    switch(roman_np_value)
    {
        case 'M':
            return 1000;

        case 'D':
            return 500;

        case 'C':
            return 100;

        case 'L':
            return 50;

        case 'X':
            return 10;

        case 'V':
            return 5;

        case 'I':
            return 1;
        default :
            return -1;
    }
}
int main()
{;

    printf("qwe");

    // long sum = 0,choice;
    // char RimNumToConvert[CHAR_MAX];
    // do
    // {
    //     printf("1 - Convert num\n2 - Exit\n");
    //     scanf("%ld",&choice);

    //     if(choice == 1) {

    //         printf("Enter a num to convert:");
    //         scanf("%30s",RimNumToConvert);
    //         sum = 0;
    //         for (int i = 0; RimNumToConvert[i] != '\0'; i++) {
    //             if(Numbers(RimNumToConvert[i]) == -1){
    //                 printf("\nYou wrote wrong symbol\n");
    //                 sum = 0;
    //                 break;
    //             }
    //             else if (Numbers(RimNumToConvert[i]) < Numbers(RimNumToConvert[i + 1])) {
    //                 sum = sum - Numbers(RimNumToConvert[i]);
    //             }
    //             else {
    //                 sum += Numbers(RimNumToConvert[i]);
    //             }
    //         }

    //         if(sum != 0) {
    //             printf("\nConverted num = %ld\n\n", sum);
    //         }
    //         sum = 0;
    //     }

    // }while(choice != 2);
}

