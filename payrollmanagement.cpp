#include <bits/stdc++.h>
using namespace std;
enum class Role
{
    ADMIN,
    EMPLOYEE
};
enum class Status
{
    WORKING,
    INACTIVE
};
string statusToString(Status s)
{
    return (s == Status::WORKING) ? "WORKING" : "INACTIVE";
};
Status stringToStatus(string s)
{
    if (s == "WORKING")
        return Status::WORKING;
    return Status::INACTIVE;
};
class User
{
public:
    string username;
    Role role;
    string id;
    User(string u, Role r, string eid = "") : username(u), role(r), id(eid) {}
};
class Employee
{
private:
    string id;

public:
    string emp_name;
    string dept;
    double base_salary;
    Status status;

    Employee(string eid, string name, string d, double sal, Status s)
        : id(eid), emp_name(name), dept(d), base_salary(sal), status(s) {}

    string getId() const
    {
        return id;
    }
    void display() const
    {
        cout << "Employee id: " << id << " | "
             << "Employee name: " << emp_name << " | "
             << "Employee deartment: " << dept << " | "
             << "Employees base salary : " << base_salary << " | "
             << "Employee status: " << statusToString(status) << " | ";
             cout<<"-----------------------\n";
    }
};
class Attendance
{
private:
    string emp_id;

public:
    int hours_worked;
    int overtime_hours;

    Attendance(string eid, int h = 0, int o = 0)
        : emp_id(eid), hours_worked(h), overtime_hours(o) {}

    string getId() const
    {
        return emp_id;
    }
    void display() const
    {
        cout << "Employee id: " << emp_id << " \n "
             << "Hours worked: " << hours_worked << "\n"
             << "Over time hours: " << overtime_hours << endl;
    }
};
class Payroll
{
private:
    string emp_id;

public:
    double base_salary;
    double overtime_pay;
    double bonus;
    double gross_salary;
    double deductions;
    double net_salry;

