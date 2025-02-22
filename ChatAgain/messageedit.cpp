#include "messageedit.h"
#include <QDropEvent>
#include <QMimeData>

MessageEdit::MessageEdit(QWidget* parent)
	:QTextEdit(parent)
{

}

const QVector<MsgInfo> MessageEdit::getMsgList()
{
	// �����͵�����תΪ���ı���ͼƬ�ᱻ��Ϊռλ����ObjectReplacementCharacter
	QString send_content = this->toPlainText();
	QString text;// ������Ϣ������
	QVector<MsgInfo> list;
	for (auto& it : send_content) {
		int i = 0;// ͼƬ������
		if (it == QChar::ObjectReplacementCharacter) {		// ͼƬ��Ϣ
			if (!text.isEmpty())							// �ı��������ǿ�
				list.append({ "text", text, QPixmap() });	// �Ƚ��ı��ضϣ�ͼƬǰ����Ϣ��Ϊһ��������Ϣ��ͼƬ��Ϊһ����Ϣ��ͼƬ�������ѭ������
			text.clear();									// ������ֻ�����
			// ����ͼƬ��Ϣ
			list.append(_img_list[i++]);
		}
		else // ��ͼƬ����Ϊ�ı�
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
