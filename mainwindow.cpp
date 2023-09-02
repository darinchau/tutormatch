#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

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
            QPushButton* button = new QPushButton("Button " + QString::number(button_number));
            grid_layout ->addWidget(button, row, col);

            // Optionally, connect a slot to handle button clicks
            connect(button, &QPushButton::clicked, [=]() {
                // Handle button click
                qDebug() << "Button " << button_number << " clicked.";
            });
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

