#include "onlineplay.h"

onlineplay::onlineplay(QWidget *parent):QWidget(parent) {

    resize(500,220);

    Btn.setColor(QPalette::Button,QColor(60,60,60));
    Btn.setColor(QPalette::ButtonText,QColor(150,235,255));

    bg.load(":/img/src/ImageSet/background1.png");
    background = new QLabel(this);
    background->setGeometry(0,0,500,220);
    background->setPixmap(bg.scaled(500,220,Qt::KeepAspectRatioByExpanding));
    background->setAlignment(Qt::AlignCenter);
    background->show();

    hostBtn = new QPushButton(this);
    hostBtn->setGeometry(50,100,150,50);
    hostBtn->setText("HOST");
    hostBtn->setFont(QFont("Fantasy",20));
    hostBtn->setPalette(Btn);
    hostBtn->setAutoFillBackground(true);
    hostBtn->show();

    clientBtn = new QPushButton(this);
    clientBtn->setGeometry(300,100,150,50);
    clientBtn->setText("CLIENT");
    clientBtn->setFont(QFont("Fantasy",20));
    clientBtn->setPalette(Btn);
    clientBtn->setAutoFillBackground(true);
    clientBtn->show();

    /*clientBox->hide();
    hostBox->hide();
    sessionBox->hide();

    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);
    checkConnect = new QTimer(this);
    checkConnect->start(100);*/

    /*connect(hostBtn, SIGNAL(clicked()), this, SLOT(hostPart()));
    connect(clientBtn, SIGNAL(clicked()), this, SLOT(clientPart()));
    connect(hostBack, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(clientBack, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(clientStart, SIGNAL(clicked()), this, SLOT(prepareStart()));
    connect(sendBtn, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(backBtn, SIGNAL(clicked()),this, SLOT(backToMenu()));*/
}

void onlineplay::hostPart()
{
    tcpServer->listen();
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
    status->setText("IP : \n");

    foreach(QHostAddress i, ipList){
        if(i.toIPv4Address())  status->setText(status->text() + i.toString() + '\n');
    }

    status->setText(status->text() + "\nport : " + QString::number(tcpServer->serverPort()) + '\n');

    /*startBox->hide();
    hostBox->show();*/
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(prepareStart()));
    character = "host";
}

void onlineplay::clientPart()
{
    /*startBox->hide();
    clientBox->show();*/
    ipEdit->setFocus();
    character = "client";
}


void onlineplay::backToMenu()
{
    /*startBox->show();
    clientBox->hide();
    sessionBox->hide();
    hostBox->hide();*/
    if(character == "host"){
        tcpServer->close();
        disconnect(tcpServer);
    }

}

void onlineplay::prepareStart()
{
    if(character == "client"){
        if(ipEdit->text().isEmpty() || portEdit->text().isEmpty()) return;

        host = ipEdit->text();
        port = portEdit->text().toInt();

        tcpSocket->connectToHost(host,port);
        connect(checkConnect, SIGNAL(timeout()), this, SLOT(connectSuccess()));
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));

    }
    else if(character == "host"){
        //hostBox->hide();
        //sessionBox->show();
        delete tcpSocket;
        tcpSocket = tcpServer->nextPendingConnection();
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    }
}

void onlineplay::readMessage()
{
    QDataStream in(tcpSocket);

    in.startTransaction();
    if(!in.commitTransaction()){
        return;
    }
    QString data;
    in>>data;
    qDebug()<<data;

    receiveMsg->setText(receiveMsg->toPlainText() + '\n' + data);
}

void onlineplay::sendMessage()
{
    QByteArray byte;
    QDataStream stream(&byte, QIODevice::WriteOnly);


    stream<<sendMsg->text();
    sendMsg->clear();
    sendMsg->setFocus();
    tcpSocket->write(byte);
}

void onlineplay::connectSuccess()
{
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        //sessionBox->show();
        //clientBox->hide();

        disconnect(checkConnect);
    }
}

void onlineplay::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        //if(sessionBox->isEnabled())
            sendMessage();
    }
}

