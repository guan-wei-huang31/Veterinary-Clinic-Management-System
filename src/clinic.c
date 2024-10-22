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
#include <string.h>
#include "core.h"
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);
            suspend();
            break;
        }
    } while (selection);
}

void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    int i, found=0;
    displayPatientTableHeader();
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);
            found++;
        }
    }
    if (found == 0) {
        printf("*** No records found ***\n");
    }
    putchar('\n');
}

void searchPatientData(const struct Patient patient[], int max) {
    int userSelect, flag;
    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        userSelect = inputIntRange(0, 2);
        putchar('\n');
        switch (userSelect) {
        case 1:
            searchPatientByPatientNumber(patient, max);
            flag = 1;
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            flag = 1;
            break;
        default:
            flag = 0;
            break;
        }
        if (flag == 1) {
            putchar('\n');
            suspend();
        }
    } while (userSelect != 0);
}

void addPatient(struct Patient patient[], int max) {
    int result = findPatientIndexByPatientNum(0, patient, max);
    if (result == -1) {
        printf("ERROR: Patient listing is FULL!\n");
    }
    else {
        int nextNo = nextPatientNumber(patient, max);
        patient[result].patientNumber = nextNo;
        inputPatient(&patient[result]);
        printf("*** New patient record added ***\n");
    }
    putchar('\n');
}

void editPatient(struct Patient patient[], int max) {
    printf("Enter the patient number: ");
    int inputNo = inputInt();
    putchar('\n');
    int position = findPatientIndexByPatientNum(inputNo, patient, max);
    if (position == -1) {
        printf("ERROR: Patient record not found!\n");
    }
    else {
        menuPatientEdit(&patient[position]);
    }
}

