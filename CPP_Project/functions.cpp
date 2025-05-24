#include "functions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <regex>
using namespace std;

// ===== Khai báo các hàm của struct Student =====
void Student::input(istream &file)
{
    file >> id;
    file.ignore();
    string line;
    getline(file, line);
    name = line;
}

void Student::display() const
{
    cout << "ID: " << id << endl;
    cout << "-> Name: " << name << endl;
}

bool Student::checkDuplicateID(const vector<Student> &students, const string &id)
{
    for (const Student &s : students)
    {
        if (s.id == id)
        {
            return true;
        }
    }
    return false;
}

// ===== Khai báo các hàm của struct Subject =====
void Subject::input(istream &file)
{
    file >> code >> credit;
    file.ignore();
    string line;
    getline(file, line);
    name = line;
}

void Subject::display() const
{
    cout << "Code: " << code << endl;
    cout << "-> Subject: " << name << endl;
    cout << "-> Credits: " << credit << endl;
}

bool Subject::checkDuplicateCode(const vector<Subject> &subjects, const string &code)
{
    for (const auto &sub : subjects)
    {
        if (sub.code == code)
        {
            return true;
        }
    }
    return false;
}

bool Subject::checkDuplicateName(const vector<Subject> &subjects, const string &name)
{
    for (const auto &sub : subjects)
    {
        if (sub.name == name)
        {
            return true;
        }
    }
    return false;
}

// ===== Khai báo các hàm của struct Registration =====
void Registration::input(istream &file)
{
    subjectCodes.clear();
    string line;
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> studentID;
        string subjectCode;
        while (ss >> subjectCode)
        {
            subjectCodes.push_back(subjectCode);
        }
    }
}

void Registration::display(const Registration &reg, const vector<Student> &students, const vector<Subject> &subjects) const
{
    int totalCredit = 0;
    string studentName = "Unknown";
    for (const auto &s : students)
    {
        if (s.id == reg.studentID)
        {
            studentName = s.name;
            break;
        }
    }

    cout << "Student: " << studentName << " (ID: " << reg.studentID << ")\n";
    for (const string &code : reg.subjectCodes)
    {
        for (const auto &subject : subjects)
        {
            if (subject.code == code)
            {
                totalCredit += stoi(subject.credit);
                cout << " -> Subject: " << subject.name << " (Code: " << code << ")\n";
                break;
            }
        }
    }
    cout << " --> Total credit: " << totalCredit << endl;
}

bool Registration::checkIdAndCode(const vector<Student> &students, const vector<Subject> &subjects)
{
    // Kiểm tra studentID có tồn tại
    bool foundStudent = false;
    for (const auto &s : students)
    {
        if (s.id == studentID)
        {
            foundStudent = true;
            break;
        }
    }

    // Kiểm tra tất cả subjectCodes có tồn tại
    bool allSubjectsExist = true;
    for (const auto &code : subjectCodes)
    {
        bool found = false;
        for (const auto &sub : subjects)
        {
            if (sub.code == code)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            allSubjectsExist = false;
            break;
        }
    }

    // Nếu sinh viên tồn tại và tất cả môn học đều hợp lệ → return false (không có lỗi)
    // Ngược lại → return true (có lỗi)
    return !(foundStudent && allSubjectsExist);
}