    Payroll(string eid, double bs = 0, double op = 0, double b = 0, double g = 0, double d = 0, double ns = 0)
        : emp_id(eid), base_salary(bs), overtime_pay(op), bonus(b), gross_salary(g), deductions(d), net_salry(ns) {}
    string getId() const
    {
        return emp_id;
    }
    void display() const
    {
        cout << "Employee id: " << emp_id << " \n "
             << "Base salary: " << base_salary << "\n"
             << "Over_time pay: " << overtime_pay << "\n"
             << "Bonus: " << bonus << "\n"
             << "Gross Salary: " << gross_salary << "\n"
             << "Deductions : " << deductions << "\n"
             << "Net Salary: " << net_salry << endl;
    }
};
class Calculation
{
public:
    double Hourly_rate(double base_salary)
    {
        return base_salary / 160;
    };
    double Overtime_pay(double hourley_rate, int overtime)
    {
        return hourley_rate * overtime * 1.5;
    };
    double Gross_salary(double base_salary, double overtime_pay, double bonus)
    {
        return base_salary + overtime_pay + bonus;
    };
    double Deductions(double gross_salary)
    {
        return (gross_salary * 0.10) + (gross_salary * 0.05);
    };
    double Net_salary(double gross_salary, double deductions)
    {
        return gross_salary - deductions;
    };
};
string simplehash(const string &pass)
{
    int hash = 0;
    for (char c : pass)
        c+=hash * 31;
    return to_string(hash);
};
bool isValidName(const string &s)
{
    if (s.empty())
        return false;
    for (char c : s)
        if (!isalpha(c) && c != ' ')
            return false;
    return true;
};
bool isValidDept(const string &s)
{
    if (s.empty())
        return false;
    vector<string> depts = {"PRODUCTION", "QC", "MAINTAINANCE", "INVENTORY", "MARKETING", "SALES", "ACCOUNTING", "OTHERS"};
    for (const auto &dept : depts)
    {
        if (s == dept)
            return true;
    }
    return false;
}
class AuthManager
{
public:
    static User login()
    {

        ifstream file("payrollmanagement/user.txt");
        if (!file)
        {
            cout << "user.txt not found!\n";
            exit(0);
        }
        string uname, pass;
        cout << "Username : ";
        getline(cin, uname);
        cout << "Password : ";
        getline(cin, pass);

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string fuser, fpass, frole, fid;
            getline(ss, fuser, ',');
            getline(ss, fpass, ',');
            getline(ss, frole, ',');
            getline(ss, fid, ',');

            if (uname == fuser && simplehash(pass) == fpass)
            {
                Role role;
                if (frole == "ADMIN")
                    role = Role::ADMIN;
                else
                    role = Role::EMPLOYEE;

                cout << "Login Successful !\n";
                return User(fuser, role, fid);
            }
        }
        cout << "Invalid username or password\n";
        exit(0);
    }
};
class AttendanceFileManager
{
public:
    static void save_Attendance(const vector<Attendance> &attendance)
    {
        ofstream file("payrollmanagement/attendance.txt");
        if (!file)
            return;
        for (auto &e : attendance)
        {
            file << e.getId() << ","
                 << e.hours_worked << ","
                 << e.overtime_hours << "\n";
        }
    }
    static vector<Attendance> load_attendance()
    {
        vector<Attendance> attendance;
        ifstream file("payrollmanagement/attendance.txt");
        if (!file)
            return attendance;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, hours_worked, over_time;
            getline(ss, id, ',');
            getline(ss, hours_worked, ',');
            getline(ss, over_time, ',');
            attendance.emplace_back(id,
                                    stoi(hours_worked),
                                    stoi(over_time));
        }
        return attendance;
    }
};
class EmployeeFileManager
{
public:
    static void save_Employee(const vector<Employee> &employees)
    {
        ofstream file("payrollmanagement/employees.txt");
        if (!file)
            return;
        for (auto &e : employees)
        {
            file << e.getId() << ","
                 << e.emp_name << ","
                 << e.dept << ","
                 << e.base_salary << ","
                 << statusToString(e.status) << "\n";
        }
    }
    static vector<Employee> load_employee()
    {
        vector<Employee> employees;
        ifstream file("payrollmanagement/employees.txt");
        if (!file)
            return employees;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, name, dept, base_salary, status;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, dept, ',');
            getline(ss, base_salary, ',');
            getline(ss, status, ',');
            employees.emplace_back(
                id,
                name,
                dept,
                stod(base_salary),
                stringToStatus(status));
        }
        return employees;
    }
};
class PayrollFileManager
{
public:
    static void save_payroll(const vector<Payroll> &payroll)
    {
        ofstream file("payrollmanagement/payroll.txt");
        if (!file)
            return;
        for (auto &e : payroll)
        {
            file << e.getId() << ","
                 << e.base_salary << ","
                 << e.overtime_pay << ","
                 << e.bonus << ","
                 << e.gross_salary << ","
                 << e.deductions << ","
                 << e.net_salry << "\n";
        }
    }
    static vector<Payroll> load_payroll()
    {
        vector<Payroll> payroll;
        ifstream file("payrollmanagement/payroll.txt");
        if (!file)
            return payroll;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, base_salary, overtime_pay, bonus, gross, deductions, net_salary;
            getline(ss, id, ',');
            getline(ss, base_salary, ',');
            getline(ss, overtime_pay, ',');
            getline(ss, bonus, ',');
            getline(ss, gross, ',');
            getline(ss, deductions, ',');
            getline(ss, net_salary, ',');
            payroll.emplace_back(id,
                                 stod(base_salary),
                                 stod(overtime_pay),
                                 stod(bonus),
                                 stod(gross),
                                 stod(deductions),
                                 stod(net_salary));
        }
        return payroll;
    }
};
class EmployeeManager
{
private:
    vector<Employee> employees;
    int findIndexById(const string &id) const
    {
        for (size_t i = 0; i < employees.size(); i++)
        {
            if (employees[i].getId() == id)
                return i;
        }
        return -1;
    }

public:
    EmployeeManager(const vector<Employee> &employees) : employees(employees) {}
    EmployeeManager()
    {
        employees = EmployeeFileManager::load_employee();
    }
    void addEmployee(const User &user, string id, string name, string dept, double sal, Status s)
    {
        if (user.role != Role::ADMIN)
        {
            cout << "Access denied";
            return;
        }
        int idx = findIndexById(id);
        if (idx != -1)
        {
            cout << "Employee already exists\n";
            return;
        }

        employees.emplace_back(id, name, dept, sal, s);
        EmployeeFileManager::save_Employee(employees);
    }
    void sortById()
    {
        sort(employees.begin(), employees.end(),
             [](const Employee &a, const Employee &b)
             {
                 return a.getId() < b.getId();
             });
    }
    void displayUser(const User &user) const
    {
        if (user.role == Role::ADMIN)
        {
            // Admin sees all
            for (const auto &s : employees)
                s.display();
        }
        else if (user.role == Role::EMPLOYEE)
        {

            int idx = findIndexById(user.id);
            if (idx != -1)
                employees[idx].display();
            else
                cout << "No record found\n";
        }
        else
        {
            cout << "Access restricted\n";
        }
    }
    void searchEmployee(const User &user, const string &eid) const
    {
        if (user.role == Role::ADMIN)
        {
            int idx = findIndexById(eid);
            if (idx != -1)
                employees[idx].display();
            else
                cout << "Employee not found\n";
        }
        else if (user.role == Role::EMPLOYEE)
        {
            if (user.id == eid)
            {
                int idx = findIndexById(eid);
                if (idx != -1)
                    employees[idx].display();
                else
                    cout << "No record found\n";
            }
            else
            {
                cout << "Access denied (privacy protected)\n";
            }
        }
    }
    void updateName(const User &user, const string &id, const string &newName)
    {
        if (user.role != Role::ADMIN)
        {
            cout << "Access denied\n";
            return;
        }
        int idx = findIndexById(id);
        if (idx == -1)
        {
            cout << "Employee not found\n";
            return;
        }

        employees[idx].emp_name = newName;
        sortById();
        EmployeeFileManager::save_Employee(employees);
        cout << "Updated\n";
    }
    void updateDept(const User &user, const string &id, const string &newName)
    {
        if (user.role != Role::ADMIN)
        {
            cout << "Access denied\n";
            return;
        }
        int idx = findIndexById(id);
        if (idx == -1)
        {
            cout << "Employee not found\n";
            return;
        }

        employees[idx].dept = newName;
        sortById();
        EmployeeFileManager::save_Employee(employees);  cout << "Updated\n";
    }
    void updateBaseSalary(const User &user, const string &id, const double &newName)
    {
        if (user.role != Role::ADMIN)
        {
            cout << "Access denied\n";
            return;
        }
        int idx = findIndexById(id);
        if (idx == -1)
        {
            cout << "Employee not found\n";
            return;
        }

        employees[idx].base_salary = newName;
        sortById();
        EmployeeFileManager::save_Employee(employees);  cout << "Updated\n";
    }
    void updateStatus(const User &user, const string &id, Status newStatus)
    {
        if (user.role != Role::ADMIN)
        {
            cout << "Access denied\n";
            return;
        }
        int idx = findIndexById(id);
        if (idx == -1)
        {
            cout << "Employee not found\n";
            return;
        }
        employees[idx].status = newStatus;
        sortById();
        EmployeeFileManager::save_Employee(employees);  cout << "Updated\n";
    }
    bool exists(const string &id) const
    {
        return findIndexById(id) != -1;
    }
};
class AttendanceManager
{
private:
    vector<Attendance> attendance;
    int findIndexById(const string &id) const
    {
        for (size_t i = 0; i < attendance.size(); i++)
        {
            if (attendance[i].getId() == id)
                return i;
        }
        return -1;
    }

public:
    EmployeeManager em();
    AttendanceManager(const vector<Attendance> &attendances) : attendance(attendances) {}
    AttendanceManager()

