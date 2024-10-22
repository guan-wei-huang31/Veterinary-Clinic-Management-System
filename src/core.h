//////////////////////////////////////////////////////////////////////////
//                        Assignment 1 - Milestone 3
//Full Name  : Guan-Wei Huang
//////////////////////////////////////////////////////////////////////////
//Veterinary - Clinic - Management - System
//Author : Guan - Wei Huang
//Email : gwhuang24@gmail.com
//
//Copyright 2024 Guan - Wei Huang
//All rights reserved.
//
//This project, including all source code and associated documentation files,
//is the intellectual property of Lynn Lin.Unauthorized copying, distribution,
//modification, or use of any part of this software, in whole or in part, without
//explicit written permission from the copyright owner is strictly prohibited.
//
//This software is provided "as is" without warranty of any kind, express or implied,
//including but not limited to the warranties of merchantability, fitness for a
//particular purpose, and noninfringement.In no event shall the copyright holder be
//liable for any claim, damages, or other liability, whether in an action of contract,
//tort, or otherwise, arising from, out of, or in connection with the software or the
//use or other dealings in the software.
/////////////////////////////////////////////////////////////////////////
#ifndef CORE_H
#define CORE_H

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////
void clearInputBuffer(void);
void suspend(void);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
int inputInt(void);
int inputIntPositive(void);
int inputIntRange(int, int);
char inputCharOption(const char str[]);
void inputCString(char* str, int, int);
void displayFormattedPhone(const char *str);

#endif // !CORE_H