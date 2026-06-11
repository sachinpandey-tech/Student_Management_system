#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

class Person
{
protected:
    int id;
    string name;

public:
    Person() {}

    Person(int id, string name)
    {
        this->id = id;
        this->name = name;
    }

    int getId()
    {
        return id;
    }

    string getname()
    {
        return name;
    }

    void setname(string n)
    {
        name = n;
    }
};

class Student : public Person
{
private:
    float marks;
    float attendance;

public:
    Student() {}

    Student(int id, string name, float marks, float attendance) : Person(id, name)
    {
        this->marks = marks;
        this->attendance = attendance;
    }

    float getMarks() const
    {
        return marks;
    }

    float getAttendance() const
    {
        return attendance;
    }

    void setGrade(float g)
    {
        marks = g;
    }

    void setAttendance(float a)
    {
        attendance = a;
    }

    string getGrade() const
    {

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
}