void removePatient(struct Patient patient[], int max) {
    char userSelect;
    printf("Enter the patient number: ");
    int inputNo = inputInt();
    putchar('\n');
    int position = findPatientIndexByPatientNum(inputNo, patient, max);
    if (position == -1) {
        printf("ERROR: Patient record not found!\n");
    }
    else {
        displayPatientData(&patient[position], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        userSelect = inputCharOption("yn");
        if (userSelect == 'n') {
            printf("Operation aborted.\n");
        }
        else {
            *patient[position].name = 0;
            patient[position].patientNumber = 0;
            *patient[position].phone.description = 0;
            *patient[position].phone.number = 0;
            printf("Patient record has been removed!\n");
        }
    }
    putchar('\n');
}

int compareDates(struct Date d1, struct Date d2) {
    int value;
    if (d1.year != d2.year) {
        value = d1.year - d2.year;
    }
    else if (d1.month != d2.month) {
        value = d1.month - d2.month;
    }
    else {
        value = d1.day - d2.day;
    }
    return value;
}
void swap(struct Appointment* a, struct Appointment* b) {
    struct Appointment t = *a;
    *a = *b;
    *b = t;
}
int compareTimes(struct Time t1, struct Time t2) {
    int value;
    if (t1.hour != t2.hour) {
        value = t1.hour - t2.hour;
    }
    else {
        value = t1.min - t2.min;
    }
    return value;
}

int partition(struct Appointment arr[], int low, int high) {
    struct Appointment pivot = arr[high];
    int i = (low - 1);
    int j;
    for (j = low; j <= high - 1; j++) {
        if (compareDates(arr[j].date, pivot.date) < 0 ||
            (compareDates(arr[j].date, pivot.date) == 0 && compareTimes(arr[j].time, pivot.time) < 0)) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(struct Appointment arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void inputDate(struct Date* date, struct Time* time, int flagDate, int flagTime) {
    int days;
    if (flagDate) {
        printf("Year        : ");
        date->year = inputIntPositive();
        printf("Month (%d-%d): ", 1, 12);
        date->month = inputIntRange(1, 12);
        printf("Day (%d-", 1);
        if (date->month == 1 || date->month == 3 || date->month == 5 || date->month == 7 || date->month == 8 || date->month == 10 || date->month == 11) {
            days = 31;
        }
        else if (date->year % 4 == 0 && date->month == 2) {
            days = 29;
        }
        else if (date->month == 2){
            days = 28;
        }
        else {
            days = 30;
        }
        printf("%d)  : ", days);
        date->day = inputIntRange(1, days);
    }
    if (flagTime) {
        printf("Hour (%d-%d)  : ", 0, 23);
        time->hour = inputIntRange(0, 23);
        printf("Minute (%d-%d): ", 0, 59);
        time->min = inputIntRange(0, 59);
    }
}

int getAvailiableAppointmentIndex(struct Appointment* appointments, int maxAppointments) {
    int i, position, flag = 1;
    for (i = 0; i < maxAppointments && flag == 1; i++) {
        if (appointments[i].patientID == 0) {
            position = i;
            flag = 0;
        }
    }
    return position;
}

void viewAllAppointments(struct ClinicData* data) {
    int i, j, number=0;
    for (i = 0; i < data->maxAppointments; i++) {
        if (data->appointments[i].patientID != 0) {
            data->appointments[number++] = data->appointments[i];
        }
    }
    quickSort(data->appointments, 0, number - 1);
    displayScheduleTableHeader(NULL, 1);
    
    for (i = 0; i < number; i++) {
        struct Patient* patient = NULL;
        int flag = 1;
        for (j = 0; j < data->maxPatient && flag == 1; j++) {
            if (data->patients[j].patientNumber == data->appointments[i].patientID) {
                patient = &data->patients[j];
                flag = 0;
            }
        }
        if (patient != NULL) {
            displayScheduleData(patient, &data->appointments[i], 1);
        }
    }
    putchar('\n');
}

void viewAppointmentSchedule(struct ClinicData* data) {
    int i, j, number = 0;
    struct Date date;
    inputDate(&date, NULL, 1, 0);
    putchar('\n');
    displayScheduleTableHeader(&date, 0);
    for (i = 0; i < data->maxAppointments; i++) {
        if (data->appointments[i].patientID != 0) {
            number++;
        }
    }
    quickSort(data->appointments, 0, number - 1);
    for (i = 0; i < data->maxAppointments; i++){
        for (j = 0; j < data->maxPatient; j++) {
            if (data->appointments[i].patientID == data->patients[j].patientNumber) {
                if (date.year == data->appointments[i].date.year && date.month == data->appointments[i].date.month && date.day == data->appointments[i].date.day) {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                }
            }
        }
    }
    putchar('\n');
}

void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient){
    int currentTotal, flag = 1;
    for (currentTotal = 0; currentTotal < maxAppointments && flag == 1; currentTotal++) {
        if (appointments[currentTotal].patientID == 0) {
            flag = 0;
        }
    }
    if (currentTotal < maxAppointments) {
        int availiable;
        do {
            int i, flag1 = 1;
            availiable = getAvailiableAppointmentIndex(appointments, maxAppointments);
            printf("Patient Number: ");
            appointments[availiable].patientID = inputIntPositive();
            if (availiable != -1) {
                do {
                    int valid = 1;
                    inputDate(&appointments[availiable].date, &appointments[availiable].time, 1, 1);
                    for (i = 0; i < availiable && valid == 1; i++) {
                        if (appointments[availiable].date.year == appointments[i].date.year && appointments[availiable].date.month == appointments[i].date.month
                            && appointments[availiable].date.day == appointments[i].date.day && appointments[availiable].time.hour == appointments[i].time.hour
                            && appointments[availiable].time.min == appointments[i].time.min) {
                            valid = 0;
                        }
                    }
                    if (valid == 0) {
                        printf("\nERROR: Appointment timeslot is not available!\n");
                        putchar('\n');
                    }
                    else {
                        while (appointments[availiable].time.hour < START_TIME || appointments[availiable].time.hour > END_TIME || (appointments[availiable].time.hour == END_TIME
                            && appointments[availiable].time.min > 0) || appointments[availiable].time.min % MIN_INTERVAL != 0) {
                            printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n");
                            putchar('\n');
                            inputDate(NULL, &appointments[availiable].time, 0, 1);
                        }
                        flag1 = 0;
                        printf("\n*** Appointment scheduled! ***\n\n");
                    }
                } while (flag1);
            }
            else {
                printf("ERROR: Patient record not found!\n\n");
            }
        } while (availiable == -1);
    }
    else {
        printf("ERROR: Appointment listing is FULL!\n");
        putchar('\n');
    }
}

void removeAppointment(struct Appointment* appoints, int maxAppointments, struct Patient* patients, int maxPatient) {
    struct Date date;
    int patientID, checkID, i = 0, flag = 1, patientIndex;
    printf("Patient Number: ");
    patientID = inputIntPositive();
    checkID = findPatientIndexByPatientNum(patientID, patients, maxAppointments);
    if (checkID != -1) {
        inputDate(&date, NULL, 1, 0);
        for (i = 0; i < maxAppointments && flag == 1; i++) {
            if (patientID == appoints[i].patientID && date.year == appoints[i].date.year && date.month == appoints[i].date.month && date.day == appoints[i].date.day)
                flag = 0;
        }
        patientIndex = i - 1;
        putchar('\n');
        if (patientIndex > -1) {
            displayPatientData(&patients[checkID], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");
            if (inputCharOption("yn") == 'y')
                appoints[patientIndex].patientID = '\0';
            printf("\nAppointment record has been removed!\n\n");
        }
    }
    else {
        printf("ERROR: Patient record not found!\n\n");
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    printf("Search by patient number: ");
    int value = inputInt();
    int result = findPatientIndexByPatientNum(value, patient, max);
    putchar('\n');
    if (result == -1) {
        printf("*** No records found ***\n");
    }
    else {
        displayPatientData(&patient[result], FMT_FORM);
    }
}

void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    int i, found = 0;
    char patientPhoneNo[PHONE_LEN + 1];
    struct Patient temp[20] = { {0} };
    printf("Search by phone number: ");
    inputCString(patientPhoneNo, PHONE_LEN, PHONE_LEN);
    putchar('\n');
    for (i = 0; i < max; i++) {
        if (strcmp(patientPhoneNo, patient[i].phone.number) == 0) {
            temp[found++] = patient[i];
        }
    }
    displayPatientTableHeader();
    if (found == 0) {
        printf("\n*** No records found ***\n");
    }
    else {
        for (i = 0; i < found; i++) {
            displayPatientData(&temp[i], FMT_TABLE);
        }
    }
}

int nextPatientNumber(const struct Patient patient[], int max) {
    int i, maxNo = 0;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > maxNo) {
            maxNo = patient[i].patientNumber;
        }
    }
    return maxNo + 1;
}

int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {
    int i, flag = 1, value = -1;
    for (i = 0; i < max && flag == 1; i++) {
        if (patientNumber == patient[i].patientNumber) {
            flag = 0;
            value = i; 
        }
    }
    return value;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

void inputPatient(struct Patient* patient) {
    char inputPatientName[NAME_LEN+1];
    printf("Patient Data Input\n"
        "------------------\n"
        "Number: %05d\n"
        "Name  : ", patient->patientNumber);
    inputCString(inputPatientName, 1, NAME_LEN);
    strncpy(patient->name, inputPatientName, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

void inputPhoneData(struct Phone* phone) {
    char temp[30];
    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    int selection = inputIntRange(1, 4);
    if (selection != 4) {
        switch (selection) {
        case 1:
            strncpy(phone->description, "CELL", PHONE_DESC_LEN);
            break;
        case 2:
            strncpy(phone->description, "HOME", PHONE_DESC_LEN);
            break;
        case 3:
            strncpy(phone->description, "WORK", PHONE_DESC_LEN);
            break;
        default:
            break;
        }
        printf("\nContact: %s\n"
            "Number : ", phone->description);
        do {
            scanf(" %[^\n]", temp);
            clearInputBuffer();
            if (strlen(temp) != PHONE_LEN) {
                printf("Invalid 10-digit number! Number: ");
            }
            else
            {
                putchar('\n');
                strncpy(phone->number, temp, PHONE_LEN);
            }
        } while (strlen(temp) != PHONE_LEN);
    }
    else {
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);
        phone->number[0] = '\0';
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

int importPatients(const char* datafile, struct Patient patients[], int max) {
    int i = 0;
    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    if (fp != NULL) {
        do {
            fscanf(fp, "%d|%15[^|]|%4[^|]|%10[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number);
            i++;
        } while (!feof(fp) && i < max);
        fclose(fp);
    }
    else {
        printf("File open Unsuccessful!\n");
    }
    return i;
}

int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    int i = 0;
    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    if (fp != NULL) {
        do {
            fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientID, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min);
            i++;
        } while (!feof(fp) && i < max);
        fclose(fp);
    }
    else {
        printf("File open Unsuccessful!\n");
    }
    return i-1;
}