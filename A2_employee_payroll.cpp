#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Base class for Staff details
class Staff {
protected:
    string staffId;
    string staffName;
    string jobTitle;
    string staffStatus; // Full-time or Part-time
    int daysOff;
    double extraHours;
    double shiftHours; // Used for part-time staff
    string startDate;

public:
    Staff() : staffId(""), staffName(""), jobTitle(""), staffStatus(""),
              daysOff(0), extraHours(0), shiftHours(0) {}

    void inputStaffDetails() {
        cout << "Enter Employee ID: ";
        getline(cin, staffId);
        cout << "Enter Employee Name: ";
        getline(cin, staffName);

        // Job Title choices
        cout << "Enter Job Title [Full-time: (1- Barista, 2- Cashier, 3- Supervisor), Part-time: (4- Kitchen Staff, 5- Cleaner, 6- Waiter)] : ";
        int titleChoice;
        cin >> titleChoice;
        cin.ignore();  // Clear buffer

        // Validate job title choice
        while (titleChoice < 1 || titleChoice > 6) {
            cout << "Invalid job title! Please enter a valid title (1-6): ";
            cin >> titleChoice;
            cin.ignore();  // Clear buffer
        }

        // Assign job title based on number
        switch (titleChoice) {
            case 1: jobTitle = "barista"; 
            break;
            case 2: jobTitle = "cashier"; 
            break;
            case 3: jobTitle = "supervisor"; 
            break;
            case 4: jobTitle = "kitchen staff"; 
            break;
            case 5: jobTitle = "cleaner"; 
            break;
            case 6: jobTitle = "waiter"; 
            break;
            default: jobTitle = "unknown"; 
            break;
        }

        // Staff status: f for full-time, p for part-time
        cout << "Enter Employee Status (type: (""F"" or ""f"") Full-time,  (""P"" or ""p"") Part-time): ";
        char statusChoice;
        cin >> statusChoice;
        cin.ignore(); // Clear buffer

        // Validate staff status
        while (statusChoice != 'f' && statusChoice != 'F' && statusChoice != 'p' && statusChoice != 'P') {
            cout << "Invalid input! Please enter Full-time(f or F) or Part-time(p or P) ";
            cin >> statusChoice;
            cin.ignore(); // Clear buffer
        }

        // Assign staff status
        if (statusChoice == 'f' || statusChoice == 'F') {
            staffStatus = "full-time";
        } else if (statusChoice == 'p' || statusChoice == 'P') {
            staffStatus = "part-time";
        } else {
            staffStatus = "Wrong Input!";
        }

        // Ask for start date
        cout << "Enter Start Date (yyyy/mm/dd): ";
        getline(cin, startDate); 
   
        if (staffStatus == "full-time") {
            cout << "Enter leave days: ";
            cin >> daysOff;

            cout << "Enter overtime Hours: ";
            cin >> extraHours;
        }

        // Only ask for shift hours if the staff is part-time
        if (staffStatus == "part-time") {
            cout << "Enter working Hours (Only for part-time): ";
            cin >> shiftHours;
        }

        cin.ignore(); // Clear the buffer
    }

    void displayStaffDetails() const {
        cout << "| " << setw(12) << left << staffId
             << "| " << setw(20) << left << staffName
             << "| " << setw(15) << left << jobTitle
             << "| " << setw(12) << left;

        // Display full form of staff status
        if (staffStatus == "full-time") {
            cout << "Full-time";
        } else if (staffStatus == "part-time") {
            cout << "Part-time";
        } else {
            cout << "Unknown";
        }

        // Only show Days Off and Extra Hours for Full-time staff
        if (staffStatus == "full-time") {
            cout << "| " << setw(10) << left << daysOff
                 << "| " << setw(14) << left << extraHours;
        } else {
            cout << "| " << setw(10) << left << "N/A"
                 << "| " << setw(14) << left << "N/A";
        }
        cout << "| " << setw(12) << left << startDate;  // Display start date
        cout << " |" << endl;
    }

    string getStaffId() const { return staffId; } // Getter for Staff ID
    string getStaffName() const { return staffName; } // Getter for Staff Name
    string getJobTitle() const { return jobTitle; }
    string getStaffStatus() const { return staffStatus; }
    int getDaysOff() const { return daysOff; }
    double getExtraHours() const { return extraHours; }
    double getShiftHours() const { return shiftHours; }
    string getStartDate() const { return startDate; }
};

// Salary Calculation Class
class PayCalculator {
public:
    double calculateBaseSalary(const Staff& stf) const {
        if (stf.getJobTitle() == "barista") return 1920;
        else if (stf.getJobTitle() == "cashier") return 1790;
        else if (stf.getJobTitle() == "kitchen staff" && stf.getStaffStatus() == "full-time") return 1850;
        else if (stf.getJobTitle() == "kitchen staff" && stf.getStaffStatus() == "part-time") return 1850;
        else if (stf.getJobTitle() == "cleaner" && stf.getStaffStatus() == "full-time") return 1400;
        else if (stf.getJobTitle() == "cleaner" && stf.getStaffStatus() == "part-time") return 1400;
        else if (stf.getJobTitle() == "waiter" && stf.getStaffStatus() == "full-time") return 1700;
        else if (stf.getJobTitle() == "waiter" && stf.getStaffStatus() == "part-time") return 1700;
        else if (stf.getJobTitle() == "supervisor") return 2400;
        return 0;
    }

