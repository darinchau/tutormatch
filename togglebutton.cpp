#include "togglebutton.h"
#include <QDebug>

ToggleButton::ToggleButton(const QString& label, QWidget* parent):
    QPushButton(label, parent),
    toggled{false},
    onclick_events{}
{
    connect(this, &QPushButton::clicked, this, &ToggleButton::handleClicked);
}

void ToggleButton::register_onclick(const std::function<void(bool)>& f) {
    this -> onclick_events.push_back(f);
}
