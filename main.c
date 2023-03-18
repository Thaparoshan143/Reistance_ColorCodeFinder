/* This is the program designed in C for finding :
    1. Resistance of the given color code
    2. Color code based on given resistance
*/

#include<stdio.h>
#include<stdlib.h>

//Macors Used
#define MENU_ITEM_SIZE 3


//enum
typedef enum
{
    black,
    brown,
    red,
    orange,
    yellow,
    green,
    blue,
    violet,
    grey,
    white
}ResColorCode;

typedef enum
{
    nocolor,
    gold,
    silver
}Tolerance;

//Global Variable Decleartion
char MenuList[MENU_ITEM_SIZE][15]={"3 Band","4 Band","5 Band"};


// Other Helper Functions//

void stringInDesign(char* str)
{
    printf("===> ");
    printf("%s",str);
    printf(" <===\n");
}

// Main Sub Functions
void welcomeUser()
{
    stringInDesign("Welcome to this program");
}

void clearScreen()
{
    clrscr();
}


void displayMenu()
{
    int menuChoice=0;
    printf("\t");
    stringInDesign("Menu");
    stringInDesign("Resistor Band Size");
    for(int i=0;i<MENU_ITEM_SIZE;i++)
    {
        printf("%d. %s\n",i+1,MenuList[i]);
    }
    printf("Choose the menu based on band size : ");
    scanf("%d",&menuChoice);
    if(menuChoice<0 || MENU_ITEM_SIZE-menuChoice<0)
    {
        printf("Inccorect choice. Try again!");
    }
    else
    {
        clearScreen();
    }
}

void main()
{
    welcomeUser();
    displayMenu();

}