// ===== Đọc dữ liệu từ file =====
void readData(vector<Student> &students, vector<Subject> &subjects, vector<Registration> &regs, const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error opening file\n";
        exit(1);
    }
    int lineNumber = 0;
    int errors = 0;
    string line;
    // Phần sinh viên
    while (getline(file, line) && line != "***")
    {
        lineNumber++;
        Student s;
        istringstream iss(line);
        s.input(iss);
        if (s.checkDuplicateID(students, s.id))
        {
            errors++;
            cout << errors << ". Duplicate student ID at line " << lineNumber << endl;
        }
        if (!isValidStudentID(s.id))
        {
            errors++;
            cout << errors << ". Invalid student ID at line " << lineNumber << endl;
        }
        if (!isValidName(s.name))
        {
            errors++;
            cout << errors << ". Invalid student Name at line " << lineNumber << endl;
        }
        students.push_back(s);
    }
    lineNumber++;

    // Phần môn học
    while (getline(file, line) && line != "***")
    {
        lineNumber++;
        Subject c;
        istringstream iss(line);
        c.input(iss);
        if (c.checkDuplicateCode(subjects, c.code))
        {
            errors++;
            cout << errors << ". Duplicate subject Code at line " << lineNumber << endl;
        }
        if (c.checkDuplicateName(subjects, c.name))
        {
            errors++;
            cout << errors << ". Duplicate subject Name at line " << lineNumber << endl;
        }
        if (!isValidSubjectCode(c.code))
        {
            errors++;
            cout << errors << ". Invalid subject Code at line " << lineNumber << endl;
        }
        if (!isValidSubjectCredit(c.credit))
        {
            errors++;
            cout << errors << ". Invalid subject Credit at line " << lineNumber << endl;
        }
        if (!isValidName(c.name))
        {
            errors++;
            cout << errors << ". Invalid subject Name at line " << lineNumber << endl;
        }
        subjects.push_back(c);
    }
    lineNumber++;

    // Phần đăng ký
    while (getline(file, line))
    {
        lineNumber++;
        Registration r;
        istringstream iss(line);
        r.input(iss);
        if (r.checkIdAndCode(students, subjects))
        {
            errors++;
            cout << errors << ". Invalid subject Code or student ID at line " << lineNumber << endl;
        }
        regs.push_back(r);
    }
    if (errors != 0)
    {
        cout << endl;
        cout << "Please fix data file before continue!" << endl;
        exit(1);
    }

    file.close();
}

// ===== Hàm check mã sv và mã mh =====
bool isValidStudentID(const string &id)
{
    regex pattern("^SV\\d{2}$");
    return regex_match(id, pattern);
}
bool isValidSubjectCode(const string &id)
{
    regex pattern("^MH\\d{2}$");
    return regex_match(id, pattern);
}
bool isValidName(const string &name)
{
    if (name.empty())
        return false;
    for (char c : name)
    {
        if (!isalpha(c) && !isspace(c))
            return false;
    }
    return true;
}
bool isValidSubjectCredit(const string &credit)
{
    if (credit.empty())
        return false;
    for (char c : credit)
    {
        if (!isdigit(c))
            return false;
    }
    if (stoi(credit) > 4 || stoi(credit) <= 0)
        return false;
    return true;
}
// ===== Hiển thị danh sách =====
void displayStudents(const vector<Student> &students)
{
    cout << "--------------" << endl;
    cout << "Student list: " << students.size() << " students" << endl;
    cout << "--------------" << endl;
    for (const auto &s : students)
    {
        s.display();
        cout << endl;
    }
}

void displaySubjects(const vector<Subject> &subjects)
{
    cout << "--------------" << endl;
    cout << "Subject list: " << subjects.size() << " subjects" << endl;
    cout << "--------------" << endl;
    for (const auto &s : subjects)
    {
        s.display();
        cout << endl;
    }
}

void displayRegistrations(const vector<Registration> &regists, const vector<Student> &students, const vector<Subject> &subjects)
{
    cout << "--------------" << endl;
    cout << "Registration list: " << regists.size() << " registrations" << endl;
    cout << "--------------" << endl;
    for (const auto &r : regists)
    {
        r.display(r, students, subjects);
        cout << endl;
    }
}

