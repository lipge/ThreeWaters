#include "mainwindow.h"
#include "global.h"
#include <QApplication>
#include <QFile>
#include <QStyleFactory>
#include "findresdlg.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	// 加载qss
	QFile qss(":/style/stylesheet.qss");
	if (!qss.open(QFile::ReadOnly)) {
		qDebug("Open failed");
		return 0;
	}
	// 加载qss成功
	QString style = QLatin1String(qss.readAll());
	a.setStyleSheet(style);
	qss.close();

	// 读取当前路径下的配置文件"config.ini"
	QString fileName = "config.ini";                                                        // 配置文件名
	QString app_path = QCoreApplication::applicationDirPath();                              // 用于获取当前应用程序的目录路径
	qDebug() << "AppPath:" << app_path;
	QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + fileName);// 配置文件路径
	qDebug() << "ConfigPath:" << config_path;
	QSettings settings(config_path, QSettings::IniFormat);                                   // 读取配置文件
	QString gate_host = settings.value("GateServer/host").toString();
	QString gate_port = settings.value("GateServer/port").toString();
	qDebug() << "GateHost:" << gate_host << "\nGatePort:" << gate_port;
	// http请求前缀
	gate_url_prefix = "http://" + gate_host + ":" + gate_port;

	MainWindow w;
	w.show();
	return a.exec();
}
