#ifndef CLICKBTN_H
#define CLICKBTN_H
#include <QPushButton>
class ClickBtn:public QPushButton
{
    Q_OBJECT
public:
    ClickBtn(QWidget* parent = nullptr);
    ClickBtn();
    ~ClickBtn();

    void SetState(QString normal,QString hover,QString press);

private:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    QString _normal;
    QString _hover;
    QString _press;
};

#endif // CLICKBTN_H
