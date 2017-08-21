#ifndef HOSTSTOOL_H
#define HOSTSTOOL_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QSsl>
#include <QtNetwork/QSslConfiguration>
#include <QtNetwork/QSslSocket>
#include <QStandardPaths>
#include <QtGlobal>
#include <QFileDialog>

#ifdef Q_OS_WIN
    #include <windows.h>
#endif

namespace Ui {
class HostsTool;
}

class HostsTool : public QMainWindow
{
    Q_OBJECT
public:
    explicit HostsTool(QWidget *parent = NULL);
    ~HostsTool();
private slots:
    void readyread();
    void on_pushButton_start_clicked();
    void on_action_about_triggered();
    // void on_commandLinkButton_2_clicked();
    // void on_commandLinkButton_clicked();
    // void on_commandLinkButton_3_clicked();
    void on_action_backupHosts_triggered();
private:
    Ui::HostsTool *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString hosts_source;
    QString hosts_path;
    QString get;
};

#endif // HOSTSTOOL_H
