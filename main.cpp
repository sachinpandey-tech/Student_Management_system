#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

// ================= PERSON CLASS =================
class Person {
protected:
    int id;
    string name;

public:
    Person() {}

    Person(int id, string name) {
        this->id = id;
        this->name = name;
    }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    void setName(string n) {
        name = n;
    }
};

// ================= STUDENT CLASS =================
class Student : public Person {
private:
    float marks;
    float attendance;

public:
    Student() {}

    Student(int id, string name,
            float marks,
            float attendance)
        : Person(id, name)
    {
        this->marks = marks;
        this->attendance = attendance;
    }

    float getMarks() const {
        return marks;
    }

    float getAttendance() const {
        return attendance;
    }

    void setMarks(float m) {
        marks = m;
    }

    void setAttendance(float a) {
        attendance = a;
    }

    string getGrade() const {

        if (marks >= 90)
            return "A";

        else if (marks >= 75)
            return "B";

        else if (marks >= 60)
            return "C";

        else if (marks >= 40)
            return "D";

        return "F";
    }

    void display() const {

        cout << "\n--------------------------\n";
        cout << "ID         : " << id << endl;
        cout << "Name       : " << name << endl;
        cout << "Marks      : " << marks << endl;
        cout << "Grade      : " << getGrade() << endl;
        cout << "Attendance : " << attendance << "%" << endl;
        cout << "--------------------------\n";
    }
};

// ================= GLOBAL VECTOR =================
vector<Student> students;

// ================= SAVE FILE =================
void saveToFile() {

    ofstream file("students.txt");

    for (const auto &s : students) {

        file << s.getId() << ","
             << s.getName() << ","
             << s.getMarks() << ","
             << s.getAttendance() << endl;
    }

    file.close();
}

// ================= LOAD FILE =================
void loadFromFile() {

    students.clear();

    ifstream file("students.txt");

    if (!file.is_open())
        return;

    string line;

    while (getline(file, line)) {

        stringstream ss(line);

        string idStr, name, marksStr, attendanceStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, marksStr, ',');
        getline(ss, attendanceStr, ',');

        students.push_back(
            Student(
                stoi(idStr),
                name,
                stof(marksStr),
                stof(attendanceStr)
            )
        );
    }

    file.close();
}

// ================= SEARCH =================
int findStudent(int id) {

    for (int i = 0; i < students.size(); i++) {

        if (students[i].getId() == id)
            return i;
    }

    return -1;
}

// ================= ADD =================
void addStudent() {

    int id;
    string name;
    float marks;
    float attendance;

    cout << "Enter ID: ";
    cin >> id;

    if (findStudent(id) != -1) {

        cout << "Student ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Marks: ";
    cin >> marks;

    cout << "Enter Attendance (%): ";
    cin >> attendance;

    students.push_back(
        Student(id, name, marks, attendance)
    );

    saveToFile();

    cout << "\nStudent Added Successfully!\n";
}

// ================= UPDATE =================
void updateStudent() {

    int id;

    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {

        cout << "Student Not Found!\n";
        return;
    }

    string name;
    float marks;
    float attendance;

    cin.ignore();

    cout << "Enter New Name: ";
    getline(cin, name);

    cout << "Enter New Marks: ";
    cin >> marks;

    cout << "Enter New Attendance: ";
    cin >> attendance;

    students[index].setName(name);
    students[index].setMarks(marks);
    students[index].setAttendance(attendance);

    saveToFile();

    cout << "\nRecord Updated Successfully!\n";
}

// ================= DELETE =================
void deleteStudent() {

    int id;

    cout << "Enter ID to Delete: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {

        cout << "Student Not Found!\n";
        return;
    }

    students.erase(students.begin() + index);

    saveToFile();

    cout << "\nStudent Deleted Successfully!\n";
}

// ================= SEARCH DISPLAY =================
void searchStudent() {

    int id;

    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {

        cout << "Student Not Found!\n";
        return;
    }

    students[index].display();
}

// ================= DISPLAY ALL =================
void displayAll() {

    if (students.empty()) {

        cout << "\nNo Records Available!\n";
        return;
    }

    for (const auto &s : students)
        s.display();
}

// ================= SORT =================
void sortByMarks() {

    sort(students.begin(),
         students.end(),
         [](Student a, Student b) {
             return a.getMarks() > b.getMarks();
         });

    cout << "\nStudents Sorted By Marks!\n";

    displayAll();
}

// ================= REPORT CARD =================
void generateReport() {

    int id;

    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {

        cout << "Student Not Found!\n";
        return;
    }

    Student s = students[index];

    cout << "\n========== REPORT CARD ==========\n";
    cout << "Name       : " << s.getName() << endl;
    cout << "ID         : " << s.getId() << endl;
    cout << "Marks      : " << s.getMarks() << endl;
    cout << "Grade      : " << s.getGrade() << endl;
    cout << "Attendance : "
         << s.getAttendance() << "%" << endl;
    cout << "=================================\n";
}

// ================= MAIN =================
int main() {

    loadFromFile();

    int choice;

    do {

        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====\n";

        cout << "1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Search Student\n";
        cout << "5. Display All Students\n";
        cout << "6. Sort By Marks\n";
        cout << "7. Generate Report Card\n";
        cout << "8. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addStudent();
            break;

        case 2:
            updateStudent();
            break;

        case 3:
            deleteStudent();
            break;

        case 4:
            searchStudent();
            break;

        case 5:
            displayAll();
            break;

        case 6:
            sortByMarks();
            break;

        case 7:
            generateReport();
            break;

        case 8:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}