    {
        attendance = AttendanceFileManager::load_attendance();
    }
    void addAttendance(const User &user, string id, int hours_worked, int over_time)
    {

        EmployeeManager em;
        if (!em.exists(id))
        {
            cout << "Employee does not exist\n";
            return;
        }

        if (user.role != Role::ADMIN)
        {
            cout << "Access denied";
            return;
        }
        if (findIndexById(id) != -1)
        {
            cout << "Employee attendance already added \n";
            return;
        }
        attendance.emplace_back(id, hours_worked, over_time);
        AttendanceFileManager::save_Attendance(attendance);
    }
    void updateHoursWorked(const User &user, const string &id, const int &newName)
    {
        if (user.role != Role::ADMIN)
        {
            cout << "Access denied\n";
            return;
        }
        int idx = findIndexById(id);
        if (idx == -1)
        {
            cout << "Employee  not found\n";
            return;
        }

        attendance[idx].hours_worked = newName;
        AttendanceFileManager::save_Attendance(attendance);
    }
    void updateOverTime(const User &user, const string &id, const int &newName)
    {
        if (user.role != Role::ADMIN)
        {
            cout << "Access denied\n";
            return;
        }
        int idx = findIndexById(id);
        if (idx == -1)
        {
            cout << "Employee  not found\n";
            return;
        }

        attendance[idx].overtime_hours = newName;
        AttendanceFileManager::save_Attendance(attendance);
    }
    void displayUser(const User &user) const
    {
        if (user.role == Role::ADMIN)
        {
            // Admin sees all
            for (const auto &s : attendance)
                s.display();
        }
        else if (user.role == Role::EMPLOYEE)
        {

            int idx = findIndexById(user.id);
            if (idx != -1)
                attendance[idx].display();
            else
                cout << "No record found\n";
        }
        else
        {
            cout << "Access restricted\n";
        }
    }
};
class PayrollManager
{
private:
    vector<Payroll> payrolls;
    vector<Employee> employees = EmployeeFileManager::load_employee();
    vector<Attendance> attendance = AttendanceFileManager::load_attendance();
    int findIndexById(const string &id) const
    {
        for (size_t i = 0; i < attendance.size(); i++)
        {
            if (attendance[i].getId() == id)
                return i;
        }
        return -1;
    }

public:
    Calculation c;
    void generatePayroll()
    {
        employees = EmployeeFileManager::load_employee();
        attendance = AttendanceFileManager::load_attendance();

        payrolls.clear();
        for (auto &emp : employees)
        {
            for (auto &att : attendance)
            {
                if (emp.getId() == att.getId())
                {
                    double hourly = c.Hourly_rate(emp.base_salary);
                    double overtimepay = c.Overtime_pay(hourly, att.overtime_hours);
                    double bonus = (att.hours_worked > 160) ? 100 : 0;
                    double gross = c.Gross_salary(emp.base_salary, overtimepay, bonus);
                    double deductions = c.Deductions(gross);
                    double net = c.Net_salary(gross, deductions);

                    payrolls.emplace_back(
                        emp.getId(),
                        emp.base_salary,
                        overtimepay,
                        bonus,
                        gross,
                        deductions,
                        net);
                }
            }
        }
        PayrollFileManager::save_payroll(payrolls);
        cout << "Payroll generated successfully for all employees!\n";
    }
    void viewPayroll(const User &user)
    {
        payrolls = PayrollFileManager::load_payroll();

        for (const auto &p : payrolls)
        {
            if (user.role == Role::ADMIN || p.getId() == user.id)
                p.display();
        }
    }
};
void adminMenu(const User &user, EmployeeManager &employeeManager, AttendanceManager &attendanceManager, PayrollManager &payrollManager)
{
    int choice;
    cout << "1. Add Employee" << "\n"
         << "2. Update Employee" << "\n"
         << "3. View all Employee details " << "\n"
         << "4. Add Attendance " << "\n"
         << "5. update Attendance " << "\n"
         << "6. Generate Payroll" << "\n"
         << "7. View Payroll" << "\n"
         << "8. Logout" << "\n";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string id, name, dept, base_salary, status, hours_worked, over_time;
    double bs;
    int hw, ot;
    switch (choice)
    {
    case 1:
    {
        cout << "Enter Employee ID: ";
        getline(cin, id);
        if (id.empty())
        {
            cout << "ID cannot be empty\n";
            return;
        }
        cout << "Name: ";
        getline(cin, name);
        if (!isValidName(name))
        {
            cout << "Invalid name!\n";
            return;
        }
        cout << "Department: ";
        getline(cin, dept);
        if (!isValidDept(dept))
        {
            cout << "Invalid department!\n";
            return;
        }
        cout << "\nBase salary: ";
        getline(cin, base_salary);
        bs = stod(base_salary);
        cout << "\nWorking Status: ";
        getline(cin, status);

        employeeManager.addEmployee(user, id, name, dept, bs, stringToStatus(status));   adminMenu(user, employeeManager, attendanceManager, payrollManager);
    }
    break;
    case 2:
    {
        cout << "Enter Employee ID: ";
        getline(cin, id);
        if (id.empty())
        {
            cout << "ID cannot be empty\n";
            return;
        }
        cout << "1.Name  2.Dept  3.Base salary  4.Status\n";
        cout << "Enter your choice: ";
        int c;
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (c == 1)
        {
            cout << "New Name: ";
            getline(cin, name);
            employeeManager.updateName(user, id, name);   adminMenu(user, employeeManager, attendanceManager, payrollManager);
        }
        else if (c == 2)
        {
            cout << "New dept: ";
            getline(cin, dept);
            employeeManager.updateDept(user, id, dept);   adminMenu(user, employeeManager, attendanceManager, payrollManager);
        }
        else if (c == 3)
        {
            cout << "Base salary: ";
            getline(cin, base_salary);
            bs = stod(base_salary);
            employeeManager.updateBaseSalary(user, id, bs);   adminMenu(user, employeeManager, attendanceManager, payrollManager);
        }
        else if (c == 4)
        {
            cout << "Status: ";
            getline(cin, status);
            employeeManager.updateStatus(user, id, stringToStatus(status));   adminMenu(user, employeeManager, attendanceManager, payrollManager);
        }
        else
            cout << "Invalid choice\n";
    }
    break;
    case 3:
    {
        employeeManager.displayUser(user);   adminMenu(user, employeeManager, attendanceManager, payrollManager);
    }break;
    case 4:
    {
        cout << "Enter Employee ID: ";
        getline(cin, id);
        if (id.empty())
        {
            cout << "ID cannot be empty\n";
            return;
        }
        cout << "Hours_worked: ";
        getline(cin, hours_worked);
        hw = stoi(hours_worked);
        cout << "Overtime_hours: ";
        getline(cin, over_time);
        ot = stoi(over_time);
        attendanceManager.addAttendance(user, id, hw, ot);   adminMenu(user, employeeManager, attendanceManager, payrollManager);
    }
    break;
    case 5:
    {
        cout << "Enter Employee ID: ";
        cin >> id;
        cout << "1- Update Hours worked\n2. Update Overtime hours\n";
        int c;
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (c == 1)
        {
            cout << "Hours_worked: ";
            cin >> hours_worked;
            hw = stoi(hours_worked);
            attendanceManager.updateHoursWorked(user, id, hw);   adminMenu(user, employeeManager, attendanceManager, payrollManager);
        }
        else if (c == 2)
        {
            cout << "Overtime_hours: ";
            cin >> over_time;
            ot = stoi(over_time);
            attendanceManager.updateOverTime(user, id, ot);   adminMenu(user, employeeManager, attendanceManager, payrollManager);
        }
        else
        {
            cout << "Invalid choice\n";   adminMenu(user, employeeManager, attendanceManager, payrollManager);
            return;
        }
    }
    break;
    case 6:
    {
        payrollManager.generatePayroll();   adminMenu(user, employeeManager, attendanceManager, payrollManager);
    }
    break;
    case 7:
    {
        payrollManager.viewPayroll(user);   adminMenu(user, employeeManager, attendanceManager, payrollManager);
    }
    break;
    case 8:
        cout << "Logging out...\n";
        break;
    default:
        cout << "Invalid choice\n";
        adminMenu(user, employeeManager, attendanceManager, payrollManager);
        break;
    }
};
void employeeMenu(const User &user, EmployeeManager &emp, AttendanceManager &attendance, PayrollManager &payroll)
{
    cout << "1.View own profile\n2.View own Attendance\n3.View own payroll";
    int choice;
    cout << "Enter your choice";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string id;
    switch (choice)
    {
    case 1:
        emp.displayUser(user);
        break;
    case 2:
        attendance.displayUser(user);
        break;
    case 3:
        payroll.viewPayroll(user);
        break;
    }
};
int main()
{
    EmployeeManager employeeManager;
    AttendanceManager attendanceManager;
    PayrollManager payrollManager;
    User currentUser = AuthManager::login();
    if (currentUser.role == Role::ADMIN)
        adminMenu(currentUser, employeeManager, attendanceManager, payrollManager);
    else if (currentUser.role == Role::EMPLOYEE)
        employeeMenu(currentUser, employeeManager, attendanceManager, payrollManager);
    return 0;
}