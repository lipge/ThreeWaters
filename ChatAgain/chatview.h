#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>

namespace Ui {
class ChatView;
}

class ChatView : public QWidget
{
    Q_OBJECT

public:
    explicit ChatView(QWidget *parent = nullptr);
    ~ChatView();
    void appendChatItem(QWidget* item);
    void rmAllItem();
protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

private:
    Ui::ChatView *ui;
};

#endif // CHATVIEW_H
