#pragma once

#include <string>

struct PersonID {
    int series;
    int number;

    bool operator==(const PersonID& other) const {
        return this->series == other.series && this->number == other.number;
    }
};

class Person {
protected:
    PersonID id;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    int age;

public:
    // Конструкторы и деструктор
    Person() : id{0, 0}, firstName(""), middleName(""), lastName(""), age(0) {}
    Person(PersonID person_id, std::string first_name, std::string middle_name, std::string last_name, int person_age)
        : id(person_id), firstName(first_name), middleName(middle_name), lastName(last_name), age(person_age) {}
    virtual ~Person() = default;

    // Геттеры
    PersonID GetID() const {
        return this->id;
    }

    std::string GetFirstName() const {
        return this->firstName;
    }

    std::string GetMiddleName() const {
        return this->middleName;
    }

    std::string GetLastName() const {
        return this->lastName;
    }

    std::string GetFullName() const {
        return this->firstName + " " + this->middleName + " " + this->lastName;
    }

    // Перегрузка операторов
    bool operator==(const Person& other) const {
        return this->id == other.id;
    }

    bool operator!=(const Person& other) const {
        return !(*this == other);
    }
};


class Student : public Person {
private:
    int groupNumber;
    int admissionYear;
    double averageGrade;

public:
    // Конструкторы и деструктор
    Student() : Person(), groupNumber(0), admissionYear(0), averageGrade(0.0) {}
    Student(PersonID person_id, std::string first_name, std::string middle_name, std::string last_name, int person_age,
            int group_number, int admission_year, double average_grade)
        : Person(person_id, first_name, middle_name, last_name, person_age),
          groupNumber(group_number),
          admissionYear(admission_year),
          averageGrade(average_grade) {}
    ~Student() override = default;

    // Геттеры
    int GetGroupNumber() const {
        return this->groupNumber;
    }

    int GetAdmisionYear() const {
        return this->admissionYear;
    }

    double GetAverageGrade() const {
        return this->averageGrade;
    }
};


class Teacher : public Person {
private:
    std::string subjectName;
    std::string facultyName;

public:
    // Конструкторы
    Teacher() : Person(), subjectName(""), facultyName("") {}
    Teacher(PersonID person_id, std::string first_name, std::string middle_name, std::string last_name, int person_age,
            std::string subject_name, std::string faculty_name)
        : Person(person_id, first_name, middle_name, last_name, person_age),
          subjectName(subject_name),
          facultyName(faculty_name) {}
    ~Teacher() override = default;

    // Геттеры
    std::string GetSubjectName() const {
        return this->subjectName;
    }

    std::string GetFacultyName() const {
        return this->facultyName;
    }
};