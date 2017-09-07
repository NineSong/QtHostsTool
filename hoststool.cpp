#include "hoststool.h"
#include "ui_hoststool.h"
//#include <qdebug.h>

HostsTool::HostsTool(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::HostsTool)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    ui->textEdit->append(">>Initialization success!");

#ifdef Q_OS_WIN
    wchar_t buffer[1024];
    GetSystemDirectory(buffer, 1024);
    hosts_path = QString::fromWCharArray(buffer) + "/drivers/etc/hosts";
#else
    hosts_path = "/etc/hosts";
#endif
}

HostsTool::~HostsTool()
{
    delete ui;
}

void HostsTool::on_pushButton_start_clicked()
{
    hosts_source = ui->comboBox->currentText();
    ui->textEdit->append("<p style=\"color:green\">>>开始配置hosts</p>");
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_2);
    QNetworkRequest request;
    request.setSslConfiguration(config);
    request.setUrl(QUrl(hosts_source));
//    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.2; rv:16.0) Gecko/20100101 Firefox/16.0");
    reply = manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(readyread()));
}

void HostsTool::readyread()
{
    if (reply->error() == QNetworkReply::NoError)
    {
        get = QString::fromUtf8(reply->readAll());
        ui->textEdit->append("<p style=\"color:green\">>>服务器获取hosts成功,请保证网络通畅</p>");
        ui->textEdit->append(get);
        ui->textEdit->append(">>从<a href=\"" + hosts_source + "\">" + hosts_source + "</a>获取hosts成功！");
        QFile file(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/hosts.txt");
        file.open(QIODevice::WriteOnly | QFile::Text);

        if (file.isOpen())
        {
            QTextStream stream(&file);
            stream << get;
            file.close();
            ui->textEdit->append("<p style=\"color:green\">>>你可以尝试复制上面的内容到C:\\Windows\\System32\\drivers\\etc\\hosts文件中,或者使用桌面生成的hosts文件(请重命名hosts.txt为hosts再进行覆盖)</p>");
        }
        else
        {
            ui->textEdit->append("<p style=\"color:red\">>>未知错误:尝试打开新创建的文件失败!</p>");
            file.close();
        }
    }
    else
        ui->textEdit->append("<body style=\" font-family;'微软雅黑\'; font-size:10pt; font-weight:72; font-style:normal;\"><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ff0000;\">&gt;&gt;从服务器获取hosts失败，请执行：</span></p><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">·打开网络连接</span></p><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">·检查hosts源是否存在</span></p><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">·更换hosts源</span></p></body>");
}

void HostsTool::on_action_about_triggered()
{
    QMessageBox::about(this, "About", "Copyright © 2014-2015  racal, All Rights Reserved");
}

void HostsTool::on_action_backupHosts_triggered()
{
    QFileDialog dialog(this, "备份hosts");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.selectFile("hosts");

    if (dialog.exec())
    {
        QString path = dialog.selectedFiles().first();

        if (QFile::copy(hosts_path, path))
            QMessageBox::information(this, "", "备份成功！");
        else
            QMessageBox::information(this, "", "备份失败！");
    }
}
