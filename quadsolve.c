/*
ACS126 - Lab 4
quadsolve2.c - Allows the user to define three coefficients for a quadratic equation, and solves it.
By Rory Charlesworth
*/

#include <stdio.h>
#include <Math.h>

int main() {
    float A, B, C;
    int x[50], i;
    
    while(1)
    {
            printf("Please input a floating-point value for the coefficient of x^2, which is > -1.0.\n");
            scanf("%f", &A);
            if(A > -1.0) break;
            printf("Your number did not meet the conditions specified.\n");
    }
    while(1)
    {
            printf("Please input a floating-point value for the coefficient of x, which is between -10.0 and 10.0 (exclusive).\n");
            scanf("%f", &B);
            if(B > -10.0 && B < 10.0) break;
            printf("Your number did not meet the conditions specified.\n");
    }
    while(1)
    {
            printf("Please input a floating-point value, which is < 0.1.\n");
            scanf("%f", &C);
            if(C < 0.1) break;
            printf("Your number did not meet the conditions specified.\n");
    }
    
    printf("\nYour quadratic equation is: %fx^2 + %fx + %f\n", A, B, C);
    
    printf(" x    y(x)\n---  ------\n");
    
    for(i = 0; i<50; i++)
    {
        x[i] = i;
        printf(" %d    %.1f\n", x[i], (A*(pow(x[i], 2)) + B*x[i] + C));
    }
    
    system("pause");
}
