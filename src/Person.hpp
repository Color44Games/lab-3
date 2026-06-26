#pragma once

#include <cstring>

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
    const char* firstName;
    const char* middleName;
    const char* lastName;
    int age;

public:
    // Конструкторы и деструктор
    Person() : id{0, 0}, firstName(""), middleName(""), lastName(""), age(0) {}
    Person(PersonID person_id, const char* first_name, const char* middle_name, const char* last_name, int person_age)
        : id(person_id), firstName(first_name), middleName(middle_name), lastName(last_name), age(person_age) {}
    virtual ~Person() = default;

    // Геттеры
    PersonID GetID() const {
        return this->id;
    }

    const char* GetFirstName() const {
        return this->firstName;
    }

    const char* GetMiddleName() const {
        return this->middleName;
    }

    const char* GetLastName() const {
        return this->lastName;
    }

    char* GetFullName() const {
        char* fullName =
            new char[std::strlen(this->firstName) + std::strlen(this->middleName) + std::strlen(this->lastName) + 3];

        std::strcpy(fullName, this->firstName);
        std::strcat(fullName, " ");
        std::strcat(fullName, this->middleName);
        std::strcat(fullName, " ");
        std::strcat(fullName, this->lastName);

        return fullName;
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
    Student(PersonID person_id, const char* first_name, const char* middle_name, const char* last_name, int person_age,
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
    const char* subjectName;
    const char* facultyName;

public:
    // Конструкторы
    Teacher() : Person(), subjectName(""), facultyName("") {}
    Teacher(PersonID person_id, const char* first_name, const char* middle_name, const char* last_name, int person_age,
            const char* subject_name, const char* faculty_name)
        : Person(person_id, first_name, middle_name, last_name, person_age),
          subjectName(subject_name),
          facultyName(faculty_name) {}
    ~Teacher() override = default;

    // Геттеры
    const char* GetSubjectName() const {
        return this->subjectName;
    }

    const char* GetFacultyName() const {
        return this->facultyName;
    }
};