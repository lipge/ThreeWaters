#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"
#include "clickedlabel.h"
#include <QRandomGenerator>
RegisterDialog::RegisterDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::RegisterDialog)
	, _timer_cnt(5)
{
	ui->setupUi(this);

	// 注册回调函数
	initHttpHandlers();

	// 检测输入是否合理逻辑
	connect(ui->usr_Edit, &QLineEdit::editingFinished, this, [this]() {
		checkUserValid();
		});
	connect(ui->email_Edit, &QLineEdit::editingFinished, this, [this]() {
		checkEmailValid();
		});
	connect(ui->pass_Edit, &QLineEdit::editingFinished, this, [this]() {
		checkPassValid();
		});
	connect(ui->confirm_Edit, &QLineEdit::editingFinished, this, [this]() {
		checkConfirmValid();
		});
	connect(ui->code_Edit, &QLineEdit::editingFinished, this, [this]() {
		checkVarifyValid();
		});

	// 点击右侧label，设置密码是否可见
	connect(ui->pass_visable, &ClickedLabel::clicked, this, [this]() {
		if (ui->pass_visable->GetState() == ClickLbState::Selected)
			ui->pass_Edit->setEchoMode(QLineEdit::Normal);
		else
			ui->pass_Edit->setEchoMode(QLineEdit::Password);
		});
	connect(ui->confirm_visable, &ClickedLabel::clicked, this, [this]() {
		if (ui->confirm_visable->GetState() == ClickLbState::Selected)
			ui->confirm_Edit->setEchoMode(QLineEdit::Normal);
		else
			ui->confirm_Edit->setEchoMode(QLineEdit::Password);
		});

	// 实现按钮点击不同状态效果初始化
	ui->pass_visable->SetState(":/res/visible.png", ":/res/unvisible.png",
		":/res/visible_hover.png", ":/res/unvisible_hover.png");
	ui->confirm_visable->SetState(":/res/visible.png", ":/res/unvisible.png",
		":/res/visible_hover.png", ":/res/unvisible_hover.png");
	// 定时器初始化
	_return_timer = new QTimer(this);

	// 设置默认状态
	ui->pass_Edit->setEchoMode(QLineEdit::Password);
	ui->confirm_Edit->setEchoMode(QLineEdit::Password);
	ui->err_tip->setProperty("state", "normal");
	repolish(ui->err_tip);
	ui->err_tip->clear();

	// 注册返回登陆界面逻辑，计时器结束自动返回登录界面
	connect(_return_timer, &QTimer::timeout, this, [this] {
		if (_timer_cnt == 0) {
			_return_timer->stop();
			emit sigSwitchLogin();
		}
		_timer_cnt--;
		ui->tip_regsuc->setText(QString("注册成功，%1秒后返回...").arg(_timer_cnt));
		});

	// 连接注册完成逻辑
	connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);
	// 获取验证码按钮继承自QPushButton，显式连接一下点击信号
	connect(ui->getButton, &QPushButton::clicked, this, &RegisterDialog::on_getButton_clicked);
}

RegisterDialog::~RegisterDialog()
{
	delete ui;
	qDebug() << "Register Dialog destroy";
}

void RegisterDialog::showTip(QString str, bool b_ok)
{
	if (!b_ok) {
		ui->err_tip->setProperty("state", "err");
	}
	else {
		ui->err_tip->setProperty("state", "success");
	}
	ui->err_tip->setText(str);
	// 刷新qss
	repolish(ui->err_tip);
}

// 注册回调函数，但函数运行在此进行
void RegisterDialog::initHttpHandlers()
{
	// 注册获取验证码回包的逻辑
	_handlers[ReqId::ID_GET_VARIFY_CODE] = [this](const QJsonObject& jsonobj) {
		int error = jsonobj["error"].toInt();
		if (error != ErrorCodes::SUCCESS) {
			showTip(tr("参数错误"), false);
			return;
		}

		auto email = jsonobj["email"].toString();
		showTip(tr("验证码已发送。"), true);
		};
	// 注册注册用户回包逻辑
	_handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj) {
		int error = jsonObj["error"].toInt();
		if (error != ErrorCodes::SUCCESS) {
			showTip("参数错误", false);
			return;
		}
		auto email = jsonObj["email"].toString();
		showTip(tr("注册成功"), true);
		changePage();
		});
}

void RegisterDialog::changePage()
{
	ui->stackedWidget->setCurrentWidget(ui->page_2);
	_return_timer->start(1000);
}


// 获取验证码按钮点击逻辑
void RegisterDialog::on_getButton_clicked()
{
	auto email = ui->email_Edit->text();                                // 获取输入的邮箱
	QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
	bool match = regex.match(email).hasMatch();							//.hasMatch() 来检查是否匹配成功
	if (!match) {
		showTip(tr("邮箱地址格式错误或不支持"), false);					// 打印提示信息
		return;
	}

	// 发送验证码
	QJsonObject json_obj;
	json_obj["email"] = email;
	qDebug() << QUrl(gate_url_prefix + "/get_varifycode");
	HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/get_varifycode"),
		json_obj, ReqId::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);
}

