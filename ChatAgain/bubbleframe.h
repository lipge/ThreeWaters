#ifndef BUBBLEFRAME_H
#define BUBBLEFRAME_H

#include <QFrame>
#include "global.h"
#include <QHBoxLayout>

class BubbleFrame : public QFrame
{
public:
    BubbleFrame(MessageRole role, QWidget* parent);
    void setWidget(QWidget* w);
    void setMargin(int size);
protected:
    void paintEvent(QPaintEvent *) override;

private:
    QHBoxLayout* hLayout;
    int _margin;
    MessageRole _role;
};

#endif // BUBBLEFRAME_H
