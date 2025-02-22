#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatdialog.h"
#include "tcpmgr.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	_login_dlg = new LoginDialog(this);//???


	// 使窗口没有系统默认的边框和标题栏，然后就能嵌入进窗口了
	_login_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	setCentralWidget(_login_dlg);
	_login_dlg->show();
	// 跳转注册界面
	connect(_login_dlg, &LoginDialog::SwitchRegister, this, &MainWindow::SlotSwitchRegister);
	// 登录界面忘记密码
	connect(_login_dlg, &LoginDialog::SwitchReset, this, &MainWindow::SlotSwitchReset);
	// 跳转聊天界面
	connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_switch_chatdlg, this, &MainWindow::SlotSwitchChat);
	//emit _login_dlg->SwitchChat();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::SlotSwitchRegister()
{
	// 初始化注册界面
	_reg_dlg = new RegisterDialog();
	_reg_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	setCentralWidget(_reg_dlg);
	_reg_dlg->show();

	// 新new的_reg_dlg需要重新连接回到登录界面的信号
	connect(_reg_dlg, &RegisterDialog::sigSwitchLogin, this, &MainWindow::SlotSwitchLogin);
}

// 返回登陆界面槽函数，需要重新连接忘记密码界面、注册界面
void MainWindow::SlotSwitchLogin()
{
	_login_dlg = new LoginDialog(this);
	_login_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	setCentralWidget(_login_dlg);
	_login_dlg->show();
	// 点击注册按钮
	connect(_login_dlg, &LoginDialog::SwitchRegister, this, &MainWindow::SlotSwitchRegister);
	// 点击忘记密码
	connect(_login_dlg, &LoginDialog::SwitchReset, this, &MainWindow::SlotSwitchReset);
}

void MainWindow::SlotSwitchReset()
{
	_reset_dlg = new ResetDialog(this);
	_reset_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	setCentralWidget(_reset_dlg);
	_reset_dlg->show();
	connect(_reset_dlg, &ResetDialog::switchLogin, this, &MainWindow::SlotSwitchLogin);
}

void MainWindow::SlotSwitchChat()
{
	qDebug() << "SlotSwitchChat";
	_chat_dlg = new ChatDialog();
	_chat_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	setCentralWidget(_chat_dlg);
	_chat_dlg->show();
	this->setMinimumSize(QSize(910, 640));
	this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}
