#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include <QGraphicsSvgItem>
#include <QMediaPlaylist>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QPushButton>
#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QSvgWidget>
#include <QKeyEvent>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QDebug>

#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QCamera>

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QTimer>
#include <QImage>

#include <iostream>
#include <cmath>
#include "boardinfo.h"
#include "onlineplay.h"
using namespace std;
using namespace binfo;

#define MAX_TURN 1000
#define DIMENSION_X 8
#define DIMENSION_Y 8
#define SLOWRATE 5

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void reset();
    void set_dead(bool,short);
    void show_proute(int,int,bool,bool,bool,bool);
    void show_rroute(int,int,bool,bool,bool);
    void show_nroute(int,int,bool,bool,bool);
    void show_broute(int,int,bool,bool,bool);
    void show_qroute(int,int,bool,bool,bool);
    void show_kroute(int,int,bool,bool,bool,bool);
    void route_judge(bool);
    void animation(const int,const bool,const board_info,const board_info);
    void game_judge();
    void reset_route(bool);
    void debug();
    bool king_check();
    bool check_solved(const bool);
    ~MainWindow();

private slots:
    void assign_id_func();
    void set_piece();
    void updown();
    void game_start();
    void undo_set();
    void edit_set();

    void displayImage(int id,QImage image);
    void videoFrameCapture();
    void cerror();

signals:
    void piece_clicked();
    void route_clicked();



private:
    Ui::MainWindow *ui;
    QPushButton *start_ctrl,*undo,*edit_ctrl;
    QPalette button,text;
    QLabel *background,*logo,*game,*board_table,*red;//for img
    QLabel *checkerboard[8][8];//for block
    QLabel *dead_text[2],*player[2];
    QMediaPlayer *put_sound,*dead,*check_sound[2],*win_sound[2];
    QPixmap piece[2][7];
    QPixmap b_color[3];//0 for temp,1 for temp info,2for kill op
    QPixmap block_color[2];
    QPixmap logo_img;
    QPixmap game_img;
    board_info board[8][8],temp,t_info;//for play info
    record_info *game_record;
    pieces chess_pieces[2][16];

    QCamera *c;
    QCameraViewfinder *vf;
    QLabel *imgLabel;
    QCameraImageCapture*ic;
    QTimer * t;

    onlineplay *on;

    bool pturn;
    bool turn;
    bool start;
    bool edit;
    bool edit_move;
    bool done;
    bool up_down;
    int board_xpos[8];
    int board_ypos[8];
    int edit_xpos[8];
    int edit_ypos[4];
    int edit_group;
    int edit_chess;
    int dead_xpos[16];
    int dead_ypos[4];
    int dead_count[2];
    int slow_rate[6];
    int record_index;
    int updown_y;
    const int block_width,frame_width,edit_width,dead_width;

};

#endif // MAINWINDOW_H
