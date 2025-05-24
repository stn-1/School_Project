#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Student
{
    string id;
    string name;

    void input(istream &file);
    bool checkDuplicateID(const vector<Student> &students, const string &id);
    void display() const;
};

struct Subject
{
    string code;
    string name;
    string credit;
    const int TUITION_PER_CREDIT = 300000;

    void input(istream &file);
    bool checkDuplicateCode(const vector<Subject> &subjects, const string &code);
    bool checkDuplicateName(const vector<Subject> &Subjects, const string &name);
    void display() const;
};

struct Registration
{
    string studentID;
    vector<string> subjectCodes;
    void input(istream &file);
    bool checkIdAndCode(const vector<Student> &students, const vector<Subject> &subjects);
    void display(const Registration &reg, const vector<Student> &students, const vector<Subject> &subjects) const;
};

void readData(vector<Student> &students, vector<Subject> &subjects, vector<Registration> &regs, const string &filename);

bool isValidStudentID(const string &id);
bool isValidSubjectCode(const string &code);
bool isValidName(const string &name);
bool isValidSubjectCredit(const string &credit);

void displayStudents(const vector<Student> &students);
void displaySubjects(const vector<Subject> &subjects);
void displayRegistrations(const vector<Registration> &regists, const vector<Student> &students, const vector<Subject> &subjects);

void searchStudent(const vector<Student> &students, const vector<Registration> &regists, const vector<Subject> &subjects);
void searchSubject(const vector<Subject> &subjects);
void searchRegistrationsBySubjectCode(const vector<Registration> &regists, const vector<Student> &students, const vector<Subject> &subjects);

string formatVietnamese(int num);
void generateStatistics(
    const vector<Registration> &regists,
    const vector<Student> &students,
    const vector<Subject> &subjects,
    const string &outputFile);

#endif
