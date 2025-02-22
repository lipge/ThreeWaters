#include "logindialog.h"
#include "ui_logindialog.h"
#include "tcpmgr.h"
#include "httpmgr.h"
#include "loginfailed.h"

LoginDialog::LoginDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::LoginDialog)

{
	ui->setupUi(this);

	connect(ui->foget_lable, &ClickedLabel::clicked, this, &LoginDialog::SwitchReset);
	connect(ui->email_Edit, &QLineEdit::textEdited, this, [this] {setLoginBtnEnable(); });
	connect(ui->pass_Edit, &QLineEdit::textEdited, this, [this] {setLoginBtnEnable(); });

	initHttpHandlers();
	// 连接登陆回包信号
	connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish,
		this, &LoginDialog::slot_login_mod_finish);

	// 可以进行TCP连接信号
	connect(this, &LoginDialog::sig_connect_tcp, TcpMgr::GetInstance().get(), &TcpMgr::slot_tcp_connect);
	// TcpMgr连接完成信号
	connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_con_success, this, &LoginDialog::slot_tcp_con_finish);
	// 接收tcp界面转换信号发送
	//connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_switch_chatdlg, this, &LoginDialog::SwitchChat);


	// 设置忘记密码label样式
	ui->foget_lable->SetState();
	// 将登录按钮失效
	ui->login_Button->setEnabled(false);
	// 设置密码输入样式
	ui->pass_Edit->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
	qDebug() << "LoginDialog Dialog destroy";
	delete ui;
}

void LoginDialog::initHttpHandlers()
{
	_handlers.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj) {
		qDebug() << "登录请求回包";
		setLoginBtnEnable();                // 设置登录按钮状态
		int error = jsonObj["error"].toInt();
		if (error != ErrorCodes::SUCCESS) {
			QPoint center = this->mapToGlobal(this->rect().center());// 获取当前窗口的中心点
			if (error == LoginState::PasswdErr) {                      // 密码错误
				LoginFailed failed(LoginState::PasswdErr, center);
				connect(&failed, &LoginFailed::turn_forget, this, &LoginDialog::SwitchReset);
				failed.exec();
			}
			qDebug() << "对端网络错误 ErrorCodes:" << error;
			if (error == LoginState::RPCFailed) {                     // 网络错误
				LoginFailed failed(LoginState::RPCFailed, center);
				failed.exec();
			}
			return;
		}

		auto email = jsonObj["email"].toString();
		qDebug() << "Email: " << email;
		ServerInfo si;
		si.Uid = jsonObj["uid"].toInt();
		si.Host = jsonObj["host"].toString();
		si.Port = jsonObj["port"].toString();
		si.Token = jsonObj["token"].toString();
		qDebug() << "对方服务器toeken:" << si.Token;
		qDebug() << "用户Uid:" << si.Uid;
		_uid = si.Uid;
		_token = si.Token;
		// 可以建立tcp连接的信号
		emit sig_connect_tcp(si);
		});
}



bool LoginDialog::checkEmailValid()
{
	auto email = ui->email_Edit->text();                                // 获取输入的邮箱
	QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
	bool match = regex.match(email).hasMatch();                 //.hasMatch() 来检查是否有匹配成功。
	if (!match) {
		return false;
	}

	return true;
}

bool LoginDialog::checkPwdValid()
{
	auto pass = ui->pass_Edit->text();

	if (pass.length() < 6 || pass.length() > 15) {
		return false;
	}
	// 创建一个正则表达式对象，按照上述密码要求
	// ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
	QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*.]{6,15}$");
	bool match = regExp.match(pass).hasMatch();
	if (!match) {
		return false;;
	}
	return true;
}

bool LoginDialog::setLoginBtnEnable()
{
	// 为空的话使按钮失效
	if (ui->pass_Edit->text() == "" || ui->email_Edit->text() == "") {
		ui->login_Button->setEnabled(false);
		return false;
	}
	ui->login_Button->setEnabled(true);
	return true;
}


void LoginDialog::on_login_Button_clicked()
{
	// 获取当前窗口的中心点
	QPoint center = this->mapToGlobal(this->rect().center());
	LoginFailed failed(LoginState::PasswdErr, QPoint(center.x(), center.y()));
	connect(&failed, &LoginFailed::turn_forget, this, &LoginDialog::SwitchReset);

	// 初步检测，长度不对时触发
	if (checkEmailValid() == false || checkPwdValid() == false) {
		ui->pass_Edit->clear();
		setLoginBtnEnable();
		failed.exec();
		return;
	}

	auto email = ui->email_Edit->text();
	auto pwd = ui->pass_Edit->text();
	QJsonObject json_obj;
	json_obj["email"] = email;
	json_obj["passwd"] = xorString(pwd);

	ui->login_Button->setEnabled(false);
	HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/user_login"),
		json_obj, ReqId::ID_LOGIN_USER, Modules::LOGINMOD);
}

// PSOT请求处理完成且已经接收回包 触发这个函数
void LoginDialog::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err)
{
	// 1.不等于SUCCESS 只可能是POST失败，或者json解析出错。POST失败视为网络错误
	if (err != ErrorCodes::SUCCESS) {
		qDebug() << "Login Mod Failed";
		// 获取当前窗口的中心点
		QPoint center = this->mapToGlobal(this->rect().center());
		LoginFailed failed(LoginState::PostFailed, QPoint(center.x(), center.y()));
		failed.exec();
		setLoginBtnEnable();
		return;
	}

	// 2.网络没出错 处理回包，也就是json序列串，视为POST失败--本地解析失败或服务端设置字段发生错误
	QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
	if (jsonDoc.isNull() || !jsonDoc.isObject()) {
		qDebug() << "json解析错误";
		// 获取当前窗口的中心点
		QPoint center = this->mapToGlobal(this->rect().center());
		LoginFailed failed(LoginState::PostFailed, QPoint(center.x(), center.y()));
		failed.exec();
		setLoginBtnEnable();
		return;
	}

	// 3.进行到此，说明本地网络正常 调用对应的逻辑,根据id回调。
	_handlers[id](jsonDoc.object());
	return;
}

void LoginDialog::slot_tcp_con_finish(bool success)
{
	if (success) {

		QJsonObject jsonObj;
		jsonObj["uid"] = _uid;     // 用户id
		jsonObj["token"] = _token;  // 服务器token

		QJsonDocument doc(jsonObj);
		// 使用 Compact 而不是 Indented，减少传输数据量
		QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

		// 发送前最好做些检查
		if (jsonData.isEmpty()) {
			qWarning() << "Failed to create JSON data";
			return;
		}
		//发送tcp请求给chat server
		emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN, jsonData);
	}
	else {
		qDebug() << "连接TCP网络错误";
		QPoint center = this->mapToGlobal(this->rect().center());
		LoginFailed failed(LoginState::TCPFailed, center);
		failed.exec();
		setLoginBtnEnable();                // 设置登录按钮状态
	}
}

// 点击注册界面，给mainwindow界面发出信号
void LoginDialog::on_register_Button_clicked()
{
	emit SwitchRegister();
}

