#ifndef ONLINEPLAY_H
#define ONLINEPLAY_H
#include "boardinfo.h"
#include <QWidget>

#include <QDialog>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QList>
#include <QLabel>
#include <QTextBrowser>
#include <QKeyEvent>
#include <QPixmap>

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QTimer>

using namespace binfo;


class onlineplay : public QWidget
{
    Q_OBJECT
public:
    onlineplay(QWidget *parent=nullptr);

public:
    QLineEdit *ipEdit;
    QLineEdit *portEdit;

private:
    QPalette Btn;
    QPushButton *hostBtn;
    QPushButton *clientBtn;
    QPushButton *clientBack;
    QPushButton *clientStart;
    QPushButton *hostBack;
    QPushButton *backBtn;
    QPushButton *sendBtn;
    QLabel *status;
    QLabel *background;
    QPixmap bg;
    QTextBrowser *receiveMsg;
    QLineEdit *sendMsg;
    QString host;
    quint16 port;

    /*QGroupBox *hostBox;
    QGroupBox *startBox;
    QGroupBox *clientBox;
    QGroupBox *sessionBox;*/

    QString character;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QTcpSocket *receive;
    QTimer *checkConnect;

private slots:
    void hostPart();
    void clientPart();
    void backToMenu();
    void prepareStart();
    void readMessage();
    void sendMessage();
    void connectSuccess();

    virtual void keyPressEvent(QKeyEvent *event);

};

#endif // BOARD_H
