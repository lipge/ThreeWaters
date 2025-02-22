#include "customizeedit.h"
#include <QAction>
#include <QMouseEvent>
CustomizeEdit::CustomizeEdit(QWidget* parent)
    :QLineEdit(parent)
{
}

void CustomizeEdit::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void CustomizeEdit::focusInEvent(QFocusEvent *e)
{
    emit focusIn();
    QLineEdit::focusInEvent(e);
}

void CustomizeEdit::focusOutEvent(QFocusEvent *e)
{
    emit focusOut();
    QLineEdit::focusOutEvent(e);
}