    // Calculate part-time salary based on shift hours per day
    double calculatePartTimeSalary(const Staff& stf) const {
        double baseSalary = calculateBaseSalary(stf) / 30;  // Monthly salary divided by 30 days
        double hourlyRate = baseSalary / 8;    // Daily wage divided by 8 to get hourly wage
        return hourlyRate * stf.getShiftHours(); // Multiply to get salary
    }

    // Calculate days off bonus (only for full-time staff)
    double calculateDaysOffBonus(const Staff& stf) const {
        if (stf.getStaffStatus() == "part-time") return 0;

        if (stf.getDaysOff() >= 4) {
            return 0;
        } else if (stf.getDaysOff() == 0) {
            return 300;
        } else if (stf.getDaysOff() == 1) {
            return 200;
        } else if (stf.getDaysOff() == 2) {
            return 100;
        }
        return 0;
    }

    // Calculate overtime pay (only for full-time staff)
    double calculateOvertimePay(const Staff& stf) const {
        if (stf.getStaffStatus() == "part-time") return 0;

        if (stf.getDaysOff() >= 4) {
            return 0;
        }

        double baseSalary = calculateBaseSalary(stf);
        double dailyRate = baseSalary / 30; // Assuming 30 working days in a month
        double hourlyRate = dailyRate / 8; // Assuming 8 working hours in a day
        return stf.getExtraHours() * (hourlyRate * 2); // Overtime is paid at double the hourly rate
    }

    // Calculate deductions (only for full-time staff)
    double calculateDeductions(const Staff& stf) const {
        if (stf.getStaffStatus() == "part-time") return 0;

        double deduction = 0;

        if (stf.getDaysOff() >= 4 && stf.getExtraHours() > 0) {
            deduction = calculateBaseSalary(stf) * 0.01; // 1% salary deduction
        }
        return deduction;
    }

    // Calculate total salary including deductions and bonuses
    double calculateSalary(const Staff& stf) const {
        double baseSalary = calculateBaseSalary(stf);
        double daysOffBonus = calculateDaysOffBonus(stf);
        double overtimePay = calculateOvertimePay(stf);
        double deductions = calculateDeductions(stf);

        double totalSalary = 0;

        if (stf.getStaffStatus() == "part-time") {
            totalSalary = calculatePartTimeSalary(stf); // Only part-time salary calculation
        } else {
            if (stf.getDaysOff() >= 4 && stf.getExtraHours() > 0) {
                daysOffBonus = 0;
                overtimePay = 0;
                totalSalary = baseSalary - (baseSalary * 0.01); // 1% penalty
            } else {
                totalSalary = baseSalary + daysOffBonus + overtimePay - deductions;
            }
        }

        if (stf.getStaffStatus() == "full-time") {
            double tax = totalSalary * 0.02; // 2% tax
            double socialSecurity = 10; // Fixed $10 social security
            return totalSalary - tax - socialSecurity;
        }

        return totalSalary; // For part-time staff, no tax deductions
    }
};

// StaffManager Class to handle adding, viewing, updating, and deleting staff
class StaffInfo {
private:
    vector<Staff> staffList;
    PayCalculator payCalculator;

public:
    void addStaff() {
        Staff stf;
        stf.inputStaffDetails();
        staffList.push_back(stf);
        cout << "Staff added successfully!\n";
    }

