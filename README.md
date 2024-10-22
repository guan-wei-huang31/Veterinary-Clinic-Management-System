# **Veterinary Clinic Management System**

## **Project Overview**
This project is a **veterinary clinic management system** developed in **C language**. It aims to assist veterinarians in managing patient records and scheduling appointments. The system provides features for adding, searching, editing, and deleting patient information, as well as managing appointments.

---

## **Features**
- **Patient Management**:  
  - Add, edit, search, and delete patient information.
- **Appointment Management**:  
  - View appointments by date.
  - Add and cancel appointments with conflict detection.
- **Data Import**:  
  - Load patient and appointment data from files for batch management.
- **Sorting Algorithm**:  
  - Implements **Quicksort** to sort appointments by date and time.

---

## **Directory Structure**
```
Veterinary-Clinic-Management-System/ 
│ ├── src/                    # Source code files 
│    ├── a1ms3.c              # Main program entry point 
│    ├── clinic.c             # Clinic management implementation 
│    ├── core.c               # Core functions implementation 
│    ├── clinic.h             # Clinic function declarations 
│    └── core.h               # Core function declarations 
│ ├── data/                   # Data files 
│    ├── patientData.txt      # Patient data file 
│    └── appointmentData.txt  # Appointment data file 
├── Makefile                  # Build instructions 
├── README.md                 # Project documentation (this file) 
└── .gitignore                # Git ignore rules 
```


---

## **System Requirements**
- **Operating System**: Windows / Linux / macOS
- **C Compiler**: GCC or any compiler supporting the C11 standard
- **Make Tool** (optional): If using `Makefile` for compilation

---

## **Compilation and Execution**

### **Using Makefile:**
1. Open a terminal or command prompt in the project’s root directory.
2. Run:
   ```bash
   make
   ```
3. Execute the system:
   ```bash
   make run
   ```
4. Clean:
   ```bash
   make clean
   ```

### **Manual Compilation:**
If not using Makefile, compile manually with:
   ```bash
   gcc src/a1ms3.c src/clinic.c src/core.c -o bin/clinic_system
   ./bin/clinic_system
   ```

### **Data File Formats**
1. Patient Data (patientData.txt):
   ```
   1024|Shaggy Yanson|CELL|3048005191
   1032|Pugsley Yanson|CELL|3048005191
   ```
   - **Format**: PatientNumber | Name | ContactDescription | PhoneNumber
2. Appointment Data (appointmentData.txt):
   ```
   1040,2024,2,29,13,0
   1112,2027,3,12,13,0
   ```
   - **Format**: PatientNumber, Year, Month, Day, Hour, Minute

### **Usage Instructions**
1. After launching the system, you will see the main menu:
   ```
   Veterinary Clinic System
   =========================
   1) PATIENT     Management
   2) APPOINTMENT Management
   -------------------------
   0) Exit System
   -------------------------
   Selection:
   ```
2. Use the menu options to manage patients and appointments.

### **FAQ**
1. How to Avoid Appointment Conflicts?
   - The system checks for time conflicts when adding appointments to prevent overlapping bookings.
2. Unable to Load Patient or Appointment Data?
   - Make sure that patientData.txt and appointmentData.txt exist in the data/ directory and follow the correct format.
   
### **Future Plans**
- Add appointment reminder functionality.
- Improve the user interface with more interactive features.
- Develop a web-based or GUI version of the system.

### **Contact**
For questions or suggestions, feel free to contact:  
Email: gwhuang24@gmail.com

### **Conclusion**
Thank you for using the Veterinary Clinic Management System! We hope this system helps you effectively manage patient records and clinic appointments. If you have any feedback or suggestions, please don’t hesitate to reach out.