// ===== Tìm kiếm =====
void searchStudent(const vector<Student> &students, const vector<Registration> &regists, const vector<Subject> &subjects)
{
    cout << "--------------" << endl;
    string id = "";
    while (!isValidStudentID(id))
    {
        cout << "Enter student ID you want to search (VD: SV01): ";
        cin >> id;
    }

    for (const auto &st : students)
    {
        if (st.id == id)
        {
            int sum = 0;
            cout << endl;
            cout << "Student data:\n";
            cout << endl;
            st.display();
            cout<<endl;
            cout<<"Subjects registered:"<<endl;
            for (const auto &r : regists)
            {
                if (r.studentID == id)
                {
                    for (const auto &code : r.subjectCodes)
                    {
                        for (const auto &subject : subjects)
                        {
                            if (subject.code == code)
                            {
                                sum += stoi(subject.credit);
                                subject.display();
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            cout << "-----------------------------------" << endl;
            cout << "Total credits registered: " << sum << endl;
            return;
        }
    }

    cout << "There is no student with ID " << id << endl;
}

void searchSubject(const vector<Subject> &subjects)
{
    cout << "--------------" << endl;
    string code = "";
    while (!isValidSubjectCode(code))
    {
        cout << "Enter subject Code you want to search (VD: MH01): ";
        cin >> code;
    }

    for (const auto &s : subjects)
    {
        if (s.code == code)
        {
            cout << endl;
            cout << "Subject data:\n";
            cout << endl;
            s.display();
            return;
        }
    }
    cout << "There is no subject with Code " << code << endl;
}

void searchRegistrationsBySubjectCode(const vector<Registration> &regists, const vector<Student> &students, const vector<Subject> &subjects)
{
    cout << "--------------" << endl;
    string code;
    cout << "Enter the Subject code for Registration list: ";
    cin >> code;

    vector<string> studentIDs;
    for (const auto &r : regists)
    {
        if (find(r.subjectCodes.begin(), r.subjectCodes.end(), code) != r.subjectCodes.end())
        {
            studentIDs.push_back(r.studentID);
        }
    }

    if (studentIDs.empty())
    {
        cout << "No student enrolled in this subject." << endl;
    }
    else
    {
        cout << "Students enrolled in subject " << code << ":" << endl;
        for (const auto &id : studentIDs)
        {
            for (const auto &s : students)
            {
                if (s.id == id)
                {
                    s.display();
                    cout << endl;
                    break;
                }
            }
        }
    }
}

// ===== Thống kê học phí và Số tín chỉ của mỗi sinh viên =====
string formatVietnamese(int num)
{
    string str = to_string(num);
    int insertPos = str.length() - 3;

    while (insertPos > 0)
    {
        str.insert(insertPos, ".");
        insertPos -= 3;
    }

    return str;
}

void generateStatistics(
    const vector<Registration> &regists,
    const vector<Student> &students,
    const vector<Subject> &subjects,
    const string &outputFile)
{

    ofstream out(outputFile);
    if (!out)
    {
        cerr << "Cannot open file: " << outputFile << endl;
        return;
    }
    int totalRevenue = 0;
    out << "Subject Registration Statistics\n";
    for (const auto &sub : subjects)
    {
        int count = 0;
        for (const auto &reg : regists)
        {
            if (find(reg.subjectCodes.begin(), reg.subjectCodes.end(), sub.code) != reg.subjectCodes.end())
            {
                count++;
            }
        }
        totalRevenue += stoi(sub.credit) * sub.TUITION_PER_CREDIT * count;
        out << sub.code << " - " << sub.name
            << ": " << count << " student(s) - Total tuition: "
            << formatVietnamese(stoi(sub.credit) * sub.TUITION_PER_CREDIT * count) << " VND\n";
    }
    out << "Total Revenue: " << formatVietnamese(totalRevenue) << " VND" << endl;
    out << endl;
    out << "Student Registration Statistics" << endl;

    for (const auto &student : students)
    {
        int totalCredits = 0;
        vector<string> registeredSubjects;

        for (const auto &reg : regists)
        {
            if (reg.studentID == student.id)
            {
                registeredSubjects = reg.subjectCodes;

                for (const auto &subCode : reg.subjectCodes)
                {
                    for (const auto &sub : subjects)
                    {
                        if (sub.code == subCode)
                        {
                            totalCredits += stoi(sub.credit);
                            break;
                        }
                    }
                }
                break; // mỗi sinh viên chỉ có một bản ghi đăng ký
            }
        }

        out << student.id << " - " << student.name << "\n";
        out << "  Subjects registered (" << registeredSubjects.size() << "): ";

        for (const auto &code : registeredSubjects)
        {
            out << code << " ";
        }

        out << "\n  Total credits: " << totalCredits;

        if (totalCredits < 15)
        {
            out << " -> Đăng ký thiếu tín chỉ!";
        }

        out << "\n\n";
    }

    out.close();
    cout << "--------------" << endl;
    cout << "Statistics written to file: " << outputFile << endl;
    cout << "--------------" << endl;
}
