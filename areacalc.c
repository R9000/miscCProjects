/*
ACS126 - Lab 5
areacalc.c - Allows the user to define dimensions for a shape, and calculates the area.
By Rory Charlesworth
*/

#include <stdio.h>
#include <Math.h>

float rectanglearea(float length, float width);
float circlearea(float radius);
float trianglearea(float base, float height);

int main(){
    char shapename[50];
    float length, width, radius, base, height;
    while(1){
        printf("Hello! Please enter a shape name to get started. Choose from 'Rectangle', 'Circle', or 'Triangle'.\nYou can also type 'Exit' to exit.\n");
        scanf("%s", shapename);
        
        if(strcmp(shapename, "Rectangle") == 0)
        {
         printf("Please enter the length of your rectangle.\n");
         scanf("%f", &length);
         printf("Please enter the width of your rectangle.\n");
         scanf("%f", &width);
         printf("Your rectangle's area is %.2f cm squared.\n", rectanglearea(length, width));
         system("pause");
        }
        else if(strcmp(shapename, "Circle") == 0)
        {
             printf("Please enter the radius of your circle.\n");
             scanf("%f", &radius);
             printf("Your circle's area is %.2f cm squared.\n", circlearea(radius));
             system("pause");
        }
        else if(strcmp(shapename, "Triangle") == 0)
        {
             printf("Please enter the base of your triangle.\n");
             scanf("%f", &base);
             printf("Please enter the height of your triangle.\n");
             scanf("%f", &height);
             printf("Your triangle's area is %.2f cm squared.\n", trianglearea(base, height));
             system("pause");
        }
        else if(strcmp(shapename, "Exit") == 0){
             printf("Exited.\n");
             break;
        }
        else{printf("Please enter a valid option. This program is case-sensitive.\n");}
    }
    system("pause");
}

float rectanglearea(float length, float width){
      return length*width;
}
      
float circlearea(float radius){
      return M_PI*pow(radius, 2);
}

float trianglearea(float base, float height){
      return (base*height)/2;
}
