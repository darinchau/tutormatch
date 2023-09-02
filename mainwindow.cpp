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

ToggleButton* create_button (const int num_rows, const int num_cols, const int row, const int col) {
    int button_number = row * num_cols + col;
    const auto button_name = "Button " + QString::number(button_number);
    ToggleButton* button = new ToggleButton(button_name);

    // Onclick event for button
    button -> register_onclick([=](ToggleButton* const button, bool state_after_click) {
        qDebug() << "Button " << button_number << " is toggled:" << state_after_click;
    });

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

QLabel* create_week_label(const QString text) {
    QLabel* label = new QLabel(text);
    label -> setAlignment(Qt::AlignCenter);
    return label;
}

QLabel* create_time_label(const QString text) {
    QLabel* label = new QLabel(text);
    label -> setAlignment(Qt::AlignLeft);
    return label;
}

void add_labels(QGridLayout* const& grid_layout) {
    grid_layout -> addWidget(create_week_label("Mon"), 0, 1);
    grid_layout -> addWidget(create_week_label("Tue"), 0, 2);
    grid_layout -> addWidget(create_week_label("Wed"), 0, 3);
    grid_layout -> addWidget(create_week_label("Thu"), 0, 4);
    grid_layout -> addWidget(create_week_label("Fri"), 0, 5);

    const char* time_ranges[24] = {
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

    for (int i = 0; i < 24; i++) {
        QLabel* label = create_time_label(QString(time_ranges[i]));
        grid_layout -> addWidget(label, i+1, 0);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Do grid stuff
    QGridLayout* const& grid_layout = this -> ui -> grid;

    // Remove small gap between buttons
    grid_layout -> setSpacing(0);
    grid_layout->setContentsMargins(0, 0, 0, 0);

    // Add the time labels
    add_labels(grid_layout);

    // Set up all the buttons programmatically
    const int num_rows = 24;
    const int num_cols = 5;
    for (int row = 1; row <= num_rows; ++row) {
        for (int col = 1; col <= num_cols; ++col) {
            ToggleButton* button = create_button(num_rows, num_cols, row, col);
            grid_layout -> addWidget(button, row, col);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

