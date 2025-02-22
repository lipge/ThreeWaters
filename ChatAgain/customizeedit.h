#ifndef CUSTOMIZEEDIT_H
#define CUSTOMIZEEDIT_H
#include <QLineEdit>


class CustomizeEdit:public QLineEdit
{
    Q_OBJECT
public:
    CustomizeEdit(QWidget* parent);


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void focusInEvent(QFocusEvent *) override;
    void focusOutEvent(QFocusEvent *) override;


signals:
    void focusIn();
    void focusOut();

};

#endif // CUSTOMIZEEDIT_H