// http对网关请求 发送过来的经解析过的回包
void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes ec)
{
	if (ec != ErrorCodes::SUCCESS) {
		showTip(tr("网络请求错误"), false);
		return;
	}
	// json解析失败 解析 res->QByteArray QByteArray->QjsonDocument
	QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
	if (jsonDoc.isNull()) {
		showTip(tr("json解析失败"), false);
		return;
	}
	if (!jsonDoc.isObject()) {
		showTip(tr("json解析错误"), false);
		return;
	}
	// 成功的话根据id执行相应的回调
	_handlers[id](jsonDoc.object());
	return;
}

// 注册确认按钮点击
void RegisterDialog::on_confirm_btn_clicked()
{
	if (ui->usr_Edit->text() == "") {
		showTip(tr("用户名不能为空"), false);
		return;
	}
	if (ui->email_Edit->text() == "") {
		showTip(tr("邮箱不能为空"), false);
		return;
	}
	if (ui->pass_Edit->text() == "") {
		showTip(tr("密码不能为空"), false);
		return;
	}
	if (ui->confirm_Edit->text() == "") {
		showTip(tr("确认密码不能为空"), false);
		return;
	}
	if (ui->confirm_Edit->text() != ui->pass_Edit->text()) {
		showTip(tr("密码和确认密码不匹配"), false);
		return;
	}
	if (ui->code_Edit->text() == "") {
		showTip(tr("验证码不能为空"), false);
		return;
	}
	int index = QRandomGenerator::global()->bounded(6);
	// 发送http请求注册用户
	QJsonObject json_obj;
	json_obj["user"] = ui->usr_Edit->text();
	json_obj["email"] = ui->email_Edit->text();
	json_obj["icon"] = heads[index];			// 注册时使用随机头像
	json_obj["passwd"] = xorString(ui->pass_Edit->text());
	json_obj["confirm"] = xorString(ui->confirm_Edit->text());
	json_obj["varifycode"] = ui->code_Edit->text();
	HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/user_register"), json_obj, ReqId::ID_REG_USER, Modules::REGISTERMOD);
}

// 添加错误信息到Qmap
void RegisterDialog::AddTipErr(TipErr te, QString tips)
{
	_tip_errs[te] = tips;
	showTip(tips, false);
}

void RegisterDialog::DelTipErr(TipErr te)
{
	_tip_errs.remove(te);
	if (_tip_errs.empty()) {
		ui->err_tip->clear();
		return;
	}
	// 随便展示一条
	showTip(_tip_errs.first(), false);
}
bool RegisterDialog::checkUserValid()
{
	if (ui->usr_Edit->text() == "") {
		AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
		return false;
	}
	DelTipErr(TipErr::TIP_USER_ERR);
	return true;
}

bool RegisterDialog::checkEmailValid()
{
	auto email = ui->email_Edit->text();                                // 获取输入的邮箱
	QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
	bool match = regex.match(email).hasMatch();                 //.hasMatch() 来检查是否有匹配成功。
	if (!match) {

		AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址格式错误或不支持"));
		return false;
	}
	DelTipErr(TipErr::TIP_EMAIL_ERR);
	return true;
}

bool RegisterDialog::checkPassValid()
{
	auto pass = ui->pass_Edit->text();

	if (pass.length() < 6 || pass.length() > 15) {
		//提示长度不准确
		AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
		return false;
	}
	// 创建一个正则表达式对象，按照上述密码要求
	// ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
	QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*.]{6,15}$");
	bool match = regExp.match(pass).hasMatch();
	if (!match) {
		//提示字符非法
		AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
		return false;;
	}

	DelTipErr(TipErr::TIP_PWD_ERR);

	return true;
}

bool RegisterDialog::checkConfirmValid()
{
	if (ui->confirm_Edit->text() != ui->pass_Edit->text()) {
		AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("密码和确认密码不匹配！"));
		return false;
	}
	DelTipErr(TipErr::TIP_CONFIRM_ERR);
	return true;

}

bool RegisterDialog::checkVarifyValid()
{
	if (ui->code_Edit->text() == "") {
		AddTipErr(TipErr::TIP_VARIFY_ERR, tr("验证码不能为空"));
		return false;
	}
	DelTipErr(TipErr::TIP_VARIFY_ERR);
	return true;

}


void RegisterDialog::on_return_btn_clicked()
{
	_return_timer->stop();
	emit sigSwitchLogin();
    this->close();
}


void RegisterDialog::on_cancel_btn_clicked()
{
	_return_timer->stop();
	emit sigSwitchLogin();
    this->close();
}

