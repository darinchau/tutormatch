#ifndef STUDENT_H
#define STUDENT_H

#include<vector>
#include<QString>
#include<QDebug>
#include<stdexcept>

const int NUM_DAYS_IN_WEEK = 5;
const int NUM_TIME_IN_DAY = 24;

// A student is a person with a timetable
class Student
{
private:
    bool timetable[NUM_DAYS_IN_WEEK][NUM_TIME_IN_DAY] = {{false}};
    bool is_tutor = false;
    bool respect_dayoff = true;
    QString name;
    QString student_id;

public:
    Student();
    void mark_timetable(bool occupied, int week, int time_slot);
    bool is_occupied(int week, int time_slot) const;
    bool is_occupied_or_dayoff(int week, int time_slot) const;

    QString get_name() const {
        return this -> name;
    }

    void set_name(const QString new_name) {
        this -> name = new_name;
    }

    QString get_sid() const {
        return this -> student_id;
    }

    void set_sid(const QString new_id) {
        this -> student_id = new_id;
    }

    bool get_is_tutor() const {
        return this -> is_tutor;
    }

    void set_is_tutor(bool new_state) {
        qDebug() << "Setting " << this->name << "'s tutor status to " << new_state;
        this -> is_tutor = new_state;
    }

    bool get_respect_dayoff() const {
        return this -> is_tutor;
    }

    void set_respect_dayoff(bool new_state) {
        qDebug() << "Setting " << this->name << "'s respect dayoff to " << new_state;
        this -> respect_dayoff = new_state;
    }
};

#endif // STUDENT_H
