#include "togglebutton.h"
#include <QDebug>

ToggleButton::ToggleButton(const QString& label, int row, int col, QWidget* parent):
    QPushButton(label, parent),
    toggled{false},
    row{row},
    col{col},
    onclick_events{}
{
    // Connect the onclick events
    connect(this, &QPushButton::clicked, this, &ToggleButton::handleClicked);
}

void ToggleButton::register_onclick(const ToggleButton::ClickEvent& f) {
    this -> onclick_events.push_back(f);
}

void ToggleButton::update_ui() {
    if (this -> is_toggled()) {
        this -> setStyleSheet("background-color: #3eb489; color: black;");
    }
    else {
        this -> setStyleSheet("background-color: white; color: black;");
    }
}
