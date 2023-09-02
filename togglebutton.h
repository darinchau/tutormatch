#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <QPushButton>
#include <vector>
#include <QDebug>

class ToggleButton : public QPushButton {
    Q_OBJECT
private:
    bool toggled;
    std::vector<std::function<void(bool)>> onclick_events;

public:
    explicit ToggleButton(const QString& label, QWidget* parent = nullptr);
    void register_onclick(const std::function<void(bool)>& f);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        QPushButton::mousePressEvent(event);
        emit clicked();
    }

private slots:
    void handleClicked() {
        this -> toggled = !(this -> toggled);
        for(const auto& f: this -> onclick_events) {
            f(this -> toggled);
        }
    }
};

#endif // TOGGLEBUTTON_H
