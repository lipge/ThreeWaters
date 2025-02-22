#include "friendlabel.h"
#include "ui_friendlabel.h"
#include <clickedlabel.h>

FriendLabel::FriendLabel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FriendLabel)
{
    ui->setupUi(this);
//    connect(ui->close_lab, &ClickedLabel::clicked, this, &FriendLabel::slot_close);
}

FriendLabel::~FriendLabel()
{
    delete ui;
}

void FriendLabel::setText(QString text)
{
    _text = text;
    ui->tip_lab->setText(_text);
    ui->tip_lab->adjustSize();

    QFontMetrics fontMetrics(ui->tip_lab->font()); // 获取QLabel控件的字体信息
//    auto textWidth = fontMetrics.QFontMetrics::horizontalAdvance(ui->tip_lab->text()); // 获取文本的宽度
    auto textHeight = fontMetrics.height(); // 获取文本的高度
    this->setFixedWidth(ui->tip_lab->width()+ui->close_btn->width()+5);
  //  this->setFixedHeight(textHeight+2);
    _width = this->width();
    _height = this->height();
}

int FriendLabel::Width()
{
    return _width;
}

int FriendLabel::Height()
{
    return _height;
}

QString FriendLabel::Text()
{
    return _text;
}

void FriendLabel::on_close_btn_clicked()
{
    this->close();
    emit sig_close(this);
}

