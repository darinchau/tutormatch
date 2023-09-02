#include "student.h"
#include <QDebug>

Student::Student():
    name{QString{}},
    student_id{QString{}}
{

}

// Returns whether the student is occupied at the specified time slot.
bool Student::is_occupied(int week, int time_slot) const {
    if (week >= NUM_DAYS_IN_WEEK || week < 0 || time_slot >= NUM_TIME_IN_DAY || time_slot < 0) {
        throw std::runtime_error("Indices out of bounds in student.");
    }
    return this -> timetable[week][time_slot];
}

void Student::mark_timetable(bool occupied, int week, int time_slot) {
    if (week >= NUM_DAYS_IN_WEEK || week < 0 || time_slot >= NUM_TIME_IN_DAY || time_slot < 0) {
        throw std::runtime_error("Indices out of bounds in student.");
    }
    qDebug() << "Marking timetable " << week << " " << time_slot << " to "  << occupied;
    this -> timetable[week][time_slot] = occupied;
}

bool Student::is_occupied_or_dayoff(int week, int time_slot) const {
    bool is_occupied = this -> is_occupied(week, time_slot);
    if (is_occupied) {
        return true;
    }
}
