/* This is the program designed in C for finding :
    1. Resistance of the given color code
    2. Color code based on given resistance
*/

#include<stdio.h>
#include<stdlib.h>

#include"HeaderProto.h"

//Macors Used
#define MENU_ITEM_SIZE 3


char colorList[13][20]={"BLACK","BROWN","RED","ORANGE","YELLOW","GREEN","BLUE","VIOLET","GREY","WHITE","GOLD","SILVER","NO"};

//Global Variable Decleartion
char MenuList[MENU_ITEM_SIZE][25]={"3 Band Resistor","4 Band Resistor","5 Band Resistor"};
char SubMenuStr[2][50]={"Color Code -> Equivalent Resistance","Equivalent Resistance -> Color Code"};

int ColorInputField[MENU_ITEM_SIZE]={3,4,5};

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
    system("clear");
}


void displayMenu()
{
    welcomeUser();
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
        goToMenuNumber(menuChoice);
    }
}


void showSubMenu(int menuChoice)
{
    int subChoice=0;
    printf("\n");
    stringInDesign("Choose from below : (Given || To Calcualte)");
    printf("1. Color Code || Equivalent Resitance\n");
    printf("2. Equivalent Resistance || Color Code\n");

    printf("\nYour Choice : ");
    scanf("%d",&subChoice);
    subMenuFor(menuChoice,subChoice);
}

void subMenuFor(int menuCh, int subCh)
{
    printf("\nYou have selected %c band resitor\n",MenuList[menuCh-1][0]);
    printf("\n%s Calculator\n",SubMenuStr[subCh-1]);
    if(subCh==1)
    {
        getInputForSubOne(menuCh);
    }
    else if(subCh==2)
    {
        getInputForSubTwo(menuCh);
    }
}

void updateToUpperCase(char* s)
{
    int index=0;
    while(s[index]!='\0')
    {
        if(s[index]<=122 && s[index]>=97)
        {
            s[index]=s[index]-32;
        }
        index++;
    }
}

void displayColorName()
{
    for(int i=0;i<13;i++)
    {
        printf("%s ",colorList[i]);
    }
}

int findColorCodeNumber(char *s)
{
    int isMatched=0;
    for(int i=0;i<13;i++)
    {
        isMatched=compareString(colorList[i],s);
        if(isMatched)
        {
            return i;
        }
    }
}

int compareString(char* str1, char* str2)
{
    int index=0;
    while(str1[index]!='\0' && str2[index]!='\0')
    {
        if(str1[index]!=str2[index])
        {
            return 0;
        }
        else
        {
            index++;
        }
    }
    return 1;
}

float getPower(int base, int power)
{
    float temp=1;
    int tempbase=base;
    if(power>=0)
    {
        for(int i=0;i<power;i++)
        {
            temp=temp*tempbase;
        }
    }
    else if(power<0)
    {
        for(int i=power;i<0;i++)
        {
            temp=temp/tempbase;
        }
    }
    return temp;
}

void findEquivalentResistance(int field[], int maxIndex, float* ans)
{
    float temp=0;
    for(int i=0;i<maxIndex-2;i++)
    {
        temp=temp*10+field[i];
    }
    //multipier of resistance//
    if(field[maxIndex-2]>9 && field[maxIndex-2]<13)
    {
        if(field[maxIndex-2]==10)
        temp=temp*getPower(10,-1);
        else if(field[maxIndex-2]==11)
        temp=temp*getPower(10,-2);
    }
    else
    {
        temp=temp*getPower(10,field[maxIndex-2]);

    }
    *ans=temp;
}

int findColorTolerance(int number)
{
    if(number==12)
    {
        return 20;
    }
    else if(number==11)
    {
        return 10;
    }
    else if(number==10)
    {
        return 5;
    }
}


void getInputForSubOne(int menuCh)
{
    float answer=0;
    float *ans=&answer;
    char colorName[15];
    int inputField=ColorInputField[menuCh-1];
    int colorArr[inputField];
    int tolerance;

    char cont;

    stringInDesign("Input Color Code");
    printf("\nNote: from left to right. Case Insensetive");
    printf("\n-- Hint : ");
    displayColorName();
    printf(" --\n");

    for(int i=0;i<inputField;i++)
    {
        if(i==inputField-1 && menuCh!=1)
        {
            printf("\nTolerance Only Color : (GOLD, SILVER, NO)");
        }
        printf("\nColor %d : ",i+1);
        scanf("%s",colorName);
        updateToUpperCase(colorName);
        colorArr[i]=findColorCodeNumber(colorName);
        printf("Inputed Color : %s - Value is :%d\n",colorName,colorArr[i]);
    }
    // For 3 band tolerance is no color so adjusting//
    if(menuCh==1)
    {
        findEquivalentResistance(colorArr,inputField+1,ans);
        tolerance=20;
    }
    else
    {
        findEquivalentResistance(colorArr,inputField,ans);
        tolerance=findColorTolerance(colorArr[inputField-1]);
    }
        printf("\nFor %d band resitor of above given color",inputField);
        printf("\nEquivalent resistance is : (%.2f ± %d per) ohm",answer,tolerance);
    
    printf("\nDo you want to continue again : (Y/N) ");
    scanf(" %c",&cont);
    if(cont=='Y' || cont == 'y')
    {
        clearScreen();
        displayMenu();
    }
}

void getInputForSubTwo(int menuCh)
{
    int resisValue;
    int tolValue;
    int rem=0;

    int maxIndex=ColorInputField[menuCh-1];

    char colorCode[maxIndex][10];

    stringInDesign("Input Equivalent Reistance");
    printf("\nNote : In format (Value Then Tolerance)\n");
    printf("Enter the Reistance Value Only : ");
    scanf("%d",&resisValue);
    printf("Enter Tolerance Value Only : ");
    scanf("%d",&tolValue);
    
    int colorQuant=menuCh;

    for(int i=0;i<maxIndex-2;i++)
    {
        rem=resisValue%10;
        resisValue=resisValue/10;
    }

    if(menuCh==3)
    {
        
    }
}

void goToMenuNumber(int number)
{
    int temp;
    stringInDesign(MenuList[number-1]); 
    showSubMenu(number);
}

void main()
{
    displayMenu();
}


