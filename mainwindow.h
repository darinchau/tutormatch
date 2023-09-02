#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "student.h"
#include <vector>

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
    Student* get_current_student() { return &(this -> students[current_student]); }

private:
    Ui::MainWindow *ui;
    std::vector<Student> students;
    int current_student;

private slots:
    void update_name();
    void update_sid();
    void calculate();
};
#endif // MAINWINDOW_H
