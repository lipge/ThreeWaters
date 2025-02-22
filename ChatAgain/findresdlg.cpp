#include "findresdlg.h"
#include "ui_findresdlg.h"
#include <QDir>

FindResDlg::FindResDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindResDlg)
{
    ui->setupUi(this);
    ui->notfound_btn->SetState("normal","hover","press");
    ui->addto_contracts_btn->SetState("normal","hover","press");

    // 设置窗口的尺寸策略
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

    QString app_path = QCoreApplication::applicationDirPath();
    QString head_shot_path = QDir::toNativeSeparators(app_path + QDir::separator() +
                                                      "static" + QDir::separator() + "head_1.jpg");

    QPixmap head_short(head_shot_path);
    head_short = head_short.scaled(ui->headshot_lab->size(), Qt::KeepAspectRatio , Qt::SmoothTransformation);
    ui->headshot_lab->setPixmap(head_short);

    _req_addfriend_dlg = new RequestAddFriendsDlg(this);
}
FindResDlg::~FindResDlg()
{
    delete ui;
}

void FindResDlg::on_notfound_btn_clicked() {
    // 设置页面的推荐尺寸
    ui->success_page->setFixedSize(260, 160);
    this->close();
}

void FindResDlg::on_addto_contracts_btn_clicked() {
//    ui->stack_wid->setCurrentWidget(ui->failed_page);
    // // 设置页面的推荐尺寸
    // ui->failed_page->setFixedSize(280, 186);
    // // 手动调整窗口大小
    // this->resize(ui->failed_page->size());

    _req_addfriend_dlg->show();

}

void FindResDlg::setSearchInfo(std::shared_ptr<SearchInfo> si)
{
    ui->name_lab->setText(si->_name);                                                       // 姓名
    if(si->_sex == 1)   ui->sex_lab->setPixmap(QPixmap(":/res/male.png"));                  // 性别
    else if(si->_sex == 0)  ui->sex_lab->setPixmap(QPixmap(":/res/female.png"));
    ui->desc_lab->setText(si->_desc);                                                       // 昵称
    _req_addfriend_dlg->setSearchInfo(si);
}

void FindResDlg::showDlg(bool success)
{
    if(!success){
        ui->stack_wid->setCurrentIndex(1);
    }
    else{
        ui->stack_wid->setCurrentIndex(0);
    }
    this->show();
}
