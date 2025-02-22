#ifndef REQUESTADDFRIENDSDLG_H
#define REQUESTADDFRIENDSDLG_H

#include <QDialog>
#include "userdata.h"
#include "clickedlabel.h"
namespace Ui {
class RequestAddFriendsDlg;
}

class RequestAddFriendsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RequestAddFriendsDlg(QWidget *parent = nullptr);
    ~RequestAddFriendsDlg();
    void initTips();
    void addTips();
    void setSearchInfo(std::shared_ptr<SearchInfo> si);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event) override;

public slots:
    void on_cancle_btn_clicked();
    void slot_addlabel(QString text);// 添加标签

private:
    Ui::RequestAddFriendsDlg *ui;
    QVector<QString> _tip_data;
    int _lab_x;
    //已经创建好的标签
    QMap<QString, ClickedLabel*> _add_labels;
    void resetLabels();
    std::shared_ptr<SearchInfo> _si;

private slots:
    void showWid(bool willshow);
    void on_confim_btn_clicked();
};

#endif // REQUESTADDFRIENDSDLG_H
