#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QLabel>

class TextWidget : public QLabel {
public:
    TextWidget(QWidget* parent = nullptr)
        : QLabel(parent) {
        this->setWordWrap(true);
        this->setFont(QFont("Arial", 16));
    }
};

#endif // TEXTWIDGET_H
