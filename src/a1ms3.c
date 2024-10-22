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
#include <stdio.h>
#include "clinic.h"

#define MAX_PETS 20
#define MAX_APPOINTMENTS 50

int main(void)
{
    struct Patient pets[MAX_PETS] = { {0} };
    struct Appointment appoints[MAX_APPOINTMENTS] = { {0} };
    struct ClinicData data = { pets, MAX_PETS, appoints, MAX_APPOINTMENTS };

    int patientCount = importPatients("./data/patientData.txt", pets, MAX_PETS);
    int appointmentCount = importAppointments("./data/appointmentData.txt", appoints, MAX_APPOINTMENTS);

    printf("Imported %d patient records...\n", patientCount);
    printf("Imported %d appointment records...\n\n", appointmentCount);

    menuMain(&data);
    
    return 0;
}