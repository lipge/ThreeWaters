#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QLabel>
#include "global.h"

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget* parent);
//    ClickedLabel(QWidget* parent,QString text);
    ~ClickedLabel();
    void SetState();
    void SetState(QString normal,QString hover, QString press);
    void SetState(QString normal,QString selected,QString normal_hover,QString select_hover);
    ClickLbState GetState();
private:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
    ClickLbState GetCurState();
    ClickLbState _state;
    QPixmap _normal_pix;
    QPixmap _selected_pix;
    QPixmap _normal_hover_pix;
    QPixmap _selected_hover_pix;
    bool _need_selected;
signals:
    void clicked();
};

#endif // CLICKEDLABEL_H
