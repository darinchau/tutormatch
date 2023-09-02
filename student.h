#ifndef STUDENT_H
#define STUDENT_H

#include<vector>
#include<QString>
#include<stdexcept>

const int NUM_DAYS_IN_WEEK = 5;
const int NUM_TIME_IN_DAY = 24;

// A student is a person with a timetable
class Student
{
private:
    bool timetable[NUM_DAYS_IN_WEEK][NUM_TIME_IN_DAY] = {{false}};
    bool is_tutor = false;
    QString name;
    QString student_id;

public:
    Student();
    void mark_timetable(bool occupied, int week, int time_slot);
    bool get_is_tutor() const {
        return this -> is_tutor;
    }
    bool is_occupied(int week, int time_slot) const;
};

#endif // STUDENT_H
