#ifndef FINDRESDLG_H
#define FINDRESDLG_H

#include <QDialog>
#include <memory>
#include "requestaddfriendsdlg.h"

#include "userdata.h"

namespace Ui {
class FindResDlg;
}

class FindResDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FindResDlg(QWidget *parent = nullptr);
    ~FindResDlg();
    void setSearchInfo(std::shared_ptr<SearchInfo> si);
    void showDlg(bool success = true);
private slots:
    void on_notfound_btn_clicked();
    void on_addto_contracts_btn_clicked();


private:
    Ui::FindResDlg *ui;
    std::shared_ptr<SearchInfo> _si;
    QWidget* _parent;
    RequestAddFriendsDlg* _req_addfriend_dlg;
};



#endif // FINDRESDLG_H
