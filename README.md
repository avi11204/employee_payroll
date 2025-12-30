# Payroll Management System (C++)

A file-based Payroll Management System implemented in C++ using OOP concepts.

## Features
- Role-based login (Admin & Employee)
- Employee management (CRUD)
- Attendance tracking
- Payroll calculation
- File-based storage (No SQL)
- Secure login with hashed passwords

## Roles
### Admin
- Add / update employees
- Add / update attendance
- Generate payroll
- View all payroll records

### Employee
- View own profile
- View own attendance
- View own payroll


## UML Diagram

<img width="1122" height="488" alt="image" src="https://github.com/user-attachments/assets/8c836f65-1fca-4389-bcce-5980c49d75f4" />

## WORKFLOW Diagram

<img width="5112" height="4052" alt="image" src="https://github.com/user-attachments/assets/45fc61c7-8b52-4ea4-bd76-e21a1187c491" />


## Technologies Used
- C++
- STL (vector, string, map)
- File handling
- OOP principles

## Files Used
- user.txt
- employees.txt
- attendance.txt
- payroll.txt

## How to Run
```bash
g++ main.cpp -o payroll
./payroll
