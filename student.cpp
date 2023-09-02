#include "student.h"
#include <QDebug>

Student::Student():
    name{QString{}},
    student_id{QString{}}
{

}

bool Student::is_occupied(int week, int time_slot) const {
    if (week >= NUM_DAYS_IN_WEEK || week < 0 || time_slot >= NUM_TIME_IN_DAY || time_slot < 0) {
        throw std::runtime_error("Indices out of bounds in student.");
    }
    return this -> timetable[week][time_slot];
}

void Student::mark_timetable(bool occupied, int week, int time_slot) {
    qDebug() << "Marking timetable " << week << " " << time_slot << " to "  << occupied;
    if (week >= NUM_DAYS_IN_WEEK || week < 0 || time_slot >= NUM_TIME_IN_DAY || time_slot < 0) {
        throw std::runtime_error("Indices out of bounds in student.");
    }
    this -> timetable[week][time_slot] = occupied;
}
