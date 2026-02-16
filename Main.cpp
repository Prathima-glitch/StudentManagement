#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class Student
{
private:
    int rollNo;
    string name;
    int marks[5];
    int total;
    float percentage;

public:
    void input()
    {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);

        total = 0;
        cout << "Enter marks for 5 subjects (out of 100):\n";
        for (int i = 0; i < 5; i++)
        {
            cout << "Subject " << i + 1 << ": ";
            cin >> marks[i];
            total += marks[i];
        }

        percentage = (total / 500.0f) * 100;
    }

    void display() const
    {
        cout << "\n----------------------------------\n";
        cout << "Roll No: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Marks: ";
        for (int i = 0; i < 5; i++)
        {
            cout << marks[i] << " ";
        }
        cout << "\nTotal: " << total;
        cout << "\nPercentage: " << fixed << setprecision(2)
             << percentage << "%\n";
    }

    // Getters (needed for CSV)
    int getRollNo() const { return rollNo; }
    string getName() const { return name; }
    int getMarks(int i) const { return marks[i]; }
    int getTotal() const { return total; }
    float getPercentage() const { return percentage; }
};

int main()
{
    vector<Student> students;
    int choice;

    do
    {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search by Roll Number\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Student s;
            s.input();
            students.push_back(s);

            // Append to CSV
            ofstream file("students.csv", ios::app);

            file << s.getRollNo() << ","
                 << s.getName() << ","
                 << s.getMarks(0) << ","
                 << s.getMarks(1) << ","
                 << s.getMarks(2) << ","
                 << s.getMarks(3) << ","
                 << s.getMarks(4) << ","
                 << s.getTotal() << ","
                 << fixed << setprecision(2)
                 << s.getPercentage()
                 << "\n";

            file.close();

            cout << "Student added & saved to CSV successfully!\n";
        }
        else if (choice == 2)
        {
            if (students.empty())
            {
                cout << "No students in memory.\n";
            }
            else
            {
                for (const auto &s : students)
                {
                    s.display();
                }
            }
        }
        else if (choice == 3)
        {
            int searchRoll;
            cout << "Enter Roll Number to search: ";
            cin >> searchRoll;

            bool found = false;
            for (const auto &s : students)
            {
                if (s.getRollNo() == searchRoll)
                {
                    s.display();
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Student not found in memory.\n";
            }
        }
        else if (choice == 4)
        {
            cout << "Exiting program...\n";
        }
        else
        {
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
