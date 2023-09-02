#include <iostream>
#include <QDebug>
#include <memory>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <string>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "togglebutton.h"
#include "student.h"

const char* WEEK[NUM_DAYS_IN_WEEK] = {
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri"
};

const char* TIME_RANGES[NUM_TIME_IN_DAY]  = {
    "9:00am - 9:30am",
    "9:30am - 10:00am",
    "10:00am - 10:30am",
    "10:30am - 11:00am",
    "11:00am - 11:30am",
    "11:30am - 12:00pm",
    "12:00pm - 12:30pm",
    "12:30pm - 1:00pm",
    "1:00pm - 1:30pm",
    "1:30pm - 2:00pm",
    "2:00pm - 2:30pm",
    "2:30pm - 3:00pm",
    "3:00pm - 3:30pm",
    "3:30pm - 4:00pm",
    "4:00pm - 4:30pm",
    "4:30pm - 5:00pm",
    "5:00pm - 5:30pm",
    "5:30pm - 6:00pm",
    "6:00pm - 6:30pm",
    "6:30pm - 7:00pm",
    "7:00pm - 7:30pm",
    "7:30pm - 8:00pm",
    "8:00pm - 8:30pm",
    "8:30pm - 9:00pm"
};

ToggleButton* create_button (const int num_rows, const int num_cols, const int row, const int col) {
    const QString button_name = QString(WEEK[col - 1]) + QString(" ") + QString(TIME_RANGES[row - 1]);
    ToggleButton* button = new ToggleButton(button_name);

    // Change button color on click
    button -> register_onclick([](ToggleButton* const button, bool state_after_click) {
        if (state_after_click) {
            button -> setStyleSheet("background-color: #3eb489; color: black;");
        }
        else {
            button -> setStyleSheet("background-color: white; color: black;");
        }
    });

    return button;
}

void add_labels(QGridLayout* const& grid_layout) {
    for (int i = 0; i < 5; i++) {
        QLabel* label = new QLabel(QString(WEEK[i]));
        label -> setAlignment(Qt::AlignCenter);
        grid_layout -> addWidget(label, 0, i+1);
    }

    for (int i = 0; i < 24; i++) {
        QLabel* label = new QLabel(QString(TIME_RANGES[i]));
        label -> setAlignment(Qt::AlignLeft);
        grid_layout -> addWidget(label, i+1, 0);
    }
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    students{1, Student()}
{
    ui->setupUi(this);

    // Initialize the grid layout
    QGridLayout* const& grid_layout = this -> ui -> grid;

    grid_layout -> setSpacing(0);
    grid_layout ->setContentsMargins(0, 0, 0, 0);

    add_labels(grid_layout);

    const int num_rows = NUM_TIME_IN_DAY;
    const int num_cols = NUM_DAYS_IN_WEEK;
    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            ToggleButton* button = create_button(num_rows, num_cols, row+1, col+1);

            // Change the current student event
            button -> register_onclick([this, row, col](ToggleButton* const button, bool state_after_click) {
                Student* student = this -> get_current_student();
                student -> mark_timetable(state_after_click, col, row);
            });

            grid_layout -> addWidget(button, row+1, col+1);
        }
    }

    this -> refresh_ui();

    // Hook the text box and button events onto the current student
    connect(this -> ui -> name_textbox, &QTextEdit::textChanged, this, &MainWindow::update_name);
    connect(this -> ui -> sid_textbox, &QTextEdit::textChanged, this, &MainWindow::update_sid);
    connect(this -> ui -> calculate_button, &QPushButton::clicked, this, &MainWindow::calculate);
    connect(this -> ui -> tutor_checkbox, &QCheckBox::stateChanged, this, &MainWindow::update_tutor);
    connect(this -> ui -> respect_dayoff_checkbox, &QCheckBox::stateChanged, this, &MainWindow::update_respect_dayoff);
    connect(this -> ui -> next_student, &QPushButton::clicked, this, &MainWindow::update_next_student);
    connect(this -> ui -> prev_student, &QPushButton::clicked, this, &MainWindow::update_prev_student);

    // Precheck the dayoff thing
    this -> ui -> respect_dayoff_checkbox -> setChecked(true);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::update_name() {
    const QString text = this -> ui -> name_textbox -> toPlainText();
    this -> get_current_student() -> set_name(text);
}

void MainWindow::update_sid() {
    const QString text = this -> ui -> sid_textbox -> toPlainText();
    qDebug() << text;
    this -> get_current_student() -> set_sid(text);
}

// Load the current setting for a given student
void MainWindow::initialize_window_with_student(const Student* student) {
    qDebug() << "Initializing student";
}

void MainWindow::calculate() {
    // Implement later
    qDebug() << "Calculate is pressed";
}

void MainWindow::update_tutor(int state) {
    this -> get_current_student() -> set_is_tutor(state != 0);
}

void MainWindow::update_respect_dayoff(int state) {
    this -> get_current_student() -> set_respect_dayoff(state != 0);
}

void MainWindow::update_next_student() {
    int current_idx = this -> get_current_student_idx();
    if (current_idx == this -> get_num_students() - 1) {
        Student new_student = Student();
        this -> students.push_back(new_student);
    }

    this -> set_current_student_idx(current_idx + 1);
    this -> refresh_ui();
}

void MainWindow::update_prev_student() {
    int current_idx = this -> get_current_student_idx();
    if (current_idx == 0) {
        return;
    }
    this -> set_current_student_idx(current_idx - 1);
    this -> refresh_ui();
}
