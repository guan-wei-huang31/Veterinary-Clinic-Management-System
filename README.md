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