    void viewStaff() const {
        cout << "| " << setw(12) << left << "Staff ID"
             << "| " << setw(20) << left << "Staff Name"
             << "| " << setw(15) << left << "Job Title"
             << "| " << setw(12) << left << "Staff Status"
             << "| " << setw(10) << left << "Days Off"
             << "| " << setw(14) << left << "Extra Hours"
             << "| " << setw(12) << left << "Start Date"
             << " |\n";
        cout << "---------------------------------------------------------------------------------------------------\n";

        for (const auto& stf : staffList) {
            stf.displayStaffDetails();
        }
    }
void viewPayroll() {
    // Sort staff list by total salary in descending order using insertion sort
    for (size_t i = 1; i < staffList.size(); ++i) {
        Staff key = staffList[i];
        double keySalary = payCalculator.calculateSalary(key);
        size_t j = i;

        // Compare the salaries and rearrange in descending order
        while (j > 0 && payCalculator.calculateSalary(staffList[j - 1]) < keySalary) {
            staffList[j] = staffList[j - 1];
            --j;
        }
        staffList[j] = key;
    }

    // Display payroll after sorting
    cout << "| " << setw(12) << left << "Employee-ID"
         << "| " << setw(20) << left << "Employee-Name"
         << "| " << setw(15) << left << "Job Title"
         << "| " << setw(12) << left << "Staff Status"
         << "| " << setw(10) << left << "Leave Days "
         << "| " << setw(14) << left << "Overtime Hours"
         << "| " << setw(12) << left << "Basic Salary"
         << "| " << setw(12) << left << "Leave Bonus"
         << "| " << setw(12) << left << "Overtime Bonus"
         << "| " << setw(12) << left << "Tax"
         << "| " << setw(12) << left << "Total Salary"
         << " |\n";
    cout << "------------------------------------------------------------------------------------------------------------\n";

    for (const auto& stf : staffList) {
        double baseSalary = payCalculator.calculateBaseSalary(stf);
        double leaveBonus = payCalculator.calculateDaysOffBonus(stf);
        double overtimeBonus = payCalculator.calculateOvertimePay(stf);
        double tax = (stf.getStaffStatus() == "full-time") ? (baseSalary + leaveBonus + overtimeBonus) * 0.02 : 0; // 2% tax only for full-time staff
        double totalSalary = payCalculator.calculateSalary(stf);

        cout << "| " << setw(12) << left << stf.getStaffId()
             << "| " << setw(20) << left << stf.getStaffName()
             << "| " << setw(15) << left << stf.getJobTitle()
             << "| " << setw(12) << left << stf.getStaffStatus()
             << "| " << setw(10) << left << stf.getDaysOff()
             << "| " << setw(14) << left << stf.getExtraHours()
             << "| " << setw(12) << left << baseSalary
             << "| " << setw(12) << left << leaveBonus
             << "| " << setw(12) << left << overtimeBonus
             << "| " << setw(12) << left << tax
             << "| " << setw(12) << left << totalSalary
             << " |\n";
    }
}

void MonthlyReport() const {
    int fullTimeCount = 0;
    int partTimeCount = 0;
    double fullTimeSalaryTotal = 0.0;
    double partTimeSalaryTotal = 0.0;

    // Traverse through the staff list and calculate totals
    for (const auto& stf : staffList) {
        double baseSalary = payCalculator.calculateBaseSalary(stf);
        double leaveBonus = payCalculator.calculateDaysOffBonus(stf);
        double overtimeBonus = payCalculator.calculateOvertimePay(stf);
        double tax = (stf.getStaffStatus() == "full-time") ? (baseSalary + leaveBonus + overtimeBonus) * 0.02 : 0; // 2% tax for full-time
        double totalSalary = payCalculator.calculateSalary(stf);

        // Check staff status and update totals
        if (stf.getStaffStatus() == "full-time") {
            fullTimeCount++;
            fullTimeSalaryTotal += totalSalary;
        } else if (stf.getStaffStatus() == "part-time") {
            partTimeCount++;
            partTimeSalaryTotal += totalSalary;
        }
    }

    // Output the summary report
    cout << "\n--- Monthly Report ---\n";
    cout << "***************************************************************\n";
    cout << "| FullTime Employees total   | " << setw(20) << left << fullTimeCount << " \n";
    cout << "| PartTime Employees total   | " << setw(20) << left << partTimeCount << " \n";
    cout << "| Total Salary of (fulltime) | $ " << setw(12) << left << fullTimeSalaryTotal << " \n";
    cout << "| Total Salary of (parttime) | $ " << setw(12) << left << partTimeSalaryTotal << " \n";
    cout << "| Total Salary of All        | $ " << setw(12) << left << (fullTimeSalaryTotal + partTimeSalaryTotal) << " \n";
    
}

    void updateStaff() {
        string staffId;
        cout << "Enter  Employee ID to update: ";
        cin >> staffId;
        cin.ignore(); // Clear buffer

        bool found = false;
        for (auto& stf : staffList) {
            if (stf.getStaffId() == staffId) {
                stf.inputStaffDetails();
                cout << "Staff details updated successfully!\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Employee ID not found.\n";
        }
    }

    void deleteStaff() {
        string staffId;
        cout << "Enter Employee ID to delete: ";
        cin >> staffId;
        cin.ignore(); // Clear buffer

        bool found = false;
        for (auto it = staffList.begin(); it != staffList.end(); ++it) {
            if (it->getStaffId() == staffId) {
                staffList.erase(it);
                cout << "Deleted successfully!!!\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Employee ID not found.\n";
        }
    }
};

int main() {
    StaffInfo info;
    int choice;

    do {
        cout << "\nJava Jolt Café Menu:\n";
        cout << "1. Insert Employee\n";
        cout << "2. Display Employee\n";
        cout << "3. Display Payroll\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. View Monthly Report\n";  // New option for Monthly Report
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To ignore newline characters left in the buffer after reading integers

        switch (choice) {
            case 1: info.addStaff(); break;
            case 2: info.viewStaff(); break;
            case 3: info.viewPayroll(); break;
            case 4: info.updateStaff(); break;
            case 5: info.deleteStaff(); break;
            case 6: info.MonthlyReport(); break;  // Call to generate monthly report
            case 7: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n"; break;
        }

    } while (choice != 7);

    return 0;
}