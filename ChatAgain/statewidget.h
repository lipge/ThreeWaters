#ifndef STATEWIDGET_H
#define STATEWIDGET_H
#include <QWidget>

class StateWidget:public QWidget
{
    Q_OBJECT
public:
    StateWidget(QWidget* parent = nullptr);
    void setPixmap(const QString& normal, const QString& hover, const QString& press);
    void clearState();  // 设置为默认状态
    void setSelected(); // 设置为选中状态
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void enterEvent(QEnterEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
    QPixmap _normal;
    QPixmap _hover;
    QPixmap _press;
    QPixmap _current;
    bool _is_selected;
signals:
    void clicked();
};

#endif // STATEWIDGET_H
