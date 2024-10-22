/*/////////////////////////////////////////////////////////////////////////
                      Veterinary-Clinic-Management-System
Author     : Guan-Wei Huang
Email      : gwhuang24@gmail.com

Copyright 2024 Guan-Wei Huang
All rights reserved.

This project, including all source code and associated documentation files, 
is the intellectual property of Lynn Lin. Unauthorized copying, distribution, 
modification, or use of any part of this software, in whole or in part, without 
explicit written permission from the copyright owner is strictly prohibited.

This software is provided "as is" without warranty of any kind, express or implied, 
including but not limited to the warranties of merchantability, fitness for a 
particular purpose, and noninfringement. In no event shall the copyright holder be 
liable for any claim, damages, or other liability, whether in an action of contract, 
tort, or otherwise, arising from, out of, or in connection with the software or the 
use or other dealings in the software.
/////////////////////////////////////////////////////////////////////////*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "core.h"
#include <string.h>

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

void clearInputBuffer(void) {
    while (getchar() != '\n') {
        ;
    }
}

void suspend(void) {
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

int inputInt(void) {
    char newline = 'x';
    int value = 0;
    do {
        scanf("%d%c", &value, &newline);
        if (newline != '\n') {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
    } while (newline != '\n');
    return value;
}

int inputIntPositive(void) {
    int value;
    do {
        value = inputInt();
        if (value <= 0) {
            printf("ERROR! Value must be > 0: ");
        }
    } while (value <= 0);
    return value;
}
int inputIntRange(int min, int max)
{
    int value;
    do {
        value = inputInt();
        if (value < min || value > max) {
            printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
        }
    } while (value < min || value > max);
    return value;
}

char inputCharOption(const char str[]) {
    char inputChar, newline;
    int flag = 1;
    while (flag) {
        scanf(" %c%c", &inputChar, &newline);
        if (newline == '\n' && strchr(str, inputChar) != NULL) {
            flag = 0;
        }
        else {
            printf("ERROR: Character must be one of [%s]: ", str);
            clearInputBuffer();
        }
    }
    return inputChar;
}

void inputCString(char* str, int min, int max) {
    char temp[30];
    int flag = 1;
    do {
        scanf(" %[^\n]", str);
        int strlength = strlen(str);
        if (strlength < min || strlength > max) {
            if (min == max) {
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
            else if (strlength > max) {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
        }
        else {
            flag = 0;
            strncpy(str, temp, strlength);
            str[strlength] = '\0';
        }
        clearInputBuffer();
    } while (flag);
}

void displayFormattedPhone(const char* str) {
    int i;
    if (str == NULL) {
        printf("(___)___-____");
        return;
    }
    for (i = 0; i < 10; i++) {
        if (str[i] < 48 || str[i] > 57 || str[10] != '\0') {
            printf("(___)___-____");
            return;
        }
    }
    printf("(%c%c%c)%c%c%c-%c%c%c%c",
        str[0], str[1], str[2],
        str[3], str[4], str[5],
        str[6], str[7], str[8], str[9]);
}