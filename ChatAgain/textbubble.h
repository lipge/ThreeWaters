#ifndef TEXTBUBBLE_H
#define TEXTBUBBLE_H

#include "bubbleframe.h"
#include "global.h"
#include <QTextEdit>
class TextBubble : public BubbleFrame
{
public:
    TextBubble(MessageRole role, const QString& text, QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent *) override;

private:
    void setWidth(const QString& text);
    void resizeTextHeight();
    QTextEdit* _edit;
};

#endif // TEXTBUBBLE_H
