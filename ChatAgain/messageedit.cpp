#include "messageedit.h"
#include <QDropEvent>
#include <QMimeData>

MessageEdit::MessageEdit(QWidget* parent)
	:QTextEdit(parent)
{

}

const QVector<MsgInfo> MessageEdit::getMsgList()
{
	// 将发送的内容转为纯文本，图片会被视为占位符：ObjectReplacementCharacter
	QString send_content = this->toPlainText();
	QString text;// 文字消息缓冲区
	QVector<MsgInfo> list;
	for (auto& it : send_content) {
		int i = 0;// 图片的索引
		if (it == QChar::ObjectReplacementCharacter) {		// 图片消息
			if (!text.isEmpty())							// 文本缓冲区非空
				list.append({ "text", text, QPixmap() });	// 先将文本截断，图片前的信息视为一条单独消息、图片视为一条消息。图片后的内容循环处理
			text.clear();									// 清空文字缓冲区
			// 插入图片信息
			list.append(_img_list[i++]);
		}
		else // 非图片，视为文本
			text.append(it);
	}
	if (!text.isEmpty()) {
		list.append({ "text", text, QPixmap() });
	}
	_img_list.clear();
	return list;
}

void MessageEdit::dropEvent(QDropEvent* e)
{
	QList<QUrl> urlList = e->mimeData()->urls();
	for (const QUrl& url : urlList) {

		QString file = url.toString().split("///").at(1);
		QImage image(file);
		if (image.width() > 120 || image.height() > 80)
		{
			if (image.width() > image.height())
			{
				image = image.scaledToWidth(120, Qt::SmoothTransformation);
			}
			else
				image = image.scaledToHeight(80, Qt::SmoothTransformation);
		}
		_img_list.append({ "image",file,QPixmap::fromImage(image) });
		QTextCursor cursor = this->textCursor();
		cursor.insertImage(image, file);
	}

	e->accept();
}
