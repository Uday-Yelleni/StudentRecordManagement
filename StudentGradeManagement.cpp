#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Student Class
class Student
{
public:
    int rollNumber;
    int marksCS, marksMath;
    double percentage;
    char grade;

    Student(int r, int cs, int math)
    {
        rollNumber = r;
        marksCS = cs;
        marksMath = math;
        calculatePercentageAndGrade();
    }

    void calculatePercentageAndGrade()
    {
        percentage = (marksCS + marksMath) / 2.0;
        if (percentage >= 91)
            grade = 'A';
        else if (percentage >= 75)
            grade = 'B';
        else if (percentage >= 60)
            grade = 'C';
        else if (percentage >= 50)
            grade = 'D';
        else
            grade = 'F';
    }
};

// Function to Display Student Records
void displayStudents(const vector<Student> &students)
{
    cout << "\nStudent Records:\n";
    for (const auto &student : students)
    {
        cout << "Roll Number: " << student.rollNumber
             << ", Marks (CS): " << student.marksCS
             << ", Marks (Math): " << student.marksMath
             << ", Percentage: " << student.percentage
             << ", Grade: " << student.grade << endl;
    }
}

// Function to Add a New Student
void addStudent(vector<Student> &students)
{
    int roll, cs, math;
    cout << "Enter Roll Number: ";
    cin >> roll;
    do
    {
        cout << "Enter Marks for Computer Science (0-100): ";
        cin >> cs;
    } while (cs > 100 || cs < 0);

    do
    {
        cout << "Enter Marks for Mathematics (0-100): ";
        cin >> math;
    } while (math > 100 || math < 0);

    students.emplace_back(roll, cs, math);
    cout << "Student added successfully!\n";
}

// Function to Search for a Student by Roll Number
void searchStudent(const vector<Student> &students, int roll)
{
    for (const auto &student : students)
    {
        if (student.rollNumber == roll)
        {
            cout << "Found Student - Roll: " << student.rollNumber
                 << ", Percentage: " << student.percentage
                 << ", Grade: " << student.grade << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

// Function to Update Marks for a Particular Student
void updateMarks(vector<Student> &students)
{
    int roll, cs, math;
    cout << "Enter Roll Number of the student to update: ";
    cin >> roll;

    for (auto &student : students)
    {
        if (student.rollNumber == roll)
        {
            do
            {
                cout << "Enter new Marks for Computer Science (0-100): ";
                cin >> cs;
            } while (cs > 100 || cs < 0);

            do
            {
                cout << "Enter new Marks for Mathematics (0-100): ";
                cin >> math;
            } while (math > 100 || math < 0);

            student.marksCS = cs;
            student.marksMath = math;
            student.calculatePercentageAndGrade();
            cout << "Marks updated successfully!\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

// Function to Delete a Student Record
void deleteStudent(vector<Student> &students)
{
    int roll;
    cout << "Enter Roll Number of the student to delete: ";
    cin >> roll;

    auto it = remove_if(students.begin(), students.end(),
                        [roll](const Student &s)
                        { return s.rollNumber == roll; });

    if (it != students.end())
    {
        students.erase(it, students.end());
        cout << "Student record deleted successfully!\n";
    }
    else
    {
        cout << "Student not found.\n";
    }
}

// Function to Sort Students by Percentage
void sortStudents(vector<Student> &students)
{
    char sortOrder;
    cout << "\nSort student records based on percentage.\n";
    cout << "Enter 'A' for Ascending order or 'D' for Descending order: ";
    cin >> sortOrder;

    sort(students.begin(), students.end(), [&](Student a, Student b)
         { return (sortOrder == 'A' || sortOrder == 'a') ? (a.percentage < b.percentage) : (a.percentage > b.percentage); });

    cout << "Data sorted successfully in " << ((sortOrder == 'A' || sortOrder == 'a') ? "Ascending" : "Descending") << " order.\n";
}

int main()
{
    vector<Student> students;
    char choice;

    do
    {
        cout << "\n=== Student Record Management System ===\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Update Student Marks\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Sort Student Records\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            addStudent(students);
            break;
        case '2':
            displayStudents(students);
            break;
        case '3':
        {
            int roll;
            cout << "Enter Roll Number to search: ";
            cin >> roll;
            searchStudent(students, roll);
            break;
        }
        case '4':
            updateMarks(students);
            break;
        case '5':
            deleteStudent(students);
            break;
        case '6':
            sortStudents(students);
            break;
        case '7':
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '7');

    return 0;
}
