#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include "togglebutton.h"

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
    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            int button_number = row * num_cols + col;
            const auto button_name = "Button " + QString::number(button_number);
            ToggleButton* button = new ToggleButton(button_name);

            // Onclick event for button
            const auto button_event = [=](bool state_after_click) {
                qDebug() << "Button " << button_number << " is toggled:" << state_after_click;
            };

            button -> register_onclick(button_event);

            grid_layout -> addWidget(button, row, col);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

