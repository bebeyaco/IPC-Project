/*
*****************************************************************************
                        Assignment 1 - Milestone 2
Full Name  : Carlos Enrique Gonzalez Leon
Student ID#: 154179212
Email      : cgonzalez-leon@gmail.com
Section    : ZEE

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING 20
#include <stdio.h>
#include <string.h>

// As demonstrated in the course notes: 
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer 
// Clear the standard input buffer 
void clearInputBuffer(void) 
{ 
    // Discard all remaining char's from the standard input buffer: 
    while (getchar() != '\n') 
    {
        ; // do nothing! 
    }
}

// Wait for user to input the "enter" key to continue 
void suspend(void) 
{ 
    printf("<ENTER> to continue...");
    clearInputBuffer(); 
    putchar('\n'); 
}

int inputInt(void)
{
    
    int value = 0;
    char newLine = ' ';
    while (newLine != '\n')
    {
        scanf("%d%c", &value, &newLine);
        
        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        
    }
    return value;
    
}

int inputIntPositive(void)
{
    int value = -1;
    while (value < 0)
    {
        value = inputInt();
        if (value < 0)
        {
            printf("ERROR! Value must be > 0: ");
            value = inputInt();
        }
        


    }
    return value;

}

int inputIntRange (int min, int max)
{
    int value = min - 1;
    while (!(value >= min && value <= max))
    {
        value = inputInt();
        if (!(value >= min && value <= max))
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
        }
        
    }
    return value;
}

char inputCharOption(const char list[])
{
    char value;
    int valid = 0;
    size_t size = sizeof(list) / sizeof(list[0]);
    int i;
    while (valid == 0)
    {
        scanf(" %c", &value);
        for (i = 0; i < size; i++)
        {
            if (list[i] == value)
            {
                valid = 1;
            } 
        }
        if (valid == 0)
        {
            printf("ERROR: Character must be one of [%s]: ", list);
        }
        
    }

    return value;
}

void inputCString(char* value, int min, int max)
{
    char inputSTR[MAX_STRING] = { 0 };
    int red = 0;
    int i = 0;

    while (red == 0)
    {
        scanf(" %[^\n]%*c", inputSTR);
 
        int len = strlen(inputSTR);
        int red2 = 0;

        while (red2 == 0) {
            if (inputSTR[len] != '\0') {
                ++len;
            }
            else {
                red2 = 1;
            }
        }

        if (min == max)
        {
            if ((len < min) || (len > max))
            {
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
            else
            {
                red = 1;
            }
        }
        else if (min != max)
        {
            if (len < min)
            {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
            else if (len > max)
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else
            {
                red = 1;
            }
        }
    }
    strcpy(value, inputSTR);

}

    

void displayFormattedPhone(const char* phone)
{
    int index = 0;

    while (&phone[index] != '\0') 
    {
        if (phone[index] >= '0' && phone[index] <= '9')
        {
            index++;
        }
        else 
        {
            break;
        }
    }

    if (index == 10) {
        printf("(%c%c%c)%c%c%c-%c%c%c%c", phone[0], phone[1], phone[2], phone[3], phone[4], phone[5], phone[6], phone[7], phone[8], phone[9]);
    }
    else {
        printf("(___)___-____");
    }
}

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

