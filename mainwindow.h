#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "student.h"
#include <vector>
#include <stdexcept>
#include "togglebutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initialize_window_with_student(const Student* student);
    Student* get_current_student() {
        return &(this -> students[this -> current_student_idx]);
    }

    unsigned int get_num_students() const {
        return this -> students.size();
    }

    int get_current_student_idx() const {
        return this -> current_student_idx;
    }

    void set_current_student_idx(int val) {
        if (val < 0) {
            throw std::runtime_error("Trying to set a negative value to student index");
        }
        this -> current_student_idx = val;
    }

    void refresh_ui() {
        this -> initialize_window_with_student(this -> get_current_student());
    }

private:
    Ui::MainWindow *ui;
    std::vector<Student> students;
    int current_student_idx = 0;
    ToggleButton* buttons[NUM_DAYS_IN_WEEK][NUM_TIME_IN_DAY] = {{nullptr}};

private slots:
    void update_name();
    void update_sid();
    void calculate();
    void update_tutor(int state);
    void update_respect_dayoff(int state);
    void update_next_student();
    void update_prev_student();
};
#endif // MAINWINDOW_H
