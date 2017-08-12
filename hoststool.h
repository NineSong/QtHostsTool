#ifndef HOSTSTOOL_H
#define HOSTSTOOL_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qssl.h>
#include <QtNetwork/qsslconfiguration.h>
#include <QtNetwork/qsslsocket.h>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QtGlobal>
#include <QFileDialog>

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
    QString get;
};

#endif // HOSTSTOOL_H
