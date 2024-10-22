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

#ifndef CLINIC_H
#define CLINIC_H
#define FMT_FORM 1
#define FMT_TABLE 2
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10
#define START_TIME 10
#define END_TIME 14
#define MIN_INTERVAL 15
//////////////////////////////////////
// Structures
//////////////////////////////////////

struct Phone {
    char description[PHONE_DESC_LEN + 1];
    char number[PHONE_LEN + 1];
};

struct Patient {
    int patientNumber;
    char name[NAME_LEN + 1];
    struct Phone phone;
};

struct Time {
    int hour;
    int min;
};

struct Date {
    int year;
    int month;
    int day;
};

struct Appointment {
    int patientID;
    struct Date date;
    struct Time time;
};

struct ClinicData
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////
void displayPatientTableHeader(void);
void displayPatientData(const struct Patient* patient, int fmt);
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField);

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////
void menuMain(struct ClinicData* data);
void menuPatient(struct Patient patient[], int max);
void menuPatientEdit(struct Patient* patient);
void menuAppointment(struct ClinicData* data);
void displayAllPatients(const struct Patient patient[], int max, int fmt);
void searchPatientData(const struct Patient patient[], int max);
void addPatient(struct Patient patient[], int max);
void editPatient(struct Patient patient[], int max);
void removePatient(struct Patient patient[], int max);
void viewAllAppointments(struct ClinicData* data);
void viewAppointmentSchedule(struct ClinicData* data);
void addAppointment(struct Appointment* appointments, int maxAppointments,
    struct Patient* patients, int maxPatient);
void removeAppointment(struct Appointment* appointments, int maxAppointments,
    struct Patient* patients, int maxPatient);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
void searchPatientByPatientNumber(const struct Patient patient[], int max);
void searchPatientByPhoneNumber(const struct Patient patient[], int max);
int nextPatientNumber(const struct Patient patient[], int max);
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
void inputPatient(struct Patient* patient);
void inputPhoneData(struct Phone* phone);

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////
int importPatients(const char* datafile, struct Patient patients[], int max);
int importAppointments(const char* datafile, struct Appointment appoints[], int max);


#endif // !CLINIC_H