#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include "togglebutton.h"
#include <memory>

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

    // Set up all the buttons programmatically
    const int num_rows = 25;
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

