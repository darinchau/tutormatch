#ifndef CALCULATE_H
#define CALCULATE_H

#include "student.h"

// The const Student& typedef so we can put these in a vector
typedef std::reference_wrapper<const Student> StudentReference;

// A tutor is a student but also has a vector of students
class Tutor {
    const StudentReference tutor_student;
    std::vector<StudentReference> students;

public:
    // The higher this score, the more time slots the tutor and students ahve commonly available
    // Availability score based on the number of time slots the tutor and students are available
    // Take into account the upper limit thing
    int get_availability_score() const;

    bool operator<(const Tutor& other) const {
        return this -> get_availability_score() < other.get_availability_score();
    }

    Tutor(StudentReference s): tutor_student{s} {
        this -> students = std::vector<StudentReference>{};
    }

    void add_student(StudentReference s) {
        this -> students.push_back(s);
    }

    void pop_student() {
        this -> students.pop_back();
    }

    QString get_student_id() const {
        return this -> tutor_student.get().get_sid();
    }
};

bool calculate(std::vector<StudentReference>, std::vector<Tutor> tutors);

#endif // CALCULATE_H
