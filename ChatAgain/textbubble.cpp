#include "textbubble.h"
#include <QTextLayout>
#include <QTextBlock>
TextBubble::TextBubble(MessageRole role, const QString &text, QWidget *parent)
    :BubbleFrame(role,parent)
{
    this->setStyleSheet("background: transparent; border: none");
    _edit = new QTextEdit;
    _edit->setReadOnly(true);
    QFont font("Microsoft YaHei");
    font.setPointSize(12);
    _edit->setFont(font);
    _edit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWidth(text);
    setWidget(_edit);
}

void TextBubble::paintEvent(QPaintEvent *e)
{
    resizeTextHeight();
    BubbleFrame::paintEvent(e);
}

void TextBubble::setWidth(const QString& text)
{
    _edit->setPlainText(text);
    qreal doc_margin = _edit->document()->documentMargin();
    int margin_left = this->layout()->contentsMargins().left();
    int margin_right = this->layout()->contentsMargins().right();
    QFontMetrics fm(_edit->font());
    QTextDocument* doc = _edit->document();
    int max_width = 0;
    for (QTextBlock it = doc->begin(); it != doc->end(); it = it.next())    //字体总长
    {
        int txtW = int(fm.horizontalAdvance(it.text()));
        max_width = max_width < txtW ? txtW : max_width;                 //找到最长的那段
    }
    this->setMaximumWidth(max_width + doc_margin * 2 + (margin_left + margin_right) + 2);        //设置最大宽度
}

void TextBubble::resizeTextHeight()
{
    qreal doc_margin = _edit->document()->documentMargin();    //字体到边框的距离默认为4
    QTextDocument *doc = _edit->document();
    qreal text_height = 0;
    //把每一段的高度相加=文本高
    for (QTextBlock it = doc->begin(); it != doc->end(); it = it.next())
    {
        QTextLayout *pLayout = it.layout();
        QRectF text_rect = pLayout->boundingRect();                             //这段的rect
        text_height += text_rect.height();
    }
    int vMargin = this->layout()->contentsMargins().top();
    //设置这个气泡需要的高度 文本高+文本边距+TextEdit边框到气泡边框的距离
    setFixedHeight(text_height + doc_margin *2 + vMargin*2 );
}
