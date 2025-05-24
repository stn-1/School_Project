#include <iostream>
#include <vector>
#include "functions.h"
using namespace std;

int main()
{
    vector<Student> students;
    vector<Subject> subjects;
    vector<Registration> regists;
    cout << "Welcome to Student Registration System" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Please enter the file name: ";
    string filename;
    cin >> filename;
    cin.ignore();
    cout << endl;

    // Read data from file
    readData(students, subjects, regists, filename);

    // Menu
    int choice;
    do
    {
        cout << "\n--- MENU ---\n";
        cout << "1. Display all students\n";
        cout << "2. Display all subjects\n";
        cout << "3. Display all registrations\n";
        cout << "4. Search student by ID\n";
        cout << "5. Search subject by code\n";
        cout << "6. Search registrations by subject code\n";
        cout << "7. Export statistics\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            displayStudents(students);
            break;
        case 2:
            displaySubjects(subjects);
            break;
        case 3:
            displayRegistrations(regists, students, subjects);
            break;
        case 4:
            searchStudent(students, regists, subjects);
            break;
        case 5:
            searchSubject(subjects);
            break;
        case 6:
            searchRegistrationsBySubjectCode(regists, students, subjects);
            break;
        case 7:
            generateStatistics(regists, students, subjects, "output.txt");
            break;
        case 0:
            cout << endl;
            cout << "Goodbye!\n";
            cout << endl;
            break;
        default:
            cout << endl;
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
