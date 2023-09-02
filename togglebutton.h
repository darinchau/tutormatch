#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <QPushButton>
#include <vector>
#include <QDebug>

class ToggleButton : public QPushButton {
    Q_OBJECT
public:
    typedef std::function<void(ToggleButton* const, bool)> ClickEvent;

private:
    bool toggled;
    int row;
    int col;
    std::vector<ClickEvent> onclick_events;

public:
    explicit ToggleButton(const QString& label, int row, int col, QWidget* parent = nullptr);
    void register_onclick(const ClickEvent& f);
    bool is_toggled() const {
        return this -> toggled;
    }

    void set_toggled(bool val) {
        this -> toggled = val;
    }

    // This functions updates the color to match with the current toggle state
    void update_ui();

    int get_row() {
        return this -> row;
    }

    int get_col() {
        return this -> col;
    }
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
            f(this, this -> toggled);
        }
    }
};

#endif // TOGGLEBUTTON_H
